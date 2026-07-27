cmake_minimum_required(VERSION 3.20)
project(staticierge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)

add_executable(staticierge
    src/main.cpp
    src/files.cpp
)

target_include_directories(staticierge PRIVATE src)
target_link_libraries(staticierge PRIVATE tomlplusplus::tomlplusplus)
