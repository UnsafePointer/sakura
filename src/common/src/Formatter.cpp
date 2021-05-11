#include "common/Formatter.hpp"
#include "Formatter_Private.hpp"
#include <array>
#include <cstdarg>

static constexpr unsigned int FORMATTER_BUFFER_SIZE = 4096;

auto Common::Formatter::format(const char *fmt, va_list args) -> std::string {
  std::array<char, FORMATTER_BUFFER_SIZE> buffer;

  const auto result = vsnprintf(buffer.data(), buffer.size(), fmt, args);

  if (result < 0) {
    return {};
  }

  const size_t length = result;
  if (length < sizeof(buffer)) {
    return {buffer.data(), length};
  }

  std::string formatted(length, '\0');
  vsnprintf(formatted.data(), length + 1, fmt, args);

  return formatted;
}

auto Common::Formatter::format(const char *fmt, ...) -> std::string {
  va_list args;
  va_start(args, fmt);
  std::string formatted = format(fmt, args);
  va_end(args);
  return formatted;
}

auto Common::Formatter::colorize(const std::string &text,
                                 Common::Formatter::Color color, bool bright)
    -> std::string {
  return format("\033[%s%dm%s\033[0m", bright ? "1;" : "", color, text.c_str());
}
