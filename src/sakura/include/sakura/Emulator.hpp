#ifndef SAKURA_EMULATOR_HPP
#define SAKURA_EMULATOR_HPP

#include <filesystem>
#include <memory>

namespace Sakura {
namespace HuC6280 {
class Processor;
} // namespace HuC6280

class Emulator {
private:
  std::unique_ptr<HuC6280::Processor> m_processor;

public:
  Emulator();
  ~Emulator();

  void emulate();
  void initialize(const std::filesystem::path &rom);
};
}; // namespace Sakura

#endif
