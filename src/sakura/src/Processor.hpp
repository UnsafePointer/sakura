#ifndef SAKURA_PROCESSOR_HPP
#define SAKURA_PROCESSOR_HPP

#include <cstdint>
#include <filesystem>
#include <memory>

namespace Sakura::HuC6280 {
class Disassembler;
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

enum class Speed {
  Low,
  High,
};

class Processor {
private:
  friend Disassembler;

  Registers m_registers;
  std::unique_ptr<Mapping::Controller> m_mapping_controller;
  Speed m_speed{};

  template <typename T>
  friend auto SEI(std::unique_ptr<Processor> &processor) -> T;
  template <typename T>
  friend auto CSL(std::unique_ptr<Processor> &processor) -> T;
  template <typename T>
  friend auto LDA_IMM(std::unique_ptr<Processor> &processor) -> T;
  template <typename T>
  friend auto TAM_I(std::unique_ptr<Processor> &processor) -> T;
  template <typename T>
  friend auto LDA_ABS(std::unique_ptr<Processor> &processor) -> T;
  template <typename T>
  friend auto AND_IMM(std::unique_ptr<Processor> &processor) -> T;
  template <typename T>
  friend auto BEQ(std::unique_ptr<Processor> &processor) -> T;
  template <typename T>
  friend auto CLD(std::unique_ptr<Processor> &processor) -> T;
  template <typename T>
  friend auto CSH(std::unique_ptr<Processor> &processor) -> T;
  template <typename T>
  friend auto LDX_IMM(std::unique_ptr<Processor> &processor) -> T;
  template <typename T>
  friend auto TXS(std::unique_ptr<Processor> &processor) -> T;
  template <typename T>
  friend auto STA_ZP(std::unique_ptr<Processor> &processor) -> T;

public:
  Processor();
  ~Processor() = default;

  void initialize(const std::filesystem::path &rom);
  auto fetch_instruction() -> uint8_t;
};
}; // namespace Sakura::HuC6280

#endif
