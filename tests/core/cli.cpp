#include <catch2/catch_test_macros.hpp>

#include <filesystem>

#include "cli.hpp"

TEST_CASE("Test execute command")
{
    auto root = std::filesystem::path();

    REQUIRE(cli::execute_command("--version", root) == true);
    REQUIRE(cli::execute_command("build", root) == true);
    REQUIRE(cli::execute_command("does_not_exist", root) == false);
}
