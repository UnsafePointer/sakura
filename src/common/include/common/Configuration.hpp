#ifndef COMMON_CONFIGURATION_HPP
#define COMMON_CONFIGURATION_HPP

#include <filesystem>

namespace Common::Configuration {

void setup(const std::filesystem::path &path, const std::string &contents);
auto get(const std::string &key_path) -> std::string;

}; // namespace Common::Configuration

#endif
