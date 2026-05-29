cmake_minimum_required(VERSION 3.25)
project(BigInt VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Interface library for header-only BigInt
add_library(BigInt INTERFACE)
add_library(BigInt::BigInt ALIAS BigInt)

target_include_directories(BigInt INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Options
option(BIGINT_BUILD_EXAMPLES "Build example programs" ON)
option(BIGINT_BUILD_TESTS "Build unit tests" ON)

if(BIGINT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BIGINT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
