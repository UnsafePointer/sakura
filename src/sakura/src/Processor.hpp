#ifndef SAKURA_PROCESSOR_HPP
#define SAKURA_PROCESSOR_HPP

#include <cstdint>
#include <filesystem>
#include <memory>

namespace Sakura::HuC6280 {
namespace Mapping {
class Controller;
} // namespace Mapping

static const uint16_t RESET_VECTOR_INTERRUPT_REQUEST_2 = 0xFFF6;
static const uint16_t RESET_VECTOR_INTERRUPT_REQUEST_1 = 0xFFF8;
static const uint16_t RESET_VECTOR_TIMER = 0xFFFA;
static const uint16_t RESET_VECTOR_NONMASKABLE_INTERRUPT = 0xFFFC;
static const uint16_t RESET_VECTOR_RESET = 0xFFFE;

union Status {
  struct {
    uint8_t carry : 1;
    uint8_t zero : 1;
    uint8_t interrupt_disable : 1;
    uint8_t decimal : 1;
    uint8_t break_command : 1;
    uint8_t memory_operation : 1;
    uint8_t overflow : 1;
    uint8_t negative : 1;
  };
  uint8_t value;

  Status() : value() {}
};

union ProgramCounter {
  struct {
    uint16_t program_counter_low : 8;
    uint16_t program_counter_high : 8;
  };
  uint16_t value;

  ProgramCounter() : value() {}
};

struct Registers {
  uint8_t accumulator{};
  uint8_t x{};
  uint8_t y{};
  ProgramCounter program_counter;
  uint8_t stack_pointer{};
  Status status;
  uint8_t source_high{};
  uint8_t destination_high{};
  uint8_t length_high{};

  Registers() = default;
};

class Processor {
private:
  Registers m_registers;
  std::unique_ptr<Mapping::Controller> m_mapping_controller;

public:
  Processor();
  ~Processor() = default;

  void initialize(const std::filesystem::path &rom);
  auto fetch_instruction() -> uint8_t;
};
}; // namespace Sakura::HuC6280

#endif
