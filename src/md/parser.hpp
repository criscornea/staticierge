#pragma once

#include <cstdint>
#include <string>
#include <variant>
#include <vector>

#include "lexer.hpp"

namespace md::parser {
constexpr std::uint8_t MAX_HEADERS = 6;
constexpr std::uint8_t MAX_STARS = 2;
constexpr std::uint8_t MAX_MINUS = 3;

struct Heading
{
    std::uint8_t level;
    std::string text;
};

struct Paragraph
{
    std::string text;
};

struct List
{
    std::vector<std::string> items;
};

using Node = std::variant<Heading, Paragraph, List>;

std::vector<Node> parse(const std::vector<lexer::Token> &tokens);
} // namespace md::parser
