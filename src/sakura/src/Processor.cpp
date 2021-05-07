#include "sakura/Processor.hpp"
#include "sakura/Memory.hpp"

using namespace Sakura::HuC6280;

Processor::Processor()
    : m_mapping_controller(std::make_unique<Mapping::Controller>()){};

void Processor::fetch_instruction() {
  m_registers.program_counter.value++;
  m_mapping_controller->store(0x1FFF, // NOLINT(readability-magic-numbers)
                              0xAA);  // NOLINT(readability-magic-numbers)
}
