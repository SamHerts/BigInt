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
                base_repr = temp - '0';
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
            if (!this->is_big) {
                if (!rhs.is_big) {
                    if (rhs.base_repr > 0 && this->base_repr > std::numeric_limits<long long>::max() - rhs.base_repr ||
                        rhs < 0 && this->base_repr < std::numeric_limits<long long>::min() - rhs.base_repr) {
                        *this = add(std::to_string(this->base_repr), std::to_string(rhs.base_repr));
                    } else {
                        this->base_repr += rhs.base_repr;
                    }
                } else {
                    *this = add(std::to_string(this->base_repr), rhs.str);
                }
            } else {
                *this = add(this->str, rhs.str);
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
            if (!this->is_big) {
                if (!rhs.is_big) {
                    if (rhs.base_repr < 0 && this->base_repr > std::numeric_limits<long long>::max() + rhs.base_repr ||
                        rhs > 0 && this->base_repr < std::numeric_limits<long long>::min() + rhs.base_repr) {
                        *this = subtract(std::to_string(this->base_repr), std::to_string(rhs.base_repr));
                    } else {
                        this->base_repr -= rhs.base_repr;
                    }
                } else {
                    *this = subtract(std::to_string(this->base_repr), rhs.str);
                }
            } else {
                *this = subtract(this->str, rhs.str);
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
                         this->base_repr < std::numeric_limits<long long>::min() / rhs.base_repr)) {
                        *this = multiply(std::to_string(this->base_repr), std::to_string(rhs.base_repr));
                    } else {
                        this->base_repr *= rhs.base_repr;
                    }
                } else {
                    *this = multiply(std::to_string(this->base_repr), rhs.str);
                }
            } else {
                *this = multiply(this->str, rhs.str);
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
                *this = divide(this->str, rhs.str);
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
                *this = mod(this->str, rhs.str);
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
            if (!l.is_big)
            {
                if (!r.is_big)
                {
                    return l.base_repr == r.base_repr;
                }
                return std::to_string(l.base_repr) == r.str;
            }
            return l.str == r.str;
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
                return std::to_string(lhs.base_repr) < rhs.str;
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
            return lhs.str < rhs.str;
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
                return s.str.substr(1, s.str.length() - 2);

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
        if (is_negative(lhs) && is_negative(rhs)) {
            return (abs(lhs) + abs(lhs)) * -1;
        }
        if (is_negative(lhs)) {
            return rhs - abs(lhs);
        }
        if (is_negative(rhs)) {
            return lhs - abs(rhs);
        }

        // Actual string addition implementation
        int str1_len = lhs.str.length();
        int str2_len = rhs.str.length();
        std::string sum = "";

        int i, j, track_sum, carry = 0;
        for (i = str1_len - 1; i >= 0; --i) {
            for (j = str2_len - 1; j >= 0; --j) {
                track_sum = ((int) lhs.str[i]) - 48 + ((int) rhs.str[j]) - 48 + carry;
                carry = track_sum / 10;
                sum = std::to_string(track_sum % 10) + sum;
            }
        }

        if (i >= 0 && j < 0) {
            for (; i >= 0; --i) {
                track_sum = ((int) lhs.str[i]) - 48 + carry;
                carry = track_sum / 10;
                sum = std::to_string(track_sum % 10) + sum;
            }
        } else if (j >= 0 && i < 0) {
            for (; j >= 0; --j) {
                track_sum = ((int) rhs.str[j]) - 48 + carry;
                carry = track_sum / 10;
                sum = std::to_string(track_sum % 10) + sum;
            }
        }
        if (carry) {
            sum = std::to_string(carry) + sum;
        }

        return sum;
    }

    inline bigint bigint::subtract(const bigint &lhs, const bigint &rhs)
    {
        if (lhs == rhs) {
            return 0;
        }

        if (is_negative(lhs) && is_negative(rhs)) {
            return abs(rhs) - abs(lhs);
        }

        if (is_negative(rhs)) {
            return lhs + abs(rhs);
        }

        if (is_negative(lhs)) {
            return lhs + rhs;
        }

        if (lhs < rhs) {
            return (rhs - lhs) * -1;
        }

        // Actual string subtraction implementation
        int str1_len = lhs.str.length();
        int str2_len = rhs.str.length();
        std::string sum = "";

        int i, j, track_sum, carry = 0;

        // first number is larger
        int val1, val2;
        for (i = str1_len - 1, j = str2_len - 1; i >= 0 || j >= 0; --i, --j) {
            if (i >= 0) {
                val1 = (int) (lhs.str[i] - 48);
            } else {
                val1 = 0;
            }
            if (j >= 0) {
                val2 = (int) (rhs.str[j] - 48);
            } else {
                val2 = 0;
            }
            track_sum = val1 - val2 - carry;
            if (track_sum < 0) {
                track_sum += 10;
                carry = 1;
            } else {
                carry = 0;
            }
            sum.insert(0, std::to_string(track_sum));
        }

        return trim(sum);
    }

    inline bigint bigint::multiply(const bigint &lhs, const bigint &rhs)
    {
        if (is_negative(lhs) && is_negative(rhs)) {
            return (abs(lhs) * abs(lhs));
        }
        if (is_negative(lhs) || is_negative(rhs)) {
            return (abs(lhs) * abs(rhs)) * -1;
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
        if (numerator == denominator) {
            return 1;
        }

        if (denominator == 1) {
            return numerator;
        }

        if (numerator == 0) {
            return 0;
        }

        bigint ans = 0;
        if (is_negative(numerator) && is_negative(denominator)) {
            return abs(numerator) / abs(denominator);
        } else if (is_negative(numerator) || is_negative(denominator)) {
            return (abs(numerator) / abs(denominator)) * -1;
        } else {
            if (denominator > numerator) {
                return 0;
            }
                // TODO: Implement shortDivide
//        if(str2.length() <= 19) {
//            std::stringstream strstrm(str2);
//            unsigned long long int int_str2 = 0;
//            strstrm >> int_str2;
//            ans = shortDivide(str1, int_str2);
//        }
            else {
                bigint temp = numerator;
                while (temp >= denominator) {
                    temp -= denominator;
                    ans++;
                }
            }
        }
        return ans;
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
