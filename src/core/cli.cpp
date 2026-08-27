#include "cli.hpp"
#include "filesystem.hpp"
#include "reader.hpp"
#include "renderer.hpp"
#include "settings.hpp"

#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

namespace cli {
std::unordered_map<std::string_view, Command> command_map{
    {"build", Command::BUILD}, {"--version", Command::VERSION}};
}

namespace {
void build(fs::path current_dir)
{
    std::cout << "Loading settings.toml" << "\n";

    current_dir.append("settings.toml");
    auto config = settings::parse_file(current_dir.string());
    if (!config) {
        // TODO: error here
        return;
    }
    auto sources = settings::find_sources(config);

    fs::path asset_folder;

    std::cout << "Loading markdown files" << "\n";
    for (const auto &source : sources) {
        auto folder = filesystem::find_folder(source.folder);
        if (!folder) {
            // TODO: log warning here
            continue;
        }

        if (source.type == SourceType::ASSET) {
            asset_folder = source.folder;
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

    if (!asset_folder.empty()) {
        std::cout << "Moving assets" << "\n";

        auto asset_out = fs::path("output") / asset_folder.filename();
        fs::create_directories(asset_out);
        fs::copy(asset_folder, asset_out, fs::copy_options::recursive);
    }
}
} // namespace

bool cli::execute_command(std::string_view command_name, fs::path current_dir)
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
