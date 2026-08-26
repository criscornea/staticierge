#pragma once

#include <filesystem>
#include <string>
#include <vector>

struct SourceFile;
enum class SourceType : std::uint8_t;

struct OutputFile
{
    std::filesystem::path path;
    std::string content;
};

namespace content::renderer {

std::vector<OutputFile> html(const std::vector<SourceFile> &pages, SourceType source_type);

std::filesystem::path create_dirs(const SourceFile &page, SourceType source_type);
} // namespace content::renderer
