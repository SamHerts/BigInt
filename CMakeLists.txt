cmake_minimum_required(VERSION 3.25)
project(BigInt VERSION 1.2.0 LANGUAGES CXX)

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

# Detect if BigInt is being built as the main top-level project or as a dependency
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(BIGINT_IS_TOPLEVEL ON)
else()
    set(BIGINT_IS_TOPLEVEL OFF)
endif()

# Options
option(BIGINT_BUILD_EXAMPLES "Build example programs" ${BIGINT_IS_TOPLEVEL})
option(BIGINT_BUILD_TESTS "Build unit tests" ${BIGINT_IS_TOPLEVEL})

if(BIGINT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BIGINT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
