cmake_minimum_required(VERSION 3.16)

# Project info
project(SnakeRetro VERSION 1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build types
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release) # Default to Release
endif()

# Compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Include dirs
include_directories(include)

# Find raylib
find_package(raylib REQUIRED)

# Executable
add_executable(SnakeRetro ${SOURCES})

# Link libraries
target_link_libraries(SnakeRetro raylib)

# Assets copy (optional for clean builds)
add_custom_command(TARGET SnakeRetro POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:SnakeRetro>/assets
)

# Optionally: Enable tests
# enable_testing()
# add_subdirectory(tests)
