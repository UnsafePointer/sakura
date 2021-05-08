#ifndef _ARGUMENTPARSER_HPP
#define _ARGUMENTPARSER_HPP

#include <filesystem>

namespace App {
struct Configuration {
  std::filesystem::path rom;
};

class ArgumentParser {
private:
  static void print_usage();

public:
  // NOLINTNEXTLINE(modernize-avoid-c-arrays)
  static auto parse(int argc, char *argv[]) -> Configuration;
};
} // namespace App

#endif
