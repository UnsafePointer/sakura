#include "Disassembler.hpp"
#include "Disassembler.tcc"
#include "Instructions.hpp"
#include "Processor.hpp"
#include <common/Formatter.hpp>
#include <iostream>

using namespace Sakura::HuC6280;

Disassembler::Disassembler(std::unique_ptr<Processor> &processor)
    : m_processor(processor) {}

auto Disassembler::previous_program_counter() -> std::string {
  return Common::Formatter::colorize(
      Common::Formatter::format(
          "%04X", m_processor->m_registers.program_counter.value - 1),
      Common::Formatter::Color::Green, false);
}

void Disassembler::disassemble(uint8_t opcode) {
  InstructionHandler<std::string> handler =
      INSTRUCTION_TABLE<std::string>[opcode];
  std::string instruction = handler(m_processor);
  std::cout << Common::Formatter::format("%s: %s",
                                         previous_program_counter().c_str(),
                                         instruction.c_str())
            << std::endl;
}
