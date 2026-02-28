# BigInt

![example workflow](https://github.com/SamHerts/BigInt/actions/workflows/CI-CD.yml/badge.svg)  ![c++]( https://img.shields.io/badge/-c++11-blue?logo=c%2B%2B) ![c++]( https://img.shields.io/badge/-c++20-blue?logo=c%2B%2B)

## Overview

**BigInt** is a single-header C++ library designed to facilitate the creation and manipulation of arbitrary-sized integers. This lightweight and efficient library provides an easy-to-use interface for handling large integers that exceed the limits of built-in data types.

## Features

- **Arbitrary Integer Size**: Create integers of any size, limited only by available memory.
- **Basic Arithmetic Operations**: Support for addition, subtraction, multiplication, and division.
- **Advanced Computations**: Support for modulos, Square Roots, Powers, and Logarithms
- **Comparison Operators**: Full set of comparison operators (==, !=, <, <=, >, >=).
- **Stream Input/Output**: Easy input and output via standard streams.
- **Modular Design**: Simple and modular code for easy integration and extension.

## Getting Started

### Prerequisites

Ensure you have a C++11 (or higher) compatible compiler.

### Installation

Simply include the header file in your project.

1. Download `BigInt.h`.
2. Include it in your source file:
    ```cpp
    #include "BigInt.h"
    ```

### Usage

Below is a basic example demonstrating the usage of the library.

```cpp
#include <iostream>
#include "bigint.h"

int main() {
    bigint a("123456789012345678901234567890");
    bigint b("987654321098765432109876543210");

    bigint small_number = 10;
    bigint big_number = 789456123;

    bigint c = "123456789012345678901234567890";
    bigint d = "-987654321098765432109876543210";

    bigint sum = a + b;
    bigint diff = a - b;
    bigint product = a * b;
    bigint quotient = a / b;
    bigint modulo = a % b;

    std::cout << "a + b = " << sum << std::endl;
    std::cout << "a - b = " << diff << std::endl;
    std::cout << "a * b = " << product << std::endl;
    std::cout << "a / b = " << quotient << std::endl;
    std::cout << "a % b = " << modulo << std::endl;

    return 0;
}
```

### API Reference
Class: bigint
Constructors

    BigInt(): Default constructor.
    BigInt(const std::string& value): Constructs a BigInt from a string.
    BigInt(const BigInt& other): Copy constructor.

### Operators

    BigInt operator+(const BigInt& rhs) const: Addition.
    BigInt operator+=(const BigInt& rhs)

    BigInt operator-(const BigInt& rhs) const: Subtraction.
    BigInt operator-=(const BigInt& rhs)

    BigInt operator*(const BigInt& rhs) const: Multiplication.
    BigInt operator*=(const BigInt& rhs)

    BigInt operator/(const BigInt& rhs) const: Division.
    BigInt operator/=(const BigInt& rhs)

    BigInt operator%(const BigInt& rhs) const: Modulo.
    BigInt operator%=(const BigInt& rhs)

    bool operator==(const BigInt& rhs) const: Equality.

    bool operator!=(const BigInt& rhs) const: Inequality.

    bool operator<(const BigInt& rhs) const: Less than.

    bool operator<=(const BigInt& rhs) const: Less than or equal to.

    bool operator>(const BigInt& rhs) const: Greater than.

    bool operator>=(const BigInt& rhs) const: Greater than or equal to.    

### Member Functions

    bigint pow(const bigint &base, const bigint &exponent): Returns the base raised to the exponent

    bigint maximum(const bigint &lhs, const bigint &rhs): Returns the larger number
    
    bigint minimum(const bigint &lhs, const bigint &rhs): Returns the smaller number
    
    bigint abs(const bigint &s): Returns the absolute (positive) value
    
    bigint sqrt(const bigint &): Returns the square root
    
    bigint log2(const bigint &): Returns the binary log
    
    bigint log10(const bigint &): Returns the decimal log
    
    bigint logwithbase(const bigint &, const bigint &): Returns an arbitrary integer based log
    
    bigint antilog2(const bigint &): Returns the binary anti-log
    
    bigint antilog10(const bigint &): Returns the decimal anti-log
    
    void swap(bigint &, bigint &)
    
    bigint gcd(const bigint &, const bigint &): Returns the greatest common divisor
    
    bigint lcm(const bigint &lhs, const bigint &rhs): Returns the least common multiple
    
    bigint factorial(const bigint &): Returns n! = (n)*(n-1)...(n-k)
    
    bool is_even(const bigint &input)
    
    bool is_negative(const bigint &input)
    
    bool is_prime(const bigint &): Rudimentary prime check based on divisibility loop
    
    bigint sum_of_digits(const bigint& input)

### Stream Operators

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num): Output stream.    

### Build and Run Unit Tests

```bash
$ git clone https://github.com/SamHerts/BigInt.git
$ cd BigInt
$ cd tests
$ cmake .
$ make
$ ./BigInt_gtest
```

### Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request.

    Fork the repository.
    Create your feature branch (git checkout -b feature/NewFeature).
    Commit your changes (git commit -am 'Add some feature').
    Push to the branch (git push origin feature/NewFeature).
    Open a pull request.

### License

This project is licensed under the MIT License. See the LICENSE file for details.
Acknowledgments

Special thanks to the open-source community for their invaluable contributions and support.
