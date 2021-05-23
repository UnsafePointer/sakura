#include "VideoDisplayController.hpp"
#include <fmt/core.h>
#include <spdlog/spdlog.h>

using namespace Sakura::HuC6270;

auto REGISTER_SYMBOL_FOR_ADDRESS(uint8_t address) -> std::string {
  switch (address) {
  case 0b00000:
    return "MAWR";
  case 0b00001:
    return "MARR";
  case 0b00010:
    return "VWR";
  case 0b00011:
    return "RESERVED";
  case 0b00100:
    return "RESERVED";
  case 0b00101:
    return "CR";
  case 0b00110:
    return "RCR";
  case 0b00111:
    return "BXR";
  case 0b01000:
    return "BYR";
  case 0b01001:
    return "MWR";
  case 0b01010:
    return "HSR";
  case 0b01011:
    return "HDR";
  case 0b01100:
    return "VPR";
  case 0b01101:
    return "VDW";
  case 0b01110:
    return "VCR";
  case 0b01111:
    return "DCR";
  case 0b10000:
    return "SOUR";
  case 0b10001:
    return "DESR";
  case 0b10010:
    return "LENR";
  case 0b10011:
    return "DVSSR";
  default:
    return "";
  }
}

auto Controller::load(uint16_t offset) const -> uint8_t {
  switch (offset & 0b11) {
  case 0b00:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[L] [{:^7}] [xx]: {:#04x}", "SR", m_status.value));
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
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [xx]: {:#04x}", "AR", value));
    m_address.value = value;
    break;
  case 0b10:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [ll]: {:#04x}",
                           REGISTER_SYMBOL_FOR_ADDRESS(m_address.address),
                           value));
    break;
  case 0b11:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [hh]: {:#04x}",
                           REGISTER_SYMBOL_FOR_ADDRESS(m_address.address),
                           value));
    break;
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format(
            "Unhandled HuC6270 store with offset: {:#06x}, value: {:#04x}",
            offset, value));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}
