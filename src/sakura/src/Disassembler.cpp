#include "Disassembler.hpp"
#include "Disassembler_Impl.hpp"
#include "Instructions.hpp"
#include "Processor.hpp"
#include <common/Formatter.hpp>
#include <iostream>
#include <sstream>

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
  InstructionHandler<Disassembled> handler =
      INSTRUCTION_TABLE<Disassembled>[opcode];
  Disassembled instruction = handler(m_processor);
  std::stringstream machine_code = std::stringstream();
  machine_code << "; ";
  machine_code << Common::Formatter::colorize(
      Common::Formatter::format("%02X", opcode),
      Common::Formatter::Color::Magenta, false);
  for (uint8_t i = 0; i < instruction.length - 1; i++) {
    uint8_t byte = m_processor->m_mapping_controller->load(
        m_processor->m_registers.program_counter.value + i);
    machine_code << Common::Formatter::colorize(
        Common::Formatter::format(" %02X", byte), Common::Formatter::Magenta,
        false);
  }
  std::string separator(10 - instruction.mnemonic.length(), ' ');
  std::cout << Common::Formatter::format(
                   "%s: %s%s%s", previous_program_counter().c_str(),
                   instruction.mnemonic.c_str(), separator.c_str(),
                   machine_code.str().c_str())
            << std::endl;
}
