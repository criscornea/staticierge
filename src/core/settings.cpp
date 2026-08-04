#include <string_view>
#include <toml++/impl/parse_error.hpp>
#include <toml++/toml.hpp>

#include "settings.hpp"

toml::parse_result settings::parse_file(std::string_view file_path)
{
    return toml::parse_file(file_path);
}

std::vector<Source> settings::find_sources(toml::table &config)
{
    // TODO: content here (tm)
}
