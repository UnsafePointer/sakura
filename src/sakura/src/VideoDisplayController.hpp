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

union BackgroundXScroll {
  struct {
    uint16_t bxr : 10;
    uint16_t unused : 6;
  };
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  BackgroundXScroll() : value() {}
};

union BackgroundYScroll {
  struct {
    uint16_t byr : 9;
    uint16_t unused : 7;
  };
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  BackgroundYScroll() : value() {}
};

union MemoryAccessWidth {
  struct {
    uint16_t vram_access_width_mode : 2;
    uint16_t sprite_access_width_mode : 2;
    uint16_t screen : 3;
    uint16_t cg_mode : 1;
    uint16_t unused : 8;
  };
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  MemoryAccessWidth() : value() {}
};

union HorizontalSync {
  struct {
    uint16_t horizontal_sync_pulse_width : 5;
    uint16_t unused : 3;
    uint16_t horizontal_display_start_position : 7;
    uint16_t unused_2 : 1;
  };
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  HorizontalSync() : value() {}
};

union HorizontalDisplay {
  struct {
    uint16_t horizontal_display_width : 7;
    uint16_t unused : 1;
    uint16_t horizontal_display_end_position : 7;
    uint16_t unused_2 : 1;
  };
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  HorizontalDisplay() : value() {}
};

union VerticalSync {
  struct {
    uint16_t vertical_sync_pulse_width : 5;
    uint16_t unused : 3;
    uint16_t vertical_display_start_position : 8;
  };
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  VerticalSync() : value() {}
};

union VerticalDisplay {
  struct {
    uint16_t vertical_display_width : 9;
    uint16_t unused : 7;
  };
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  VerticalDisplay() : value() {}
};

union VerticalDisplayEndPosition {
  struct {
    uint16_t vertical_display_end_position : 8;
    uint16_t unused : 8;
  };
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  VerticalDisplayEndPosition() : value() {}
};

union BlockTransferControl {
  struct {
    uint16_t vram_satb_transfer_complete_interrupt_request_enable : 1;
    uint16_t vram_vram_transfer_complete_interrupt_request_enable : 1;
    uint16_t source_address_inc_dec : 1;
    uint16_t destination_address_inc_dec : 1;
    uint16_t vram_satb_transfer_auto_repeat : 1;
    uint16_t unused : 11;
  };
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  BlockTransferControl() : value() {}
};

union BlockTransferSourceAddressVRAMSATB {
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  BlockTransferSourceAddressVRAMSATB() : value() {}
};

class Controller {
private:
  Address m_address;
  Status m_status;
  Control m_control;
  ScanningLineDetection m_scanning_line_detection;
  BackgroundXScroll m_background_x_scroll;
  BackgroundYScroll m_background_y_scroll;
  MemoryAccessWidth m_memory_access_width;
  HorizontalSync m_horizontal_sync;
  HorizontalDisplay m_horizontal_display;
  VerticalSync m_vertical_sync;
  VerticalDisplay m_vertical_display;
  VerticalDisplayEndPosition m_vertical_display_end_position;
  BlockTransferControl m_block_transfer_control;
  BlockTransferSourceAddressVRAMSATB m_block_transfer_source_address_vram_satb;

  void store_register(bool low, uint8_t value);

public:
  Controller() = default;
  ~Controller() = default;

  [[nodiscard]] auto load(uint16_t offset) const -> uint8_t;
  void store(uint16_t offset, uint8_t value);
};
}; // namespace Sakura::HuC6270

#endif
