#ifndef SAKURA_INSTRUCTIONS_IMPL_HPP
#define SAKURA_INSTRUCTIONS_IMPL_HPP

#include "Memory.hpp"
#include "Processor.hpp"
#include <common/Bits.hpp>
#include <common/Formatter.hpp>
#include <cstdint>
#include <iostream>
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
  processor->m_speed = Speed::Low;

  processor->m_registers.status.memory_operation = 0;
  return 3;
}

template <>
auto Sakura::HuC6280::LDA_IMM(std::unique_ptr<Processor> &processor)
    -> uint8_t {
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  processor->m_registers.accumulator = imm;

  processor->m_registers.status.negative = (imm >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = imm == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::TAM_I(std::unique_ptr<Processor> &processor) -> uint8_t {
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  int bit_position = Common::Bits::test_power_of_2(imm);
  if (bit_position == -1) {
    std::cout << Common::Formatter::format("Invalid TAMi argument: %02x", imm)
              << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }

  processor->m_mapping_controller->set_mapping_register(
      bit_position, processor->m_registers.accumulator);

  processor->m_registers.status.memory_operation = 0;
  return 5;
}

template <>
auto Sakura::HuC6280::LDA_ABS(std::unique_ptr<Processor> &processor)
    -> uint8_t {
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);
  processor->m_registers.accumulator = value;

  processor->m_registers.status.negative = (value >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = value == 0;
  return 5;
}

template <>
auto Sakura::HuC6280::AND_IMM(std::unique_ptr<Processor> &processor)
    -> uint8_t {
  if (processor->m_registers.status.memory_operation) {
    std::cout << "Unhandled AND (IMM) with T flag set" << std::endl;
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint8_t result = processor->m_registers.accumulator & imm;
  processor->m_registers.accumulator = result;

  processor->m_registers.status.negative = (result >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = result == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::BEQ(std::unique_ptr<Processor> &processor) -> uint8_t {
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t cycles = 2;
  if (processor->m_registers.status.zero) {
    cycles += 2;
    processor->m_registers.program_counter.value += imm;
  }

  processor->m_registers.status.memory_operation = 0;
  return cycles;
}

template <>
auto Sakura::HuC6280::CLD(std::unique_ptr<Processor> &processor) -> uint8_t {
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.decimal = 0;
  return 2;
}

template <>
auto Sakura::HuC6280::CSH(std::unique_ptr<Processor> &processor) -> uint8_t {
  processor->m_speed = Speed::High;

  processor->m_registers.status.memory_operation = 0;
  return 3;
}

template <>
auto Sakura::HuC6280::LDX_IMM(std::unique_ptr<Processor> &processor)
    -> uint8_t {
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  processor->m_registers.x = imm;

  processor->m_registers.status.negative = (imm >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = imm == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::TXS(std::unique_ptr<Processor> &processor) -> uint8_t {
  processor->m_registers.stack_pointer = processor->m_registers.x;

  processor->m_registers.status.memory_operation = 0;
  return 2;
}

template <>
auto Sakura::HuC6280::STA_ZP(std::unique_ptr<Processor> &processor) -> uint8_t {
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  processor->m_mapping_controller->store(address,
                                         processor->m_registers.accumulator);

  processor->m_registers.status.memory_operation = 0;
  return 4;
}

template <>
auto Sakura::HuC6280::STA_ABS(std::unique_ptr<Processor> &processor)
    -> uint8_t {
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  processor->m_mapping_controller->store(address,
                                         processor->m_registers.accumulator);

  processor->m_registers.status.memory_operation = 0;
  return 5;
}

template <>
auto Sakura::HuC6280::STZ_ABS(std::unique_ptr<Processor> &processor)
    -> uint8_t {
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  processor->m_mapping_controller->store(address, 0x00);

  processor->m_registers.status.memory_operation = 0;
  return 5;
}

template <>
auto Sakura::HuC6280::STZ_ZP(std::unique_ptr<Processor> &processor) -> uint8_t {
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  processor->m_mapping_controller->store(address, 0x00);

  processor->m_registers.status.memory_operation = 0;
  return 4;
}

template <>
auto Sakura::HuC6280::TAI(std::unique_ptr<Processor> &processor) -> uint8_t {
  uint8_t sl = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint8_t sh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t dl = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint8_t dh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint8_t lh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t total_length =
      processor->execute_block_transfer(sl, sh, dl, dh, ll, lh);
  processor->m_registers.status.memory_operation = 0;
  return 17 + 6 * total_length;
}

#endif
