#ifndef SAKURA_TIMER_HPP
#define SAKURA_TIMER_HPP

#include <cstdint>
#include <memory>
#include <string>

namespace Sakura::HuC6280 {
namespace Interrupt {
class Controller;
} // namespace Interrupt

namespace Timer {

static const std::string LOGGER_NAME = "---timer---";

union Control {
  struct {
    uint8_t start_stop : 1;
    uint8_t unused : 7;
  };
  uint8_t value;

  Control() : value() {}
};

union Reload {
  struct {
    uint8_t contents : 7;
    uint8_t unused : 1;
  };
  uint8_t value;

  Reload() : value() {}
};

class Controller {
private:
  uint32_t m_total_cycles;
  uint32_t m_downcounter;

  Control m_control;
  Reload m_reload;

  std::unique_ptr<Interrupt::Controller> &m_interrupt_controller;

public:
  Controller(std::unique_ptr<Interrupt::Controller> &interrupt_controller);
  ~Controller() = default;

  [[nodiscard]] auto load(uint16_t offset) const -> uint8_t;
  void store(uint16_t offset, uint8_t value);

  void step(uint8_t cycles);
};
}; // namespace Timer
}; // namespace Sakura::HuC6280

#endif
