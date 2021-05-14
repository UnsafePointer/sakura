#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <common/Bits.hpp>
#include <common/Range.hpp>
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

TEST_CASE("Test ranges between two numbers", "[range_contains]") {
  struct TestCase {
    uint32_t start;
    uint32_t length;
    uint32_t number;
    std::optional<uint32_t> result;
  };
  std::vector<TestCase> test_cases = {
      {.start = 0x0,
       .length = 0x100,
       .number = 0x20,
       .result = std::optional<uint32_t>(0x20)},
      {.start = 0x0, .length = 0x100, .number = 0x120, .result = std::nullopt},
      {.start = 0x1FF000,
       .length = 0x400,
       .number = 0x1FF3FF,
       .result = std::optional<uint32_t>(0x3FF)},
      {.start = 0x1FF000,
       .length = 0x400,
       .number = 0x1FF000,
       .result = std::optional<uint32_t>(0x0)}};
  for (auto &test_case : test_cases) {
    auto range = Common::Range<uint32_t>(test_case.start, test_case.length);
    REQUIRE(test_case.result == range.contains(test_case.number));
  }
}
