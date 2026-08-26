#include "cli.hpp"
#include "filesystem.hpp"
#include "reader.hpp"
#include "renderer.hpp"
#include "settings.hpp"

#include <cstdio>
#include <iostream>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace cli {
std::unordered_map<std::string_view, Command> command_map{
    {"build", Command::BUILD}, {"--version", Command::VERSION}};
}

namespace {
void build(std::filesystem::path current_dir)
{
    std::cout << "Loading settings.toml" << "\n";

    current_dir.append("settings.toml");
    auto config = settings::parse_file(current_dir.string());
    if (!config) {
        // TODO: error here
        return;
    }
    auto sources = settings::find_sources(config);

    std::cout << "Loading markdown files" << "\n";
    for (const auto &source : sources) {
        auto folder = filesystem::find_folder(source.folder);
        if (!folder) {
            // TODO: error here
            continue;
        }

        std::cout << "Building files for " << source.folder << "\n";
        std::vector<SourceFile> source_files;

        auto md_files = filesystem::find_markdown_files(folder.value());
        source_files.reserve(md_files.size());
        for (const auto &md : md_files) {
            auto sf = content::reader::load(md);
            if (!sf) {
                continue;
            }
            source_files.push_back(sf.value());
        }

        auto output_files = content::renderer::html(source_files, source.type);
        for (const auto &html : output_files) {
            auto ok = filesystem::save_file(html.path, html.content);
            if (!ok) {
                // TODO: error here
                continue;
            }
        }
    }
}
} // namespace

bool cli::execute_command(std::string_view command_name,
                          std::filesystem::path current_dir)
{
    if (auto command = command_map.find(command_name);
        command != command_map.end()) {
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
