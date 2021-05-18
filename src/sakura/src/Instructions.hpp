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

template <typename T>
const std::array<InstructionHandler<T>, 0x100> INSTRUCTION_TABLE = {
  //     +0       +1    +2       +3     +4      +5      +6    +7     +8    +9         +A       +B    +C         +D         +E       +F
  /*0+*/ NULL,    NULL, NULL,    NULL,  NULL,   NULL,   NULL, RMB_I, NULL, NULL,      ASL_ACC, NULL, NULL,      NULL,      NULL,    NULL,
  /*1+*/ BPL,     NULL, NULL,    NULL,  NULL,   NULL,   NULL, RMB_I, NULL, ORA_ABS_Y, INC_ACC, NULL, NULL,      NULL,      NULL,    NULL,
  /*2+*/ JSR,     NULL, NULL,    NULL,  NULL,   NULL,   NULL, RMB_I, NULL, AND_IMM,   NULL,    NULL, NULL,      NULL,      NULL,    NULL,
  /*3+*/ NULL,    NULL, NULL,    NULL,  NULL,   NULL,   NULL, RMB_I, NULL, AND_ABS_Y, NULL,    NULL, NULL,      NULL,      NULL,    NULL,
  /*4+*/ NULL,    NULL, NULL,    TMA_I, NULL,   NULL,   NULL, RMB_I, PHA,  EOR_IMM,   NULL,    NULL, NULL,      NULL,      NULL,    NULL,
  /*5+*/ NULL,    NULL, NULL,    TAM_I, CSL,    NULL,   NULL, RMB_I, NULL, EOR_ABS_Y, PHY,     NULL, NULL,      NULL,      NULL,    NULL,
  /*6+*/ RST,     NULL, NULL,    NULL,  STZ_ZP, NULL,   NULL, RMB_I, PLA,  NULL,      NULL,    NULL, NULL,      NULL,      NULL,    NULL,
  /*7+*/ NULL,    NULL, NULL,    NULL,  NULL,   NULL,   NULL, RMB_I, SEI,  NULL,      PLY,     NULL, JMP_ABS_X, NULL,      NULL,    NULL,
  /*8+*/ NULL,    NULL, CLX,     NULL,  NULL,   STA_ZP, NULL, SMB_I, NULL, NULL,      NULL,    NULL, NULL,      STA_ABS,   STX_ABS, NULL,
  /*9+*/ BCC,     NULL, NULL,    NULL,  NULL,   NULL,   NULL, SMB_I, TYA,  STA_ABS_Y, TXS,     NULL, STZ_ABS,   NULL,      NULL,    NULL,
  /*A+*/ LDY_IMM, NULL, LDX_IMM, NULL,  NULL,   LDA_ZP, NULL, SMB_I, NULL, LDA_IMM,   TAX,     NULL, NULL,      LDA_ABS,   NULL,    NULL,
  /*B+*/ NULL,    NULL, NULL,    NULL,  NULL,   NULL,   NULL, SMB_I, NULL, LDA_ABS_Y, NULL,    NULL, NULL,      LDA_ABS_X, NULL,    NULL,
  /*C+*/ CPY_IMM, NULL, CLY,     NULL,  NULL,   NULL,   NULL, SMB_I, INY,  CMP_IMM,   DEX,     NULL, NULL,      NULL,      NULL,    NULL,
  /*D+*/ BNE,     NULL, NULL,    NULL,  CSH,    NULL,   NULL, SMB_I, CLD,  NULL,      PHX,     NULL, NULL,      NULL,      NULL,    NULL,
  /*E+*/ CPX_IMM, NULL, NULL,    NULL,  NULL,   NULL,   NULL, SMB_I, INX,  NULL,      NOP,     NULL, NULL,      NULL,      NULL,    NULL,
  /*F+*/ BEQ,     NULL, NULL,    TAI,   NULL,   NULL,   NULL, SMB_I, NULL, NULL,      PLX,     NULL, NULL,      NULL,      NULL,    NULL,
};
// clang-format on

}; // namespace Sakura::HuC6280

#endif
