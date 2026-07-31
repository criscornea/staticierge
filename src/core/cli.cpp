#include "cli.hpp"

#include <cstdio>
#include <map>
#include <string_view>

namespace cli {
std::map<std::string_view, Command> command_map{{"build", Command::BUILD},
                                                {"--version", Command::VERSION}};
}

bool cli::execute_command(std::string_view command_name)
{
    if (auto command = command_map.find(command_name); command != command_map.end()) {
        switch (command->second) {
        case cli::Command::VERSION:
            std::printf("CLI Tool v0.0.1\n");
            break;
        case cli::Command::BUILD:
            std::printf("We will build here very soon\n");
            break;
        }

        return true;
    }

    return false;
}
