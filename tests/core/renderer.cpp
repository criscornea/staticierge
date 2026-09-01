#include <catch2/catch_test_macros.hpp>
#include <filesystem>

#include "reader.hpp"
#include "renderer.hpp"
#include "settings.hpp"

namespace fs = std::filesystem;

TEST_CASE("test html build")
{
    auto source = SourceFile{.source_path = "test_dir",
                             .title = "Test File",
                             .content = "Test Content"};

    auto result = content::renderer::html(std::vector<SourceFile>{source},
                                          SourceType::PAGE);
    auto result_html = result.front().content;

    // create_dirs test
    auto output_path = fs::path("output") / source.source_path;
    REQUIRE(fs::is_directory(output_path));

    // html output test
    const std::string expected_html =
        "<html>\n<head>\n<title>Test File</title>\n</head>\n<body>\n<p>Test "
        "Content</p>\n</body>\n</html>";
    REQUIRE(result_html == expected_html);
}
