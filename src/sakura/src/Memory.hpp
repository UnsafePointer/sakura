#ifndef SAKURA_MEMORY_HPP
#define SAKURA_MEMORY_HPP

#include <array>
#include <common/Range.hpp>
#include <cstdint>
#include <filesystem>
#include <memory>

namespace Sakura {
namespace HuC6260 {
class Controller;
} // namespace HuC6260
namespace HuC6270 {
class Controller;
} // namespace HuC6270
namespace HuC6280 {
namespace IO {
class Controller;
} // namespace IO
namespace ProgrammableSoundGenerator {
class Controller;
} // namespace ProgrammableSoundGenerator

class Disassembler;

namespace Mapping {

const Common::Range<uint32_t> IO_RANGE =
    Common::Range<uint32_t>(0x1FF000, 0x400);

const Common::Range<uint32_t> VIDEO_DISPLAY_CONTROLLER_RANGE =
    Common::Range<uint32_t>(0x1FE000, 0x400);

const Common::Range<uint32_t> VIDEO_COLOR_ENCODER_RANGE =
    Common::Range<uint32_t>(0x1FE400, 0x400);

const Common::Range<uint32_t> PROGRAMMABLE_SOUND_GENERATOR_RANGE =
    Common::Range<uint32_t>(0x1FE800, 0xC00);

union Registers {
  struct {
    uint8_t mapping_register_0;
    uint8_t mapping_register_1;
    uint8_t mapping_register_2;
    uint8_t mapping_register_3;
    uint8_t mapping_register_4;
    uint8_t mapping_register_5;
    uint8_t mapping_register_6;
    uint8_t mapping_register_7;
  };
  std::array<uint8_t, 8> values;

  Registers() : values() {}
};

class Controller {
private:
  friend Disassembler;

  Registers m_registers;
  std::array<uint8_t, 0x2000> m_RAM;
  std::array<uint8_t, 0x100000> m_ROM;

  std::unique_ptr<IO::Controller> m_IO_controller;
  std::unique_ptr<HuC6270::Controller> m_video_display_controller;
  std::unique_ptr<ProgrammableSoundGenerator::Controller>
      m_programmable_sound_generator_controller;
  std::unique_ptr<HuC6260::Controller> m_video_color_encoder_controller;

public:
  Controller();
  ~Controller();

  void initialize();
  void load_rom(const std::filesystem::path &path);

  auto load(uint16_t logical_address) -> uint8_t;
  void store(uint16_t logical_address, uint8_t value);
  void store_video_display_controller(uint32_t physical_address, uint8_t value);

  void set_mapping_register(uint8_t index, uint8_t value);
  auto mapping_register(uint8_t index) -> uint8_t;
};
}; // namespace Mapping
}; // namespace HuC6280
}; // namespace Sakura

#endif
