#ifndef SAKURA_DISASSEMBLER_TCC
#define SAKURA_DISASSEMBLER_TCC

#include "Instructions.hpp"
#include <cstdint>
#include <memory>

using namespace Sakura::HuC6280;

template <>
auto Sakura::HuC6280::SEI(std::unique_ptr<Processor> &processor)
    -> std::string {
  (void)processor;
  return "SEI";
}

#endif
