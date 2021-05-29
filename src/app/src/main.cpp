#include "ArgumentParser.hpp"
#include "Configuration.hpp"
#include <iostream>
#include <sakura/Emulator.hpp>

auto main(int argc, char *argv[]) -> int {
  App::Configuration::setup();
  auto log_config = App::Configuration::get_log_config();
  App::Args configuration = App::ArgumentParser::parse(argc, argv);
  Sakura::Emulator emulator = Sakura::Emulator();
  emulator.set_vsync_callback(
      [&]() { std::cout << "vsync callback" << std::endl; });
  emulator.initialize(configuration.rom, log_config);
  for (;;) {
    emulator.emulate();
  }
  return 0;
}
