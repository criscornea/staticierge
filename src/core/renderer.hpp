#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

struct SourceFile;
enum class SourceType : std::uint8_t;

struct OutputFile
{
    std::filesystem::path path;
    std::string content;
};

namespace content::renderer {

std::vector<OutputFile> html(const std::vector<SourceFile> &pages,
                             SourceType source_type, std::string_view tmpl);
} // namespace content::renderer
