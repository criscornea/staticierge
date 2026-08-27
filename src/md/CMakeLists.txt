add_library(staticierge_md
    lexer.cpp
)

target_include_directories(staticierge_md PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(staticierge_md PRIVATE 
    project_warnings
)
