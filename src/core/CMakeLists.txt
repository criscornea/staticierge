add_library(staticierge_core
    cli.cpp
    filesystem.cpp
    settings.cpp
    renderer.cpp
    reader.cpp
)

target_compile_definitions(staticierge_core PRIVATE
    TOML_EXCEPTIONS=0
)

target_include_directories(staticierge_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(staticierge_core PRIVATE 
    staticierge_md
    project_warnings
    tomlplusplus::tomlplusplus
)
