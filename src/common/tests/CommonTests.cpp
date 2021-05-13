#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <common/Bits.hpp>

TEST_CASE("Bit test power of two numbers", "[test_power_of_2]") {
  int position = Common::Bits::test_power_of_2(8);
  REQUIRE(position == 3);
}
