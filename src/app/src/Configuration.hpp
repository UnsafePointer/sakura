#ifndef APP_CONFIGURATION_HPP
#define APP_CONFIGURATION_HPP
#include <sakura/Emulator.hpp>

namespace App::Configuration {
void setup();
auto get_log_config() -> Sakura::LogConfig;
auto get_vdc_config() -> Sakura::VDCConfig;
}; // namespace App::Configuration

#endif
