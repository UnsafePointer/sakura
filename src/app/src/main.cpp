#include "ArgumentParser.hpp"
#include "Configuration.hpp"
#include <SDL2/SDL.h>
#include <fmt/core.h>
#include <glad/glad.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
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
  if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0) {
    std::cout << "Failed to initialize the OpenGL context." << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor
            << std::endl;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO *io = &ImGui::GetIO();
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init();

  App::Configuration::setup();
  auto log_config = App::Configuration::get_log_config();
  App::Args configuration = App::ArgumentParser::parse(argc, argv);
  Sakura::Emulator emulator = Sakura::Emulator();
  emulator.set_vsync_callback(
      [&](std::array<float, COLOR_TABLE_RAM_DATA_LENGTH> color_table_data) {
        emulator.set_should_pause();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);

        ImGui::NewFrame();
        {
          if (ImGui::Begin("Color Table RAM", nullptr,
                           ImGuiWindowFlags_AlwaysAutoResize)) {
            if (ImGui::BeginTabBar("color-table-ram", ImGuiTabBarFlags_None)) {
              const int color_button_side = 20;
              for (unsigned int color_table_ram_area = 0;
                   color_table_ram_area < COLOR_TABLE_RAM_NUMBER_OF_AREAS;
                   color_table_ram_area++) {
                std::string tab_title =
                    fmt::format("{:#04x}", color_table_ram_area);
                if (ImGui::BeginTabItem(tab_title.c_str())) {
                  std::array<std::string, COLOR_TABLE_RAM_NUMBER_OF_SECTIONS>
                      titles = {"Background", "Sprite"};
                  for (unsigned int section = 0;
                       section < COLOR_TABLE_RAM_NUMBER_OF_SECTIONS;
                       section++) {
                    ImGui::Text("%s", titles[section].c_str());
                    for (unsigned int area_color = 0;
                         area_color < COLOR_TABLE_RAM_NUMBER_OF_COLORS_PER_AREA;
                         area_color++) {
                      ImGui::PushID(area_color);
                      std::string color_button_title =
                          fmt::format("{:#04x}", area_color);
                      unsigned int color_index =
                          COLOR_TABLE_RAM_NUMBER_OF_COLORS_PER_AREA *
                              color_table_ram_area +
                          area_color +
                          section *
                              COLOR_TABLE_RAM_NUMBER_OF_COLORS_PER_SECTION;
                      ImGui::ColorButton(
                          color_button_title.c_str(),
                          ImVec4(color_table_data[color_index * 3],
                                 color_table_data[color_index * 3 + 1],
                                 color_table_data[color_index * 3 + 2], 1.00f),
                          ImGuiColorEditFlags_None,
                          ImVec2(color_button_side, color_button_side));
                      if (area_color + 1 !=
                          COLOR_TABLE_RAM_NUMBER_OF_COLORS_PER_AREA) {
                        ImGui::SameLine(0, color_button_side);
                      }
                      ImGui::PopID();
                    }
                  }
                  ImGui::EndTabItem();
                }
              }
              ImGui::EndTabBar();
            }
          }
          ImGui::End();
        }
        ImGui::Render();

        glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
        glClearColor(252 / 255.0f, // NOLINT(readability-magic-numbers)
                     221 / 255.0f, // NOLINT(readability-magic-numbers)
                     237 / 255.0f, // NOLINT(readability-magic-numbers)
                     1.0f);        // NOLINT(readability-magic-numbers)
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
      });
  emulator.initialize(configuration.rom, log_config);

  bool quit = false;
  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }
    uint32_t frame_time = SDL_GetTicks();
    emulator.emulate();
    frame_time = SDL_GetTicks() - frame_time;
    std::cout << "Frame time: " << std::dec << frame_time << std::endl;
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  SDL_Quit();
  return 0;
}
