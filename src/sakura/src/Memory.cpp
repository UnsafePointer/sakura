#include "Memory.hpp"
#include "IO.hpp"
#include "Interrupt.hpp"
#include "ProgrammableSoundGenerator.hpp"
#include "VideoColorEncoder.hpp"
#include "VideoDisplayController.hpp"
#include <fmt/core.h>
#include <fstream>
#include <spdlog/spdlog.h>

using namespace Sakura::HuC6280::Mapping;

Controller::Controller()
    : m_RAM(), m_ROM(), m_IO_controller(std::make_unique<IO::Controller>()),
      m_video_display_controller(std::make_unique<HuC6270::Controller>()),
      m_programmable_sound_generator_controller(
          std::make_unique<ProgrammableSoundGenerator::Controller>()),
      m_video_color_encoder_controller(std::make_unique<HuC6260::Controller>()),
      m_interrupt_controller(
          std::make_unique<HuC6280::Interrupt::Controller>()){};

Controller::~Controller() = default;

void Controller::initialize() { m_registers.mapping_register_7 = 0x0; }

void Controller::load_rom(const std::filesystem::path &path) {
  std::ifstream rom_file = std::ifstream();
  rom_file.open(path, std::ios::binary | std::ios::ate);
  if (!rom_file.is_open()) {
    spdlog::get(LOGGER_NAME)
        ->critical(
            fmt::format("Unable to open ROM at path {:s}", path.c_str()));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  std::streampos file_size = rom_file.tellg();
  spdlog::get(LOGGER_NAME)
      ->debug(fmt::format("Opened ROM file of size: {:#X}", file_size));

  rom_file.seekg(0, std::ifstream::beg);
  rom_file.read(reinterpret_cast<char *>(&m_ROM[0]), file_size);
  rom_file.close();
}

auto Controller::load(uint16_t logical_address) -> uint8_t {
  uint8_t register_index = logical_address >> 13;
  uint8_t bank = m_registers.values[register_index];
  uint32_t mask = bank << 13;
  uint32_t offset = logical_address & 0x1FFF;
  uint32_t physical_address = mask | offset;

  if (bank <= 0x7F) {
    return m_ROM[physical_address];
  }
  if (bank >= 0x80 && bank <= 0xF7) {
    spdlog::get(LOGGER_NAME)
        ->info("Accessing unused memory map range: 0x80-0xF7");
    return 0xFF;
  }
  if (bank >= 0xF8 && bank <= 0xFB) {
    // pages 0xF9-0xFB mirror page 0xF8 so here we take the offset instead of
    // the physicall address
    return m_RAM[offset];
  }
  if (bank >= 0xFC && bank <= 0xFE) {
    spdlog::get(LOGGER_NAME)
        ->info("Accessing unused memory map range: 0xFC-0xFE");
    return 0xFF;
  } // bank == 0xFF

  if (IO_RANGE.contains(physical_address)) {
    return m_IO_controller->load();
  }
  auto offset_hw = VIDEO_DISPLAY_CONTROLLER_RANGE.contains(physical_address);
  if (offset_hw) {
    return m_video_display_controller->load(*offset_hw);
  }
  offset_hw = VIDEO_COLOR_ENCODER_RANGE.contains(physical_address);
  if (offset_hw) {
    return m_video_color_encoder_controller->load(*offset_hw);
  }
  offset_hw = PROGRAMMABLE_SOUND_GENERATOR_RANGE.contains(physical_address);
  if (offset_hw) {
    return m_programmable_sound_generator_controller->load(*offset_hw);
  }
  offset_hw = INTERRUPT_RANGE.contains(physical_address);
  if (offset_hw) {
    return m_interrupt_controller->load(*offset_hw);
  }

  spdlog::get(LOGGER_NAME)
      ->critical(fmt::format(
          "Unhandled hardware page access at physical address: {:#10x}",
          physical_address));
  exit(1); // NOLINT(concurrency-mt-unsafe)
}

void Controller::store(uint16_t logical_address, uint8_t value) {
  uint8_t register_index = logical_address >> 13;
  uint8_t bank = m_registers.values[register_index];
  uint32_t mask = bank << 13;
  uint32_t offset = logical_address & 0x1FFF;
  uint32_t physical_address = mask | offset;

  if (bank <= 0x7F) {
    spdlog::get(LOGGER_NAME)->critical("Attempting to write ROM");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  } else if (bank >= 0x80 && bank <= 0xF7) {
    spdlog::get(LOGGER_NAME)
        ->critical("Attempting to write unused memory map range: 0x80-0xF7");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  } else if (bank >= 0xF8 && bank <= 0xFB) {
    // pages 0xF9-0xFB mirror page 0xF8 so here we take the offset instead of
    // the physicall address
    m_RAM[offset] = value;
  } else if (bank >= 0xFC && bank <= 0xFE) {
    spdlog::get(LOGGER_NAME)
        ->critical("Attempting to write unused memory map range: 0xFC-0xFE");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  } else {   // bank == 0xFF
    if (IO_RANGE.contains(physical_address)) {
      m_IO_controller->store(value);
      return;
    }
    auto offset_hw = VIDEO_DISPLAY_CONTROLLER_RANGE.contains(physical_address);
    if (offset_hw) {
      m_video_display_controller->store(*offset_hw, value);
      return;
    }
    offset_hw = VIDEO_COLOR_ENCODER_RANGE.contains(physical_address);
    if (offset_hw) {
      m_video_color_encoder_controller->store(*offset_hw, value);
      return;
    }
    offset_hw = PROGRAMMABLE_SOUND_GENERATOR_RANGE.contains(physical_address);
    if (offset_hw) {
      m_programmable_sound_generator_controller->store(*offset_hw, value);
      return;
    }
    offset_hw = INTERRUPT_RANGE.contains(physical_address);
    if (offset_hw) {
      m_interrupt_controller->store(*offset_hw, value);
      return;
    }

    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format(
            "Unhandled hardware page access at physical address: {:#10x}",
            physical_address));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}

void Controller::store_video_display_controller(uint32_t physical_address,
                                                uint8_t value) {
  auto offset_hw = VIDEO_DISPLAY_CONTROLLER_RANGE.contains(physical_address);
  if (!offset_hw) {
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format(
            "Physical address: {:#10x} doesn't belong to HuC6270 VDC",
            physical_address));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  m_video_display_controller->store(*offset_hw, value);
}

void Controller::set_mapping_register(uint8_t index, uint8_t value) {
  m_registers.values[index] = value;
}

auto Controller::mapping_register(uint8_t index) -> uint8_t {
  return m_registers.values[index];
}
