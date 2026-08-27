#include "renderer.hpp"
#include "reader.hpp"
#include "settings.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {
fs::path create_dirs(const SourceFile &page, SourceType source_type)
{
    std::cout << "starting dir operation" << "\n";

    auto source_path = page.source_path;
    auto target_path = "output" / source_path;

    std::cout << "target path is: " << target_path.string() << "\n";
    fs::create_directories(target_path);

    std::cout << "created directories" << "\n";
    return target_path;
}

std::string build_content(const SourceFile &page, SourceType type)
{
    std::cout << "build content" << "\n";

    return "<html><head><title>" + page.title + "</title></head><body>" +
           page.content + "</body></html>";
}
} // namespace

std::vector<OutputFile>
content::renderer::html(const std::vector<SourceFile> &pages,
                        SourceType source_type)
{
    std::cout << "starting html operation" << "\n";

    std::vector<OutputFile> result;
    for (const auto &page : pages) {
        auto file = OutputFile{.path = create_dirs(page, source_type),
                               .content = build_content(page, source_type)};

        result.push_back(file);
    }

    std::cout << "done" << "\n";
    return result;
}
