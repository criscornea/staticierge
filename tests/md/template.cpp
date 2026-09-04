#include <catch2/catch_test_macros.hpp>
#include <string>
#include <string_view>
#include <unordered_map>

#include "template.hpp"

TEST_CASE("render")
{
    std::string title = "Test Title";
    std::string description = "Test Description";
    std::string content = "Test Content";

    std::string_view tmpl =
        "<html><head>"
        "<title>{{title}}</title>"
        "<meta name=\"description\" content=\"{{description}}\">"
        "</head><body>{{content}}</body></html>";
    std::unordered_map<std::string, std::string> ctx = {
        {"title", title},
        {"description", description},
        {"content", content},
    };

    auto result = content::tmpl::render(tmpl, ctx);
    std::string expected = "<html><head>"
                           "<title>" +
                           title +
                           "</title>"
                           "<meta name=\"description\" content=\"" +
                           description +
                           "\">"
                           "</head><body>" +
                           content + "</body></html>";
    REQUIRE(result == expected);
}
