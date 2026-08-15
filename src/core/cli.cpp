#include "cli.hpp"
#include "filesystem.hpp"
#include "settings.hpp"

#include <cstdio>
#include <string_view>
#include <unordered_map>

namespace cli {
std::unordered_map<std::string_view, Command> command_map{{"build", Command::BUILD},
                                                          {"--version", Command::VERSION}};
}

namespace {
void build(std::filesystem::path current_dir)
{
    std::printf("Loading settings.toml\n");
    current_dir.append("settings.toml");
    auto config = settings::parse_file(current_dir.string());
    if (!config) {
        // TODO: error here
        return;
    }
    auto sources = settings::find_sources(config);

    std::printf("Loading markdown files\n");
    for (auto source : sources) {
        auto folder = filesystem::find_folder(source.folder);
        if (!folder) {
            // TODO: error here
            continue;
        }

        auto files = filesystem::find_markdown_files(folder.value());

        std::printf("Building files for %s\n", source.folder.c_str());
        // TODO: Build here
    }
}
} // namespace

bool cli::execute_command(std::string_view command_name, std::filesystem::path current_dir)
{
    if (auto command = command_map.find(command_name); command != command_map.end()) {
        switch (command->second) {
        case cli::Command::VERSION:
            std::printf("CLI Tool v0.0.1\n");
            break;
        case cli::Command::BUILD:
            build(std::move(current_dir));
            break;
        }

        return true;
    }

    return false;
}
