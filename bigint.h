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

namespace bigint_ns {

    class bigint {
    private:

        // Function Definitions for Internal Uses
        static std::string trim(std::string);

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
//            if (rhs == 3)
//            {
//                auto sum = sum_of_digits(lhs);
//                while (sum > 10)
//                    sum = sum_of_digits(sum);
//                return sum % 3;
//            }

            return lhs - ((lhs / rhs) * rhs);
        }

        static std::string shortDivide(std::string, unsigned long long int);

        static bool is_bigint(const std::string &);

        inline static int char_to_int(const char input)
        {
            return input - '0';
        }

        inline static int int_to_char(const int input)
        {
            return input + '0';
        }

        inline static bigint negate(bigint input)
        {
            return input.str.insert(0, "-");
        }

    public:
        bool is_big = false;
        std::string str;
        long long int base_repr{};

        bigint() = default;

        bigint(const std::string &s)
        {
            if (!is_bigint(s))
                throw std::runtime_error(
                        "Invalid Big Integer.");  
            str = s;
            is_big = true;
        }

        bigint(const char c)
        {
            int temp = static_cast<int>(c);
            if (isdigit(temp)) {
                base_repr = char_to_int(c);
            } else {
                throw std::runtime_error("Invalid Big Integer has been fed.");
            }
        }

        bigint(unsigned int n) : bigint(static_cast<long long>(n))
        {}

        bigint(int n) : bigint(static_cast<long long>(n))
        {}

        bigint(long n) : bigint(static_cast<long long>(n))
        {}

        bigint(double n) : bigint(static_cast<long long>(n))
        {}

        bigint(long long n)
        {
            base_repr = n;
        }

        bigint(const bigint &n)
        {
            is_big = n.is_big;
            if (is_big)
                str = n.str;
            else
                base_repr = n.base_repr;
        }

        bigint(const char *string) : bigint(std::string(string)) {}

        bigint &operator=(const bigint &other)
        {
            if (this == &other)
                return *this;
            this->is_big = other.is_big;
            if (this->is_big)
            {
                this->str = other.str;
            }
            else
            {
                this->base_repr = other.base_repr;
            }

            return *this;
        }

        explicit operator int() const
        {
            if (!is_big) {
                return base_repr;
            }
            std::stringstream ss(str);
            int num;
            ss >> num;
            return num;
        }

        friend std::ostream &operator<<(std::ostream &stream, const bigint &n)
        {
            stream << (n.is_big ? n.str : std::to_string(n.base_repr));
            return stream;
        }

        bigint operator+=(const bigint &rhs)
        {
            if (this->is_big || rhs.is_big)
            {
                *this = add(this->is_big ? this->str : std::to_string(this->base_repr), rhs.is_big ? rhs.str : std::to_string(rhs.base_repr));
            }
            else if (rhs.base_repr > 0 && this->base_repr > std::numeric_limits<long long>::max() - rhs.base_repr ||
                rhs < 0 && this->base_repr < std::numeric_limits<long long>::min() - rhs.base_repr)
            {
                *this = add(std::to_string(this->base_repr), std::to_string(rhs.base_repr));
            }
            else
            {
                this->base_repr += rhs.base_repr;
            }
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
            if (this->is_big || rhs.is_big)
            {
                *this = subtract(this->is_big ? this->str : std::to_string(this->base_repr), rhs.is_big ? rhs.str : std::to_string(rhs.base_repr));
            }
            else if ((rhs.base_repr < 0 && this->base_repr > std::numeric_limits<long long>::max() + rhs.base_repr) ||
                    (rhs > 0 && this->base_repr < std::numeric_limits<long long>::min() + rhs.base_repr))
            {
                *this = subtract(std::to_string(this->base_repr), std::to_string(rhs.base_repr));
            }
            else
            {
                this->base_repr -= rhs.base_repr;
            }
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
            if (!this->is_big) {
                if (!rhs.is_big) {
                    if ((this->base_repr == -1 && rhs.base_repr == std::numeric_limits<long long>::min()) ||
                        (rhs.base_repr == -1 && this->base_repr == std::numeric_limits<long long>::min()) ||
                        (rhs.base_repr != 0 &&
                         this->base_repr > std::numeric_limits<long long>::max() / rhs.base_repr) ||
                        (rhs.base_repr != 0 &&
                         this->base_repr < std::numeric_limits<long long>::min() / rhs.base_repr))
                    {
                        *this = multiply(std::to_string(this->base_repr), std::to_string(rhs.base_repr));
                    }
                    else
                    {
                        this->base_repr *= rhs.base_repr;
                    }
                }
                else
                {
                    *this = multiply(std::to_string(this->base_repr), rhs.str);
                }
            }
            else
            {
                if (!rhs.is_big)
                {
                    *this = multiply(this->str, std::to_string(rhs.base_repr));
                }
                else
                {
                    *this = multiply(this->str, rhs.str);
                }
            }
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
            if (!this->is_big) {
                if (!rhs.is_big) {
                    this->base_repr /= rhs.base_repr;
                } else {
                    *this = divide(std::to_string(this->base_repr), rhs.str);
                }
            } else {
                if (!rhs.is_big)
                {
                    *this = divide( this->str, std::to_string(rhs.base_repr));
                }
                else{
                    *this = divide(this->str, rhs.str);
                }
            }
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
            if (!this->is_big) {
                if (!rhs.is_big) {
                    this->base_repr %= rhs.base_repr;
                } else {
                    *this = mod(std::to_string(this->base_repr), rhs.str);
                }
            } else {
                if (!rhs.is_big) {
                    *this = mod(this->str, std::to_string(rhs.base_repr));
                }
                else {
                    *this = mod(this->str, rhs.str);
                }
            }

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
            if (l.is_big || r.is_big)
            {
                return (l.is_big ? l.str : std::to_string(l.base_repr)) ==
                       (r.is_big ? r.str : std::to_string(r.base_repr));
            }
            return l.base_repr == r.base_repr;
        }

        friend bool operator!=(const bigint &l, const bigint &r)
        { return !(l == r); }

        // Relational comparisons:
        // implementing a lexicographical comparison which induces a
        // strict weak ordering.
        friend bool operator<(const bigint &lhs, const bigint &rhs)
        {
            if (!lhs.is_big) {
                if (!rhs.is_big) {
                    return lhs.base_repr < rhs.base_repr;
                }
                // TODO: Implement half
                auto temp = std::to_string(lhs.base_repr);
                if(temp.length() == rhs.str.length())
                {
                    return temp < rhs.str;
                }

                return temp.length() < rhs.str.length();
            }

            if (is_negative(lhs) && is_negative(rhs)) {
                return abs(lhs) > abs(rhs);
            }

            if (is_negative(lhs)) {
                return true;
            }

            if (is_negative(rhs)) {
                return false;
            }

            if(lhs.str.length() == rhs.str.length())
            {
                return lhs.str < rhs.str;
            }

            return lhs.str.length() < rhs.str.length();
        }

        friend bool operator>(const bigint &l, const bigint &r)
        { return r < l; }

        friend bool operator<=(const bigint &l, const bigint &r)
        { return !(r < l); }

        friend bool operator>=(const bigint &l, const bigint &r)
        { return !(l < r); }


        explicit operator bool() const
        {
            if (!this->is_big) {
                return this->base_repr;
            }
            return this->str != "0";
        }

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
            if (!s.is_big) {
                return std::abs(s.base_repr);
            }
            if (is_negative(s))
                return s.str.substr(1, s.str.length() - 1);

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
            if (!input.is_big) {
                bool temp = input.base_repr & 1;
                bool temp2 = !temp;
                return temp2;
//            return !(input.base_repr & 1);
            }
            return (input.str.ends_with("0") || input.str.ends_with("2") || input.str.ends_with("4") ||
                    input.str.ends_with("6") || input.str.ends_with("8"));
        }

        inline static bool is_negative(const bigint &input)
        {
            return !input.is_big ? input.base_repr < 0 : input.str[0] == '-';
        }

        static bool is_prime(const bigint &);

        inline static bigint sum_of_digits(const bigint& input)
        {
            bigint sum;
            if (input.is_big)
            {
                for (auto c : input.str)
                {
                    sum += (c - '0');
                }
            }
            else
            {
                auto base = input.base_repr;
                for (sum = 0; base > 0; sum += base % 10, base /= 10);
            }
            return sum;
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

    struct KeyHasher {
        std::size_t operator()(const bigint &k) const
        {
            using std::size_t;
            using std::hash;
            using std::string;

            return (hash<string>()(k.str) >> 1) ^ hash<long long>()(k.base_repr) << 1;
        }
    };

    inline bigint bigint::add(const bigint &lhs, const bigint &rhs)
    {
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

        // Actual string addition implementation
        int lhs_length = lhs.str.length();
        int rhs_length = rhs.str.length();
        int max_length = std::max(lhs_length, rhs_length);
        std::string result;
        int carry = 0;

        for (int i = 0; i < max_length; ++i)
        {
            auto digit_1 = i < lhs_length ? char_to_int(lhs.str[lhs_length - 1 - i]) : 0;
            auto digit_2 = i < rhs_length ? char_to_int(rhs.str[rhs_length - 1 - i]) : 0;

            int sum = digit_1 + digit_2 + carry;
            carry = sum / 10;
            sum = sum % 10;

            result.push_back(int_to_char(sum));
        }

        if (carry > 0)
        {
            result.push_back(int_to_char(carry));
        }

        std::reverse(result.begin(), result.end());

        return result;

    }

    inline bigint bigint::subtract(const bigint &lhs, const bigint &rhs)
    {
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

        // Actual string subtraction implementation
        int lhs_length = lhs.str.size();
        int rhs_length = rhs.str.size();
        std::string result;
        int borrow = 0;

        // Subtract digits from right to left
        for (int i = 0; i < lhs_length; ++i) {
            int digit1 = char_to_int(lhs.str[lhs_length - 1 - i]);
            int digit2 = (i < rhs_length) ? char_to_int(rhs.str[rhs_length - 1 - i]) : 0;

            // Apply borrow if necessary
            digit1 -= borrow;

            if (digit1 < digit2)
            {
                digit1 += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            int diff = digit1 - digit2;
            result.push_back(int_to_char(diff));
        }

        // The result is currently in reverse order
        std::reverse(result.begin(), result.end());

        // Remove leading zeros from the result

        return trim(result);;
    }

    inline bigint bigint::multiply(const bigint &lhs, const bigint &rhs)
    {
        if (is_negative(lhs) && is_negative(rhs)) {
            return (abs(lhs) * abs(lhs));
        }
        if (is_negative(lhs) || is_negative(rhs)) {
            return negate(abs(lhs) * abs(rhs));
        }

        std::string ans = "";

        int str1_len = lhs.str.length();
        int str2_len = rhs.str.length();
        std::vector<int> result(str1_len + str2_len, 0);
        int i_n1 = 0;
        int i_n2 = 0;
        for (int i = str1_len - 1; i >= 0; i--) {
            int carry = 0;
            int n1 = lhs.str[i] - '0';
            i_n2 = 0;
            for (int j = str2_len - 1; j >= 0; j--) {
                int n2 = rhs.str[j] - '0';
                int sum = n1 * n2 + result[i_n1 + i_n2] + carry;
                carry = sum / 10;
                result[i_n1 + i_n2] = sum % 10;
                i_n2++;
            }
            if (carry > 0) {
                result[i_n1 + i_n2] += carry;
            }
            i_n1++;
        }
        int i = result.size() - 1;
        while (i >= 0 && result[i] == 0) {
            i--;
        }
        if (i == -1) {
            return 0;
        }
        while (i >= 0) {
            ans += std::to_string(result[i--]);
        }

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

        // As result can be very large store it in string
        std::string ans;

        // Find prefix of number that is larger
        // than divisor.
        int idx = 0;
        bigint temp = char_to_int(numerator.str[idx]);
        while (idx < (numerator.str.size() - 1) && temp < denominator) {
            temp = temp * 10 + (char_to_int(numerator.str[++idx]));
        }
        // Repeatedly divide divisor with temp. After
        // every division, update temp to include one
        // more digit.
        while ((numerator.str.size() - 1) > idx)
        {
            // Store result in answer i.e. temp / divisor
            ans += int_to_char(int(temp / int(denominator)));

            // Take next digit of number
            temp = char_to_int(int((temp % denominator) * 10 + numerator.str[++idx]));
        }

        ans += int_to_char(int(temp / int(denominator)));

        // If divisor is greater than number
        if (ans.length() == 0)
            return "0";

        // else return ans
        return ans;


        // TODO: Implement shortDivide
//        if(str2.length() <= 19) {
//            std::stringstream strstrm(str2);
//            unsigned long long int int_str2 = 0;
//            strstrm >> int_str2;
//            ans = shortDivide(str1, int_str2);
//        }
    }

    inline std::string bigint::shortDivide(std::string s1, unsigned long long int divisor)
    {     // return arithmetic division of str1/str2
        std::string ans;
        int idx = 0;
        long long int temp = s1[idx] - '0';

        while (temp < divisor) {
            temp = temp * 10 + (s1[++idx] - '0');
            if (idx >= s1.length())
                break;
        }
        while (s1.length() > idx) {
            ans += (temp / divisor) + '0';
            temp = (temp % divisor) * 10 + s1[++idx] - '0';
        }

        if (ans.length() == 0)
            return "0";

        return ans;
    }


    inline std::string bigint::trim(std::string s)
    {
        if (s == "0")
            return s;

        int i = s[0] == '-' ? 1 : 0;

        while (s[i] == '0') {
            s.erase(i, 1);
        }

        return s;
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

        if (!input.is_big) {
            return std::log2(input.base_repr);
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
            throw std::domain_error("Invalid input for natural log");

        if (input == 1)
            return 0;

        if (!input.is_big) {
            return std::log10(input.base_repr);
        }

        return static_cast<int>(input.str.length()) - 1;
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
        if (s.is_negative(s) || s == 1)
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

} // namespace::bigint_ns

#endif /* BIGINT_H_ */
