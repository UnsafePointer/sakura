#include <sakura/Emulator.hpp>

auto main(int argc, char *argv[]) -> int {
  (void)argc;
  (void)argv;
  Sakura::Emulator::emulate();
  return 0;
}
