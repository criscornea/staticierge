#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "html.hpp"
#include "parser.hpp"

TEST_CASE("hmtl render")
{
    std::vector<md::parser::Node> nodes;
    auto header1 =
        md::parser::Node{md::parser::Heading{.level = 1, .text = "Header 1"}};
    nodes.push_back(header1);
    auto paragraph =
        md::parser::Node{md::parser::Paragraph{.text = "a paragraph"}};
    nodes.push_back(paragraph);
    auto header2 =
        md::parser::Node{md::parser::Heading{.level = 2, .text = "Header 2"}};
    nodes.push_back(header2);
    auto list = md::parser::Node{
        md::parser::List{.items = {"listitem 1", "listitem 2"}}};
    nodes.push_back(list);

    auto result = md::html::render(nodes);
    std::string expected =
        "<h1>Header 1</h1>\n<p>a paragraph</p>\n<h2>Header "
        "2</h2>\n<ul>\n<li>listitem 1</li>\n<li>listitem 2</li>\n</ul>\n";
    REQUIRE(result == expected);
}
