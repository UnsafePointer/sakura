cmake_minimum_required(VERSION 3.12...3.20)

project(
    sakura
    VERSION 0.1
    DESCRIPTION "An instruction accurate PC Engine/TurboGrafx-16 emulator"
    LANGUAGES CXX)

include(CTest)

add_subdirectory(common)
add_subdirectory(common/tests)
add_subdirectory(sakura)
add_subdirectory(app)
