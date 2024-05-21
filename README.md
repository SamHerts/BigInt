# BigInt

## Overview

**BigInt** is a single-header C++ library designed to facilitate the creation and manipulation of arbitrary-sized integers. This lightweight and efficient library provides an easy-to-use interface for handling large integers that exceed the limits of built-in data types.

## Features

- **Unlimited Integer Size**: Create integers of any size, limited only by available memory.
- **Basic Arithmetic Operations**: Support for addition, subtraction, multiplication, and division.
- **Advanced Computations**: Support for modulos, Square Roots, Powers, and Logarithms
- **Comparison Operators**: Full set of comparison operators (==, !=, <, <=, >, >=).
- **Stream Input/Output**: Easy input and output via standard streams.
- **Modular Design**: Simple and modular code for easy integration and extension.

## Getting Started

### Prerequisites

Ensure you have a C++20 compatible compiler.

### Installation

Simply include the header file in your project.

1. Download `BigInt.hpp`.
2. Include it in your source file:
    ```cpp
    #include "BigInt.hpp"
    ```

### Usage

Below is a basic example demonstrating the usage of the library.

```cpp
#include <iostream>
#include "bigint.hpp"

int main() {
    bigint a("123456789012345678901234567890");
    bigint b("987654321098765432109876543210");

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

    BigInt operator-(const BigInt& rhs) const: Subtraction.

    BigInt operator*(const BigInt& rhs) const: Multiplication.

    BigInt operator/(const BigInt& rhs) const: Division.

    bool operator==(const BigInt& rhs) const: Equality.

    bool operator!=(const BigInt& rhs) const: Inequality.

    bool operator<(const BigInt& rhs) const: Less than.

    bool operator<=(const BigInt& rhs) const: Less than or equal to.

    bool operator>(const BigInt& rhs) const: Greater than.

    bool operator>=(const BigInt& rhs) const: Greater than or equal to.

    bool operator%(const bigint &rhs) const: Modulo.

### Member Functions

    inline  bigint pow(const bigint &base, const bigint &exponent)

    bigint maximum(const bigint &lhs, const bigint &rhs)
    
    bigint minimum(const bigint &lhs, const bigint &rhs)
    
    bigint abs(const bigint &s)
    
    bigint sqrt(const bigint &);
    
    bigint log2(const bigint &);
    
    bigint log10(const bigint &);
    
    bigint logwithbase(const bigint &, const bigint &);
    
    bigint antilog2(const bigint &);
    
    bigint antilog10(const bigint &);
    
    void swap(bigint &, bigint &);
    
    bigint gcd(const bigint &, const bigint &);
    
    bigint lcm(const bigint &lhs, const bigint &rhs)
    
    bigint factorial(const bigint &);
    
    bool is_even(const bigint &input)
    
    bool is_negative(const bigint &input)
    
    bool is_prime(const bigint &);
    
    bigint sum_of_digits(const bigint& input)

### Stream Operators

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num): Output stream.    

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
