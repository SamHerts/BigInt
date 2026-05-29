# GTest download
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.17.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Unit tests executable
file(GLOB Test_Sources *.cpp)
add_executable(BigInt_tests ${Test_Sources})
target_link_libraries(BigInt_tests PRIVATE BigInt::BigInt gtest_main)

add_test(NAME BigInt_Tests COMMAND BigInt_tests)
