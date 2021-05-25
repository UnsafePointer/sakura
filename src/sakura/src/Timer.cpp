#include "Timer.hpp"
#include <fmt/core.h>
#include <spdlog/spdlog.h>

using namespace Sakura::HuC6280::Timer;

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
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format("Unhandled HuC6280 timer store with offset: "
                               "{:#06x}, value: {:#04x}",
                               offset, value));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}
