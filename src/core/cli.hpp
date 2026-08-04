#pragma once

#include <cstdint>
#include <filesystem>
#include <string_view>

namespace cli {
enum class Command : std::uint8_t {
    VERSION,
    BUILD,
};
bool execute_command(std::string_view command_name, std::filesystem::path current_dir);
} // namespace cli
