#include "Interrupt.hpp"
#include <common/Formatter.hpp>
#include <spdlog/spdlog.h>

using namespace Sakura::HuC6280::Interrupt;

auto Controller::load(uint16_t offset) const -> uint8_t {
  switch (offset & 0b11) {
  case 0b10:
    return m_disable.value;
  case 0b11:
    return m_request.value;
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(Common::Formatter::format(
            "Unhandled HuC6280 interrupt load with offset: %04x", offset));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}

void Controller::store(uint16_t offset, uint8_t value) {
  switch (offset & 0b11) {
  case 0b10:
    m_disable.value = (value & 0b111);
    return;
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(
            Common::Formatter::format("Unhandled HuC6280 interrupt write "
                                      "with offset: %04x, value %02x",
                                      offset, value));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}
