add_executable(staticierge_tests
    core/cli.cpp
    core/filesystem.cpp
    core/settings.cpp
    core/reader.cpp
    core/renderer.cpp
    md/lexer.cpp
    md/parser.cpp
    md/html.cpp
    md/template.cpp
)

# update list because of FetchContent
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(Catch)
catch_discover_tests(staticierge_tests)

target_compile_definitions(staticierge_tests PRIVATE
    TOML_EXCEPTIONS=0
)

target_include_directories(staticierge_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(staticierge_tests PRIVATE 
    staticierge_core
    staticierge_md
    Catch2::Catch2WithMain
    tomlplusplus::tomlplusplus
)
