#include "Interrupt.hpp"
#include <fmt/core.h>
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
        ->critical(fmt::format(
            "Unhandled HuC6280 interrupt load with offset: {:#06x}", offset));
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
        ->critical(fmt::format("Unhandled HuC6280 interrupt write "
                               "with offset: {:#06x}, value {:#04x}",
                               offset, value));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}

void Controller::request_interrupt(RequestField field) {
  m_request.value |= field;
}

auto Controller::priority_request() const -> RequestField {
  if (m_request.timer_interrupt_request) {
    return RequestField::TIMER;
  }
  if (m_request.interrupt_request_1) {
    return RequestField::IRQ1;
  }
  if (m_request.interrupt_request_2) {
    return RequestField::IRQ2;
  }
  return RequestField::None;
}
