/**
 * Factorial Calculation Example
 * 
 * This example demonstrates calculating large factorials using BigInt.
 * Factorials grow extremely fast; 21! already exceeds the capacity 
 * of a 64-bit unsigned integer.
 */
#include <iostream>
#include "../bigint.h"

using namespace BigInt;

// Iterative factorial implementation using bigint
bigint example_factorial(const bigint& n) {
    bigint ans = 1;
    for (bigint i = 2; i <= n; ++i) {
        ans = ans * i;
    }
    return ans;
}

int main() {
    const int max_val = 500;
    std::cout << "Calculating factorials up to " << max_val << "!" << std::endl;

    for (int i = 0; i <= max_val; ++i) {
        std::cout << i << "! = " << example_factorial(i) << std::endl;
    }

    // Demonstrate the built-in library function for comparison
    std::cout << "\nUsing library function bigint::factorial(" << max_val << "):" << std::endl;
    std::cout << bigint::factorial(max_val) << std::endl;

    return 0;
}