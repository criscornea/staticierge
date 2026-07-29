#include <catch2/catch_test_macros.hpp>

static int factorial(int number) {
  return number <= 1 ? 1 : factorial(number - 1) * number;
}

TEST_CASE("First test case") { REQUIRE(factorial(0) == 1); }
