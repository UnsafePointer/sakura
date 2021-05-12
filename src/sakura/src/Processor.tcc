#ifndef SAKURA_PROCESSOR_TCC
#define SAKURA_PROCESSOR_TCC

#include "Processor.hpp"
#include <cstdint>
#include <memory>

using namespace Sakura::HuC6280;

template <>
auto Sakura::HuC6280::SEI(std::unique_ptr<Processor> &processor) -> uint8_t {
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.interrupt_disable = 1;
  return 2;
}

template <>
auto Sakura::HuC6280::CSL(std::unique_ptr<Processor> &processor) -> uint8_t {
  processor->m_registers.status.memory_operation = 0;
  processor->m_speed = Speed::Low;
  return 3;
}

template <>
auto Sakura::HuC6280::LDA_IMM(std::unique_ptr<Processor> &processor)
    -> uint8_t {
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  processor->m_registers.accumulator = imm;
  return 2;
}

#endif
