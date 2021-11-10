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
template <typename T> auto RTS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
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
template <typename T> auto LSR_ACC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ADC_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto JMP_ABS_IND(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto TSX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto DEC_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto SAX(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto DEC_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CMP_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto INC_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto DEC_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ADC_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ORA_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ST1(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ST2(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BBS_I(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STY_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto TSB_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto TRB_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BVC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BVS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BRK(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto SED(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CLV(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDX_ZP_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CMP_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDX_ABS_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STX_ZP_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDY_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDY_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STY_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CMP_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CMP_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CPX_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CPY_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CPY_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CMP_IND_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LDA_IND_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto STA_IND_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BIT_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto BIT_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto CMP_IND_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ROL_ACC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ROR_ACC(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ROR_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ASL_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LSR_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ROL_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ROR_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LSR_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ROL_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ROR_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ASL_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto LSR_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ROL_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ROR_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto INC_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto AND_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto AND_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto AND_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto AND_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto AND_IND_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto AND_IND_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto EOR_ZP(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto EOR_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto EOR_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto EOR_ABS_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto EOR_IND_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto EOR_IND_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ORA_ABS(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ORA_ZP_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ORA_IND_X(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;
template <typename T> auto ORA_IND_Y(std::unique_ptr<Processor> &processor, uint8_t opcode) -> T;

template <typename T>
const std::array<InstructionHandler<T>, 0x100> INSTRUCTION_TABLE = {
  //     +0       +1         +2       +3     +4        +5        +6        +7     +8    +9         +A       +B    +C           +D         +E         +F
  /*0+*/ BRK,     ORA_IND_X, SXY,     ST0,   TSB_ZP,   ORA_ZP,   ASL_ZP,   RMB_I, PHP,  ORA_IMM,   ASL_ACC, NULL, NULL,        ORA_ABS,   ASL_ABS,   BBR_I,
  /*1+*/ BPL,     ORA_IND_Y, NULL,    ST1,   NULL,     ORA_ZP_X, ASL_ZP_X, RMB_I, CLC,  ORA_ABS_Y, INC_ACC, NULL, TRB_ABS,     ORA_ABS_X, ASL_ABS_X, BBR_I,
  /*2+*/ JSR,     AND_IND_X, SAX,     ST2,   BIT_ZP,   AND_ZP,   ROL_ZP,   RMB_I, PLP,  AND_IMM,   ROL_ACC, NULL, BIT_ABS,     AND_ABS,   ROL_ABS,   BBR_I,
  /*3+*/ BMI,     AND_IND_Y, NULL,    NULL,  NULL,     AND_ZP_X, ROL_ZP_X, RMB_I, SEC,  AND_ABS_Y, DEC_ACC, NULL, NULL,        AND_ABS_X, ROL_ABS_X, BBR_I,
  /*4+*/ RTI,     EOR_IND_X, SAY,     TMA_I, BSR,      EOR_ZP,   LSR_ZP,   RMB_I, PHA,  EOR_IMM,   LSR_ACC, NULL, JMP_ABS,     EOR_ABS,   LSR_ABS,   BBR_I,
  /*5+*/ BVC,     EOR_IND_Y, NULL,    TAM_I, CSL,      EOR_ZP_X, LSR_ZP_X, RMB_I, CLI,  EOR_ABS_Y, PHY,     NULL, NULL,        EOR_ABS_X, LSR_ABS_X, BBR_I,
  /*6+*/ RTS,     NULL,      CLA,     NULL,  STZ_ZP,   ADC_ZP,   ROR_ZP,   RMB_I, PLA,  ADC_IMM,   ROR_ACC, NULL, JMP_ABS_IND, ADC_ABS,   ROR_ABS,   BBR_I,
  /*7+*/ BVS,     NULL,      ADC_IND, NULL,  NULL,     NULL,     ROR_ZP_X, RMB_I, SEI,  ADC_ABS_Y, PLY,     NULL, JMP_ABS_X,   ADC_ABS_X, ROR_ABS_X, BBR_I,
  /*8+*/ BRA,     STA_IND_X, CLX,     NULL,  STY_ZP,   STA_ZP,   STX_ZP,   SMB_I, DEY,  BIT_IMM,   TXA,     NULL, STY_ABS,     STA_ABS,   STX_ABS,   BBS_I,
  /*9+*/ BCC,     STA_IND_Y, STA_IND, NULL,  STY_ZP_X, STA_ZP_X, STX_ZP_Y, SMB_I, TYA,  STA_ABS_Y, TXS,     NULL, STZ_ABS,     STA_ABS_X, STZ_ABS_X, BBS_I,
  /*A+*/ LDY_IMM, LDA_IND_X, LDX_IMM, NULL,  LDY_ZP,   LDA_ZP,   LDX_ZP,   SMB_I, TAY,  LDA_IMM,   TAX,     NULL, LDY_ABS,     LDA_ABS,   LDX_ABS,   BBS_I,
  /*B+*/ BCS,     LDA_IND_Y, LDA_IND, NULL,  LDY_ZP_X, LDA_ZP_X, LDX_ZP_Y, SMB_I, CLV,  LDA_ABS_Y, TSX,     NULL, LDY_ABS_X,   LDA_ABS_X, LDX_ABS_Y, BBS_I,
  /*C+*/ CPY_IMM, CMP_IND_X, CLY,     NULL,  CPY_ZP,   CMP_ZP,   DEC_ZP,   SMB_I, INY,  CMP_IMM,   DEX,     NULL, CPY_ABS,     CMP_ABS,   DEC_ABS,   BBS_I,
  /*D+*/ BNE,     CMP_IND_Y, NULL,    NULL,  CSH,      CMP_ZP_X, DEC_ZP_X, SMB_I, CLD,  CMP_ABS_Y, PHX,     NULL, NULL,        CMP_ABS_X, DEC_ABS_X, BBS_I,
  /*E+*/ CPX_IMM, NULL,      NULL,    TIA,   CPX_ZP,   NULL,     INC_ZP,   SMB_I, INX,  SBC_IMM,   NOP,     NULL, CPX_ABS,     NULL,      INC_ABS,   BBS_I,
  /*F+*/ BEQ,     NULL,      NULL,    TAI,   NULL,     NULL,     INC_ZP_X, SMB_I, SED,  NULL,      PLX,     NULL, NULL,        NULL,      INC_ABS_X, BBS_I,
};
// clang-format on

}; // namespace Sakura::HuC6280

#endif
