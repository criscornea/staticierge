#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

struct SourceFile
{
    // General data
    std::filesystem::path source_path;
    std::string title;
    std::string content;

    // Type specific data
    std::optional<std::string> date;
    std::optional<uint8_t> order;
    std::optional<std::string> category;
    std::optional<std::vector<std::string>> tags;

    bool operator==(const SourceFile &other) const = default;
};

namespace content::reader {
std::optional<SourceFile> load(const std::filesystem::path &file);
};
