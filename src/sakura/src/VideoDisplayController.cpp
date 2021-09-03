#include "VideoDisplayController.hpp"
#include "Interrupt.hpp"
#include "VideoColorEncoder.hpp"
#include "sakura/Emulator.hpp"
#include <bitset>
#include <cmath>
#include <fmt/core.h>
#include <functional>
#include <spdlog/spdlog.h>

using namespace Sakura::HuC6270;

const uint32_t G_HIGH_SPEED_CYCLES_PER_SECOND = 21477270;
const double G_FRAME_RATE = 60.0;
const uint32_t G_CYCLES_PER_FRAME =
    ceil((float)G_HIGH_SPEED_CYCLES_PER_SECOND / G_FRAME_RATE);

Controller::Controller(
    Sakura::VDCConfig config,
    std::unique_ptr<HuC6280::Interrupt::Controller> &interrupt_controller,
    std::unique_ptr<HuC6260::Controller> &video_color_encoder_controller)
    : m_VRAM(), m_cycles(), m_interrupt_controller(interrupt_controller),
      m_video_color_encoder_controller(video_color_encoder_controller),
      m_state(std::make_unique<ControllerState>()), m_vsync_callback(nullptr) {
  if (config.deadbeef_vram) {
    m_VRAM.fill(0xDEAD);
  }
}

auto REGISTER_SYMBOL_FOR_ADDRESS(uint8_t address) -> std::string {
  switch (address) {
  case 0b00000:
    return "MAWR";
  case 0b00001:
    return "MARR";
  case 0b00010:
    return "VWR";
  case 0b00011:
    return "RESERVED";
  case 0b00100:
    return "RESERVED";
  case 0b00101:
    return "CR";
  case 0b00110:
    return "RCR";
  case 0b00111:
    return "BXR";
  case 0b01000:
    return "BYR";
  case 0b01001:
    return "MWR";
  case 0b01010:
    return "HSR";
  case 0b01011:
    return "HDR";
  case 0b01100:
    return "VPR";
  case 0b01101:
    return "VDW";
  case 0b01110:
    return "VCR";
  case 0b01111:
    return "DCR";
  case 0b10000:
    return "SOUR";
  case 0b10001:
    return "DESR";
  case 0b10010:
    return "LENR";
  case 0b10011:
    return "DVSSR";
  default:
    return "";
  }
}

void Controller::store_register(bool low, uint8_t value) {
  switch (m_address.address) {
  case 0b00101:
    if (low) {
      m_control.low = value;
    } else {
      m_control.high = value;
    }
    break;
  case 0b00110:
    if (low) {
      m_scanning_line_detection.low = value;
    } else {
      m_scanning_line_detection.high = value;
    }
    break;
  case 0b00111:
    if (low) {
      m_background_x_scroll.low = value;
    } else {
      m_background_x_scroll.high = value;
    }
    break;
  case 0b01000:
    if (low) {
      m_background_y_scroll.low = value;
    } else {
      m_background_y_scroll.high = value;
    }
    break;
  case 0b01001:
    if (low) {
      m_memory_access_width.low = value;
    } else {
      m_memory_access_width.high = value;
    }
    break;
  case 0b01010:
    if (low) {
      m_horizontal_sync.low = value;
    } else {
      m_horizontal_sync.high = value;
    }
    break;
  case 0b01011:
    if (low) {
      m_horizontal_display.low = value;
    } else {
      m_horizontal_display.high = value;
    }
    break;
  case 0b01100:
    if (low) {
      m_vertical_sync.low = value;
    } else {
      m_vertical_sync.high = value;
    }
    break;
  case 0b01101:
    if (low) {
      m_vertical_display.low = value;
    } else {
      m_vertical_display.high = value;
    }
    break;
  case 0b01110:
    if (low) {
      m_vertical_display_end_position.low = value;
    } else {
      m_vertical_display_end_position.high = value;
    }
    break;
  case 0b01111:
    if (low) {
      m_block_transfer_control.low = value;
    } else {
      m_block_transfer_control.high = value;
    }
    break;
  case 0b10011:
    if (low) {
      m_block_transfer_source_address_vram_satb.low = value;
    } else {
      m_block_transfer_source_address_vram_satb.high = value;
    }
    break;
  case 0b00000:
    if (low) {
      m_memory_address_write.low = value;
    } else {
      m_memory_address_write.high = value;
    }
    break;
  case 0b00010:
    if (low) {
      m_vram_data_write.low = value;
    } else {
      m_vram_data_write.high = value;
      store_vram();
    }
    break;
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format("Unhandled HuC6270 {} register store",
                               REGISTER_SYMBOL_FOR_ADDRESS(m_address.address)));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}

auto Controller::load_vram(uint16_t address) -> uint16_t {
  return m_VRAM[address];
}

void Controller::store_vram() {
  m_VRAM[m_memory_address_write.value] = m_vram_data_write.value;
  m_memory_address_write.value++;
}

auto Controller::load(uint16_t offset) const -> uint8_t {
  switch (offset & 0b11) {
  case 0b00:
    m_state->mark_dirty();
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[L] [{:^7}] [xx]: {:#04x}", "SR", m_status.value));
    return m_status.value;
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(
            fmt::format("Unhandled HuC6270 load with offset: {:#06x}", offset));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}

void Controller::store(uint16_t offset, uint8_t value) {
  switch (offset & 0b11) {
  case 0b00:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [xx]: {:#04x}", "AR", value));
    m_address.value = value;
    break;
  case 0b10:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [ll]: {:#04x}",
                           REGISTER_SYMBOL_FOR_ADDRESS(m_address.address),
                           value));
    store_register(true, value);
    break;
  case 0b11:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [hh]: {:#04x}",
                           REGISTER_SYMBOL_FOR_ADDRESS(m_address.address),
                           value));
    store_register(false, value);
    break;
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format(
            "Unhandled HuC6270 store with offset: {:#06x}, value: {:#04x}",
            offset, value));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}

void Controller::step(uint8_t cycles) {
  if (m_state->is_dirty()) {
    uint8_t busy = m_status.busy;
    m_status.value = 0x0;
    m_status.busy = busy;
    m_state->clear_dirty();
    m_interrupt_controller->acknowledge_interrupt(
        HuC6280::Interrupt::RequestField::IRQ1);
  }
  m_cycles += cycles;
  if (m_cycles >= G_CYCLES_PER_FRAME) {
    m_cycles = 0;
    if ((m_control.interrupt_request_enable &
         InterruptRequestField::VerticalBlankingPeriodDetect) != 0) {
      m_interrupt_controller->request_interrupt(
          HuC6280::Interrupt::RequestField::IRQ1);
      m_status.vertical_blanking_period = 1;
    }
    if (m_vsync_callback != nullptr) {
      m_vsync_callback();
    }
  }
}

void Controller::set_vsync_callback(std::function<void()> vsync_callback) {
  m_vsync_callback = std::move(vsync_callback);
}

auto Controller::get_background_character_data(Character character)
    -> std::array<float, CHARACTER_DATA_LENGTH> {
  std::array<float, CHARACTER_DATA_LENGTH> character_data = {};
  uint16_t address = character.code;
  address <<= 4;
  std::array<uint16_t, BACKGROUND_CHARACTER_GENERATOR_WORDS_LENGTH>
      character_generator_data = {};
  for (unsigned int i = 0; i < BACKGROUND_CHARACTER_GENERATOR_WORDS_LENGTH;
       i++) {
    character_generator_data[i] = load_vram(address + i);
  }

  for (unsigned int i = 0; i < CHARACTER_DOTS_HEIGHT; i++) {
    uint16_t ch1_ch0 = character_generator_data[i];
    uint8_t ch0_data = ch1_ch0 & 0x00FF;
    auto ch0 = std::bitset<8>(ch0_data);
    uint8_t ch1_data = (ch1_ch0 & 0xFF00) >> 8;
    auto ch1 = std::bitset<8>(ch1_data);
    uint16_t ch3_ch2 = character_generator_data[i + 8];
    uint8_t ch2_data = ch3_ch2 & 0x00FF;
    auto ch2 = std::bitset<8>(ch2_data);
    uint8_t ch3_data = (ch3_ch2 & 0xFF00) >> 8;
    auto ch3 = std::bitset<8>(ch3_data);
    std::array<std::bitset<8>, 4> chs = {ch0, ch1, ch2, ch3};
    for (int j = (CHARACTER_DOTS_WIDTH - 1); j >= 0; j--) {
      auto color_data = std::bitset<4>(0);
      for (std::array<std::bitset<8>, 4>::size_type k = 0; k < chs.size();
           k++) {
        if (chs[k].test(j)) {
          color_data.set(k);
        }
      }
      uint8_t pattern_color = color_data.to_ulong();
      // We reverse the iteration index because the data is displayed
      // left-to-right
      unsigned int reversed_iteration_index = CHARACTER_DOTS_WIDTH - 1 - j;
      unsigned int character_data_index =
          (reversed_iteration_index + i * CHARACTER_DOTS_HEIGHT) * 3;
      auto color = m_video_color_encoder_controller->get_color_data(
          0, character.cg_color, pattern_color);
      character_data[character_data_index] = color[0];
      character_data[character_data_index + 1] = color[1];
      character_data[character_data_index + 2] = color[2];
    }
  }

  return character_data;
}

auto Controller::get_background_attribute_table_data()
    -> std::array<float, BACKGROUND_ATTRIBUTE_TABLE_DATA_LENGTH> {
  std::array<float, BACKGROUND_ATTRIBUTE_TABLE_DATA_LENGTH> background_data =
      {};
  for (unsigned int y = 0; y < BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_ROWS; y++) {
    for (unsigned int x = 0;
         x < BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS_PER_ROW; x++) {
      unsigned int address =
          x + y * BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS_PER_ROW;
      uint16_t data = load_vram(address);
      auto character = Character(data);
      auto character_data = get_background_character_data(character);
      for (unsigned int y_char = 0; y_char < CHARACTER_DOTS_HEIGHT; y_char++) {
        for (unsigned int x_char = 0; x_char < CHARACTER_DOTS_WIDTH; x_char++) {
          unsigned int source_index =
              (x_char + y_char * CHARACTER_DOTS_HEIGHT) * 3;
          unsigned int destination_index =
              (x_char + (x * CHARACTER_DOTS_WIDTH)) * 3 +
              (y_char + (y * CHARACTER_DOTS_HEIGHT)) * CHARACTER_DOTS_HEIGHT *
                  BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS_PER_ROW * 3;
          background_data[destination_index] = character_data[source_index];
          background_data[destination_index + 1] =
              character_data[source_index + 1];
          background_data[destination_index + 2] =
              character_data[source_index + 2];
        }
      }
    }
  }
  return background_data;
}

auto Controller::get_character_data(unsigned int index)
    -> std::array<float, CHARACTER_DATA_LENGTH> {
  std::array<float, CHARACTER_DATA_LENGTH> character_data = {};
  uint16_t address = (index * 16) + 0x400;
  std::array<uint16_t, BACKGROUND_CHARACTER_GENERATOR_WORDS_LENGTH>
      character_generator_data = {};
  for (unsigned int i = 0; i < BACKGROUND_CHARACTER_GENERATOR_WORDS_LENGTH;
       i++) {
    character_generator_data[i] = load_vram(address + i);
  }

  for (unsigned int i = 0; i < CHARACTER_DOTS_HEIGHT; i++) {
    uint16_t ch1_ch0 = character_generator_data[i];
    uint8_t ch0_data = ch1_ch0 & 0x00FF;
    auto ch0 = std::bitset<8>(ch0_data);
    uint8_t ch1_data = (ch1_ch0 & 0xFF00) >> 8;
    auto ch1 = std::bitset<8>(ch1_data);
    uint16_t ch3_ch2 = character_generator_data[i + 8];
    uint8_t ch2_data = ch3_ch2 & 0x00FF;
    auto ch2 = std::bitset<8>(ch2_data);
    uint8_t ch3_data = (ch3_ch2 & 0xFF00) >> 8;
    auto ch3 = std::bitset<8>(ch3_data);
    std::array<std::bitset<8>, 4> chs = {ch0, ch1, ch2, ch3};
    for (int j = (CHARACTER_DOTS_WIDTH - 1); j >= 0; j--) {
      auto color_data = std::bitset<4>(0);
      for (std::array<std::bitset<8>, 4>::size_type k = 0; k < chs.size();
           k++) {
        if (chs[k].test(j)) {
          color_data.set(k);
        }
      }
      uint8_t pattern_color = color_data.to_ulong();
      // We reverse the iteration index because the data is displayed
      // left-to-right
      unsigned int reversed_iteration_index = CHARACTER_DOTS_WIDTH - 1 - j;
      unsigned int character_data_index =
          (reversed_iteration_index + i * CHARACTER_DOTS_HEIGHT) * 3;
      auto color =
          m_video_color_encoder_controller->get_color_data(0, 0, pattern_color);
      character_data[character_data_index] = color[0];
      character_data[character_data_index + 1] = color[1];
      character_data[character_data_index + 2] = color[2];
    }
  }

  return character_data;
}

auto Controller::get_character_generator_data()
    -> std::array<float, CHARACTER_GENERATOR_DATA_LENGTH> {
  std::array<float, CHARACTER_GENERATOR_DATA_LENGTH> character_generator_data =
      {};
  for (unsigned int y = 0; y < CHARACTER_GENERATOR_NUMBER_OF_ROWS; y++) {
    for (unsigned int x = 0;
         x < CHARACTER_GENERATOR_NUMBER_OF_CHARACTERS_PER_ROW; x++) {
      unsigned int index =
          x + y * CHARACTER_GENERATOR_NUMBER_OF_CHARACTERS_PER_ROW;
      auto character_data = get_character_data(index);
      for (unsigned int y_char = 0; y_char < CHARACTER_DOTS_HEIGHT; y_char++) {
        for (unsigned int x_char = 0; x_char < CHARACTER_DOTS_WIDTH; x_char++) {
          unsigned int source_index =
              (x_char + y_char * CHARACTER_DOTS_HEIGHT) * 3;
          unsigned int destination_index =
              (x_char + (x * CHARACTER_DOTS_WIDTH)) * 3 +
              (y_char + (y * CHARACTER_DOTS_HEIGHT)) * CHARACTER_DOTS_HEIGHT *
                  CHARACTER_GENERATOR_NUMBER_OF_CHARACTERS_PER_ROW * 3;
          character_generator_data[destination_index] =
              character_data[source_index];
          character_generator_data[destination_index + 1] =
              character_data[source_index + 1];
          character_generator_data[destination_index + 2] =
              character_data[source_index + 2];
        }
      }
    }
  }
  return character_generator_data;
}
