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

auto Controller::get_color_table_data()
    -> std::array<float, COLOR_TABLE_RAM_DATA_LENGTH> {
  std::array<float, COLOR_TABLE_RAM_DATA_LENGTH> color_data = {};
  unsigned int i = 0;
  for (auto const &entry : m_color_table_RAM) {
    color_data[i] = entry.r / 7.0F;
    color_data[i + 1] = entry.g / 7.0F;
    color_data[i + 2] = entry.b / 7.0F;
    i += 3;
  }
  return color_data;
}

auto Controller::get_color_data(uint16_t background, uint16_t color_area,
                                uint16_t pattern_color)
    -> std::array<float, 3> {
  uint16_t address = ((background & 0b1) << 8);
  address |= ((color_area & 0b1111) << 3);
  address |= (pattern_color & 0b1111);
  auto entry = m_color_table_RAM[address];
  return {entry.r / 7.0F, entry.g / 7.0F, entry.b / 7.0F};
}
