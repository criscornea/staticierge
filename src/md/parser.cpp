#include "parser.hpp"
#include "lexer.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace {
using md::lexer::Token;
using md::lexer::TokenType;

constexpr std::array<TokenType, 2> paragraph_killers{
    TokenType::HASHTAG,
    TokenType::MINUS,
};

void parse_heading(std::size_t &pos, const std::vector<Token> &tokens,
                   std::vector<md::parser::Node> &result,
                   const std::size_t max_size)
{
    std::uint8_t level = 1;
    while (level < md::parser::MAX_HEADERS) {
        if (pos + level < max_size &&
            tokens[pos + level].type == TokenType::HASHTAG) {

            level++;
            continue;
        }

        break;
    }
    pos += level;

    // next element needs to be of type TEXT
    if (pos < max_size && tokens[pos].type == TokenType::TEXT) {
        result.push_back(md::parser::Node{md::parser::Heading{
            .level = level,
            .text = std::string(tokens[pos].value),
        }});

        pos++;
    }
}

void parse_list(std::size_t &pos, const std::vector<Token> &tokens,
                std::vector<md::parser::Node> &result,
                const std::size_t max_size)
{
    std::vector<std::string> items;

    while (pos < max_size && tokens[pos].type == TokenType::MINUS) {
        // next element needs to be of type TEXT
        if (pos + 1 >= max_size || tokens[pos + 1].type != TokenType::TEXT) {
            break; // no valid list entry
        }
        items.push_back(tokens[pos + 1].value);
        pos += 2; // MINUS + TEXT

        if (pos < max_size && tokens[pos].type == TokenType::NEWLINE) {
            pos++; // NEWNLINE optional
        }
    }
    if (!items.empty()) {
        result.push_back(md::parser::Node{md::parser::List{.items = items}});
    }
}

void parse_paragraph(std::size_t &pos, const std::vector<Token> &tokens,
                     std::vector<md::parser::Node> &result,
                     const std::size_t max_size)
{
    std::string buffer = tokens[pos].value;

    auto paragraph_end = [&pos, &tokens, &max_size]() {
        // end reached
        if (pos >= max_size) {
            return true;
        }

        // paragraph killing token next
        if (std::find(paragraph_killers.begin(), paragraph_killers.end(),
                      tokens[pos].type) != paragraph_killers.end()) {

            return true;
        }

        // double new line end
        if (pos + 1 < max_size && tokens[pos].type == TokenType::NEWLINE &&
            tokens[pos + 1].type == TokenType::NEWLINE) {

            return true;
        }

        return false;
    };

    while (paragraph_end()) {
        buffer += tokens[pos + 1].value; // TEXT or NEWLINE
        pos++;
    }

    result.push_back(md::parser::Node{md::parser::Paragraph{.text = buffer}});
}
} // namespace

namespace md {
std::vector<parser::Node> parser::parse(const std::vector<lexer::Token> &tokens)
{
    std::vector<parser::Node> result;
    std::size_t pos = 0;
    const std::size_t max_size = tokens.size();

    while (pos < max_size) {
        const auto &token = tokens[pos];

        switch (token.type) {
        case lexer::TokenType::HASHTAG: {
            parse_heading(pos, tokens, result, max_size);
            break;
        }
        case lexer::TokenType::MINUS: {
            parse_list(pos, tokens, result, max_size);
            break;
        }
        case lexer::TokenType::TEXT: {
            parse_paragraph(pos, tokens, result, max_size);
            break;
        }
        default: {
            pos++;
            break;
        }
        }
    }

    return result;
}
} // namespace md
