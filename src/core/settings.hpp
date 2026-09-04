#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include <toml++/toml.hpp>

enum class SourceType : std::uint8_t { BLOG, WIKI, PAGE, ASSET, TEMPLATE };

struct Source
{
    std::string folder;
    SourceType type;

    bool operator==(const Source &T) const = default;
};

namespace settings {
toml::parse_result parse_file(std::string_view file_path);
toml::parse_result parse_content(std::string_view content);
std::vector<Source> find_sources(toml::table &config);
} // namespace settings
