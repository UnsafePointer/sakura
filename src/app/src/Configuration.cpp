#include "Configuration.hpp"
#include <common/Configuration.hpp>
#include <cstring>
#include <filesystem>

void App::Configuration::setup() {
  std::filesystem::path config_file_path =
      std::filesystem::current_path() / std::string("sakura.json");
  std::string contents = R"json(
{
  "log": {
    "block_transfer_instruction": "debug",
    "disassembler": "debug",
    "interrupt_controller": "debug",
    "io": "debug",
    "mapping_controller": "debug",
    "processor": "debug",
    "programmable_sound_generator": "debug",
    "timer": "debug",
    "video_color_encoder": "debug",
    "video_display_controller": "debug"
  },
  "vdc": {
    "deadbeef_vram": "false"
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
          .timer = Common::Configuration::get("log.timer"),
          .video_color_encoder =
              Common::Configuration::get("log.video_color_encoder"),
          .video_display_controller =
              Common::Configuration::get("log.video_display_controller"),
          .block_transfer_instruction =
              Common::Configuration::get("log.block_transfer_instruction")};
}

// TODO: solve templating problem with Common::Configuration::get, this is
// unacceptable
auto is_true(const std::string &value) -> bool {
  return strcasecmp("true", value.c_str()) == 0;
}

auto App::Configuration::get_vdc_config() -> Sakura::VDCConfig {
  return {.deadbeef_vram =
              is_true(Common::Configuration::get("vdc.deadbeef_vram"))};
}
