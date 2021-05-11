#ifndef COMMON_FORMATTER_HPP
#define COMMON_FORMATTER_HPP

#include <cstdarg>
#include <string>

namespace Common {
namespace Formatter {
enum Color {
  Red = 31,
  Green = 32,
  Yellow = 33,
  Magenta = 35,
  Blue = 36,
};

auto format(const char *fmt, ...) -> std::string;
auto colorize(const std::string &text, Common::Formatter::Color color,
              bool bright = false) -> std::string;
}; // namespace Formatter
}; // namespace Common

#endif
