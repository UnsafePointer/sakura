#include "ArgumentParser.hpp"
#include "Configuration.hpp"
#include <sakura/Emulator.hpp>

auto main(int argc, char *argv[]) -> int {
  App::Configuration::setup();
  auto log_config = App::Configuration::get_log_config();
  App::Args configuration = App::ArgumentParser::parse(argc, argv);
  Sakura::Emulator emulator = Sakura::Emulator();
  emulator.initialize(configuration.rom, log_config);
  emulator.emulate();
  return 0;
}
