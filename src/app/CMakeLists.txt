find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(sakura
    src/ArgumentParser.cpp
    src/Configuration.cpp
    src/main.cpp)
target_compile_features(sakura PRIVATE cxx_std_17)
target_compile_options(sakura PRIVATE -Werror -Wall -Wextra)

target_link_libraries(sakura PRIVATE libsakura)
target_link_libraries(sakura PRIVATE libcommon)
target_link_libraries(sakura PRIVATE libgrafx)
target_link_libraries(sakura PRIVATE SDL2::SDL2main SDL2::SDL2-static)
target_link_libraries(sakura PRIVATE glad::glad)
target_link_libraries(sakura PRIVATE imgui::imgui)
target_link_libraries(sakura PRIVATE fmt::fmt-header-only)
