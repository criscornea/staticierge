#pragma once

#include <filesystem>
#include <optional>
#include <vector>

namespace filesystem {
std::optional<std::filesystem::path> find_folder(std::string_view path);
std::vector<std::filesystem::path> find_markdown_files(std::filesystem::path root);
} // namespace filesystem
