#include <catch2/catch_test_macros.hpp>
#include <variant>

#include "lexer.hpp"
#include "parser.hpp"

using md::lexer::Token;
using md::lexer::TokenType;
using md::parser::Heading;
using md::parser::List;
using md::parser::Node;
using md::parser::Paragraph;

auto CHECK_RESULT = [](std::vector<Node> result, Node expected,
                       size_t size = 1) {
    INFO("[EXPECTED]" << "\n" << expected);
    INFO("[RESULT]" << "\n" << result[0]);

    CHECK(result.size() == size);
    CHECK(result[0] == expected);
};

TEST_CASE("parse heading")
{
    std::vector<Token> single_headline_1{
        {TokenType::HASHTAG, "#", 1, 1},
        {TokenType::TEXT, "test text", 1, 3},
    };
    auto expected1 = Node{Heading{.level = 1, .text = "test text"}};
    auto result1 = md::parser::parse(single_headline_1);
    CHECK_RESULT(result1, expected1);

    std::vector<Token> single_headline_3{
        {TokenType::HASHTAG, "#", 1, 1},
        {TokenType::HASHTAG, "#", 1, 2},
        {TokenType::HASHTAG, "#", 1, 3},
        {TokenType::TEXT, "test text", 1, 5},
    };
    auto expected2 = Node{Heading{.level = 3, .text = "test text"}};
    auto result2 = md::parser::parse(single_headline_3);
    CHECK_RESULT(result2, expected2);

    std::vector<Token> single_headline_with_text{
        {TokenType::HASHTAG, "#", 1, 1},
        {TokenType::TEXT, "testing", 1, 3},
        {TokenType::NEWLINE, "\n", 1, 13},
        {TokenType::TEXT, "text", 2, 1},
    };
    auto expected3 = Node{Heading{.level = 1, .text = "testing"}};
    auto result3 = md::parser::parse(single_headline_with_text);
    CHECK_RESULT(result3, expected3, 2);
    CHECK(result3[1] == Node{Paragraph{.text = "text"}});
}

TEST_CASE("parse list")
{
    std::vector<Token> list{
        {TokenType::MINUS, "-", 1, 1},
        {TokenType::TEXT, "list item 1", 1, 3},
        {TokenType::MINUS, "-", 1, 1},
        {TokenType::TEXT, "list item 2", 1, 3},
    };
    auto result = md::parser::parse(list);
    auto expected = Node{List{.items = {"list item 1", "list item 2"}}};
    CHECK_RESULT(result, expected);
}

TEST_CASE("parse paragraph")
{
    std::vector<Token> simple{
        {TokenType::TEXT, "Just some text."},
    };
    auto expected1 = Node{Paragraph{.text = simple[0].value}};
    auto result1 = md::parser::parse(simple);
    CHECK_RESULT(result1, expected1);

    std::vector<Token> multi{
        {TokenType::TEXT, "text"},
        {TokenType::NEWLINE, "\n"},
        {TokenType::TEXT, "text"},
    };
    auto expected2 = Node{Paragraph{.text = "text\ntext"}};
    auto result2 = md::parser::parse(multi);
    CHECK_RESULT(result2, expected2);

    std::vector<Token> kill_with_newline{
        {TokenType::TEXT, "first paragraph"},
        {TokenType::NEWLINE, "\n"},
        {TokenType::NEWLINE, "\n"},
        {TokenType::TEXT, "new paragraph"},
    };
    auto expected3 = Node{Paragraph{.text = "first paragraph"}};
    auto result3 = md::parser::parse(kill_with_newline);
    CHECK_RESULT(result3, expected3, 2);
    CHECK(result3[1] == Node{Paragraph{.text = "new paragraph"}});

    std::vector<Token> kill_with_hashtag{
        {TokenType::TEXT, "first paragraph"},
        {TokenType::HASHTAG, "#"},
        {TokenType::TEXT, "headline"},
    };
    auto expected4 = Node{Paragraph{.text = "first paragraph"}};
    auto result4 = md::parser::parse(kill_with_hashtag);
    CHECK_RESULT(result4, expected4, 2);
    CHECK(result4[1] == Node{Heading{.level = 1, .text = "headline"}});

    std::vector<Token> kill_with_minus{
        {TokenType::TEXT, "first paragraph"},
        {TokenType::MINUS, "-"},
        {TokenType::TEXT, "list item"},
        {TokenType::TEXT, "new paragraph"},
    };
    auto expected5 = Node{Paragraph{.text = "first paragraph"}};
    auto result5 = md::parser::parse(kill_with_minus);
    CHECK_RESULT(result5, expected5, 3);
    CHECK(result5[1] == Node{List{.items = {"list item"}}});
    CHECK(result5[2] == Node{Paragraph{.text = "new paragraph"}});
}
