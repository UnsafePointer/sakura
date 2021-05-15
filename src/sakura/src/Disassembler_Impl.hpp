#ifndef SAKURA_DISASSEMBLER_IMPL_HPP
#define SAKURA_DISASSEMBLER_IMPL_HPP

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
    -> Disassembled {
  (void)processor;
  return {.mnemonic = "SEI", .length = 1};
}

template <>
auto Sakura::HuC6280::CSL(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  (void)processor;
  return {.mnemonic = "CLS", .length = 1};
}

template <>
auto Sakura::HuC6280::LDA_IMM(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = Common::Formatter::format("LDA #%02x", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::TAM_I(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  int bit_position = Common::Bits::test_power_of_2(imm);

  return {.mnemonic = Common::Formatter::format("TAM%d", bit_position),
          .length = 2};
}

template <>
auto Sakura::HuC6280::LDA_ABS(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);

  return {.mnemonic = Common::Formatter::format("LDA %02x%02x  @%04x=%02x", hh,
                                                ll, address, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::AND_IMM(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = Common::Formatter::format("AND #%02x", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::BEQ(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t destination = processor->m_registers.program_counter.value + 1 + imm;
  return {.mnemonic = Common::Formatter::format("BEQ %04x", destination),
          .length = 2};
}

template <>
auto Sakura::HuC6280::CLD(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  (void)processor;
  return {.mnemonic = "CLD", .length = 1};
}

template <>
auto Sakura::HuC6280::CSH(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  (void)processor;
  return {.mnemonic = "CSH", .length = 1};
}

template <>
auto Sakura::HuC6280::LDX_IMM(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = Common::Formatter::format("LDX #%02x", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::TXS(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  (void)processor;
  return {.mnemonic = "TXS", .length = 1};
}

template <>
auto Sakura::HuC6280::STA_ZP(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = Common::Formatter::format("STA %02x", zp), .length = 2};
}

template <>
auto Sakura::HuC6280::STA_ABS(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;

  return {.mnemonic = Common::Formatter::format("STA %04x", address),
          .length = 3};
}

template <>
auto Sakura::HuC6280::STZ_ABS(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;

  return {.mnemonic = Common::Formatter::format("STZ %04x", address),
          .length = 3};
}

template <>
auto Sakura::HuC6280::STZ_ZP(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = Common::Formatter::format("STZ %02x", zp), .length = 2};
}

template <>
auto Sakura::HuC6280::TAI(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  uint8_t sl = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint8_t sh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint8_t dl = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 2);
  uint8_t dh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 3);

  uint8_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 4);
  uint8_t lh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 5);

  return {.mnemonic = Common::Formatter::format(
              "TAI %02x%02x, %02x%02x, %02x%02x", sh, sl, dh, dl, lh, ll),
          .length = 7};
}

template <>
auto Sakura::HuC6280::PHX(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  (void)processor;
  return {.mnemonic = "PHX", .length = 1};
}

template <>
auto Sakura::HuC6280::PHY(std::unique_ptr<Processor> &processor)
    -> Disassembled {
  (void)processor;
  return {.mnemonic = "PHY", .length = 1};
}

#endif
