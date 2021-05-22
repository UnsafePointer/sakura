#include "Configuration.hpp"
#include <common/Configuration.hpp>
#include <filesystem>

void App::Configuration::setup() {
  std::filesystem::path config_file_path =
      std::filesystem::current_path() / std::string("sakura.json");
  std::string contents = R"json(
{
  "log": {
    "disassembler": "debug",
    "interrupt_controller": "debug",
    "io": "debug",
    "mapping_controller": "debug",
    "processor": "debug",
    "programmable_sound_generator": "debug",
    "video_color_encoder": "debug",
    "video_display_controller": "debug"
  }
}
    )json";
  Common::Configuration::setup(config_file_path, contents);
}

auto App::Configuration::get_log_config() -> Sakura::LogConfig {
  return {.disassembler = Common::Configuration::get("log.disassembler"),
          .interrupt_controller =
              Common::Configuration::get("log.interrupt_controller"),
          .io = Common::Configuration::get("log.io"),
          .mapping_controller =
              Common::Configuration::get("log.mapping_controller"),
          .processor = Common::Configuration::get("log.processor"),
          .programmable_sound_generator =
              Common::Configuration::get("log.programmable_sound_generator"),
          .video_color_encoder =
              Common::Configuration::get("log.video_color_encoder"),
          .video_display_controller =
              Common::Configuration::get("log.video_display_controller")};
}
