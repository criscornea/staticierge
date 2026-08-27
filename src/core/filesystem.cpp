#include "filesystem.hpp"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <system_error>

namespace fs = std::filesystem;

std::optional<fs::path> filesystem::find_folder(const std::string_view path)
{
    fs::path folder = path;

    if (!fs::is_directory(folder)) {
        return std::nullopt;
    }

    return folder;
}

std::optional<std::string>
filesystem::read_file(const std::filesystem::path &filepath)
{
    std::ifstream file(filepath);
    if (!file) {
        return std::nullopt;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

std::vector<fs::path> filesystem::find_markdown_files(const fs::path &root)
{
    std::vector<fs::path> files;
    std::error_code ec;
    for (auto it = fs::recursive_directory_iterator(root, ec);
         it != fs::recursive_directory_iterator(); it.increment(ec)) {

        // do not enter hidden .folders
        std::string name = it->path().filename().string();
        if (!name.empty() && name[0] == '.') {
            it.disable_recursion_pending();
            continue;
        }

        // to lower case
        std::string ext = it->path().extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        if (!it->is_directory() && ext == ".md") {
            files.push_back(it->path());
        }
    }

    if (ec) {
        // TODO: what to do with the error?
    }

    // Keep the sequence deterministic
    std::sort(files.begin(), files.end());

    return files;
}

bool filesystem::save_file(const fs::path &filepath,
                           const std::string_view content)
{
    std::ofstream file(filepath.string());

    if (!file) {
        return false;
    }

    file << content;

    return true;
}
