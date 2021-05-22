#include "ArgumentParser.hpp"
#include <sakura/Emulator.hpp>

auto main(int argc, char *argv[]) -> int {
  App::Configuration configuration = App::ArgumentParser::parse(argc, argv);
  Sakura::Emulator emulator = Sakura::Emulator();
  Sakura::LogConfig log_config = {.disassembler = "debug",
                                  .interrupt_controller = "debug",
                                  .io = "debug",
                                  .mapping_controller = "debug",
                                  .processor = "debug",
                                  .programmable_sound_generator = "debug",
                                  .video_color_encoder = "debug",
                                  .video_display_controller = "debug"};
  emulator.initialize(configuration.rom, log_config);
  emulator.emulate();
  return 0;
}
