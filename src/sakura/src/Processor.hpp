#ifndef SAKURA_PROCESSOR_HPP
#define SAKURA_PROCESSOR_HPP

#include <cstdint>
#include <filesystem>
#include <memory>
#include <stack>

namespace Sakura {
struct MOS6502ModeConfig;
namespace HuC6280 {
namespace Interrupt {
class Controller;
} // namespace Interrupt
class Disassembler;
namespace Mapping {
class Controller;
} // namespace Mapping

static const std::string LOGGER_NAME = "--huc6280--";
static const std::string BLOCK_TRANSFER_LOGGER_NAME = "--blocktx--";
static const std::string STACK_LOGGER_NAME = "---stack---";

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

enum class BlockTransferType {
  TAI,
  TIA,
};

struct BlockTransferSpec {
  uint8_t sl;
  uint8_t sh;
  uint8_t dl;
  uint8_t dh;
  uint8_t ll;
  uint8_t lh;
  BlockTransferType type;
};

class Processor {
private:
  friend Disassembler;

  Registers m_registers;
  Speed m_speed{};

  const bool m_mos_6502_mode_enabled;

  std::unique_ptr<Mapping::Controller> &m_mapping_controller;
  std::unique_ptr<Interrupt::Controller> &m_interrupt_controller;

  const uint16_t m_stack_pointer_address_base;
  bool m_stack_pointer_initialized;
  std::stack<uint8_t> m_fallback_stack;

  void push_into_stack(uint8_t value);
  auto pop_from_stack() -> uint8_t;
  auto execute_block_transfer(BlockTransferSpec spec) -> uint16_t;

  [[nodiscard]] auto get_zero_page_address(uint8_t address) const -> uint16_t;

  void trace(uint8_t opcode);

  // clang-format off
  template <typename T>
  friend auto SEI(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CSL(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDA_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto TAM_I(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDA_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto AND_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BEQ(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CLD(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CSH(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDX_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto TXS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STA_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STA_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STZ_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STZ_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto TAI(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto PHX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto PHY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto JSR(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto TMA_I(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto PHA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto INC_ACC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ASL_ACC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto TAX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto JMP_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto SMB_I(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto RMB_I(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STX_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto DEX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BPL(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDY_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto TYA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto PLA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto RTS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto PLY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto PLX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDA_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CLY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto NOP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDA_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STA_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ORA_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto EOR_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto EOR_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto AND_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto INY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CPY_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BCC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CMP_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BNE(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CLX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDA_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto INX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CPX_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ST0(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto DEY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto TAY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDY_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDA_IND(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STA_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDA_IND_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CLC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ADC_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STZ_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CPX_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto SEC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto SBC_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto DEC_ACC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ORA_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CLI(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto JMP_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BRA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ORA_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STA_IND(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STA_IND_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CLA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BCS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ASL_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ROL_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ADC_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ADC_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BSR(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BMI(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto INC_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STA_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STX_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ASL_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto DEC_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LSR_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto PHP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto PLP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDX_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto INC_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDX_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDY_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto SAY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto RTI(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BBR_I(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BIT_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CMP_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto TIA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto SXY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ADC_IND(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STY_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDA_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto TXA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LSR_ACC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ADC_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto JMP_ABS_IND(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto TSX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto DEC_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto SAX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto DEC_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CMP_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto INC_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto DEC_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ADC_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ORA_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ST1(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ST2(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BBS_I(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STY_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto TSB_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto TRB_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BVC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BVS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BRK(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto SED(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CLV(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDX_ZP_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CMP_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDX_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STX_ZP_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDY_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDY_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STY_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CMP_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CMP_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CPX_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CPY_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CPY_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CMP_IND_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto LDA_IND_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto STA_IND_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BIT_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto BIT_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto CMP_IND_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ROL_ACC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ROR_ACC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ROR_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  template <typename T>
  friend auto ASL_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
  // clang-format on

public:
  Processor(const Sakura::MOS6502ModeConfig &mos_6502_mode_config,
            std::unique_ptr<Mapping::Controller> &mapping_controller,
            std::unique_ptr<Interrupt::Controller> &interrupt_controller);
  ~Processor() = default;

  void initialize(const std::filesystem::path &rom);
  auto fetch_instruction() -> uint8_t;

  void check_interrupts();
};
}; // namespace HuC6280
}; // namespace Sakura

#endif
