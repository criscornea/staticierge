#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace md::lexer {
enum class TokenType : std::uint8_t {
    HASHTAG,        // #
    STAR,           // *
    BRACKET_OPEN,   // [
    BRACKET_CLOSED, // ]
    PAREN_OPEN,     // (
    PAREN_CLOSED,   // )
    TEXT,           // words
    NEWLINE,        // \n
    CHEVRON,        // >
    MINUS,          // -
};

struct Token
{
    TokenType type;
    std::string value;
    std::size_t line;
    std::size_t column;
};

std::vector<Token> tokenize(std::string_view input);

} // namespace md::lexer
