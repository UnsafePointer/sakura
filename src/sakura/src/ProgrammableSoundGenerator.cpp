#include "ProgrammableSoundGenerator.hpp"
#include <spdlog/spdlog.h>

using namespace Sakura::HuC6280::ProgrammableSoundGenerator;

auto Controller::load(uint16_t offset) const -> uint8_t {
  switch (offset & 0b1111) {
  case 0b0000:
    return m_channel_select.value;
  case 0b0001:
    return m_main_amplitude_level_adjustment.value;
  case 0b0010:
  case 0b0011:
  case 0b0100:
  case 0b0101:
  case 0b0110:
  case 0b0111:
    spdlog::get(LOGGER_NAME)
        ->warn(fmt::format(
            "Unimplemented HuC6280 PSG load with offset: {:#06x}", offset));
    return 0xFF;
  case 0b1000:
    return m_low_frequency_oscillator_frequency;
  case 0b1001:
    return m_low_frequency_oscillator_control.value;
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format(
            "Unhandled HuC6280 PSG load with offset: {:#06x}", offset));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}

void Controller::store(uint16_t offset, uint8_t value) {
  switch (offset & 0b1111) {
  case 0b0000:
    m_channel_select.value = value;
    break;
  case 0b0001:
    m_main_amplitude_level_adjustment.value = value;
    break;
  case 0b0010:
  case 0b0011:
  case 0b0100:
  case 0b0101:
  case 0b0110:
  case 0b0111:
    spdlog::get(LOGGER_NAME)
        ->warn(fmt::format("Unimplemented HuC6280 PSG store "
                           "with offset: {:#06x}, value: {:#04x}",
                           offset, value));
    break;
  case 0b1000:
    m_low_frequency_oscillator_frequency = value;
    break;
  case 0b1001:
    m_low_frequency_oscillator_control.value = value;
    break;
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format(
            "Unhandled HuC6280 PSG store with offset: {:#06x}, value: {:#04x}",
            offset, value));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}
