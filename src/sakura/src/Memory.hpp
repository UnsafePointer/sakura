#ifndef SAKURA_MEMORY_HPP
#define SAKURA_MEMORY_HPP

#include <array>
#include <cstdint>
#include <filesystem>

namespace Sakura::HuC6280 {
class Disassembler;

namespace Mapping {

union Registers {
  struct {
    uint8_t mapping_register_0;
    uint8_t mapping_register_1;
    uint8_t mapping_register_2;
    uint8_t mapping_register_3;
    uint8_t mapping_register_4;
    uint8_t mapping_register_5;
    uint8_t mapping_register_6;
    uint8_t mapping_register_7;
  };
  std::array<uint8_t, 8> values;

  Registers() : values() {}
};

class Controller {
private:
  friend Disassembler;

  Registers m_registers;
  std::array<uint8_t, 0x2000> m_RAM;
  std::array<uint8_t, 0x100000> m_ROM;

public:
  Controller();
  ~Controller() = default;

  void initialize();
  void load_rom(const std::filesystem::path &path);

  auto load(uint16_t logical_address) -> uint8_t;
  void store(uint16_t logical_address, uint8_t value);

  void set_mapping_register(uint8_t index, uint8_t value);
};
}; // namespace Mapping
}; // namespace Sakura::HuC6280

#endif
