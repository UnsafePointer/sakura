#include "sakura/Emulator.hpp"
#include "Disassembler.hpp"
#include "Instructions.hpp"
#include "Memory.hpp"
#include "Processor.hpp"
#include "Processor.tcc"
#include <iostream>

using namespace Sakura;

Emulator::Emulator()
    : m_processor(std::make_unique<HuC6280::Processor>()),
      m_disassembler(std::make_unique<HuC6280::Disassembler>(m_processor)){};

Emulator::~Emulator() = default;

void Emulator::emulate() {
  uint8_t opcode = m_processor->fetch_instruction();
  m_disassembler->disassemble(opcode);
  HuC6280::InstructionHandler<uint8_t> handler =
      HuC6280::INSTRUCTION_TABLE<uint8_t>[opcode];
  handler(m_processor);
}

void Emulator::initialize(const std::filesystem::path &rom) {
  m_processor->initialize(rom);
}
