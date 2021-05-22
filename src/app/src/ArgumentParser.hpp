#ifndef APP_ARGUMENT_PARSER_HPP
#define APP_ARGUMENT_PARSER_HPP

#include <filesystem>

namespace App {
struct Args {
  std::filesystem::path rom;
};

class ArgumentParser {
private:
  static void print_usage();

public:
  // NOLINTNEXTLINE(modernize-avoid-c-arrays)
  static auto parse(int argc, char *argv[]) -> Args;
};
} // namespace App

#endif
