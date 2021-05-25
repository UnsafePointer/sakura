#ifndef SAKURA_INSTRUCTIONS_IMPL_HPP
#define SAKURA_INSTRUCTIONS_IMPL_HPP

#include "Memory.hpp"
#include "Processor.hpp"
#include <common/Bits.hpp>
#include <cstdint>
#include <memory>
#include <spdlog/spdlog.h>

using namespace Sakura::HuC6280;

template <>
auto Sakura::HuC6280::SEI(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.interrupt_disable = 1;
  return 2;
}

template <>
auto Sakura::HuC6280::CSL(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_speed = Speed::Low;

  processor->m_registers.status.memory_operation = 0;
  return 3;
}

template <>
auto Sakura::HuC6280::LDA_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
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
auto Sakura::HuC6280::TAM_I(std::unique_ptr<Processor> &processor,
                            uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  int bit_position = Common::Bits::test_power_of_2(imm);
  if (bit_position == -1) {
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format("Invalid TAMi argument: {:#04x}", imm));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }

  processor->m_mapping_controller->set_mapping_register(
      bit_position, processor->m_registers.accumulator);

  processor->m_registers.status.memory_operation = 0;
  return 5;
}

template <>
auto Sakura::HuC6280::LDA_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
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
auto Sakura::HuC6280::AND_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  if (processor->m_registers.status.memory_operation) {
    spdlog::get(LOGGER_NAME)->critical("Unhandled AND (IMM) with T flag set");
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
auto Sakura::HuC6280::BEQ(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
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
auto Sakura::HuC6280::CLD(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.decimal = 0;
  return 2;
}

template <>
auto Sakura::HuC6280::CSH(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_speed = Speed::High;

  processor->m_registers.status.memory_operation = 0;
  return 3;
}

template <>
auto Sakura::HuC6280::LDX_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
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
auto Sakura::HuC6280::TXS(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.stack_pointer = processor->m_registers.x;

  processor->m_registers.status.memory_operation = 0;
  return 2;
}

template <>
auto Sakura::HuC6280::STA_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
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
auto Sakura::HuC6280::STA_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
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
auto Sakura::HuC6280::STZ_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
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
auto Sakura::HuC6280::STZ_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  processor->m_mapping_controller->store(address, 0x00);

  processor->m_registers.status.memory_operation = 0;
  return 4;
}

template <>
auto Sakura::HuC6280::TAI(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
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

template <>
auto Sakura::HuC6280::PHX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->push_into_stack(processor->m_registers.x);
  processor->m_registers.status.memory_operation = 0;
  return 3;
}

template <>
auto Sakura::HuC6280::PHY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->push_into_stack(processor->m_registers.y);
  processor->m_registers.status.memory_operation = 0;
  return 3;
}

template <>
auto Sakura::HuC6280::JSR(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  processor->push_into_stack(
      processor->m_registers.program_counter.program_counter_high);
  processor->push_into_stack(
      processor->m_registers.program_counter.program_counter_low);

  uint16_t address = hh << 8 | ll;
  processor->m_registers.program_counter.value = address;

  processor->m_registers.status.memory_operation = 0;
  return 7;
}

template <>
auto Sakura::HuC6280::TMA_I(std::unique_ptr<Processor> &processor,
                            uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  int bit_position = Common::Bits::test_power_of_2(imm);
  if (bit_position == -1) {
    spdlog::get(LOGGER_NAME)
        ->critical(fmt::format("Invalid TMAi argument: {:#04x}", imm));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }

  uint8_t value =
      processor->m_mapping_controller->mapping_register(bit_position);
  processor->m_registers.accumulator = value;

  processor->m_registers.status.memory_operation = 0;
  return 4;
}

template <>
auto Sakura::HuC6280::PHA(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->push_into_stack(processor->m_registers.accumulator);
  processor->m_registers.status.memory_operation = 0;
  return 3;
}

template <>
auto Sakura::HuC6280::INC_ACC(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  processor->m_registers.accumulator++;

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::ASL_ACC(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t carry = processor->m_registers.accumulator >> 7 & 0b1;
  processor->m_registers.accumulator <<= 1;

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  processor->m_registers.status.carry = carry;
  return 2;
}

template <>
auto Sakura::HuC6280::TAX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.x = processor->m_registers.accumulator;

  processor->m_registers.status.negative =
      (processor->m_registers.x >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.x == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::JMP_ABS_X(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  processor->m_registers.program_counter.program_counter_low =
      processor->m_mapping_controller->load(address + processor->m_registers.x);
  processor->m_registers.program_counter.program_counter_high =
      processor->m_mapping_controller->load(address + processor->m_registers.x +
                                            1);

  processor->m_registers.status.memory_operation = 0;
  return 7;
}

template <>
auto Sakura::HuC6280::SMB_I(std::unique_ptr<Processor> &processor,
                            uint8_t opcode) -> uint8_t {
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zz;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t index = opcode & 0x70;
  index >>= 4;
  value |= 1UL << index;

  processor->m_mapping_controller->store(address, value);

  processor->m_registers.status.memory_operation = 0;
  return 7;
}

template <>
auto Sakura::HuC6280::RMB_I(std::unique_ptr<Processor> &processor,
                            uint8_t opcode) -> uint8_t {
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zz;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t index = opcode & 0x70;
  index >>= 4;
  value &= ~(1UL << index);

  processor->m_mapping_controller->store(address, value);

  processor->m_registers.status.memory_operation = 0;
  return 7;
}

template <>
auto Sakura::HuC6280::STX_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  processor->m_mapping_controller->store(address, processor->m_registers.x);

  processor->m_registers.status.memory_operation = 0;
  return 5;
}

template <>
auto Sakura::HuC6280::DEX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.x--;

  processor->m_registers.status.negative =
      (processor->m_registers.x >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.x == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::BPL(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t cycles = 2;
  if (processor->m_registers.status.negative == 0) {
    cycles += 2;
    processor->m_registers.program_counter.value += imm;
  }

  processor->m_registers.status.memory_operation = 0;
  return cycles;
}

template <>
auto Sakura::HuC6280::LDY_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  processor->m_registers.y = imm;

  processor->m_registers.status.negative = (imm >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = imm == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::TYA(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.accumulator = processor->m_registers.y;

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::PLA(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.accumulator = processor->pop_from_stack();

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 4;
}

template <>
auto Sakura::HuC6280::RST(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.program_counter.program_counter_low =
      processor->pop_from_stack();
  processor->m_registers.program_counter.program_counter_high =
      processor->pop_from_stack();

  processor->m_registers.status.memory_operation = 0;
  return 7;
}

template <>
auto Sakura::HuC6280::PLY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.y = processor->pop_from_stack();

  processor->m_registers.status.negative =
      (processor->m_registers.y >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.y == 0;
  return 4;
}

template <>
auto Sakura::HuC6280::PLX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.x = processor->pop_from_stack();

  processor->m_registers.status.negative =
      (processor->m_registers.x >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.x == 0;
  return 4;
}

template <>
auto Sakura::HuC6280::LDA_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  processor->m_registers.accumulator =
      processor->m_mapping_controller->load(address);

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 4;
}

template <>
auto Sakura::HuC6280::CLY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.y = 0x0;

  processor->m_registers.status.memory_operation = 0;
  return 2;
}

template <>
auto Sakura::HuC6280::NOP(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  (void)processor;

  processor->m_registers.status.memory_operation = 0;
  return 2;
}

template <>
auto Sakura::HuC6280::LDA_ABS_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  processor->m_registers.accumulator =
      processor->m_mapping_controller->load(address + processor->m_registers.y);

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 5;
}

template <>
auto Sakura::HuC6280::STA_ABS_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  processor->m_mapping_controller->store(address + processor->m_registers.y,
                                         processor->m_registers.accumulator);

  processor->m_registers.status.memory_operation = 0;
  return 5;
}

template <>
auto Sakura::HuC6280::ORA_ABS_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> uint8_t {
  (void)opcode;
  if (processor->m_registers.status.memory_operation) {
    spdlog::get(LOGGER_NAME)
        ->critical("Unhandled ORA (ABS, Y) with T flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  uint8_t value =
      processor->m_mapping_controller->load(address + processor->m_registers.y);
  processor->m_registers.accumulator |= value;

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 5;
}

template <>
auto Sakura::HuC6280::EOR_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  if (processor->m_registers.status.memory_operation) {
    spdlog::get(LOGGER_NAME)->critical("Unhandled EOR (IMM) with T flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  processor->m_registers.accumulator ^= imm;

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::EOR_ABS_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> uint8_t {
  (void)opcode;
  if (processor->m_registers.status.memory_operation) {
    spdlog::get(LOGGER_NAME)
        ->critical("Unhandled EOR (ABS, Y) with T flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  uint8_t value =
      processor->m_mapping_controller->load(address + processor->m_registers.y);
  processor->m_registers.accumulator ^= value;

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 5;
}

template <>
auto Sakura::HuC6280::AND_ABS_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> uint8_t {
  (void)opcode;
  if (processor->m_registers.status.memory_operation) {
    spdlog::get(LOGGER_NAME)
        ->critical("Unhandled AND (ABS, Y) with T flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  uint8_t value =
      processor->m_mapping_controller->load(address + processor->m_registers.y);
  processor->m_registers.accumulator &= value;

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 5;
}

template <>
auto Sakura::HuC6280::INY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.y++;

  processor->m_registers.status.negative =
      (processor->m_registers.y >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.y == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::CPY_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t result = processor->m_registers.y - imm;

  processor->m_registers.status.negative = (result >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = result == 0;
  processor->m_registers.status.carry = processor->m_registers.y >= imm;
  return 2;
}

template <>
auto Sakura::HuC6280::BCC(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t cycles = 2;
  if (processor->m_registers.status.carry == 0) {
    cycles += 2;
    processor->m_registers.program_counter.value += imm;
  }

  processor->m_registers.status.memory_operation = 0;
  return cycles;
}

template <>
auto Sakura::HuC6280::CMP_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t result = processor->m_registers.accumulator - imm;

  processor->m_registers.status.negative = (result >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = result == 0;
  processor->m_registers.status.carry =
      processor->m_registers.accumulator >= imm;
  return 2;
}

template <>
auto Sakura::HuC6280::BNE(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t cycles = 2;
  if (processor->m_registers.status.zero == 0) {
    cycles += 2;
    processor->m_registers.program_counter.value += imm;
  }

  processor->m_registers.status.memory_operation = 0;
  return cycles;
}

template <>
auto Sakura::HuC6280::CLX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.x = 0x0;

  processor->m_registers.status.memory_operation = 0;
  return 2;
}

template <>
auto Sakura::HuC6280::LDA_ABS_X(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  processor->m_registers.accumulator =
      processor->m_mapping_controller->load(address + processor->m_registers.x);

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 5;
}

template <>
auto Sakura::HuC6280::INX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.x++;

  processor->m_registers.status.negative =
      (processor->m_registers.x >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.x == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::CPX_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t result = processor->m_registers.x - imm;

  processor->m_registers.status.negative = (result >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = result == 0;
  processor->m_registers.status.carry = processor->m_registers.x >= imm;
  return 2;
}

template <>
auto Sakura::HuC6280::ST0(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint32_t address = 0x001FE000;
  processor->m_mapping_controller->store_video_display_controller(address, imm);

  processor->m_registers.status.memory_operation = 0;
  return 4;
}

template <>
auto Sakura::HuC6280::DEY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.y--;

  processor->m_registers.status.negative =
      (processor->m_registers.y >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.y == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::TAY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.y = processor->m_registers.accumulator;

  processor->m_registers.status.negative =
      (processor->m_registers.y >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.y == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::LDY_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);
  processor->m_registers.y = value;

  processor->m_registers.status.negative = (value >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = value == 0;
  return 5;
}

template <>
auto Sakura::HuC6280::LDA_IND(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t zp_address = 0x2000 | zz;
  uint16_t ll = processor->m_registers.accumulator =
      processor->m_mapping_controller->load(zp_address);
  uint16_t hh = processor->m_registers.accumulator =
      processor->m_mapping_controller->load(zp_address + 1);

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);
  processor->m_registers.accumulator = value;

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 7;
}

template <>
auto Sakura::HuC6280::STA_ABS_X(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  processor->m_mapping_controller->store(address + processor->m_registers.x,
                                         processor->m_registers.accumulator);

  processor->m_registers.status.memory_operation = 0;
  return 5;
}

template <>
auto Sakura::HuC6280::LDA_IND_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t zp_address = 0x2000 | zz;
  uint16_t ll = processor->m_registers.accumulator =
      processor->m_mapping_controller->load(zp_address);
  uint16_t hh = processor->m_registers.accumulator =
      processor->m_mapping_controller->load(zp_address + 1);

  uint16_t address = hh << 8 | ll;
  address += processor->m_registers.y;
  uint8_t value = processor->m_mapping_controller->load(address);
  processor->m_registers.accumulator = value;

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 7;
}

template <>
auto Sakura::HuC6280::CLC(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.carry = 0;
  return 2;
}

template <>
auto Sakura::HuC6280::ADC_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  if (processor->m_registers.status.memory_operation) {
    spdlog::get(LOGGER_NAME)->critical("Unhandled ADC (IMM) with T flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  if (processor->m_registers.status.decimal) {
    spdlog::get(LOGGER_NAME)->critical("Unhandled ADC (IMM) with D flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t result = processor->m_registers.accumulator + imm +
                   processor->m_registers.status.carry;
  auto carry = static_cast<uint8_t>(
      ((((uint16_t)processor->m_registers.accumulator & 0xFF) +
        ((uint16_t)imm & 0xFF) +
        ((uint16_t)processor->m_registers.status.carry & 0x1)) &
       0x100) == 0x100);
  processor->m_registers.accumulator = result;

  processor->m_registers.status.negative = (result >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = result == 0;
  processor->m_registers.status.carry = carry;
  return 2;
}

template <>
auto Sakura::HuC6280::STZ_ABS_X(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  processor->m_mapping_controller->store(address + processor->m_registers.x,
                                         0x0);

  processor->m_registers.status.memory_operation = 0;
  return 5;
}

template <>
auto Sakura::HuC6280::CPX_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t result = processor->m_registers.x - value;

  processor->m_registers.status.negative = (result >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = result == 0;
  processor->m_registers.status.carry = processor->m_registers.x >= value;
  return 4;
}

template <>
auto Sakura::HuC6280::SEC(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.carry = 1;
  return 2;
}

template <>
auto Sakura::HuC6280::SBC_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  if (processor->m_registers.status.memory_operation) {
    spdlog::get(LOGGER_NAME)->critical("Unhandled SBC (IMM) with T flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  if (processor->m_registers.status.decimal) {
    spdlog::get(LOGGER_NAME)->critical("Unhandled SBC (IMM) with D flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t result = processor->m_registers.accumulator -
                   (imm + processor->m_registers.status.carry);
  auto carry =
      static_cast<uint8_t>(processor->m_registers.accumulator <
                           (imm + processor->m_registers.status.carry));
  processor->m_registers.accumulator = result;

  processor->m_registers.status.negative = (result >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = result == 0;
  processor->m_registers.status.carry = carry;
  return 2;
}

template <>
auto Sakura::HuC6280::DEC_ACC(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  processor->m_registers.accumulator--;

  processor->m_registers.status.negative =
      (processor->m_registers.accumulator >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.accumulator == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::ORA_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  if (processor->m_registers.status.memory_operation) {
    spdlog::get(LOGGER_NAME)->critical("Unhandled ORA (IMM) with T flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint8_t result = processor->m_registers.accumulator | imm;
  processor->m_registers.accumulator = result;

  processor->m_registers.status.negative = (result >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = result == 0;
  return 2;
}

template <>
auto Sakura::HuC6280::CLI(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.interrupt_disable = 0;
  return 2;
}

template <>
auto Sakura::HuC6280::JMP_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  processor->m_registers.program_counter.program_counter_low = ll;
  processor->m_registers.program_counter.program_counter_high = hh;

  processor->m_registers.status.memory_operation = 0;
  return 4;
}

template <>
auto Sakura::HuC6280::BRA(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  processor->m_registers.program_counter.value += imm;

  processor->m_registers.status.memory_operation = 0;
  return 4;
}

template <>
auto Sakura::HuC6280::ORA_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  if (processor->m_registers.status.memory_operation) {
    spdlog::get(LOGGER_NAME)->critical("Unhandled ORA (ZP) with T flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t result = processor->m_registers.accumulator | value;
  processor->m_registers.accumulator = result;

  processor->m_registers.status.negative = (result >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = result == 0;
  return 4;
}

template <>
auto Sakura::HuC6280::STA_IND(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t zp_address = 0x2000 | zz;
  uint16_t ll = processor->m_registers.accumulator =
      processor->m_mapping_controller->load(zp_address);
  uint16_t hh = processor->m_registers.accumulator =
      processor->m_mapping_controller->load(zp_address + 1);

  uint16_t address = hh << 8 | ll;
  processor->m_mapping_controller->store(address,
                                         processor->m_registers.accumulator);

  processor->m_registers.status.memory_operation = 0;
  return 7;
}

template <>
auto Sakura::HuC6280::STA_IND_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t zp_address = 0x2000 | zz;
  uint16_t ll = processor->m_registers.accumulator =
      processor->m_mapping_controller->load(zp_address);
  uint16_t hh = processor->m_registers.accumulator =
      processor->m_mapping_controller->load(zp_address + 1);

  uint16_t address = hh << 8 | ll;
  address += processor->m_registers.y;
  processor->m_mapping_controller->store(address,
                                         processor->m_registers.accumulator);

  processor->m_registers.status.memory_operation = 0;
  return 7;
}

template <>
auto Sakura::HuC6280::CLA(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.accumulator = 0x0;

  processor->m_registers.status.memory_operation = 0;
  return 2;
}

template <>
auto Sakura::HuC6280::BCS(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t cycles = 2;
  if (processor->m_registers.status.carry) {
    cycles += 2;
    processor->m_registers.program_counter.value += imm;
  }

  processor->m_registers.status.memory_operation = 0;
  return cycles;
}

template <>
auto Sakura::HuC6280::ASL_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t carry = value >> 7 & 0b1;
  value <<= 1;

  processor->m_mapping_controller->store(address, value);

  processor->m_registers.status.negative = (value >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = value == 0;
  processor->m_registers.status.carry = carry;
  return 6;
}

template <>
auto Sakura::HuC6280::ROL_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t carry = value >> 7 & 0b1;
  value <<= 1;
  value |= processor->m_registers.status.carry;

  processor->m_mapping_controller->store(address, value);

  processor->m_registers.status.negative = (value >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = value == 0;
  processor->m_registers.status.carry = carry;
  return 6;
}

template <>
auto Sakura::HuC6280::ADC_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  if (processor->m_registers.status.memory_operation) {
    spdlog::get(LOGGER_NAME)->critical("Unhandled ADC (IMM) with T flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  if (processor->m_registers.status.decimal) {
    spdlog::get(LOGGER_NAME)->critical("Unhandled ADC (IMM) with D flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t result = processor->m_registers.accumulator + value +
                   processor->m_registers.status.carry;
  auto carry = static_cast<uint8_t>(
      ((((uint16_t)processor->m_registers.accumulator & 0xFF) +
        ((uint16_t)value & 0xFF) +
        ((uint16_t)processor->m_registers.status.carry & 0x1)) &
       0x100) == 0x100);
  processor->m_registers.accumulator = result;

  processor->m_registers.status.negative = (result >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = result == 0;
  processor->m_registers.status.carry = carry;
  return 4;
}

template <>
auto Sakura::HuC6280::ADC_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  if (processor->m_registers.status.memory_operation) {
    spdlog::get(LOGGER_NAME)->critical("Unhandled ADC (IMM) with T flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  if (processor->m_registers.status.decimal) {
    spdlog::get(LOGGER_NAME)->critical("Unhandled ADC (IMM) with D flag set");
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t result = processor->m_registers.accumulator + value +
                   processor->m_registers.status.carry;
  auto carry = static_cast<uint8_t>(
      ((((uint16_t)processor->m_registers.accumulator & 0xFF) +
        ((uint16_t)value & 0xFF) +
        ((uint16_t)processor->m_registers.status.carry & 0x1)) &
       0x100) == 0x100);
  processor->m_registers.accumulator = result;

  processor->m_registers.status.negative = (result >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = result == 0;
  processor->m_registers.status.carry = carry;
  return 5;
}

template <>
auto Sakura::HuC6280::BSR(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  int8_t rr = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  processor->push_into_stack(
      processor->m_registers.program_counter.program_counter_high);
  processor->push_into_stack(
      processor->m_registers.program_counter.program_counter_low);

  processor->m_registers.program_counter.value += rr;

  processor->m_registers.status.memory_operation = 0;
  return 8;
}

template <>
auto Sakura::HuC6280::BMI(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint8_t cycles = 2;
  if (processor->m_registers.status.negative == 1) {
    cycles += 2;
    processor->m_registers.program_counter.value += imm;
  }

  processor->m_registers.status.memory_operation = 0;
  return cycles;
}

template <>
auto Sakura::HuC6280::INC_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  value++;

  processor->m_mapping_controller->store(address, value);

  processor->m_registers.status.negative = (value >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = value == 0;
  return 6;
}

template <>
auto Sakura::HuC6280::STA_ZP_X(std::unique_ptr<Processor> &processor,
                               uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  zp += processor->m_registers.x;

  uint16_t address = 0x2000 | zp;
  processor->m_mapping_controller->store(address,
                                         processor->m_registers.accumulator);

  processor->m_registers.status.memory_operation = 0;
  return 4;
}

template <>
auto Sakura::HuC6280::STX_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  processor->m_mapping_controller->store(address, processor->m_registers.x);

  processor->m_registers.status.memory_operation = 0;
  return 4;
}

template <>
auto Sakura::HuC6280::ASL_ZP_X(std::unique_ptr<Processor> &processor,
                               uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  zp += processor->m_registers.x;

  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t carry = value >> 7 & 0b1;
  value <<= 1;

  processor->m_mapping_controller->store(address, value);

  processor->m_registers.status.negative = (value >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = value == 0;
  processor->m_registers.status.carry = carry;
  return 6;
}

template <>
auto Sakura::HuC6280::DEC_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  value--;

  processor->m_mapping_controller->store(address, value);

  processor->m_registers.status.negative = (value >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = value == 0;
  return 6;
}

template <>
auto Sakura::HuC6280::LSR_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t carry = value & 0b1;
  value >>= 1;

  processor->m_mapping_controller->store(address, value);

  processor->m_registers.status.negative = (value >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = value == 0;
  processor->m_registers.status.carry = carry;
  return 6;
}

template <>
auto Sakura::HuC6280::PHP(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->push_into_stack(processor->m_registers.status.value);
  processor->m_registers.status.memory_operation = 0;
  return 3;
}

template <>
auto Sakura::HuC6280::PLP(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.status.value = processor->pop_from_stack();

  return 4;
}

template <>
auto Sakura::HuC6280::LDX_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  processor->m_registers.x = processor->m_mapping_controller->load(address);

  processor->m_registers.status.negative =
      (processor->m_registers.x >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.x == 0;
  return 4;
}

template <>
auto Sakura::HuC6280::INC_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);
  value++;
  processor->m_mapping_controller->store(address, value);

  processor->m_registers.status.negative = (value >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = value == 0;
  return 7;
}

template <>
auto Sakura::HuC6280::LDX_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);
  processor->m_registers.x = value;

  processor->m_registers.status.negative = (value >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = value == 0;
  return 5;
}

template <>
auto Sakura::HuC6280::LDY_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> uint8_t {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  processor->m_registers.y = processor->m_mapping_controller->load(address);

  processor->m_registers.status.negative =
      (processor->m_registers.y >> 7) & 0b1;
  processor->m_registers.status.memory_operation = 0;
  processor->m_registers.status.zero = processor->m_registers.y == 0;
  return 4;
}

template <>
auto Sakura::HuC6280::SAY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  uint8_t accumulator = processor->m_registers.accumulator;
  processor->m_registers.accumulator = processor->m_registers.y;
  processor->m_registers.y = accumulator;

  processor->m_registers.status.memory_operation = 0;
  return 3;
}

template <>
auto Sakura::HuC6280::RTI(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> uint8_t {
  (void)opcode;
  processor->m_registers.status.value = processor->pop_from_stack();
  processor->m_registers.program_counter.program_counter_low =
      processor->pop_from_stack();
  processor->m_registers.program_counter.program_counter_high =
      processor->pop_from_stack();

  return 7;
}

template <>
auto Sakura::HuC6280::BBR_I(std::unique_ptr<Processor> &processor,
                            uint8_t opcode) -> uint8_t {
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;

  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  processor->m_registers.program_counter.value += 1;
  uint16_t destination = processor->m_registers.program_counter.value + imm;

  uint8_t index = opcode & 0x70;
  index >>= 4;

  uint8_t cycles = 6;
  if (((value >> index) & 1U) == 0) {
    processor->m_registers.program_counter.value = destination;
    cycles += 2;
  }

  processor->m_registers.status.memory_operation = 0;
  return cycles;
}

#endif
