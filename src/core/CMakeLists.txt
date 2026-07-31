add_library(staticierge_core
    cli.cpp
)

target_include_directories(staticierge_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(staticierge_core PRIVATE project_warnings)
