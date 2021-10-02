#include "Configuration.hpp"
#include <common/Configuration.hpp>
#include <cstring>
#include <filesystem>

void App::Configuration::setup() {
  std::filesystem::path config_file_path =
      std::filesystem::current_path() / std::string("sakura.json");
  std::string contents = R"json(
{
  "log_level": {
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
  "log_formatter": {
    "enabled": "true"
  },
  "vdc": {
    "deadbeef_vram": "false"
  }
}
    )json";
  Common::Configuration::setup(config_file_path, contents);
}

auto App::Configuration::get_log_level_config() -> Sakura::LogLevelConfig {
  return {.disassembler = Common::Configuration::get("log_level.disassembler"),
          .interrupt_controller =
              Common::Configuration::get("log_level.interrupt_controller"),
          .io = Common::Configuration::get("log_level.io"),
          .mapping_controller =
              Common::Configuration::get("log_level.mapping_controller"),
          .processor = Common::Configuration::get("log_level.processor"),
          .programmable_sound_generator = Common::Configuration::get(
              "log_level.programmable_sound_generator"),
          .timer = Common::Configuration::get("log_level.timer"),
          .video_color_encoder =
              Common::Configuration::get("log_level.video_color_encoder"),
          .video_display_controller =
              Common::Configuration::get("log_level.video_display_controller"),
          .block_transfer_instruction = Common::Configuration::get(
              "log_level.block_transfer_instruction")};
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

auto App::Configuration::get_log_formatter_config()
    -> Sakura::LogFormatterConfig {
  return {.enabled =
              is_true(Common::Configuration::get("log_formatter.enabled"))};
}
