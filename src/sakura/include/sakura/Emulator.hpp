#ifndef SAKURA_EMULATOR_HPP
#define SAKURA_EMULATOR_HPP

#include <filesystem>
#include <functional>
#include <memory>
#include <sakura/Constants.hpp>

namespace Sakura {
namespace HuC6280 {
namespace Mapping {
class Controller;
} // namespace Mapping
namespace Interrupt {
class Controller;
} // namespace Interrupt
class Processor;
class Disassembler;
} // namespace HuC6280
namespace HuC6270 {
class Controller;
} // namespace HuC6270
namespace HuC6260 {
class Controller;
} // namespace HuC6260

/*
Possible values: "trace", "debug", "info", "warning", "error", "critical", "off"
*/
struct LogConfig {
  std::string disassembler;
  std::string interrupt_controller;
  std::string io;
  std::string mapping_controller;
  std::string processor;
  std::string programmable_sound_generator;
  std::string timer;
  std::string video_color_encoder;
  std::string video_display_controller;
};

struct VDCConfig {
  bool deadbeef_vram;
};

class Emulator {
private:
  std::unique_ptr<HuC6280::Interrupt::Controller> m_interrupt_controller;
  std::unique_ptr<HuC6260::Controller> m_video_color_encoder_controller;
  std::unique_ptr<HuC6270::Controller> m_video_display_controller;
  std::unique_ptr<HuC6280::Mapping::Controller> m_mapping_controller;
  std::unique_ptr<HuC6280::Processor> m_processor;
  std::unique_ptr<HuC6280::Disassembler> m_disassembler;

  bool m_should_pause;

  static void register_loggers(const LogConfig &log_config);

public:
  Emulator(const VDCConfig &vdc_config);
  ~Emulator();

  void emulate();
  void initialize(const std::filesystem::path &rom,
                  const LogConfig &log_config);
  void set_vsync_callback(
      std::function<
          void(std::array<float, COLOR_TABLE_RAM_DATA_LENGTH>,
               std::array<float, BACKGROUND_ATTRIBUTE_TABLE_DATA_LENGTH>)>
          vsync_callback);
  void set_should_pause();
};
}; // namespace Sakura

#endif
