#include "core/cli.hpp"
#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::printf("Welcome to the cli\n");
        return EXIT_SUCCESS;
    }

    if (cli::execute_command(argv[1])) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
