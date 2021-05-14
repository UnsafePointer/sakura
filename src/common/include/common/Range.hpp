#ifndef COMMON_RANGE_HPP
#define COMMON_RANGE_HPP

#include <optional>

namespace Common {
template <typename T> struct Range {
  const T start;
  const T length;

  Range(T start, T length) : start(start), length(length){};
  ~Range() = default;

  [[nodiscard]] auto contains(T address) const -> std::optional<T> {
    if (address >= start && address < (start + length)) {
      return {address - start};
    }
    return std::nullopt;
  }
};
}; // namespace Common

#endif
