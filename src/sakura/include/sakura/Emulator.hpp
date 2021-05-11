#ifndef SAKURA_EMULATOR_HPP
#define SAKURA_EMULATOR_HPP

#include <filesystem>
#include <memory>

namespace Sakura {
namespace HuC6280 {
class Processor;
class Disassembler;
} // namespace HuC6280

class Emulator {
private:
  std::unique_ptr<HuC6280::Processor> m_processor;
  std::unique_ptr<HuC6280::Disassembler> m_disassembler;

public:
  Emulator();
  ~Emulator();

  void emulate();
  void initialize(const std::filesystem::path &rom);
};
}; // namespace Sakura

#endif
