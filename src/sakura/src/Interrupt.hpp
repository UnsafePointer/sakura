#ifndef SAKURA_INTERRUPT_HPP
#define SAKURA_INTERRUPT_HPP

#include <cstdint>
#include <string>

namespace Sakura::HuC6280::Interrupt {

static const std::string LOGGER_NAME = "-interrupt-";

union Request {
  struct {
    uint8_t interrupt_request_2 : 1;
    uint8_t interrupt_request_1 : 1;
    uint8_t timer_interrupt_request : 1;
    uint8_t unused;
  };
  uint8_t value;

  Request() : value() {}
};

union Disable {
  struct {
    uint8_t interrupt_request_2 : 1;
    uint8_t interrupt_request_1 : 1;
    uint8_t timer_interrupt_request : 1;
    uint8_t unused;
  };

  uint8_t value;

  Disable() : value() {}
};

class Controller {
  Request m_request;
  Disable m_disable;

public:
  Controller() = default;
  ~Controller() = default;

  [[nodiscard]] auto load(uint16_t offset) const -> uint8_t;
  void store(uint16_t offset, uint8_t value);
};
}; // namespace Sakura::HuC6280::Interrupt

#endif
