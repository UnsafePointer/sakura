#include "Disassembler.hpp"
#include "Disassembler.tcc"
#include "Instructions.hpp"
#include <iostream>

using namespace Sakura::HuC6280;

Disassembler::Disassembler(std::unique_ptr<Processor> &processor)
    : m_processor(processor) {}

void Disassembler::disassemble(uint8_t opcode) {
  InstructionHandler<std::string> handler =
      INSTRUCTION_TABLE<std::string>[opcode];
  std::string instruction = handler(m_processor);
  std::cout << instruction << std::endl;
}
