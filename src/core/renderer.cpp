#include "renderer.hpp"
#include "reader.hpp"
#include "settings.hpp"

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

namespace {
fs::path build_content(const SourceFile &page, SourceType type)
{
    // TODO: build
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

std::filesystem::path content::renderer::create_dirs(const SourceFile &page,
                                                     SourceType source_type)
{
    fs::path render_path;

    auto source_path = page.source_path;
    // TODO: split source path on /
    // TODO: create the folder structure in output path

    return render_path;
}
