#ifndef SAKURA_VIDEO_COLOR_ENCODER
#define SAKURA_VIDEO_COLOR_ENCODER

#include <array>
#include <cstdint>
#include <sakura/Constants.hpp>
#include <string>

namespace Sakura::HuC6260 {

static const std::string LOGGER_NAME = "--huc6260--";

union ColorTableAddress {
  struct {
    uint8_t low : 8;
    uint8_t high : 8;
  };
  struct {
    uint16_t cta : 9;
    uint16_t unused : 7;
  };
  uint16_t value;

  ColorTableAddress() : value() {}
};

union ColorTableDataWrite {
  struct {
    uint8_t low : 8;
    uint8_t high : 8;
  };
  struct {
    uint16_t b : 3;
    uint16_t r : 3;
    uint16_t g : 3;
    uint16_t unused : 7;
  };
  uint16_t value;

  ColorTableDataWrite() : value() {}
};

union ColorTableEntry {
  struct {
    uint16_t b : 3;
    uint16_t r : 3;
    uint16_t g : 3;
    uint16_t unused : 7;
  };
  uint16_t value;

  ColorTableEntry() : value() {}
  ColorTableEntry(uint16_t value) : value(value) {}
};

class Controller {
  std::array<ColorTableEntry, COLOR_TABLE_RAM_NUMBER_OF_COLORS>
      m_color_table_RAM;

  ColorTableAddress m_color_table_address;
  ColorTableDataWrite m_color_table_data_write;
  uint8_t m_control;

  void store_color_table_ram();

public:
  Controller() = default;
  ~Controller() = default;

  [[nodiscard]] auto load(uint16_t offset) const -> uint8_t;
  void store(uint16_t offset, uint8_t value);

  auto get_color_table_data() -> std::array<float, COLOR_TABLE_RAM_DATA_LENGTH>;
  auto get_color_data(uint16_t background, uint16_t color_area,
                      uint16_t pattern_color) -> std::array<float, 3>;
};
}; // namespace Sakura::HuC6260

#endif
