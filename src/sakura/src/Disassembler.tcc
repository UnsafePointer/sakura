#ifndef SAKURA_DISASSEMBLER_TCC
#define SAKURA_DISASSEMBLER_TCC

#include "Instructions.hpp"
#include "Memory.hpp"
#include "Processor.hpp"
#include <common/Bits.hpp>
#include <common/Formatter.hpp>
#include <cstdint>
#include <memory>

using namespace Sakura::HuC6280;

template <>
auto Sakura::HuC6280::SEI(std::unique_ptr<Processor> &processor)
    -> DisassembledInstruction {
  (void)processor;
  return {"SEI", 1};
}

template <>
auto Sakura::HuC6280::CSL(std::unique_ptr<Processor> &processor)
    -> DisassembledInstruction {
  (void)processor;
  return {"CLS", 1};
}

template <>
auto Sakura::HuC6280::LDA_IMM(std::unique_ptr<Processor> &processor)
    -> DisassembledInstruction {
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {Common::Formatter::format("LDA #%02x", imm), 2};
}

template <>
auto Sakura::HuC6280::TAM_I(std::unique_ptr<Processor> &processor)
    -> DisassembledInstruction {
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  int bit_position = Common::Bits::test_power_of_2(imm);

  return {Common::Formatter::format("TAM%d", bit_position), 2};
}

#endif
