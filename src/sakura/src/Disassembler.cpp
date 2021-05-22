#include "Disassembler.hpp"
#include "Disassembler_Impl.hpp"
#include "Instructions.hpp"
#include "Processor.hpp"
#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <sstream>

using namespace Sakura::HuC6280;

Disassembler::Disassembler(std::unique_ptr<Processor> &processor)
    : m_processor(processor) {}

auto Disassembler::previous_program_counter() -> std::string {
  return fmt::format("{:04X}",
                     m_processor->m_registers.program_counter.value - 1);
}

void Disassembler::disassemble(uint8_t opcode) {
  InstructionHandler<Disassembled> handler =
      INSTRUCTION_TABLE<Disassembled>[opcode];
  if (handler == nullptr) {
    spdlog::get(DISASSEMBLER_LOGGER_NAME)
        ->critical(fmt::format("{:s}: Unhandled opcode: {:#04x}",
                               previous_program_counter().c_str(), opcode));
    exit(1); // NOLINT(concurrency-mt-unsafe)
  }
  Disassembled instruction = handler(m_processor, opcode);
  std::stringstream machine_code = std::stringstream();
  machine_code << "; ";
  machine_code << fmt::format("{:02X}", opcode);
  for (uint8_t i = 0; i < instruction.length - 1; i++) {
    uint8_t byte = m_processor->m_mapping_controller->load(
        m_processor->m_registers.program_counter.value + i);
    machine_code << fmt::format(" {:02X}", byte);
  }
  std::string separator(40 - instruction.mnemonic.length(), ' ');
  std::string message =
      fmt::format("{:s}: {:s}{:s}{:s}", previous_program_counter().c_str(),
                  instruction.mnemonic.c_str(), separator.c_str(),
                  machine_code.str().c_str());
  spdlog::get(DISASSEMBLER_LOGGER_NAME)->debug(message);
}
