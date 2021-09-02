#ifndef SAKURA_VIDEO_DISPLAY_CONTROLLER_HPP
#define SAKURA_VIDEO_DISPLAY_CONTROLLER_HPP

#include <array>
#include <cstdint>
#include <functional>
#include <memory>
#include <sakura/Constants.hpp>
#include <string>

namespace Sakura {
struct VDCConfig;

namespace HuC6280::Interrupt {
class Controller;
} // namespace HuC6280::Interrupt

namespace HuC6260 {
class Controller;
} // namespace HuC6260

namespace HuC6270 {
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

enum InterruptRequestField : uint8_t {
  None = 0,
  CollisionDetect = 1 << 0,
  OverDetect = 1 << 1,
  ScanningLineDetect = 1 << 2,
  VerticalBlankingPeriodDetect = 1 << 3,
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

union MemoryAddressWrite {
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  MemoryAddressWrite() : value() {}
};

union VRAMDataWrite {
  struct {
    uint16_t low : 8;
    uint16_t high : 8;
  };
  uint16_t value;

  VRAMDataWrite() : value() {}
};

class ControllerState {
private:
  bool m_dirty;

public:
  ControllerState() = default;
  ~ControllerState() = default;

  [[nodiscard]] auto is_dirty() const -> bool { return m_dirty; }
  void mark_dirty() { m_dirty = true; };
  void clear_dirty() { m_dirty = false; };
};

union Character {
  struct {
    uint16_t code : 12;
    uint16_t cg_color : 4;
  };
  uint16_t value;

  Character(uint16_t data) : value(data) {}
};

class Controller {
private:
  std::array<uint16_t, 0x8000> m_VRAM;

  uint32_t m_cycles;

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
  MemoryAddressWrite m_memory_address_write;
  VRAMDataWrite m_vram_data_write;

  std::unique_ptr<HuC6280::Interrupt::Controller> &m_interrupt_controller;
  std::unique_ptr<HuC6260::Controller> &m_video_color_encoder_controller;
  std::unique_ptr<ControllerState> m_state;

  std::function<void(std::array<float, COLOR_TABLE_RAM_DATA_LENGTH>,
                     std::array<float, BACKGROUND_ATTRIBUTE_TABLE_DATA_LENGTH>)>
      m_vsync_callback;

  auto load_vram(uint16_t address) -> uint16_t;
  void store_vram();
  void store_register(bool low, uint8_t value);
  auto get_background_character_data(Character character)
      -> std::array<float, CHARACTER_DATA_LENGTH>;
  auto get_background_attribute_table_data()
      -> std::array<float, BACKGROUND_ATTRIBUTE_TABLE_DATA_LENGTH>;
  auto get_character_data(unsigned int index)
      -> std::array<float, CHARACTER_DATA_LENGTH>;
  auto get_character_generator_data()
      -> std::array<float, CHARACTER_GENERATOR_DATA_LENGTH>;

public:
  Controller(
      Sakura::VDCConfig config,
      std::unique_ptr<HuC6280::Interrupt::Controller> &interrupt_controller,
      std::unique_ptr<HuC6260::Controller> &video_color_encoder_controller);
  ~Controller() = default;

  [[nodiscard]] auto load(uint16_t offset) const -> uint8_t;
  void store(uint16_t offset, uint8_t value);
  void step(uint8_t cycles);

  void set_vsync_callback(
      std::function<
          void(std::array<float, COLOR_TABLE_RAM_DATA_LENGTH>,
               std::array<float, BACKGROUND_ATTRIBUTE_TABLE_DATA_LENGTH>)>
          vsync_callback);
};
}; // namespace HuC6270
}; // namespace Sakura

#endif
