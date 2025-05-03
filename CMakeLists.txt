cmake_minimum_required(VERSION 3.10)
project(StringMatchingAlgorithms)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configure header
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}")
configure_file(config.h.in config.h)

# Define include and source directories
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

# Optional: output binaries to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(test_naive mains/test_naive.cpp ${SOURCES})
target_include_directories(test_naive PRIVATE include ${CMAKE_BINARY_DIR})

add_executable(test_kmp mains/test_kmp.cpp ${SOURCES})
target_include_directories(test_kmp PRIVATE include ${CMAKE_BINARY_DIR})

add_executable(test_bm mains/test_bm.cpp ${SOURCES})
target_include_directories(test_bm PRIVATE include ${CMAKE_BINARY_DIR})

add_executable(test_rk mains/test_rk.cpp ${SOURCES})
target_include_directories(test_rk PRIVATE include ${CMAKE_BINARY_DIR})
