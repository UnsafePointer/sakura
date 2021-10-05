#ifndef SAKURA_EMULATOR_HPP
#define SAKURA_EMULATOR_HPP

#include <filesystem>
#include <functional>
#include <memory>
#include <sakura/Constants.hpp>
#include <sakura/RendererInfo.hpp>

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
struct LogLevelConfig {
  std::string disassembler;
  std::string interrupt_controller;
  std::string io;
  std::string mapping_controller;
  std::string processor;
  std::string programmable_sound_generator;
  std::string timer;
  std::string video_color_encoder;
  std::string video_display_controller;
  std::string block_transfer_instruction;
  std::string stack;
};

struct VDCConfig {
  bool deadbeef_vram;
};

struct LogFormatterConfig {
  bool enabled;
};

struct MOS6502ModeConfig {
  bool enabled;
};

class Emulator {
private:
  std::unique_ptr<HuC6280::Interrupt::Controller> m_interrupt_controller;
  std::unique_ptr<HuC6260::Controller> m_video_color_encoder_controller;
  std::unique_ptr<HuC6270::Controller> m_video_display_controller;
  std::unique_ptr<HuC6280::Mapping::Controller> m_mapping_controller;
  std::unique_ptr<HuC6280::Processor> m_processor;
  std::unique_ptr<HuC6280::Disassembler> m_disassembler;
  std::unique_ptr<RendererInfo> m_renderer_info;

  bool m_should_pause;

  static void register_loggers(const LogLevelConfig &log_level_config,
                               const LogFormatterConfig &log_formatter_config);

public:
  Emulator(const VDCConfig &vdc_config,
           const MOS6502ModeConfig &mos_6502_mode_config);
  ~Emulator();

  void emulate();
  void initialize(const std::filesystem::path &rom,
                  const LogLevelConfig &log_level_config,
                  const LogFormatterConfig &log_formatter_config);
  void
  set_vsync_callback(const std::function<void(std::unique_ptr<RendererInfo> &)>
                         &vsync_callback);
  void set_should_pause();
};
}; // namespace Sakura

#endif
