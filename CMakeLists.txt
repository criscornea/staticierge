cmake_minimum_required(VERSION 3.20)
project(staticierge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Toml++
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(tomlplusplus)

# Catch2
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.15.3
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(Catch2)

# Compiler warnings
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
    -Wall
    -Wextra
)

# Sanitizer
option(ENABLE_SANITIZERS "Enable AddressSanitizer + UndefinedBehaviorSanitizer" OFF)

add_library(project_sanitizers INTERFACE)
if(ENABLE_SANITIZERS)
    target_compile_options(project_sanitizers INTERFACE
        -fsanitize=undefined
        -fno-omit-frame-pointer
    )
    target_link_options(project_sanitizers INTERFACE
        -fsanitize=undefined
    )
endif()

# Tests
enable_testing()
include(CTest)

# Executable
add_subdirectory(tests)
add_subdirectory(src/core)
add_subdirectory(src/md)
add_executable(staticierge
    src/main.cpp
)

target_include_directories(staticierge PRIVATE src)
target_link_libraries(staticierge PRIVATE 
    staticierge_core
    staticierge_md
    project_warnings
    project_sanitizers
)
