#pragma once

#include <filesystem>
#include <optional>
#include <string_view>
#include <vector>

namespace filesystem {
std::optional<std::filesystem::path> find_folder(const std::string_view path);

std::vector<std::filesystem::path>
find_markdown_files(const std::filesystem::path &root);

bool save_file(const std::filesystem::path &filepath,
               const std::string_view content);

std::optional<std::string> read_file(const std::filesystem::path &filepath);
} // namespace filesystem
