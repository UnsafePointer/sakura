find_package(nlohmann_json CONFIG REQUIRED)

add_library(libcommon
    src/Bits.cpp
    src/Configuration.cpp)
target_compile_features(libcommon PUBLIC cxx_std_17)
target_compile_options(libcommon PRIVATE -Werror -Wall -Wextra)

target_include_directories(libcommon PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_link_libraries(libcommon PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
