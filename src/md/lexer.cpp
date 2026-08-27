#include "lexer.hpp"

#include <cstddef>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace {
std::unordered_map<char, md::lexer::TokenType> token_types{
    {'#', md::lexer::TokenType::HASHTAG},
    {'*', md::lexer::TokenType::STAR},
    {'[', md::lexer::TokenType::BRACKET_OPEN},
    {']', md::lexer::TokenType::BRACKET_CLOSED},
    {'(', md::lexer::TokenType::PAREN_OPEN},
    {')', md::lexer::TokenType::PAREN_CLOSED},
    {'\n', md::lexer::TokenType::NEWLINE},
    {'>', md::lexer::TokenType::CHEVRON},
    {'-', md::lexer::TokenType::MINUS},
};
std::unordered_map<char, md::lexer::TokenType> whitespaced_tokens{
    {'#', md::lexer::TokenType::HASHTAG},
    {'>', md::lexer::TokenType::CHEVRON},
    {'-', md::lexer::TokenType::MINUS},
};

bool is_token_valid(const char &token, const std::string_view input,
                    const unsigned long input_pos)
{
    if (!token_types.contains(token)) {
        return false;
    }
    if (!whitespaced_tokens.contains(token)) {
        return true;
    }

    return input_pos + 1 < input.size() &&
           (input[input_pos + 1] == ' ' || input[input_pos + 1] == token);
}
} // namespace

namespace md {
std::vector<lexer::Token> lexer::tokenize(std::string_view input)
{
    // we start at column 1 line 1
    std::size_t line = 1;
    std::size_t column = 1;

    // flush result helper
    std::vector<lexer::Token> result;
    auto flush = [&result](const lexer::TokenType type, std::string value,
                           const std::size_t line, const std::size_t column) {
        result.push_back(lexer::Token{
            .type = type,
            .value = std::move(value),
            .line = line,
            .column = column,
        });
    };

    // counters helper
    auto update_counts = [](char token, std::size_t &line, std::size_t &column,
                            unsigned long &input_pos) {
        if (token == '\n') {
            column = 1;
            line++;
            input_pos++;
        } else {
            column++;
            input_pos++;
        }
    };

    // start tokenization
    std::string buffer;
    std::size_t buffer_line = 1;
    std::size_t buffer_column = 1;
    unsigned long input_pos = 0;
    for (const char &c : input) {
        // continue if it is a whitespace after a token
        if (c == ' ' && buffer.empty()) {
            update_counts(c, line, column, input_pos);
            continue;
        }

        auto token_type = token_types.find(c);
        if (is_token_valid(c, input, input_pos)) {
            // found tokens
            if (!buffer.empty()) {
                // close stream if open
                flush(lexer::TokenType::TEXT, buffer, buffer_line,
                      buffer_column);

                buffer.clear();
                buffer_column = 1;
            }

            flush(token_type->second, std::string(1, c), line, column);
        } else {
            // found text
            if (buffer.empty()) {
                // new buffer, cache the counts
                buffer_line = line;
                buffer_column = column;
            }
            buffer += c;
        }

        update_counts(c, line, column, input_pos);
    }

    if (!buffer.empty()) {
        flush(lexer::TokenType::TEXT, buffer, buffer_line, buffer_column);
    }

    return result;
}
} // namespace md
