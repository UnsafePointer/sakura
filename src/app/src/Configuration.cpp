#include "Configuration.hpp"
#include <common/Configuration.hpp>
#include <cstring>
#include <filesystem>

void App::Configuration::setup() {
  std::filesystem::path config_file_path =
      std::filesystem::current_path() / std::string("sakura.json");
  std::string contents = R"json(
{
  "log_formatter": {
    "enabled": "true"
  },
  "log_level": {
    "block_transfer_instruction": "critical",
    "disassembler": "critical",
    "interrupt_controller": "critical",
    "io": "critical",
    "mapping_controller": "critical",
    "processor": "critical",
    "programmable_sound_generator": "critical",
    "stack": "critical",
    "timer": "critical",
    "video_color_encoder": "critical",
    "video_display_controller": "critical"
  },
  "mos_6502_mode": {
    "enabled": "false"
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
              "log_level.block_transfer_instruction"),
          .stack = Common::Configuration::get("log_level.stack")};
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

auto App::Configuration::get_mos_6502_mode_config()
    -> Sakura::MOS6502ModeConfig {
  return {.enabled =
              is_true(Common::Configuration::get("mos_6502_mode.enabled"))};
}
