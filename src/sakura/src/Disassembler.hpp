#ifndef SAKURA_DISASSEMBLER_HPP
#define SAKURA_DISASSEMBLER_HPP

#include <memory>

namespace Sakura::HuC6280 {
class Processor;

class Disassembler {
private:
  std::unique_ptr<Processor> &m_processor;

  auto previous_program_counter() -> std::string;

public:
  Disassembler(std::unique_ptr<Processor> &processor);
  ~Disassembler() = default;

  void disassemble(uint8_t opcode);
};
}; // namespace Sakura::HuC6280

#endif
