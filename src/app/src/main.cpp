#include "ArgumentParser.hpp"
#include "Configuration.hpp"
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <sakura/Emulator.hpp>

auto main(int argc, char *argv[]) -> int {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  const int gl_major_version = 4;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major_version);
  const int gl_minor_version = 6;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor_version);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

  SDL_DisplayMode display_mode;
  if (SDL_GetDesktopDisplayMode(0, &display_mode) != 0) {
    std::cout << "Error getting desktop display mode: " << SDL_GetError()
              << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }

  const int horizontal_resolution = 256;
  const int vertical_resolution = 240;
  const float screen_ratio = 0.8;
  int max_horizontal_ratio =
      ((display_mode.w * screen_ratio) / 2) / horizontal_resolution;
  int max_vertical_ratio =
      ((display_mode.h * screen_ratio) / 2) / vertical_resolution;
  int ratio = max_horizontal_ratio > max_vertical_ratio ? max_horizontal_ratio
                                                        : max_vertical_ratio;
  int width = horizontal_resolution * ratio;
  int heigth = vertical_resolution * ratio;

  SDL_Window *window =
      SDL_CreateWindow("桜", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, heigth, SDL_WINDOW_OPENGL);
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  (void)gl_context;
  if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0) {
    std::cout << "Failed to initialize the OpenGL context." << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor
            << std::endl;

  App::Configuration::setup();
  auto log_config = App::Configuration::get_log_config();
  App::Args configuration = App::ArgumentParser::parse(argc, argv);
  Sakura::Emulator emulator = Sakura::Emulator();
  emulator.set_vsync_callback([&]() {
    emulator.set_should_pause();
    glClearColor(252 / 255.0f, // NOLINT(readability-magic-numbers)
                 221 / 255.0f, // NOLINT(readability-magic-numbers)
                 237 / 255.0f, // NOLINT(readability-magic-numbers)
                 1.0f);        // NOLINT(readability-magic-numbers)
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
  });
  emulator.initialize(configuration.rom, log_config);

  bool quit = false;
  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }
    uint32_t frame_time = SDL_GetTicks();
    emulator.emulate();
    frame_time = SDL_GetTicks() - frame_time;
    std::cout << "Frame time: " << std::dec << frame_time << std::endl;
  }

  SDL_Quit();
  return 0;
}
