find_package(Catch2 CONFIG REQUIRED)

add_executable(libcommon_tests CommonTests.cpp)
target_compile_features(libcommon_tests PRIVATE cxx_std_17)

target_link_libraries(libcommon_tests PRIVATE libcommon Catch2::Catch2)
add_test(NAME libcommon_tests COMMAND libcommon_tests)
