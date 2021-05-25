#ifndef SAKURA_EMULATOR_HPP
#define SAKURA_EMULATOR_HPP

#include <filesystem>
#include <memory>

namespace Sakura {
namespace HuC6280 {
class Processor;
class Disassembler;
} // namespace HuC6280

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

class Emulator {
private:
  std::unique_ptr<HuC6280::Processor> m_processor;
  std::unique_ptr<HuC6280::Disassembler> m_disassembler;

  static void register_loggers(const LogConfig &log_config);

public:
  Emulator();
  ~Emulator();

  void emulate();
  void initialize(const std::filesystem::path &rom,
                  const LogConfig &log_config);
};
}; // namespace Sakura

#endif
