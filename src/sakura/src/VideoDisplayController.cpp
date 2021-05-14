#include "VideoDisplayController.hpp"
#include <common/Formatter.hpp>
#include <iostream>

using namespace Sakura::HuC6270;

auto Controller::load(uint16_t offset) const -> uint8_t {
  switch (offset & 0b11) {
  case 0b00:
    return m_status.value;
  default:
    std::cout << Common::Formatter::format(
                     "Unhandled HuC6270 load with offset: %04x", offset)
              << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}

void Controller::store(uint16_t offset, uint8_t value) {
  switch (offset & 0b11) {
  case 0b00:
    m_address.value = value;
    break;
  case 0b10:
    std::cout
        << Common::Formatter::format(
               "Unhandled HuC6270 store (0b10) with selected address: %02x, "
               "value: %02x",
               m_address, value)
        << std::endl;
    break;
  case 0b11:
    std::cout
        << Common::Formatter::format(
               "Unhandled HuC6270 store (0b11) with selected address: %02x, "
               "value: %02x",
               m_address, value)
        << std::endl;
    break;
  default:
    std::cout << Common::Formatter::format(
                     "Unhandled HuC6270 store with offset: %04x, value: %02x",
                     offset, value)
              << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}
