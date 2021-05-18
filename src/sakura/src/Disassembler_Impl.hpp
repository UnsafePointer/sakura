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
  return {.mnemonic = Common::Formatter::format("LDA #%02x", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::TAM_I(std::unique_ptr<Processor> &processor,
                            uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  int bit_position = Common::Bits::test_power_of_2(imm);

  return {.mnemonic = Common::Formatter::format("TAM%d", bit_position),
          .length = 2};
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

  return {.mnemonic = Common::Formatter::format("LDA %02x%02x  @%04x=%02x", hh,
                                                ll, address, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::AND_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = Common::Formatter::format("AND #%02x", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::BEQ(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t destination = processor->m_registers.program_counter.value + 1 + imm;
  return {.mnemonic = Common::Formatter::format("BEQ %04x", destination),
          .length = 2};
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
  return {.mnemonic = Common::Formatter::format("LDX #%02x", imm), .length = 2};
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
  return {.mnemonic = Common::Formatter::format("STA %02x", zp), .length = 2};
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

  return {.mnemonic = Common::Formatter::format("STA %04x", address),
          .length = 3};
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

  return {.mnemonic = Common::Formatter::format("STZ %04x", address),
          .length = 3};
}

template <>
auto Sakura::HuC6280::STZ_ZP(std::unique_ptr<Processor> &processor,
                             uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t zp = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = Common::Formatter::format("STZ %02x", zp), .length = 2};
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

  return {.mnemonic = Common::Formatter::format(
              "TAI %02x%02x, %02x%02x, %02x%02x", sh, sl, dh, dl, lh, ll),
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

  return {.mnemonic = Common::Formatter::format("JSR %04x", address),
          .length = 3};
}

template <>
auto Sakura::HuC6280::TMA_I(std::unique_ptr<Processor> &processor,
                            uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);

  int bit_position = Common::Bits::test_power_of_2(imm);

  return {.mnemonic = Common::Formatter::format("TMA%d", bit_position),
          .length = 2};
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

  return {.mnemonic = Common::Formatter::format("JMP (%04x, X)  %04x", address,
                                                destination),
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

  return {.mnemonic = Common::Formatter::format("SMB%d %02x  @%04x=%02x", index,
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

  return {.mnemonic = Common::Formatter::format("RMB%d %02x  @%04x=%02x", index,
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

  return {.mnemonic = Common::Formatter::format("STX %04x", address),
          .length = 3};
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
  return {.mnemonic = Common::Formatter::format("BPL %04x", destination),
          .length = 2};
}

template <>
auto Sakura::HuC6280::LDY_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = Common::Formatter::format("LDY #%02x", imm), .length = 2};
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
  return {.mnemonic = Common::Formatter::format("LDA %02x", zp), .length = 2};
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

  return {.mnemonic = Common::Formatter::format("LDA %04x, Y  @%04x=%02x",
                                                address, address, value),
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

  return {.mnemonic = Common::Formatter::format(
              "STA %04x, Y @%04x", address, address + processor->m_registers.y),
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

  return {.mnemonic = Common::Formatter::format(
              "ORA %04x, Y @%04x=%02x", address,
              address + processor->m_registers.y, value),
          .length = 3};
}

template <>
auto Sakura::HuC6280::EOR_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = Common::Formatter::format("EOR #%02x", imm), .length = 2};
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

  return {.mnemonic = Common::Formatter::format(
              "EOR %04x, Y @%04x=%02x", address,
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

  return {.mnemonic = Common::Formatter::format(
              "AND %04x, Y @%04x=%02x", address,
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
  return {.mnemonic = Common::Formatter::format("CPY #%02x", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::BCC(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t destination = processor->m_registers.program_counter.value + 1 + imm;
  return {.mnemonic = Common::Formatter::format("BCC %04x", destination),
          .length = 2};
}

template <>
auto Sakura::HuC6280::CMP_IMM(std::unique_ptr<Processor> &processor,
                              uint8_t opcode) -> Disassembled {
  (void)opcode;
  uint8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  return {.mnemonic = Common::Formatter::format("CMP #%02x", imm), .length = 2};
}

template <>
auto Sakura::HuC6280::BNE(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)opcode;
  int8_t imm = processor->m_mapping_controller->load(
      processor->m_registers.program_counter.value);
  uint16_t destination = processor->m_registers.program_counter.value + 1 + imm;
  return {.mnemonic = Common::Formatter::format("BNE %04x", destination),
          .length = 2};
}

template <>
auto Sakura::HuC6280::CLX(std::unique_ptr<Processor> &processor, uint8_t opcode)
    -> Disassembled {
  (void)processor;
  (void)opcode;
  return {.mnemonic = "CLX", .length = 1};
}

#endif
