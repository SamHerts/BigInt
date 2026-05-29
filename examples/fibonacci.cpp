/**
 * Fibonacci Sequence Example
 * 
 * This example demonstrates calculating large Fibonacci numbers using BigInt.
 * Fibonacci numbers grow exponentially, and F(94) already exceeds the capacity 
 * of a 64-bit unsigned integer.
 */
#include <iostream>
#include "../bigint.h"

using namespace BigInt;

// Simple iterative Fibonacci implementation using bigint
bigint fibonacci(const bigint& n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    bigint a = 0;
    bigint b = 1;
    bigint f = 0;

    for (bigint i = 2; i <= n; ++i) {
        f = a + b;
        a = b;
        b = f;
    }
    return f;
}

int main() {
    const int max_n = 500;
    std::cout << "Calculating Fibonacci sequence up to F(" << max_n << ")..." << std::endl;

    for (int i = 0; i <= max_n; ++i) {
        std::cout << "F(" << i << ") = " << fibonacci(i) << std::endl;
    }
    
    return 0;
}