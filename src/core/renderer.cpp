#include "renderer.hpp"
#include "html.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "reader.hpp"
#include "settings.hpp"

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {
fs::path create_dirs(const SourceFile &page, SourceType source_type)
{
    auto target_path = fs::path("output") / page.source_path;
    target_path.replace_extension(".html");

    fs::create_directories(target_path.parent_path());

    return target_path;
}

std::string build_content(const SourceFile &page, SourceType type)
{
    auto tokens = md::lexer::tokenize(page.content);
    auto nodes = md::parser::parse(tokens);

    return "<html>\n<head>\n<title>" + page.title +
           "</title>\n</head>\n<body>\n" + md::html::render(nodes) +
           "</body>\n</html>";
}
} // namespace

std::vector<OutputFile>
content::renderer::html(const std::vector<SourceFile> &pages,
                        SourceType source_type)
{
    std::vector<OutputFile> result;
    for (const auto &page : pages) {
        auto file = OutputFile{.path = create_dirs(page, source_type),
                               .content = build_content(page, source_type)};

        result.push_back(file);
    }

    return result;
}
