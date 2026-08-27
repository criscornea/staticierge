#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include <string_view>

#include "settings.hpp"

class TempSettingsFile
{
  public:
    explicit TempSettingsFile() { create_file(); }
    ~TempSettingsFile() { delete_file(); }

    auto path() const { return path_.string(); }

  private:
    static constexpr const char *file_ = "settings.toml";
    std::filesystem::path path_{file_};

    void create_file()
    {
        std::ofstream settings(path_);

        settings << "[general]" << "\n";
        settings << "title = \"Test Settings\"" << "\n";

        settings << "[sources]" << "\n";
        settings << "folders = [" << "\n";
        settings << "{path = \"blog\", type = \"blog\"}," << "\n";
        settings << "{path = \"docs\", type = \"wiki\"}," << "\n";
        settings << "{path = \"static\", type = \"page\"}," << "\n";
        settings << "{path = \"assets\", type = \"asset\"}," << "\n";
        settings << "]" << "\n";

        settings.close();
    }

    void delete_file() const { std::remove(file_); }
};

auto get_settings()
{
    auto settings_file = TempSettingsFile();
    auto settings_path = settings_file.path();
    return settings::parse_file(settings_path);
}

TEST_CASE("parse settings file")
{
    auto settings = get_settings();

    // Ensure the created settings have all needed fields
    REQUIRE(settings["general"]["title"]);
    // TODO: extend as we add more fields
}

TEST_CASE("find sources")
{
    auto settings = get_settings();
    auto sources = settings::find_sources(settings);
    std::vector<Source> expected = {
        Source{.folder = "blog", .type = SourceType::BLOG},
        Source{.folder = "docs", .type = SourceType::WIKI},
        Source{.folder = "static", .type = SourceType::PAGE},
        Source{.folder = "assets", .type = SourceType::ASSET},
    };

    REQUIRE(sources == expected);
}
