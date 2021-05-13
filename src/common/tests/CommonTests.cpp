#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <common/Bits.hpp>
#include <vector>

TEST_CASE("Bit test power of two numbers", "[test_power_of_2]") {
  struct TestCase {
    int input;
    int output;
  };
  std::vector<TestCase> test_cases = {
      {.input = 1, .output = 0},     {.input = 2, .output = 1},
      {.input = 8, .output = 3},     {.input = 6, .output = -1},
      {.input = 3072, .output = -1}, {.input = 0, .output = -1},
  };
  for (auto &test_case : test_cases) {
    REQUIRE(test_case.output == Common::Bits::test_power_of_2(test_case.input));
  }
}
