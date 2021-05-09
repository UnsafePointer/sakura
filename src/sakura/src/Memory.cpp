#include "Memory.hpp"
#include <fstream>
#include <iostream>

using namespace Sakura::HuC6280::Mapping;

Controller::Controller() = default;

void Controller::initialize() { m_registers.mapping_register_7 = 0x0; }

void Controller::load_rom(const std::filesystem::path &path) {
  std::ifstream rom_file = std::ifstream();
  rom_file.open(path, std::ios::binary | std::ios::ate);
  if (!rom_file.is_open()) {
    std::cout << "Unable to open ROM at path " << path.string() << std::endl;
  }
  std::streampos file_size = rom_file.tellg();
  std::cout << "Opened ROM file of size: " << std::hex << file_size
            << std::endl;

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
    std::cout << "Accessing unused memory map range: 0x80-0xF7" << std::endl;
    return 0xFF;
  }
  if (bank >= 0xF8 && bank <= 0xFB) {
    // pages 0xF9-0xFB mirror page 0xF8 so here we take the offset instead of
    // the physicall address
    return m_RAM[offset];
  }
  if (bank >= 0xFC && bank <= 0xFE) {
    std::cout << "Accessing unused memory map range: 0xFC-0xFE" << std::endl;
    return 0xFF;
  } // bank == 0xFF
  std::cout << "Unhandled hardware page access at physical address: "
            << std::hex << physical_address << std::endl;
  exit(1); // NOLINT(concurrency-mt-unsafe)
}

void Controller::store(uint16_t logical_address, uint8_t value) {
  uint8_t register_index = logical_address >> 13;
  uint8_t bank = m_registers.values[register_index];
  uint32_t mask = bank << 13;
  uint32_t offset = logical_address & 0x1FFF;
  uint32_t physical_address = mask | offset;

  if (bank <= 0x7F) {
    std::cout << "Attempting to write ROM" << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  } else if (bank >= 0x80 && bank <= 0xF7) {
    std::cout << "Attempting to write unused memory map range: 0x80-0xF7"
              << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  } else if (bank >= 0xF8 && bank <= 0xFB) {
    // pages 0xF9-0xFB mirror page 0xF8 so here we take the offset instead of
    // the physicall address
    m_RAM[offset] = value;
  } else if (bank >= 0xFC && bank <= 0xFE) {
    std::cout << "Attempting to write unused memory map range: 0xFC-0xFE"
              << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  } else {   // bank == 0xFF
    std::cout << "Unhandled hardware page access at physical address: "
              << std::hex << physical_address << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}
