#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <toml++/impl/parse_error.hpp>
#include <toml++/toml.hpp>
#include <unordered_map>

#include "settings.hpp"

namespace settings {
std::unordered_map<std::string_view, SourceType> source_types = {
    {"blog", SourceType::BLOG},
    {"wiki", SourceType::WIKI},
    {"page", SourceType::PAGE},
    {"asset", SourceType::ASSET},
};
}

toml::parse_result settings::parse_file(std::string_view file_path)
{
    return toml::parse_file(file_path);
}

std::vector<Source> settings::find_sources(toml::table &config)
{
    auto folders = config["sources"]["folders"];
    if (!folders) {
        throw std::invalid_argument("settings have no sources:folders");
    }

    std::vector<Source> sources;
    // for (const auto &folder : folders.as_array()) {
    for (auto &&folder : *folders.as_array()) {
        auto *table = folder.as_table();
        if (!table) {
            continue;
        }

        std::string path = (*table)["path"].value_or(std::string{});
        std::string type_str = (*table)["type"].value_or(std::string{});

        auto type_it = settings::source_types.find(type_str);
        if (type_it == source_types.end()) {
            continue;
        }

        sources.push_back(Source{.folder = path, .type = type_it->second});
    }

    return sources;
}
