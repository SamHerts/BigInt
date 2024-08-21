/*
    BigInt Library for C++

    MIT License
    
    Copyright (c) 2024 Samuel Herts
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef BIGINT_H_
#define BIGINT_H_

#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <algorithm>
#include <random>
#include <iomanip>

namespace BigInt {

    class bigint {
    public:

        bigint() = default;

        bigint(const std::string &s)
        {
            if (!is_bigint(s))
                throw std::runtime_error("Invalid Big Integer.");
            if(s[0] == '-')
            {
                is_neg = true;
                vec = string_to_vector(s.substr(1));
            }
            else
            {
                vec = string_to_vector(s);
            }
        }

        bigint(const char c)
        {
            int temp = static_cast<int>(c);
            if (isdigit(temp)) {
                *this = bigint(char_to_int(c));
            } else {
                throw std::runtime_error("Invalid Big Integer has been fed.");
            }
        }

        bigint(unsigned int n) : bigint(static_cast<long long>(n)) {}

        bigint(int n) : bigint(static_cast<long long>(n)) {}

        bigint(long n) : bigint(static_cast<long long>(n)) {}

        bigint(double n) : bigint(static_cast<long long>(n)) {}

        bigint(long long n) {

//            if ( n >= 1000000000000000000)
            if ( n >= 1000000000000000000 || n <= -1000000000000000000)
            {
                vec.emplace_back(n / 1000000000000000000);
                vec.emplace_back(n % 1000000000000000000);
            }
            else{
                vec.emplace_back(n);
            }

            if (n < 0)
            {
                is_neg = true;
                for (auto& x : vec) { x = std::abs(x); }
            }
        }

        bigint(const bigint &n) { *this = n; }

        bigint(const char* string) : bigint(std::string(string)) {}

        bigint(std::vector<long long> n) {this->vec = n;}

        bigint& operator=(const bigint& other)
        {
            if (this == &other)
                return *this;
            this->is_neg = other.is_neg;
            this->vec = other.vec;

            return *this;
        }

        explicit operator int() const
        {
            return static_cast<int>(vec.back());
        }

        friend std::ostream &operator<<(std::ostream &stream, const bigint &n)
        {
            stream <<  vector_to_string(n.vec);
            return stream;
        }

        bigint operator+=(const bigint &rhs)
        {
            *this = add(*this, rhs);

//            else if (rhs.base_repr > 0 && this->base_repr > std::numeric_limits<long long>::max() - rhs.base_repr ||
//                rhs < 0 && this->base_repr < std::numeric_limits<long long>::min() - rhs.base_repr)
//            {
//                *this = add(std::to_string(this->base_repr), std::to_string(rhs.base_repr));
//            }
//            else
//            {
//                this->base_repr += rhs.base_repr;
//            }
            return *this;
        }

        inline bigint operator+(const bigint &rhs) const
        {
            bigint result = *this;
            result += rhs;
            return result;
        }

        bigint operator-=(const bigint &rhs)
        {

            *this = subtract(*this, rhs);

//            else if ((rhs.base_repr < 0 && this->base_repr > std::numeric_limits<long long>::max() + rhs.base_repr) ||
//                    (rhs > 0 && this->base_repr < std::numeric_limits<long long>::min() + rhs.base_repr))
//            {
//                *this = subtract(std::to_string(this->base_repr), std::to_string(rhs.base_repr));
//            }
//            else
//            {
//                this->base_repr -= rhs.base_repr;
//            }
            return *this;
        }

        inline bigint operator-(const bigint &rhs) const
        {
            bigint result = *this;
            result -= rhs;
            return result;
        }

        bigint operator*=(const bigint &rhs)
        {
            *this = multiply(*this, rhs);

//            else if ((this->base_repr == -1 && rhs.base_repr == std::numeric_limits<long long>::min()) ||
//                     (rhs.base_repr == -1 && this->base_repr == std::numeric_limits<long long>::min()) ||
//                     (rhs.base_repr != 0 &&
//                      this->base_repr > std::numeric_limits<long long>::max() / rhs.base_repr) ||
//                     (rhs.base_repr != 0 &&
//                      this->base_repr < std::numeric_limits<long long>::min() / rhs.base_repr))
//            {
//                *this = multiply(std::to_string(this->base_repr), std::to_string(rhs.base_repr));
//            }
//            else
//            {
//                this->base_repr *= rhs.base_repr;
//            }
            return *this;
        }

        inline bigint operator*(const bigint &rhs) const
        {
            bigint result = *this;
            result *= rhs;
            return result;
        }

        bigint &operator/=(const bigint &rhs)
        {
            *this = divide(*this, rhs);
            return *this;
        }

        inline bigint operator/(const bigint &rhs) const
        {
            bigint result = *this;
            result /= rhs;
            return result;
        }

        bigint operator%=(const bigint &rhs)
        {
            *this = mod(*this, rhs);
            return *this;
        }

        inline bigint operator%(const bigint &rhs) const
        {
            bigint result = *this;
            result %= rhs;
            return result;
        }

        bigint operator++()
        {
            *this += 1;
            return *this;
        }

        bigint operator++(int)
        {
            bigint tmp(*this);
            operator++();
            return tmp;
        }

        bigint operator--()
        {
            *this -= 1;
            return *this;
        }

        bigint operator--(int)
        {
            bigint tmp(*this);
            operator--();
            return tmp;
        }

        friend bool operator==(const bigint &l, const bigint &r)
        {
            if (l.is_neg != r.is_neg)
            {
                return false;
            }
            return l.vec == r.vec;
        }

        friend bool operator!=(const bigint &l, const bigint &r)
        { return !(l == r); }

        friend bool operator<(const bigint &lhs, const bigint &rhs)
        {
            return less_than(lhs, rhs);
        }

        friend bool operator>(const bigint &l, const bigint &r)
        { return r < l; }

        friend bool operator<=(const bigint &l, const bigint &r)
        { return !(r < l); }

        friend bool operator>=(const bigint &l, const bigint &r)
        { return !(l < r); }

        explicit operator bool() const
        {
            return !(this->vec.empty()) || this->vec.front();
        }

        friend std::hash<bigint>;

        inline static bigint pow(const bigint &base, const bigint &exponent)
        {
            if (exponent == 0) return 1;
            if (exponent == 1) return base;

            bigint tmp = pow(base, exponent / 2);
            if (exponent % 2 == 0) return tmp * tmp;
            else return base * tmp * tmp;
        }

        inline static bigint maximum(const bigint &lhs, const bigint &rhs)
        {
            return lhs > rhs ? lhs : rhs;
        }

        inline static bigint minimum(const bigint &lhs, const bigint &rhs)
        {
            return lhs > rhs ? rhs : lhs;
        }

        inline static bigint abs(const bigint &s)
        {
            if (is_negative(s))
            {
                bigint temp = s;
                temp.is_neg = false;

                return temp;
            }

            return s;
        }

        static bigint sqrt(const bigint &);

        static bigint log2(const bigint &);

        static bigint log10(const bigint &);

        static bigint logwithbase(const bigint &, const bigint &);

        static bigint antilog2(const bigint &);

        static bigint antilog10(const bigint &);

        static void swap(bigint &, bigint &);

        static bigint gcd(const bigint &, const bigint &);

        inline static bigint lcm(const bigint &lhs, const bigint &rhs)
        {
            return (lhs * rhs) / gcd(lhs, rhs);
        }

        static bigint factorial(const bigint &);

        inline static bool is_even(const bigint &input)
        {
            return !(input.vec.back() & 1);
        }

        inline static bool is_negative(const bigint &input)
        {
            return input.is_neg;
        }

        static bool is_prime(const bigint &);

        inline static bigint sum_of_digits(const bigint& input)
        {
            bigint sum;
            for (auto base : input.vec) {
                for (sum = 0; base > 0; sum += base % 10, base /= 10);
            }
            return sum;
        }

        static bigint random(size_t length);

    private:
        std::vector<long long> vec{};
        bool is_neg{};

        // Function Definitions for Internal Uses

        static bigint trim(const bigint& input) {
            auto temp = input;
            while (temp.vec.front() == 0){
                temp.vec.erase(temp.vec.begin());
            }
            return temp;
        }

        static std::vector<long long> string_to_vector(std::string input);

        static std::string vector_to_string(const std::vector<long long>& input);

        static bigint add(const bigint &, const bigint &);

        static bigint subtract(const bigint &, const bigint &);

        static bigint multiply(const bigint &, const bigint &);

        static bigint divide(const bigint &, const bigint &);

        inline static bigint mod(const bigint &lhs, const bigint &rhs)
        {
            if (lhs < rhs) {
                return lhs;
            }
            if (lhs == rhs) {
                return 0;
            }

            if (rhs == 2)
            {
                return !is_even(lhs);
            }

            return lhs - ((lhs / rhs) * rhs);
        }

        static bool is_bigint(const std::string &);

        inline static int char_to_int(const char input)
        {
            return input - '0';
        }

        inline static int int_to_char(const int input)
        {
            return input + '0';
        }

        inline static bigint negate(const bigint& input)
        {
            bigint temp = input;
            temp.is_neg = true;
            return temp;
        }

        inline static bool less_than(const bigint& lhs, const bigint& rhs)
        {
            if (is_negative(lhs) && is_negative(rhs))
            {
                return less_than(abs(rhs), abs(lhs));
            }

            if (is_negative(lhs) || is_negative(rhs))
            {
                return is_negative(lhs);
            }

            if(lhs.vec.size() == rhs.vec.size())
            {
                return lhs.vec < rhs.vec;
            }

            return lhs.vec.size() < rhs.vec.size();
        }
    };


    inline bool bigint::is_bigint(const std::string &s)
    {                              // Checks if the input integer is valid Number or not.
        if (s.empty())
            return false;

        if (s[0] == '-') {
            return s.find_first_not_of("0123456789", 1) == std::string::npos;
        }
        return s.find_first_not_of("0123456789", 0) == std::string::npos;
    }

    template <class T>
    int numDigits(T number)
    {
        int digits = 0;
        if (number < 0) digits = 1; // remove this line if '-' counts as a digit
        while (number) {
            number /= 10;
            digits++;
        }
        return digits;
    }

    std::pair<int, long long> add_with_carry(long long lhs, long long rhs)
    {
        long long max_number = 1000000000000000000;
        auto sum = lhs + rhs;

        if (sum >= max_number)
        {
            // Carry needs to happen
            auto carry = sum / max_number;
            auto result = sum % max_number;
            return {carry, result};
        }
        else
        {
            return {0, sum};
        }
    }

    inline bigint bigint::add(const bigint &lhs, const bigint &rhs)
    {
        // Ensure LHS is larger than RHS, and both are positive
        if (is_negative(lhs) && is_negative(rhs))
        {
            return negate(add(abs(lhs) ,abs(rhs)));
        }
        if (is_negative(lhs))
        {
            return rhs - abs(lhs);
        }
        if (is_negative(rhs))
        {
            return lhs - abs(rhs);
        }

        if (lhs < rhs)
        {
            return add(rhs, lhs);
        }

        bigint full_rhs =  rhs;
        std::vector<std::pair<int, long long>> carry_result(lhs.vec.size() + 1);

        // Fill the smaller to match the larger size
        while (lhs.vec.size() > full_rhs.vec.size())
        {
            full_rhs.vec.insert(full_rhs.vec.begin(), 0);
        }
//        auto my_lambda = [&](const auto& first, const auto& second)
//        {
//            if ( numDigits(first + second) > 18)
//            return first + second;
//        };

        std::transform(lhs.vec.rbegin(), lhs.vec.rend(), full_rhs.vec.rbegin(), carry_result.rbegin(), add_with_carry);

        std::vector<long long> final(lhs.vec.size() + 1);
        for (int i = carry_result.size() - 1; i >= 0; --i) {
            final[i] += carry_result[i].second;
            final[i - 1] += carry_result[i].first;
        }

        return trim(bigint(final));
    }

    std::pair<int, long long> subtract_with_borrow(long long lhs, long long rhs)
    {
        long long max_number = 1000000000000000000;

        if (lhs < rhs)
        {
            // Borrow needs to happen
            auto result = (lhs + max_number) - rhs;
            return {1, result}; // 1 represents a borrow
        }
        else
        {
            auto result = lhs - rhs;
            return {0, result}; // 0 means no borrow
        }
    }


    inline bigint bigint::subtract(const bigint &lhs, const bigint &rhs)
    {
        // Ensure LHS is larger than RHS, and both are positive
        if (lhs == rhs)
        {
            return 0;
        }

        if (is_negative(lhs) && is_negative(rhs))
        {
            return subtract(abs(rhs), abs(lhs));
        }

        if (is_negative(rhs))
        {
            return add(lhs, abs(rhs));
        }

        if (is_negative(lhs))
        {
            return add(lhs, negate(rhs));
        }

        if (lhs < rhs)
        {
            return negate(subtract(rhs, lhs));
        }

        bigint full_rhs =  rhs;
        std::vector<std::pair<int, long long>> borrow_result(lhs.vec.size());
        // Fill the smaller to match the larger size
        while (lhs.vec.size() > full_rhs.vec.size())
        {
            full_rhs.vec.insert(full_rhs.vec.begin(), 0);
        }

        std::transform(lhs.vec.rbegin(), lhs.vec.rend(), full_rhs.vec.rbegin(), borrow_result.rbegin(),
                       subtract_with_borrow);

        std::vector<long long> final(lhs.vec.size());
        for (int i = borrow_result.size() - 1; i >= 0; --i) {
            final[i] += borrow_result[i].second;
            if (borrow_result[i].first)
                final[i - 1] -= borrow_result[i].first;
        }

        return trim(final);
    }

    inline bigint bigint::multiply(const bigint &lhs, const bigint &rhs)
    {
        if (is_negative(lhs) && is_negative(rhs)) {
            return (abs(lhs) * abs(lhs));
        }
        if (is_negative(lhs) || is_negative(rhs)) {
            return negate(abs(lhs) * abs(rhs));
        }

        bigint ans;
        return ans;
    }


    inline bigint bigint::divide(const bigint &numerator, const bigint &denominator)
    {                   // return arithmetic division of str1/str2

        if (denominator == 0) {
            throw std::domain_error("Attempted to divide by zero.");
        }
        if (numerator == denominator)
        {
            return 1;
        }

        if (denominator == 1) {
            return numerator;
        }

        if (numerator == 0) {
            return 0;
        }

        if (is_negative(numerator) && is_negative(denominator))
        {
            return divide(abs(numerator), abs(denominator));
        }
        else if (is_negative(numerator) || is_negative(denominator))
        {
            return negate(divide(abs(numerator), abs(denominator)));
        }

        if (denominator > numerator)
        {
            return 0;
        }


        bigint ans;
        return ans;
    }

    inline bigint bigint::sqrt(const bigint &input)
    {
        if (is_negative(input))
            throw std::domain_error("Square root of a negative number is complex");

        if (input == 0 || input == 1)
            return input;

        bigint oom = log10(input / 2);
        oom /= 2;
        bigint low_end = pow(10, (oom));
        bigint high_end = pow(10, (oom) + 2);
        bigint mid_point, square, answer;
        while (low_end <= high_end) {
            mid_point = (low_end + high_end) / 2;
            square = mid_point * mid_point;
            if (square == input)
                return mid_point;

            if (square < input) {
                low_end = mid_point + 1;
                answer = mid_point;
            } else {
                high_end = mid_point - 1;
            }
        }
        return answer;
    }


    inline bigint bigint::log2(const bigint &input)
    {
        if (is_negative(input) || input == 0)
            throw std::domain_error("Invalid input for natural log");

        if (input == 1)
            return 0;

        if (input.vec.size() == 1) {
            return std::log2(input.vec.back());
        }

        bigint exponent = 0;
        while (pow(2, exponent) <= input) {
            ++exponent;
        }

        return exponent;
        // TODO: Convert to using division after checking big O of division vs multiplication
//    std::string logVal = "-1";
//    while(s != "0") {
//        logVal = add(logVal, "1");
//        s = divide(s, "2");
//    }
//    return logVal;
    }

    inline bigint bigint::log10(const bigint &input)
    {
        if (is_negative(input) || input == 0)
            throw std::domain_error("Invalid input for log base 10");

        if (input == 1)
            return 0;

        if (input.vec.size() == 1) {
            return std::log10(input.vec.back());
        }
        int count = 0;
        for (auto number : input.vec) {
            count += numDigits(number);
        }

        return count - 1;
    }

    inline bigint bigint::logwithbase(const bigint &input, const bigint &base)
    {
        return divide(log2(input), log2(base));
    }

    inline bigint bigint::antilog2(const bigint &input)
    {
        return pow(2, input);
    }

    inline bigint bigint::antilog10(const bigint &input)
    {
        return pow(10, input);
    }

    inline void bigint::swap(bigint &lhs, bigint &rhs)
    {
        bigint temp;
        temp = lhs;
        lhs = rhs;
        rhs = temp;
    }

    inline bigint bigint::gcd(const bigint &lhs, const bigint &rhs)
    {
        bigint temp_l = lhs, temp_r = rhs, remainder;
        if (rhs > lhs)
            swap(temp_l, temp_r);

        while (rhs > 0) {
            remainder = temp_l % temp_r;
            temp_l = temp_r;
            temp_r = remainder;
        }
        return temp_l;
    }

    inline bigint bigint::factorial(const bigint &input)
    {
        if (is_negative(input)) {
            throw std::runtime_error("Factorial of Negative Integer is not defined.");
        }
        if (input == 0)
            return 1;

        bigint ans = 1;
        bigint temp = input;
        while (temp != 0) {
            ans *= temp;
            temp -= 1;
        }
        return ans;
    }

    inline bool bigint::is_prime(const bigint &s)
    {
        if (is_negative(s) || s == 1)
            return false;

        if (s == 2 || s == 3 || s == 5)
            return true;

        if (is_even(s) || s % 5 == 0)
            return false;


        bigint i;
        for (i = 3; i * i <= s; i += 2) {
            if ((s % i) == 0) {
                return false;
            }
        }
        return true;
    }

    bigint bigint::random(size_t length) {
        const char charset[] = "0123456789";
        std::default_random_engine rng(std::random_device{}());

        // Distribution for the first digit (1-9)
        std::uniform_int_distribution<> first_dist(1, 9);
        // Distribution for the other digits (0-9)
        std::uniform_int_distribution<> dist(0, 9);

        // Lambda to generate the first character
        auto randchar_first = [charset, &first_dist, &rng]() { return charset[first_dist(rng)]; };
        // Lambda to generate subsequent characters
        auto randchar = [charset, &dist, &rng]() { return charset[dist(rng)]; };

        // Create a string with the specified length
        std::string str(length, 0);

        // Generate the first character separately to ensure it's not '0'
        str[0] = randchar_first();

        // Generate the remaining characters
        std::generate_n(str.begin() + 1, length - 1, randchar);

        return {str};
    }

    std::vector<long long> bigint::string_to_vector(std::string input) {
        // Break into chunks of 18 characters
        std::vector<long long> result;
        int chunk_size = 18;

        if (input.size() > chunk_size)
        {
            // Pad the length to get appropriate sized chunks
            while ( input.size() % chunk_size != 0)
            {
                input.insert(0, "0");
            }
        }
        for (int i = 0; i < input.size(); i+=chunk_size)
        {
            std::string temp_str = input.substr(i, chunk_size);
            result.emplace_back(stoll(temp_str));
        }

        return result;
    }

    std::string bigint::vector_to_string(const std::vector<long long>& input) {
        std::stringstream ss;
        bool first = true;
        for (auto partial : input) {
            if (first) {
                ss << partial;  // No padding for the first number
                first = false;
            } else {
                ss << std::setw(18) << std::setfill('0') << partial;  // Pad to 18 digits
            }
        }
        return ss.str();
    }

} // namespace::BigInt

namespace std {
    template<>
    struct hash<BigInt::bigint> {
        std::size_t operator()(const BigInt::bigint& input) const
        {
            std::size_t seed = input.vec.size();
            for(auto x : input.vec) {
                x = ((x >> 16) ^ x) * 0x45d9f3b;
                x = ((x >> 16) ^ x) * 0x45d9f3b;
                x = (x >> 16) ^ x;
                seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

#endif /* BIGINT_H_ */
