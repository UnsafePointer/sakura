add_executable(sakura
    src/ArgumentParser.cpp
    src/Configuration.cpp
    src/main.cpp)
target_compile_features(sakura PRIVATE cxx_std_17)
target_compile_options(sakura PRIVATE -Werror -Wall -Wextra)

target_link_libraries(sakura PRIVATE libsakura)
target_link_libraries(sakura PRIVATE libcommon)
