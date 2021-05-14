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
using InstructionHandler = T (*)(std::unique_ptr<Processor> &processor);

template <typename T> auto SEI(std::unique_ptr<Processor> &processor) -> T;
template <typename T> auto CSL(std::unique_ptr<Processor> &processor) -> T;
template <typename T> auto LDA_IMM(std::unique_ptr<Processor> &processor) -> T;
template <typename T> auto TAM_I(std::unique_ptr<Processor> &processor) -> T;
template <typename T> auto LDA_ABS(std::unique_ptr<Processor> &processor) -> T;
template <typename T> auto AND_IMM(std::unique_ptr<Processor> &processor) -> T;
template <typename T> auto BEQ(std::unique_ptr<Processor> &processor) -> T;
template <typename T> auto CLD(std::unique_ptr<Processor> &processor) -> T;
template <typename T> auto CSH(std::unique_ptr<Processor> &processor) -> T;
template <typename T> auto LDX_IMM(std::unique_ptr<Processor> &processor) -> T;

// clang-format off
template <typename T>
const std::array<InstructionHandler<T>, 0x100> INSTRUCTION_TABLE = {
  //     +0    +1    +2       +3     +4    +5    +6    +7    +8    +9       +A    +B    +C    +D       +E    +F
  /*0+*/ NULL, NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, NULL, NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*1+*/ NULL, NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, NULL, NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*2+*/ NULL, NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, NULL, AND_IMM, NULL, NULL, NULL, NULL,    NULL, NULL,
  /*3+*/ NULL, NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, NULL, NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*4+*/ NULL, NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, NULL, NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*5+*/ NULL, NULL, NULL,    TAM_I, CSL,  NULL, NULL, NULL, NULL, NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*6+*/ NULL, NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, NULL, NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*7+*/ NULL, NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, SEI,  NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*8+*/ NULL, NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, NULL, NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*9+*/ NULL, NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, NULL, NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*A+*/ NULL, NULL, LDX_IMM, NULL,  NULL, NULL, NULL, NULL, NULL, LDA_IMM, NULL, NULL, NULL, LDA_ABS, NULL, NULL,
  /*B+*/ NULL, NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, NULL, NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*C+*/ NULL, NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, NULL, NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*D+*/ NULL, NULL, NULL,    NULL,  CSH,  NULL, NULL, NULL, CLD,  NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*E+*/ NULL, NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, NULL, NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
  /*F+*/ BEQ,  NULL, NULL,    NULL,  NULL, NULL, NULL, NULL, NULL, NULL,    NULL, NULL, NULL, NULL,    NULL, NULL,
};
// clang-format on

}; // namespace Sakura::HuC6280

#endif
