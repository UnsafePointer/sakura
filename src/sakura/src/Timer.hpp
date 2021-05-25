#ifndef SAKURA_TIMER_HPP
#define SAKURA_TIMER_HPP

#include <cstdint>
#include <string>

namespace Sakura::HuC6280::Timer {

static const std::string LOGGER_NAME = "---timer---";

union Control {
  struct {
    uint8_t start_stop : 1;
    uint8_t unused : 7;
  };
  uint8_t value;

  Control() : value() {}
};

class Controller {
private:
  Control m_control;

public:
  Controller() = default;
  ~Controller() = default;

  [[nodiscard]] auto load(uint16_t offset) const -> uint8_t;
  void store(uint16_t offset, uint8_t value);
};
}; // namespace Sakura::HuC6280::Timer

#endif
