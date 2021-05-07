#include "sakura/Memory.hpp"

using namespace Sakura::HuC6280::Mapping;

Controller::Controller() = default;

auto Controller::load(uint16_t logical_address) -> uint8_t {
  // TODO: implement address mapping and physical address ranges
  return m_RAM[logical_address];
}

void Controller::store(uint16_t logical_address, uint8_t value) {
  // TODO: implement address mapping and physical address ranges
  m_RAM[logical_address] = value;
}
