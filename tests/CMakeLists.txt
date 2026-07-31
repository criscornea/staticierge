add_executable(staticierge_tests
    core/cli.cpp
)

# update list because of FetchContent
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(Catch)
catch_discover_tests(staticierge_tests)

target_include_directories(staticierge_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(staticierge_tests PRIVATE 
staticierge_core
Catch2::Catch2WithMain
)
