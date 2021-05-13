#include "common/Bits.hpp"

auto Common::Bits::test_power_of_2(int power_of_2) -> int {
  int bit_position = 0;
  for (;;) {
    if (power_of_2 == 0) {
      return -1;
    }
    int test_bit = power_of_2 & 0b1;
    if (test_bit != 0) {
      power_of_2 >>= 1;
      break;
    }
    power_of_2 >>= 1;
    bit_position += 1;
  }
  if (power_of_2 != 0) {
    return -1;
  }
  return bit_position;
}
