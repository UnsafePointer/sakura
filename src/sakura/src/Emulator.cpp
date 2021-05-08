#include "sakura/Emulator.hpp"
#include "sakura/Memory.hpp"
#include "sakura/Processor.hpp"
#include <iostream>

using namespace Sakura;

Emulator::Emulator() : m_processor(std::make_unique<HuC6280::Processor>()){};

Emulator::~Emulator() = default;

void Emulator::emulate() { m_processor->fetch_instruction(); }

void Emulator::initialize(const std::filesystem::path &rom) {
  m_processor->initialize(rom);
}
