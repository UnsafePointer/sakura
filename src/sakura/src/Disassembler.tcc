#ifndef SAKURA_DISASSEMBLER_TCC
#define SAKURA_DISASSEMBLER_TCC

#include "Instructions.hpp"
#include "Memory.hpp"
#include "Processor.hpp"
#include <common/Formatter.hpp>
#include <cstdint>
#include <memory>

using namespace Sakura::HuC6280;

template <>
auto Sakura::HuC6280::SEI(std::unique_ptr<Processor> &processor)
    -> std::string {
  (void)processor;
  return "SEI";
}

template <>
auto Sakura::HuC6280::CSL(std::unique_ptr<Processor> &processor)
    -> std::string {
  (void)processor;
  return "CLS";
}

template <>
auto Sakura::HuC6280::LDA_IMM(std::unique_ptr<Processor> &processor)
    -> std::string {
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return Common::Formatter::format("LDA #%02x", imm);
}

#endif
