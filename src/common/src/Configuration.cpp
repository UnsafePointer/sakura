#include "common/Configuration.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

static nlohmann::json g_configuration;

void Common::Configuration::setup(const std::filesystem::path &path,
                                  const std::string &contents) {
  std::fstream in_file = std::fstream(path);
  if (in_file.good()) {
    std::stringstream buffer;
    buffer << in_file.rdbuf();
    g_configuration = nlohmann::json::parse(buffer.str());
    return;
  }
  g_configuration = nlohmann::json::parse(contents);
  std::ofstream out_file = std::ofstream();
  out_file.open(path);
  out_file << std::setw(4) << g_configuration << std::endl;
  out_file.close();
}

auto split_key_path(const std::string &key_path) -> std::vector<std::string> {
  std::string delimiter = ".";
  size_t position_start = 0;
  size_t position_end;
  size_t delimimiter_len = delimiter.length();
  std::string token;
  std::vector<std::string> components;

  while ((position_end = key_path.find(delimiter, position_start)) !=
         std::string::npos) {
    token = key_path.substr(position_start, position_end - position_start);
    position_start = position_end + delimimiter_len;
    components.push_back(token);
  }

  components.push_back(key_path.substr(position_start));
  return components;
}

auto Common::Configuration::get(const std::string &key_path) -> std::string {
  std::vector<std::string> components = split_key_path(key_path);
  nlohmann::json object = g_configuration;
  for (const auto &component : components) {
    object = object[component];
  }
  return object;
}
