cmake_minimum_required(VERSION 3.10)
project(StringMatchingAlgorithms)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define include and source directories
include_directories(include)
file(GLOB SOURCES "src/*.cpp")
file(GLOB TEST_SOURCES "test/*.cpp")

# Main executable (for basic demonstration)
add_executable(main_exec src/main.cpp ${SOURCES})
target_include_directories(main_exec PRIVATE include)

# Test executable (for performance testing)
add_executable(test_runner test/test_runner.cpp test/utils.cpp ${SOURCES})
target_include_directories(test_runner PRIVATE include)

# Optional: output binaries to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
