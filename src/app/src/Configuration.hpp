#ifndef APP_CONFIGURATION_HPP
#define APP_CONFIGURATION_HPP
#include <sakura/Emulator.hpp>

namespace App::Configuration {
void setup();
auto get_log_level_config() -> Sakura::LogLevelConfig;
auto get_vdc_config() -> Sakura::VDCConfig;
auto get_log_formatter_config() -> Sakura::LogFormatterConfig;
auto get_mos_6502_mode_config() -> Sakura::MOS6502ModeConfig;
}; // namespace App::Configuration

#endif
