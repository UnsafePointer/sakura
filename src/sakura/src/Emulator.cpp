#include "sakura/Emulator.hpp"
#include "Instructions.hpp"
#include "Memory.hpp"
#include "Processor.hpp"
#include "Processor.tcc"
#include <iostream>

using namespace Sakura;

Emulator::Emulator() : m_processor(std::make_unique<HuC6280::Processor>()){};

Emulator::~Emulator() = default;

void Emulator::emulate() {
  uint8_t opcode = m_processor->fetch_instruction();
  HuC6280::InstructionHandler<uint8_t> handler =
      HuC6280::INSTRUCTION_TABLE<uint8_t>[opcode];
  handler(m_processor);
}

void Emulator::initialize(const std::filesystem::path &rom) {
  m_processor->initialize(rom);
}
