#ifndef SAKURA_INSTRUCTIONS_HPP
#define SAKURA_INSTRUCTIONS_HPP

#include <array>
#include <cstdint>
#include <memory>

namespace Sakura::HuC6280 {
class Processor;

struct Disassembled {
  std::string mnemonic;
  uint8_t length;
};

template <typename T>
using InstructionHandler = T (*)(std::unique_ptr<Processor> &processor,
                                 uint8_t opcode);

// clang-format off
template <typename T> auto SEI(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CSL(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDA_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto TAM_I(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDA_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto AND_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BEQ(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CLD(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CSH(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDX_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto TXS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STA_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STA_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STZ_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STZ_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto TAI(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto PHX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto PHY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto JSR(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto TMA_I(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto PHA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto INC_ACC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ASL_ACC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto TAX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto JMP_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto SMB_I(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto RMB_I(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STX_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto DEX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BPL(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDY_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto TYA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto PLA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto RST(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto PLY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto PLX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDA_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CLY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto NOP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDA_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STA_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ORA_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto EOR_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto EOR_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto AND_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto INY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CPY_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BCC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CMP_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BNE(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CLX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDA_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto INX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CPX_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ST0(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto DEY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto TAY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDY_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDA_IND(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STA_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDA_IND_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CLC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ADC_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STZ_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CPX_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto SEC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto SBC_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto DEC_ACC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ORA_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CLI(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto JMP_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BRA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ORA_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STA_IND(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STA_IND_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CLA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BCS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ASL_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ROL_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ADC_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ADC_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BSR(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BMI(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto INC_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STA_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STX_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ASL_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto DEC_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LSR_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto PHP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto PLP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDX_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto INC_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDX_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDY_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto SAY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto RTI(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BBR_I(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BIT_IMM(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CMP_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto TIA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto SXY(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ADC_IND(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STY_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDA_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto TXA(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;

template <typename T>
const std::array<InstructionHandler<T>, 0x100> INSTRUCTION_TABLE = {
  //     +0       +1         +2       +3     +4      +5        +6        +7     +8    +9         +A       +B    +C         +D         +E         +F
  /*0+*/ NULL,    NULL,      SXY,     ST0,   NULL,   ORA_ZP,   ASL_ZP,   RMB_I, PHP,  ORA_IMM,   ASL_ACC, NULL, NULL,      NULL,      NULL,      BBR_I,
  /*1+*/ BPL,     NULL,      NULL,    NULL,  NULL,   NULL,     ASL_ZP_X, RMB_I, CLC,  ORA_ABS_Y, INC_ACC, NULL, NULL,      NULL,      NULL,      BBR_I,
  /*2+*/ JSR,     NULL,      NULL,    NULL,  NULL,   NULL,     ROL_ZP,   RMB_I, PLP,  AND_IMM,   NULL,    NULL, NULL,      NULL,      NULL,      BBR_I,
  /*3+*/ BMI,     NULL,      NULL,    NULL,  NULL,   NULL,     NULL,     RMB_I, SEC,  AND_ABS_Y, DEC_ACC, NULL, NULL,      NULL,      NULL,      BBR_I,
  /*4+*/ RTI,     NULL,      SAY,     TMA_I, BSR,    NULL,     LSR_ZP,   RMB_I, PHA,  EOR_IMM,   NULL,    NULL, JMP_ABS,   NULL,      NULL,      BBR_I,
  /*5+*/ NULL,    NULL,      NULL,    TAM_I, CSL,    NULL,     NULL,     RMB_I, CLI,  EOR_ABS_Y, PHY,     NULL, NULL,      NULL,      NULL,      BBR_I,
  /*6+*/ RST,     NULL,      CLA,     NULL,  STZ_ZP, ADC_ZP,   NULL,     RMB_I, PLA,  ADC_IMM,   NULL,    NULL, NULL,      ADC_ABS,   NULL,      BBR_I,
  /*7+*/ NULL,    NULL,      ADC_IND, NULL,  NULL,   NULL,     NULL,     RMB_I, SEI,  NULL,      PLY,     NULL, JMP_ABS_X, NULL,      NULL,      BBR_I,
  /*8+*/ BRA,     NULL,      CLX,     NULL,  STY_ZP, STA_ZP,   STX_ZP,   SMB_I, DEY,  BIT_IMM,   TXA,     NULL, NULL,      STA_ABS,   STX_ABS,   BBR_I,
  /*9+*/ BCC,     STA_IND_Y, STA_IND, NULL,  NULL,   STA_ZP_X, NULL,     SMB_I, TYA,  STA_ABS_Y, TXS,     NULL, STZ_ABS,   STA_ABS_X, STZ_ABS_X, NULL,
  /*A+*/ LDY_IMM, NULL,      LDX_IMM, NULL,  LDY_ZP, LDA_ZP,   LDX_ZP,   SMB_I, TAY,  LDA_IMM,   TAX,     NULL, LDY_ABS,   LDA_ABS,   LDX_ABS,   NULL,
  /*B+*/ BCS,     LDA_IND_Y, LDA_IND, NULL,  NULL,   LDA_ZP_X, NULL,     SMB_I, NULL, LDA_ABS_Y, NULL,    NULL, NULL,      LDA_ABS_X, NULL,      NULL,
  /*C+*/ CPY_IMM, NULL,      CLY,     NULL,  NULL,   NULL,     DEC_ZP,   SMB_I, INY,  CMP_IMM,   DEX,     NULL, NULL,      CMP_ABS,   NULL,      NULL,
  /*D+*/ BNE,     NULL,      NULL,    NULL,  CSH,    NULL,     NULL,     SMB_I, CLD,  NULL,      PHX,     NULL, NULL,      NULL,      NULL,      NULL,
  /*E+*/ CPX_IMM, NULL,      NULL,    TIA,   CPX_ZP, NULL,     INC_ZP,   SMB_I, INX,  SBC_IMM,   NOP,     NULL, NULL,      NULL,      INC_ABS,   NULL,
  /*F+*/ BEQ,     NULL,      NULL,    TAI,   NULL,   NULL,     NULL,     SMB_I, NULL, NULL,      PLX,     NULL, NULL,      NULL,      NULL,      NULL,
};
// clang-format on

}; // namespace Sakura::HuC6280

#endif
