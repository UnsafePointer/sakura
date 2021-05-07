#include "sakura/Processor.hpp"

using namespace Sakura::HuC6280;

Processor::Processor() = default;

void Processor::fetch_instruction() { m_registers.program_counter.value++; }
