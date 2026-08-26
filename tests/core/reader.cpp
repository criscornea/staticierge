#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string_view>

#include "reader.hpp"

namespace fs = std::filesystem;

class TempMdFile
{
  public:
    TempMdFile(const std::string_view &filename,
               const std::string_view &content)
    {
        path_ = fs::path(filename);
        std::ofstream file(path_.string());
        if (!file) {
            throw std::runtime_error("Could not open file");
        }

        file << content;
    }
    ~TempMdFile() { fs::remove(path_); }

    auto path() const { return path_; }

  private:
    std::filesystem::path path_;
};

TEST_CASE("test load")
{
    static constexpr std::string_view md_content = R"(+++
title = "Full Working Test"
+++

#A Headline

Some text)";
    auto md_file = TempMdFile("working.md", md_content);
    const SourceFile expected = {
        .source_path = md_file.path().string(),
        .title = "Full Working Test",
        .content = "\n\n#A Headline\n\nSome text",
    };

    auto file = content::reader::load(md_file.path());

    CHECK(file.value().source_path == expected.source_path);
    CHECK(file.value().title == expected.title);
    CHECK(file.value().content == expected.content);
}
