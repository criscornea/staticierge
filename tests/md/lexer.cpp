#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_map>

#include "lexer.hpp"

using md::lexer::TokenType;

struct ExpectedToken
{
    TokenType type;
    std::string value;
    std::size_t column;
    std::size_t line = 1;
};

std::unordered_map<std::string, std::vector<ExpectedToken>> test_inputs{
    {"# headline test",
     {{TokenType::HASHTAG, "#", 1}, {TokenType::TEXT, "headline test", 3}}},
    {"## headline",
     {{TokenType::HASHTAG, "#", 1},
      {TokenType::HASHTAG, "#", 2},
      {TokenType::TEXT, "headline", 4}}},
    {"### headline",
     {{TokenType::HASHTAG, "#", 1},
      {TokenType::HASHTAG, "#", 2},
      {TokenType::HASHTAG, "#", 3},
      {TokenType::TEXT, "headline", 5}}},
    {"# headline\ntext",
     {{TokenType::HASHTAG, "#", 1},
      {TokenType::TEXT, "headline", 3},
      {TokenType::NEWLINE, "\n", 11},
      {TokenType::TEXT, "text", 1, 2}}},
    {"> chevron",
     {{TokenType::CHEVRON, ">", 1}, {TokenType::TEXT, "chevron", 3}}},
    {"*bold text* regular",
     {{TokenType::STAR, "*", 1},
      {TokenType::TEXT, "bold text", 2},
      {TokenType::STAR, "*", 11},
      {TokenType::TEXT, "regular", 13}}},
    {"- list item",
     {{TokenType::MINUS, "-", 1}, {TokenType::TEXT, "list item", 3}}},
};

TEST_CASE("tokenization")
{
    for (const auto &input : test_inputs) {
        INFO("Input: " << input.first);
        auto result = md::lexer::tokenize(input.first);
        CHECK(result.size() == input.second.size());

        for (size_t i = 0; i < result.size(); i++) {
            CHECK(result[i].type == input.second[i].type);
            CHECK(result[i].value == input.second[i].value);
            CHECK(result[i].line == input.second[i].line);
            CHECK(result[i].column == input.second[i].column);
        }
    }
}

TEST_CASE("clamp to max allowed tokens")
{
    // TODO: max header, stars, minus
}
