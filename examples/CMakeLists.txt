# Fibonacci example
add_executable(fibonacci fibonacci.cpp)
target_link_libraries(fibonacci PRIVATE BigInt::BigInt)

# Pascal triangle example
add_executable(pascal_triangle pascal_triangle.cpp)
target_link_libraries(pascal_triangle PRIVATE BigInt::BigInt)

# Factorial example
add_executable(factorial factorial.cpp)
target_link_libraries(factorial PRIVATE BigInt::BigInt)
