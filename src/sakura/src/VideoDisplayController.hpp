#ifndef SAKURA_VIDEO_DISPLAY_CONTROLLER_HPP
#define SAKURA_VIDEO_DISPLAY_CONTROLLER_HPP

#include <cstdint>
#include <string>

namespace Sakura::HuC6270 {

static const std::string LOGGER_NAME = "--huc6270--";

union Address {
  struct {
    uint8_t address : 5;
    uint8_t unused : 3;
  };
  uint8_t value;

  Address() : value() {}
};

union Status {
  struct {
    uint8_t collision : 1;
    uint8_t over : 1;
    uint8_t scanning_line : 1;
    uint8_t block_transfer_vram_stab_end : 1;
    uint8_t block_transfer_vram_vram_end : 1;
    uint8_t vertical_blanking_period : 1;
    uint8_t busy : 1;
    uint8_t unused : 1;
  };
  uint8_t value;

  Status() : value() {}
};

union Control {
  struct {
    uint16_t interrupt_request_enable : 4;
    uint16_t external_sync : 2;
    uint16_t sprite_blanking : 1;
    uint16_t background_blanking : 1;
    uint16_t disp_output_select : 2;
    uint16_t dynamic_ram_refresh : 1;
    uint16_t memory_address_read_write_register_increment_select : 2;
    uint16_t unused : 3;
  };
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  Control() : value() {}
};

union ScanningLineDetection {
  struct {
    uint16_t rcr : 10;
    uint16_t unused : 6;
  };
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  ScanningLineDetection() : value() {}
};

class Controller {
private:
  Address m_address;
  Status m_status;
  Control m_control;
  ScanningLineDetection m_scanning_line_detection;

  void store_register(bool low, uint8_t value);

public:
  Controller() = default;
  ~Controller() = default;

  [[nodiscard]] auto load(uint16_t offset) const -> uint8_t;
  void store(uint16_t offset, uint8_t value);
};
}; // namespace Sakura::HuC6270

#endif
