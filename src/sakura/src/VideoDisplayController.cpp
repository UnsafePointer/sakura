#include "VideoDisplayController.hpp"
#include <fmt/core.h>
#include <spdlog/spdlog.h>

using namespace Sakura::HuC6270;

auto Controller::load(uint16_t offset) const -> uint8_t {
  switch (offset & 0b11) {
  case 0b00:
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
    m_address.value = value;
    break;
  case 0b10:
    spdlog::get(LOGGER_NAME)
        ->warn(fmt::format(
            "Unhandled HuC6270 store (0b10) with selected address: {:#04x}, "
            "value: {:#04x}",
            m_address.value, value));
    break;
  case 0b11:
    spdlog::get(LOGGER_NAME)
        ->warn(fmt::format(
            "Unhandled HuC6270 store (0b11) with selected address: {:#04x}, "
            "value: {:#04x}",
            m_address.value, value));
    break;
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format(
            "Unhandled HuC6270 store with offset: {:#06x}, value: {:#04x}",
            offset, value));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}
