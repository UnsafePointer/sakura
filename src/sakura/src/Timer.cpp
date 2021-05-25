#include "Timer.hpp"
#include "Interrupt.hpp"
#include <fmt/core.h>
#include <spdlog/spdlog.h>

using namespace Sakura::HuC6280::Timer;

Controller::Controller(
    std::unique_ptr<Interrupt::Controller> &interrupt_controller)
    : m_total_cycles(), m_downcounter(),
      m_interrupt_controller(interrupt_controller) {}

auto Controller::load(uint16_t offset) const -> uint8_t {
  (void)m_control;
  switch (offset & 0b1) {
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format(
            "Unhandled HuC6280 timer load with offset: {:#06x}", offset));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}

void Controller::store(uint16_t offset, uint8_t value) {
  (void)m_control;
  switch (offset & 0b1) {
  case 0b0:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [xx]: {:#04x}", "RELOAD", value));
    m_reload.value = value;
    break;
  case 0b1:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [xx]: {:#04x}", "CONTROL", value));
    m_control.value = value;
    if (m_control.start_stop) {
      m_downcounter = m_reload.value + 1;
    }
    break;
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format("Unhandled HuC6280 timer store with offset: "
                               "{:#06x}, value: {:#04x}",
                               offset, value));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}

void Controller::step(uint8_t cycles) {
  if (m_control.start_stop == 0) {
    return;
  }
  int count = cycles;
  while (count >= 0) {
    count--;
    m_total_cycles++;
    if (m_total_cycles >= 0x3FF) {
      m_total_cycles = 0;
      m_downcounter--;
      if ((m_downcounter & 0x80000000) != 0U) {
        m_interrupt_controller->request_interrupt(
            Interrupt::RequestField::TIMER);
        m_downcounter = m_reload.value + 1;
      }
    }
  }
}
