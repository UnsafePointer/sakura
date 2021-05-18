#ifndef SAKURA_VIDEO_COLOR_ENCODER
#define SAKURA_VIDEO_COLOR_ENCODER

#include <cstdint>

namespace Sakura::HuC6260 {

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
    uint16_t r : 3;
    uint16_t g : 3;
    uint16_t b : 3;
    uint16_t unused : 7;
  };
  uint16_t value;

  ColorTableDataWrite() : value() {}
};

class Controller {
  ColorTableAddress m_color_table_address;
  ColorTableDataWrite m_color_table_data_write;
  uint8_t m_control;

public:
  Controller() = default;
  ~Controller() = default;

  [[nodiscard]] auto load(uint16_t offset) const -> uint8_t;
  void store(uint16_t offset, uint8_t value);
};
}; // namespace Sakura::HuC6260

#endif