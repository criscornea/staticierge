#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <toml++/toml.hpp>
#include <vector>

enum class SourceType : std::uint8_t { BLOG, WIKI, PAGE, ASSET };

struct Source
{
    std::string folder;
    SourceType type;

    bool operator==(const Source &T) const { return folder == T.folder && type == T.type; }
};

namespace settings {
toml::parse_result parse_file(std::string_view file_path);
std::vector<Source> find_sources(toml::table &config);
} // namespace settings
