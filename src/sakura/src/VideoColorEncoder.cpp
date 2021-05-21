#include "VideoColorEncoder.hpp"
#include <common/Formatter.hpp>
#include <spdlog/spdlog.h>

using namespace Sakura::HuC6260;

auto Controller::load(uint16_t offset) const -> uint8_t {
  (void)offset;
  (void)m_color_table_address;
  return 0xFF;
}

void Controller::store(uint16_t offset, uint8_t value) {
  switch (offset & 0b111) {
  case 0b000:
    m_control = value;
    break;
  case 0b010:
    m_color_table_address.low = value;
    break;
  case 0b011:
    m_color_table_address.high = value;
    break;
  case 0b100:
    m_color_table_data_write.low = value;
    break;
  case 0b101:
    m_color_table_data_write.high = value;
    break;
  default:
    spdlog::get(LOGGER_NAME)
        ->critical(Common::Formatter::format(
            "Unhandled HuC6260 store with offset: %04x, value: %02x", offset,
            value));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
}
