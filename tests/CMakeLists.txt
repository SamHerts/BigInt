cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(BigInt_gtest)

set(CMAKE_CXX_STANDARD 20)

# GTest download
enable_testing()
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 'Google_Tests_run' is the target name
# Add more tests and their dependencies here
file(GLOB Test_Sources *.cpp)
add_executable(BigInt_gtest ${Test_Sources})
target_link_libraries(BigInt_gtest gtest_main)
