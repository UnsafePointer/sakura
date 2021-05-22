find_package(spdlog CONFIG REQUIRED)

add_library(libsakura
    src/Disassembler.cpp
    src/Interrupt.cpp
    src/IO.cpp
    src/Memory.cpp
    src/Processor.cpp
    src/ProgrammableSoundGenerator.cpp
    src/VideoColorEncoder.cpp
    src/VideoDisplayController.cpp
    src/Emulator.cpp)
target_compile_features(libsakura PUBLIC cxx_std_17)
target_compile_options(libsakura PRIVATE -Werror -Wall -Wextra)

target_include_directories(libsakura PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_link_libraries(libsakura PRIVATE libcommon)
target_link_libraries(libsakura PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
