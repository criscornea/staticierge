#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

namespace content::tmpl {

enum class Keywords : std::uint8_t {
    TITLE,
    CONTENT,
    YEAR,
    DESCRIPTION,
};

std::string render(std::string_view tmpl,
                   const std::unordered_map<std::string, std::string> &context);
} // namespace content::tmpl
