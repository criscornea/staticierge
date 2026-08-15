#include <cstdio>
#include <cstdlib>
#include <string_view>

#include "core/cli.hpp"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::printf("Welcome to the cli\n");
        // TODO:  cli::show_help();
        return EXIT_SUCCESS;
    }

    std::string_view current_dir; // TODO: How to get current dir? like actually?
    if (cli::execute_command(argv[1], current_dir)) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
