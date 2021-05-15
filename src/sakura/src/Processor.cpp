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

auto Processor::execute_block_transfer(uint8_t sl, uint8_t sh, uint8_t dl,
                                       uint8_t dh, uint8_t ll, uint8_t lh)
    -> uint16_t {
  if (ll == 0x0 && lh == 0x0) {
    ll = 0xFF;
    lh = 0xFF;
  }

  uint16_t total_length = lh;
  total_length = (total_length << 8) | ll;

  push_into_stack(m_registers.y);
  push_into_stack(m_registers.accumulator);
  push_into_stack(m_registers.x);

  m_registers.y = dl;
  m_registers.destination_high = dh;
  m_registers.accumulator = ll;
  m_registers.length_high = lh;
  m_registers.x = sl;
  m_registers.source_high = sh;

  bool flip = true;

  for (;;) {
    uint16_t length = m_registers.length_high;
    length = (length << 8) | m_registers.accumulator;
    if (length <= 0) {
      break;
    }
    uint16_t source = m_registers.source_high;
    source = (source << 8) | m_registers.x;
    uint16_t destination = m_registers.destination_high;
    destination = (destination << 8) | m_registers.y;

    uint8_t value = m_mapping_controller->load(source);
    m_mapping_controller->store(destination, value);

    if (flip) {
      m_registers.x++;
      if (m_registers.x == 0) {
        m_registers.source_high++;
      }
    } else {
      m_registers.x--;
      if (m_registers.x == 0xFF) {
        m_registers.source_high--;
      }
    }
    flip = !flip;

    m_registers.y++;
    if (m_registers.y == 0) {
      m_registers.destination_high++;
    }
    m_registers.accumulator--;
    if (m_registers.accumulator == 0xFF) {
      m_registers.length_high--;
    }
  }

  m_registers.x = pop_from_stack();
  m_registers.accumulator = pop_from_stack();
  m_registers.y = pop_from_stack();

  return total_length;
}
