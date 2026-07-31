#pragma once

#include <cstdint>
#include <string_view>

namespace cli {
enum class Command : std::uint8_t {
    VERSION,
    BUILD,
};
bool execute_command(std::string_view command);
} // namespace cli
