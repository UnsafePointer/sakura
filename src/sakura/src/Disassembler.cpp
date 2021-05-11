#include "Disassembler.hpp"

using namespace Sakura::HuC6280;

Disassembler::Disassembler(std::unique_ptr<Processor> &processor)
    : m_processor(processor) {}

void Disassembler::disassemble(uint8_t opcode) {
  (void)opcode;
  (void)m_processor;
}
