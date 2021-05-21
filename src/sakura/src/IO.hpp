#ifndef SAKURA_IO_HPP
#define SAKURA_IO_HPP

#include <cstdint>
#include <string>

namespace Sakura::HuC6280::IO {

static const std::string LOGGER_NAME = "io";

union Port {
  struct {
    uint8_t joypad_0 : 1;
    uint8_t joypad_1 : 1;
    uint8_t joypad_2 : 1;
    uint8_t joypad_3 : 1;
    uint8_t unused : 1;
    uint8_t unused_2 : 1;
    uint8_t region : 1;
    uint8_t cd_rom : 1;
  };
  uint8_t value;

  Port() : value(0xBF) {} // TODO: Remove hardcoded value
};

class Controller {
private:
  Port m_port;

public:
  Controller() = default;
  ~Controller() = default;

  [[nodiscard]] auto load() const -> uint8_t;
  void store(uint8_t value);
};
}; // namespace Sakura::HuC6280::IO

#endif
