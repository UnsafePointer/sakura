#include "IO.hpp"

using namespace Sakura::HuC6280::IO;

auto Controller::load() const -> uint8_t { return m_port.value; }

void Controller::store(uint8_t value) {
  (void)value;
  (void)m_port;
}
