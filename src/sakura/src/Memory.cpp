#include "sakura/Memory.hpp"
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
  // TODO: implement address mapping and physical address ranges
  return m_RAM[logical_address];
}

void Controller::store(uint16_t logical_address, uint8_t value) {
  // TODO: implement address mapping and physical address ranges
  m_RAM[logical_address] = value;
}
