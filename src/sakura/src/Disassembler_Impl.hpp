#ifndef SAKURA_DISASSEMBLER_IMPL_HPP
#define SAKURA_DISASSEMBLER_IMPL_HPP

#include "Instructions.hpp"
#include "Memory.hpp"
#include "Processor.hpp"
#include <common/Bits.hpp>
#include <cstdint>
#include <fmt/core.h>
#include <memory>

using namespace Sakura::HuC6280;

template <>
auto Sakura::HuC6280::SEI(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "SEI", .length = 1};
}

template <>
auto Sakura::HuC6280::CSL(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "CLS", .length = 1};
}

template <>
auto Sakura::HuC6280::LDA_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("LDA #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::TAM_I(std::unique_ptr<Processor> &processor,
                            uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  int bit_position = Common::Bits::test_power_of_2(imm);

  return {.mnemonic = fmt::format("TAM{:d}", bit_position), .length = 2};
}

template <>
auto Sakura::HuC6280::LDA_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);

  return {.mnemonic = fmt::format("LDA {:#06x}  @{:#06x}={:#04x}", address,
                                  address, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::AND_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("AND #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::BEQ(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t destination = processor->m_registers.program_counter.value + 1 + imm;
  return {.mnemonic = fmt::format("BEQ {:#06x}", destination), .length = 2};
}

template <>
auto Sakura::HuC6280::CLD(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "CLD", .length = 1};
}

template <>
auto Sakura::HuC6280::CSH(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "CSH", .length = 1};
}

template <>
auto Sakura::HuC6280::LDX_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("LDX #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::TXS(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "TXS", .length = 1};
}

template <>
auto Sakura::HuC6280::STA_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("STA {:#04x}", zp), .length = 2};
}

template <>
auto Sakura::HuC6280::STA_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;

  return {.mnemonic = fmt::format("STA {:#06x}", address), .length = 3};
}

template <>
auto Sakura::HuC6280::STZ_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;

  return {.mnemonic = fmt::format("STZ {:#06x}", address), .length = 3};
}

template <>
auto Sakura::HuC6280::STZ_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("STZ {:#04x}", zp), .length = 2};
}

template <>
auto Sakura::HuC6280::TAI(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
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

  return {.mnemonic =
              fmt::format("TAI {:#04x}{:#04x}, {:#04x}{:#04x}, {:#04x}{:#04x}",
                          sh, sl, dh, dl, lh, ll),
          .length = 7};
}

template <>
auto Sakura::HuC6280::PHX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "PHX", .length = 1};
}

template <>
auto Sakura::HuC6280::PHY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "PHY", .length = 1};
}

template <>
auto Sakura::HuC6280::JSR(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;

  return {.mnemonic = fmt::format("JSR {:#06x}", address), .length = 3};
}

template <>
auto Sakura::HuC6280::TMA_I(std::unique_ptr<Processor> &processor,
                            uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  int bit_position = Common::Bits::test_power_of_2(imm);

  return {.mnemonic = fmt::format("TMA{:d}", bit_position), .length = 2};
}

template <>
auto Sakura::HuC6280::PHA(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "PHA", .length = 1};
}

template <>
auto Sakura::HuC6280::INC_ACC(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "INC A", .length = 1};
}

template <>
auto Sakura::HuC6280::ASL_ACC(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "ASL A", .length = 1};
}

template <>
auto Sakura::HuC6280::TAX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "TAX", .length = 1};
}

template <>
auto Sakura::HuC6280::JMP_ABS_X(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;

  uint16_t destination = processor->m_mapping_controller->load(
      address + processor->m_registers.x + 1);
  destination <<= 8;
  destination |=
      processor->m_mapping_controller->load(address + processor->m_registers.x);

  return {.mnemonic =
              fmt::format("JMP ({:#06x}, X)  {:#06x}", address, destination),
          .length = 3};
}

template <>
auto Sakura::HuC6280::SMB_I(std::unique_ptr<Processor> &processor,
                            uint8_t opcode) -> Disassembled {
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  uint16_t address = 0x2000 | zz;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t index = opcode & 0x70;
  index >>= 4;
  value |= 1UL << index;

  return {.mnemonic = fmt::format("SMB{:d} {:#04x}  @{:#06x}={:#04x}", index,
                                  zz, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::RMB_I(std::unique_ptr<Processor> &processor,
                            uint8_t opcode) -> Disassembled {
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  uint16_t address = 0x2000 | zz;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t index = opcode & 0x70;
  index >>= 4;
  value &= ~(1UL << index);

  return {.mnemonic = fmt::format("RMB{:d} {:#04x}  @{:#06x}={:#04x}", index,
                                  zz, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::STX_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;

  return {.mnemonic = fmt::format("STX {:#06x}", address), .length = 3};
}

template <>
auto Sakura::HuC6280::DEX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "DEX", .length = 1};
}

template <>
auto Sakura::HuC6280::BPL(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t destination = processor->m_registers.program_counter.value + 1 + imm;
  return {.mnemonic = fmt::format("BPL {:#06x}", destination), .length = 2};
}

template <>
auto Sakura::HuC6280::LDY_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("LDY #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::TYA(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "TYA", .length = 1};
}

template <>
auto Sakura::HuC6280::PLA(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "PLA", .length = 1};
}

template <>
auto Sakura::HuC6280::RST(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "RST", .length = 1};
}

template <>
auto Sakura::HuC6280::PLY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "PLY", .length = 1};
}

template <>
auto Sakura::HuC6280::PLX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "PLX", .length = 1};
}

template <>
auto Sakura::HuC6280::LDA_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  return {.mnemonic =
              fmt::format("LDA {:#04x}  @{:#06x}={:#04x}", zp, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::CLY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "CLY", .length = 1};
}

template <>
auto Sakura::HuC6280::NOP(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "NOP", .length = 1};
}

template <>
auto Sakura::HuC6280::LDA_ABS_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;

  uint16_t value =
      processor->m_mapping_controller->load(address + processor->m_registers.y);

  return {.mnemonic = fmt::format("LDA {:#06x}, Y  @{:#06x}={:#04x}", address,
                                  address, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::STA_ABS_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;

  return {.mnemonic = fmt::format("STA {:#06x}, Y @{:#06x}", address,
                                  address + processor->m_registers.y),
          .length = 3};
}

template <>
auto Sakura::HuC6280::ORA_ABS_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;
  uint16_t value =
      processor->m_mapping_controller->load(address + processor->m_registers.y);

  return {.mnemonic = fmt::format("ORA {:#06x}, Y @{:#06x}={:#04x}", address,
                                  address + processor->m_registers.y, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::EOR_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("EOR #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::EOR_ABS_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;
  uint16_t value =
      processor->m_mapping_controller->load(address + processor->m_registers.y);

  return {.mnemonic = fmt::format("EOR {:#06x}, Y @{:#06x}={:#04x}", address,
                                  address + processor->m_registers.y, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::AND_ABS_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;
  uint16_t value =
      processor->m_mapping_controller->load(address + processor->m_registers.y);

  return {.mnemonic = fmt::format("AND {:#06x}, Y @{:#06x}={:#04x}", address,
                                  address + processor->m_registers.y, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::INY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "INY", .length = 1};
}

template <>
auto Sakura::HuC6280::CPY_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("CPY #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::BCC(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t destination = processor->m_registers.program_counter.value + 1 + imm;
  return {.mnemonic = fmt::format("BCC {:#06x}", destination), .length = 2};
}

template <>
auto Sakura::HuC6280::CMP_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("CMP #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::BNE(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t destination = processor->m_registers.program_counter.value + 1 + imm;
  return {.mnemonic = fmt::format("BNE {:#06x}", destination), .length = 2};
}

template <>
auto Sakura::HuC6280::CLX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "CLX", .length = 1};
}

template <>
auto Sakura::HuC6280::LDA_ABS_X(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;

  uint16_t value =
      processor->m_mapping_controller->load(address + processor->m_registers.x);

  return {.mnemonic = fmt::format("LDA {:#06x}, X  @{:#06x}={:#04x}", address,
                                  address, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::INX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "INX", .length = 1};
}

template <>
auto Sakura::HuC6280::CPX_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("CPX #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::ST0(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("ST0 #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::DEY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "DEY", .length = 1};
}

template <>
auto Sakura::HuC6280::TAY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "TAY", .length = 1};
}

template <>
auto Sakura::HuC6280::LDY_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);

  return {.mnemonic = fmt::format("LDY {:#06x}  @{:#06x}={:#04x}", address,
                                  address, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::LDA_IND(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  uint16_t zp_address = 0x2000 | zz;
  uint16_t ll = processor->m_mapping_controller->load(zp_address);
  uint16_t hh = processor->m_mapping_controller->load(zp_address + 1);

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);
  return {.mnemonic = fmt::format("LDA ({:#04x})  @{:#06x}={:#04x}", zz,
                                  address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::STA_ABS_X(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;
  address += processor->m_registers.x;

  return {.mnemonic = fmt::format("STA {:#06x}, X  @{:#06x}", address, address),
          .length = 3};
}

template <>
auto Sakura::HuC6280::LDA_IND_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  uint16_t zp_address = 0x2000 | zz;
  uint16_t ll = processor->m_mapping_controller->load(zp_address);
  uint16_t hh = processor->m_mapping_controller->load(zp_address + 1);

  uint16_t address = hh << 8 | ll;
  address += processor->m_registers.y;
  uint8_t value = processor->m_mapping_controller->load(address);
  return {.mnemonic = fmt::format("LDA ({:#04x}), Y  @{:#06x}={:#04x}", zz,
                                  address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::CLC(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "CLC", .length = 1};
}

template <>
auto Sakura::HuC6280::ADC_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("ADC #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::STZ_ABS_X(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;
  address += processor->m_registers.x;

  return {.mnemonic = fmt::format("STZ {:#06x}, X  @{:#06x}", address, address),
          .length = 3};
}

template <>
auto Sakura::HuC6280::CPX_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  return {.mnemonic =
              fmt::format("CPX {:#04x}  @{:#06x}={:#04x}", zp, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::SEC(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "SEC", .length = 1};
}

template <>
auto Sakura::HuC6280::SBC_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("SBC #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::DEC_ACC(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "DEC A", .length = 1};
}

template <>
auto Sakura::HuC6280::ORA_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("ORA #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::CLI(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "CLI", .length = 1};
}

template <>
auto Sakura::HuC6280::JMP_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t destination = hh << 8 | ll;

  return {.mnemonic = fmt::format("JMP {:#06x}", destination), .length = 3};
}

template <>
auto Sakura::HuC6280::BRA(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t destination = processor->m_registers.program_counter.value + 1 + imm;
  return {.mnemonic = fmt::format("BRA {:#06x}", destination), .length = 2};
}

template <>
auto Sakura::HuC6280::ORA_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);
  return {.mnemonic =
              fmt::format("ORA {:#04x}  @{:#06x}={:#04x}", zp, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::STA_IND(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  uint16_t zp_address = 0x2000 | zz;
  uint16_t ll = processor->m_mapping_controller->load(zp_address);
  uint16_t hh = processor->m_mapping_controller->load(zp_address + 1);

  uint16_t address = hh << 8 | ll;
  return {.mnemonic = fmt::format("STA ({:#04x})  @{:#06x}", zz, address),
          .length = 2};
}

template <>
auto Sakura::HuC6280::STA_IND_Y(std::unique_ptr<Processor> &processor,
                                uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  uint16_t zp_address = 0x2000 | zz;
  uint16_t ll = processor->m_mapping_controller->load(zp_address);
  uint16_t hh = processor->m_mapping_controller->load(zp_address + 1);

  uint16_t address = hh << 8 | ll;
  address += processor->m_registers.y;
  return {.mnemonic = fmt::format("STA ({:#04x}), Y  @{:#06x}", zz, address),
          .length = 2};
}

template <>
auto Sakura::HuC6280::CLA(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "CLA", .length = 1};
}

template <>
auto Sakura::HuC6280::BCS(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t destination = processor->m_registers.program_counter.value + 1 + imm;
  return {.mnemonic = fmt::format("BCS {:#06x}", destination), .length = 2};
}

template <>
auto Sakura::HuC6280::ASL_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);
  return {.mnemonic =
              fmt::format("ASL {:#04x}  @{:#06x}={:#04x}", zp, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::ROL_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);
  return {.mnemonic =
              fmt::format("ROL {:#04x}  @{:#06x}={:#04x}", zp, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::ADC_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);
  return {.mnemonic =
              fmt::format("ADC {:#04x}  @{:#06x}={:#04x}", zp, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::ADC_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);

  return {.mnemonic = fmt::format("ADC {:#06x}  @{:#06x}={:#04x}", address,
                                  address, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::BSR(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t destination = processor->m_registers.program_counter.value + 1 + imm;
  return {.mnemonic = fmt::format("BSR {:#06x}", destination), .length = 2};
}

template <>
auto Sakura::HuC6280::BMI(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t destination = processor->m_registers.program_counter.value + 1 + imm;
  return {.mnemonic = fmt::format("BMI {:#06x}", destination), .length = 2};
}

template <>
auto Sakura::HuC6280::INC_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);
  return {.mnemonic =
              fmt::format("INC {:#04x}  @{:#06x}={:#04x}", zp, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::STA_ZP_X(std::unique_ptr<Processor> &processor,
                               uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  zp += processor->m_registers.x;

  uint16_t address = 0x2000 | zp;
  return {.mnemonic = fmt::format("STA {:#04x}, X  @{:#06x}", zp, address),
          .length = 2};
}

template <>
auto Sakura::HuC6280::STX_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("STX {:#04x}", zp), .length = 2};
}

template <>
auto Sakura::HuC6280::ASL_ZP_X(std::unique_ptr<Processor> &processor,
                               uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  zp += processor->m_registers.x;
  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);
  return {.mnemonic = fmt::format("ASL {:#04x}, X  @{:#06x}={:#04x}", zp,
                                  address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::DEC_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);
  return {.mnemonic =
              fmt::format("DEC {:#04x}  @{:#06x}={:#04x}", zp, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::LSR_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);
  return {.mnemonic =
              fmt::format("LSR {:#04x}  @{:#06x}={:#04x}", zp, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::PHP(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "PHP", .length = 1};
}

template <>
auto Sakura::HuC6280::PLP(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "PLP", .length = 1};
}

template <>
auto Sakura::HuC6280::LDX_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  return {.mnemonic =
              fmt::format("LDX {:#04x}  @{:#06x}={:#04x}", zp, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::INC_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;
  uint16_t value = processor->m_mapping_controller->load(address);

  return {.mnemonic = fmt::format("INC {:#06x} @{:#06x}={:#04x}", address,
                                  address, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::LDX_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);

  return {.mnemonic = fmt::format("LDX {:#06x}  @{:#06x}={:#04x}", address,
                                  address, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::LDY_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t address = 0x2000 | zp;
  uint8_t value = processor->m_mapping_controller->load(address);

  return {.mnemonic =
              fmt::format("LDY {:#04x}  @{:#06x}={:#04x}", zp, address, value),
          .length = 2};
}

template <>
auto Sakura::HuC6280::SAY(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "SAY", .length = 1};
}

template <>
auto Sakura::HuC6280::RTI(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "RTI", .length = 1};
}

template <>
auto Sakura::HuC6280::BBR_I(std::unique_ptr<Processor> &processor,
                            uint8_t opcode) -> Disassembled {
  uint8_t zz = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  uint16_t address = 0x2000 | zz;
  uint8_t value = processor->m_mapping_controller->load(address);

  uint8_t index = opcode & 0x70;
  index >>= 4;

  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);
  uint16_t destination = processor->m_registers.program_counter.value + 2 + imm;

  return {.mnemonic = fmt::format("BBR{:d} {:#04x} {:#06x}  @{:#06x}={:#04x}",
                                  index, zz, destination, address, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::BIT_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = fmt::format("BIT #{:#04x}", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::CMP_ABS(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint16_t ll = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t hh = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value + 1);

  uint16_t address = hh << 8 | ll;
  uint8_t value = processor->m_mapping_controller->load(address);

  return {.mnemonic = fmt::format("CMP {:#06x}  @{:#06x}={:#04x}", address,
                                  address, value),
          .length = 3};
}

#endif
