#ifndef FORMATTER_PRIVATE_HPP
#define FORMATTER_PRIVATE_HPP

#include <cstdarg>
#include <string>

namespace Common {
namespace Formatter {
auto format(const char *fmt, va_list args) -> std::string;
}; // namespace Formatter
}; // namespace Common

#endif
