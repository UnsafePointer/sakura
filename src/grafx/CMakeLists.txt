find_package(glad CONFIG REQUIRED)

add_library(libgrafx
    src/Texture.cpp)
target_compile_features(libgrafx PUBLIC cxx_std_17)
target_compile_options(libgrafx PRIVATE -Werror -Wall -Wextra)

target_include_directories(libgrafx PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_link_libraries(libgrafx PRIVATE glad::glad)
