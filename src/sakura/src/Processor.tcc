#ifndef SAKURA_PROCESSOR_TCC
#define SAKURA_PROCESSOR_TCC

#include "Processor.hpp"
#include <cstdint>
#include <memory>

using namespace Sakura::HuC6280;

template <>
auto Sakura::HuC6280::SEI(std::unique_ptr<Processor> &processor) -> uint8_t {
  (void)processor;
  return 0;
}

#endif
