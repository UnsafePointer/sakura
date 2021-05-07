#include <sakura/Emulator.hpp>

auto main(int argc, char *argv[]) -> int {
  (void)argc;
  (void)argv;
  Sakura::Emulator emulator = Sakura::Emulator();
  emulator.emulate();
  return 0;
}
