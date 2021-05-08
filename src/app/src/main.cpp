#include "ArgumentParser.hpp"
#include <sakura/Emulator.hpp>

auto main(int argc, char *argv[]) -> int {
  App::Configuration configuration = App::ArgumentParser::parse(argc, argv);
  Sakura::Emulator emulator = Sakura::Emulator();
  emulator.emulate();
  return 0;
}
