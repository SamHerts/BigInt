# BigInt

![example workflow](https://github.com/SamHerts/BigInt/actions/workflows/CI-CD.yml/badge.svg)  ![c++]( https://img.shields.io/badge/-c++11-blue?logo=c%2B%2B) ![c++]( https://img.shields.io/badge/-c++20-blue?logo=c%2B%2B)

## Overview

**BigInt** is a single-header C++ library designed for arbitrary-precision integer arithmetic. It provides a lightweight, efficient, and easy-to-use interface for handling integers that exceed the limits of built-in types like `long long`.

## Features

- **Arbitrary Precision**: Limited only by available system memory.
- **Single-Header**: Easy integration; just drop `bigint.h` into your project.
- **Modern C++**: Support for C++11 and newer (C++20 compatible).
- **Rich Operator Support**: Full set of arithmetic, comparison, and increment/decrement operators.
- **Advanced Math**: Built-in support for GCD, LCM, Factorials, Power, Square Root, and Logarithms.
- **Hexadecimal Support**: Initialize big integers directly from hex strings.
- **STL Integration**: Includes a `std::hash` specialization for use in `unordered_map` and `unordered_set`.
- **Random Generation**: Static methods to generate cryptographically-seeded random big integers.

## Getting Started

### Prerequisites

A C++11 (or higher) compatible compiler (e.g., GCC 4.8+, Clang 3.3+, MSVC 2015+).

### Installation

Simply include the header file in your project.

1. Download `bigint.h`.
2. Include it in your source:
    ```cpp
    #include "bigint.h"
    ```

Note: All functionality resides within the `BigInt` namespace.

## Usage

```cpp
#include <iostream>
#include "bigint.h"

using BigInt::bigint;

int main() {
    // Initialization from strings (decimal or hex)
    bigint a("123456789012345678901234567890");
    bigint b("0xDEADC0DEFE777"); 

    // Initialization from primitive types
    bigint small = 10;
    bigint negative = -500;

    // Basic Arithmetic
    bigint sum = a + b;
    bigint prod = a * b;
    
    // Advanced Math
    bigint p = bigint::pow(2, 1024);
    bigint s = bigint::sqrt(a);

    std::cout << "2^1024 = " << p << std::endl;
    
    // STL Integration
    if (a > b) {
        std::cout << "a is larger" << std::endl;
    }

    return 0;
}
```

## API Reference

The library uses the class `BigInt::bigint`.

### Constructors
- `bigint()`: Defaults to 0.
- `bigint(const std::string&)`: From decimal or hex (starts with `0x`) string.
- `bigint(long long)`, `bigint(int)`, `bigint(double)`: From numeric types.
- `bigint(const char*)`: From C-style strings.

### Operators
- **Arithmetic**: `+`, `-`, `*`, `/`, `%`, `+=`, `-=`, `*=`, `/=`, `%=`
- **Comparison**: `==`, `!=`, `<`, `<=`, `>`, `>=`
- **Increment/Decrement**: Prefix and postfix `++`, `--`
- **Unary**: `-` (negation)
- **I/O**: `<<` (ostream)
- **Conversion**: `explicit operator bool()`, `explicit operator std::string()`, `explicit operator int()`, `explicit operator long long()`

### Static Member Functions (Mathematical)
- `bigint::pow(base, exp)`: Power function.
- `bigint::sqrt(n)`: Integer square root.
- `bigint::abs(n)`: Absolute value.
- `bigint::gcd(a, b)`, `bigint::lcm(a, b)`: Greatest Common Divisor and Least Common Multiple.
- `bigint::factorial(n)`: Factorial of n.
- `bigint::log2(n)`, `bigint::log10(n)`, `bigint::logwithbase(n, base)`: Logarithmic functions.
- `bigint::random(digits)`: Generates a random positive bigint with the specified number of digits.
- `bigint::is_prime(n)`: Basic primality test.
- `bigint::is_even(n)`, `bigint::is_negative(n)`: Property checks.

### Other Utilities
- `bigint::sum_of_digits(n)`: Returns the sum of all digits.
- `std::hash<BigInt::bigint>`: Specialization for hashing.

## Build and Run Unit Tests

The project uses GoogleTest for verification.

```bash
git clone https://github.com/SamHerts/BigInt.git
cd BigInt/tests
cmake -B build
cmake --build build
./build/BigInt_gtest
```

## Contributing

Contributions are welcome!
1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/NewFeature`).
3. Commit your changes.
4. Push to the branch.
5. Open a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
