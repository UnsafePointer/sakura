#include <utility>

#include "Memory.hpp"
#include "Processor.hpp"

using namespace Sakura::HuC6280;

Processor::Processor()
    : m_mapping_controller(std::make_unique<Mapping::Controller>()){};

void Processor::initialize(const std::filesystem::path &rom) {
  m_registers.status.interrupt_disable = 1;
  m_registers.status.decimal = 0;
  m_mapping_controller->initialize();
  // TODO: reset interrupt disable register
  // TODO: reset Timer Interrupt Request (TIQ)
  // TODO: Set low speed mode
  m_registers.status.memory_operation = 0;
  m_mapping_controller->load_rom(rom);
  m_registers.program_counter.program_counter_high =
      m_mapping_controller->load(RESET_VECTOR_RESET + 1);
  m_registers.program_counter.program_counter_low =
      m_mapping_controller->load(RESET_VECTOR_RESET);
}

auto Processor::fetch_instruction() -> uint8_t {
  uint8_t opcode =
      m_mapping_controller->load(m_registers.program_counter.value);
  m_registers.program_counter.value += 1;
  return opcode;
}

void Processor::push_into_stack(uint8_t value) {
  uint16_t stack_address = 0x2100 | m_registers.stack_pointer;
  m_registers.stack_pointer--;
  m_mapping_controller->store(stack_address, value);
}

auto Processor::pop_from_stack() -> uint8_t {
  m_registers.stack_pointer++;
  uint16_t stack_address = 0x2100 | m_registers.stack_pointer;
  uint8_t value = m_mapping_controller->load(stack_address);
  return value;
}

void Processor::execute_block_transfer(uint8_t sl, uint8_t sh, uint8_t dl,
                                       uint8_t dh, uint8_t ll, uint8_t lh) {
  push_into_stack(m_registers.y);
  push_into_stack(m_registers.accumulator);
  push_into_stack(m_registers.x);
  (void)sl;
  (void)sh;
  (void)dl;
  (void)dh;
  (void)ll;
  (void)lh;
  m_registers.x = pop_from_stack();
  m_registers.accumulator = pop_from_stack();
  m_registers.y = pop_from_stack();
}
