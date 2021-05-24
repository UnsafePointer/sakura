#include "VideoColorEncoder.hpp"
#include <fmt/core.h>
#include <spdlog/spdlog.h>

using namespace Sakura::HuC6260;

void Controller::store_color_table_ram() {
  auto entry = ColorTableEntry(m_color_table_data_write.value);
  m_color_table_RAM[m_color_table_address.cta] = entry;
  m_color_table_address.value++;
}

auto Controller::load(uint16_t offset) const -> uint8_t {
  (void)m_control;
  switch (offset) {
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(
            fmt::format("Unhandled HuC6260 load with offset: {:#06x}", offset));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}

void Controller::store(uint16_t offset, uint8_t value) {
  switch (offset & 0b111) {
  case 0b000:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [ll]: {:#04x}", "CR", value));
    m_control = value;
    break;
  case 0b010:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [ll]: {:#04x}", "CTA", value));
    m_color_table_address.low = value;
    break;
  case 0b011:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [hh]: {:#04x}", "CTA", value));
    m_color_table_address.high = value;
    break;
  case 0b100:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [ll]: {:#04x}", "CTW", value));
    m_color_table_data_write.low = value;
    break;
  case 0b101:
    spdlog::get(LOGGER_NAME)
        ->info(fmt::format("[S] [{:^7}] [hh]: {:#04x}", "CTW", value));
    m_color_table_data_write.high = value;
    store_color_table_ram();
    break;
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format(
            "Unhandled HuC6260 store with offset: {:#06x}, value: {:#04x}",
            offset, value));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}
