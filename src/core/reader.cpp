#include "reader.hpp"
#include "filesystem.hpp"
#include "settings.hpp"
#include <iostream>
#include <optional>

namespace fs = std::filesystem;

namespace {
void add_optional_parameters(SourceFile &source_file,
                             const toml::parse_result &header)
{
    // TODO: date, tags, category, order from header
    // maybe template usage (week 9/14)
}
} // namespace

std::optional<SourceFile>
content::reader::load(const std::filesystem::path &filepath)
{
    auto file = filesystem::read_file(filepath);
    if (!file) {
        // TODO: handle error
        std::cout << "Could not read file" << "\n";
        return std::nullopt;
    }

    const std::string &content = file.value();

    if (content.find("+++") != 0) {
        // TODO: handle error
        std::cout << "File does not start with +++" << "\n";
        return std::nullopt;
    }

    auto end = content.find("+++", 3);
    if (end == std::string::npos) {
        // TODO: handle error
        std::cout << "Parameters do not end with +++" << "\n";
        return std::nullopt;
    }

    auto meta = content.substr(3, end - 3);

    auto header = settings::parse_content(meta);
    if (!header) {
        // TODO: handle error
        std::cout << "Header content parse error" << "\n";
        return std::nullopt;
    }

    auto body = content.substr(end + 3);

    auto title = header["title"].value<std::string>();
    if (!title) {
        // TODO: handle error
        std::cout << "File has no title" << "\n";
        return std::nullopt;
    }

    auto source_file = SourceFile{
        .source_path = filepath, .title = title.value(), .content = body};

    add_optional_parameters(source_file, header);

    return source_file;
}
