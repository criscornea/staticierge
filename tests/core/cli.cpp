#include <catch2/catch_test_macros.hpp>

#include "cli.hpp"

TEST_CASE("Test execute command")
{
    REQUIRE(cli::execute_command("--version") == true);
    REQUIRE(cli::execute_command("build") == true);
    REQUIRE(cli::execute_command("does_not_exist") == false);
}
