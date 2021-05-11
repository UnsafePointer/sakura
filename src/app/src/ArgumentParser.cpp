#include "ArgumentParser.hpp"
#include <common/Formatter.hpp>
#include <iostream>
#include <unistd.h>

using namespace App;

void ArgumentParser::print_usage() {
  std::cout << "Usage: shinobu [-h] filepath" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "  -h   print this message" << std::endl;
  std::cout << "" << std::endl;
}

// NOLINTNEXTLINE(modernize-avoid-c-arrays)
auto ArgumentParser::parse(int argc, char *argv[]) -> Configuration {
  int c;
  while ((c = getopt(argc, argv, "h")) != -1) { // NOLINT(concurrency-mt-unsafe)
    switch (c) {
    case 'h':
      print_usage();
      exit(0); // NOLINT(concurrency-mt-unsafe)
      break;
    case '?':
      print_usage();
      exit(1); // NOLINT(concurrency-mt-unsafe)
      break;
    default:
      std::cout << "Unexpected error while parsing options." << std::endl;
      exit(1); // NOLINT(concurrency-mt-unsafe)
    }
  }
  if (optind >= argc) {
    print_usage();
    std::cout << "Missing argument: ROM filepath." << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  char *path = argv[optind];
  std::filesystem::path rom =
      std::filesystem::current_path() / std::string(path);
  if (!std::filesystem::exists(rom)) {
    std::cout << Common::Formatter::format(
                     "The filepath provided as argument: %s doesn't exist.",
                     rom.c_str())
              << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  return {rom};
}
