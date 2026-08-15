#include <algorithm>
#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <fstream>
#include <vector>

#include "filesystem.hpp"

namespace fs = std::filesystem;

class TempDir
{
  public:
    TempDir(fs::path root) : root_(std::move(root)) { fs::create_directories(root_); }
    ~TempDir() { fs::remove_all(root_); }

    auto path() const { return root_; }

    void create_subdir(const fs::path &relative) { fs::create_directories(root_ / relative); }

    void create_file(const fs::path &relative) { std::ofstream(root_ / relative); }

  private:
    fs::path root_;
};

TEST_CASE("find folders if they exist")
{
    TempDir td("test_folder");

    REQUIRE(filesystem::find_folder("test_folder").has_value());
    REQUIRE_FALSE(filesystem::find_folder("nonexisting_folder").has_value());
}

TEST_CASE("find markdown files")
{
    TempDir td("test_folder");
    td.create_subdir(".hidden");
    td.create_subdir("pages/blog");
    td.create_file("pages/test_page.md");
    td.create_file(".hidden/not_found_page.md");
    td.create_file("pages/blog/test_blog_page.md");
    td.create_file("pages/blog/not_a_md_file.txt");
    td.create_file("pages/blog/not_a_md_file");

    auto files = filesystem::find_markdown_files(td.path());
    REQUIRE(files.size() == 2);

    std::vector<fs::path> expected = {
        td.path() / "pages" / "blog" / "test_blog_page.md",
        td.path() / "pages" / "test_page.md",
    };
    REQUIRE(files == expected);
}
