#include "sakura/Emulator.hpp"
#include "Disassembler.hpp"
#include "Instructions.hpp"
#include "Instructions_Impl.hpp"
#include "Memory.hpp"
#include "Processor.hpp"
#include <common/Formatter.hpp>
#include <iostream>

using namespace Sakura;

Emulator::Emulator()
    : m_processor(std::make_unique<HuC6280::Processor>()),
      m_disassembler(std::make_unique<HuC6280::Disassembler>(m_processor)){};

Emulator::~Emulator() = default;

void Emulator::emulate() {
  for (;;) {
    uint8_t opcode = m_processor->fetch_instruction();
    HuC6280::InstructionHandler<uint8_t> handler =
        HuC6280::INSTRUCTION_TABLE<uint8_t>[opcode];
    if (handler == nullptr) {
      std::cout << Common::Formatter::format("Unhandled opcode: %#04x", opcode)
                << std::endl;
      break;
    }
    m_disassembler->disassemble(opcode);
    handler(m_processor, opcode);
  }
}

void Emulator::initialize(const std::filesystem::path &rom) {
  m_processor->initialize(rom);
}
