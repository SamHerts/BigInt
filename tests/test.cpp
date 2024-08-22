//
// Created by SamHerts on 5/19/2024.
//

#include <gtest/gtest.h>
#include <string>
#include <climits>
#include <chrono>

#include "../bigint.h"

using namespace BigInt;

class BigInt_test : public ::testing::Test
{
protected:
    BigInt_test() = default;
    ~BigInt_test() override = default;
    void SetUp() override {}
    void TearDown() override {}
};

TEST(BigInt_test, Creation_Tests)
{
    int my_int = 100;
    long my_long = 100;
    long long my_longlong = 100;
    double my_double = 100.0;
    char my_char = '7';
    std::string my_string = "100";

    ASSERT_EQ(bigint(my_int), 100);
    ASSERT_EQ(bigint(my_long), 100);
    ASSERT_EQ(bigint(my_longlong), 100);
    ASSERT_EQ(bigint(my_double), 100);
    ASSERT_EQ(bigint(my_char), 7);
    ASSERT_EQ(bigint(my_string), "100");
}

TEST(BigInt_test, Addition_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "9999999999999999999";
    bigint negative_number = "-9876543210123456789314159";
    bigint max_ll = LLONG_MAX;
    ASSERT_EQ(bigint("10") + bigint("20"), "30");
    ASSERT_EQ(small_number + 5, 9960);
    ASSERT_EQ(small_number + small_number, 19910);
    ASSERT_EQ(huge_number_1 + 1, "123456790");
    ASSERT_EQ(huge_number_2 + 1, "10000000000000000000");

    ASSERT_EQ( max_ll + 1, "9223372036854775808");
    ASSERT_EQ(huge_number_2 + 1, "10000000000000000000");

    ASSERT_EQ(negative_number + small_number, "-9876543210123456789304204");
    ASSERT_EQ(small_number + negative_number, "-9876543210123456789304204");
    ASSERT_EQ(negative_number + negative_number, "-19753086420246913578628318");
}

TEST(BigInt_test, Subtraction_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "10000000000000000000";
    bigint negative_number = "-9876543210123456789314159";
    bigint min_ll = LLONG_MIN;
    ASSERT_EQ(bigint("30") - bigint("20"), "10");
    ASSERT_EQ(small_number - 5, 9950);
    ASSERT_EQ(small_number - small_number, 0);
    ASSERT_EQ(min_ll - 1, bigint("-9223372036854775809"));
    ASSERT_EQ(huge_number_1 - 1, "123456788");
    ASSERT_EQ(huge_number_2 - 1, "9999999999999999999");

    ASSERT_EQ(negative_number - small_number, "-9876543210123456789324114");
    ASSERT_EQ(small_number - negative_number, "9876543210123456789324114");
    ASSERT_EQ(negative_number - negative_number, "0");
}

TEST(BigInt_test, Multiplication_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "9999999999999999999";
    bigint max_ll = LLONG_MAX;
    ASSERT_EQ(bigint("30") * bigint("20"), "600");
    ASSERT_EQ(small_number * 5, 49775);
    ASSERT_EQ(small_number * small_number, 99102025);
    ASSERT_EQ(small_number * max_ll, bigint("91818668626889293158685"));
    ASSERT_EQ(huge_number_1 * 2, "246913578");
    ASSERT_EQ(huge_number_2 * huge_number_2, "99999999999999999980000000000000000001");
}


TEST(BigInt_test, Division_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "9999999999999999999";
    ASSERT_EQ(bigint("30") / bigint("20"), 1);
    ASSERT_EQ(small_number / 5, 1991);
    ASSERT_EQ(small_number / 181, 55);
    ASSERT_EQ(huge_number_1 / 2, 61728394);
    ASSERT_EQ(huge_number_1 / 3, 41152263);
    ASSERT_EQ(huge_number_2 / huge_number_1, 81000000737);
}

TEST(BigInt_test, Comparison_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "9999999999999999999";
    ASSERT_TRUE(small_number > 5);
    ASSERT_TRUE(small_number > 0);
    ASSERT_TRUE(small_number > -10);
    ASSERT_TRUE(small_number > "-123456789");
    ASSERT_FALSE(small_number > huge_number_1);

    ASSERT_TRUE(small_number < huge_number_1);
    ASSERT_TRUE(small_number < huge_number_2);
    ASSERT_TRUE(huge_number_1 < huge_number_2);

    ASSERT_TRUE(small_number == small_number);
    ASSERT_TRUE(small_number >= small_number);
    ASSERT_TRUE(small_number <= small_number);
    ASSERT_TRUE(huge_number_2 == huge_number_2);
    ASSERT_TRUE(huge_number_2 >= huge_number_2);
    ASSERT_TRUE(huge_number_2 <= huge_number_2);

    ASSERT_TRUE(huge_number_2 > 0);
    ASSERT_TRUE(huge_number_2 > "0");
    ASSERT_TRUE(huge_number_2 > "-1");

    ASSERT_TRUE(bigint(0) == 0);
    ASSERT_TRUE(bigint(0) >= 0);
    ASSERT_TRUE(bigint(0) <= 0);
    ASSERT_TRUE(bigint(0) == "0");
    ASSERT_TRUE(bigint(0) >= "0");
    ASSERT_TRUE(bigint(0) <= "0");

    ASSERT_TRUE(bigint(1) == 1);
    ASSERT_TRUE(bigint(1) >= 1);
    ASSERT_TRUE(bigint(1) <= 1);
    ASSERT_TRUE(bigint(1) == "1");
    ASSERT_TRUE(bigint(1) >= "1");
    ASSERT_TRUE(bigint(1) <= "1");

    ASSERT_TRUE(1 < huge_number_1);
    ASSERT_FALSE(1 > huge_number_1);
    ASSERT_TRUE(10 < huge_number_1);
    ASSERT_TRUE("99" < huge_number_1);
    ASSERT_TRUE(123456789 <= huge_number_1);
    ASSERT_TRUE(123456789 == huge_number_1);
    ASSERT_TRUE(123456789 >= huge_number_1);
}

TEST(BigInt_test, Modulus_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "9999999999999999999";
    ASSERT_EQ(small_number % 2, 1);
    ASSERT_EQ(small_number % 3, 1);
    ASSERT_EQ(small_number % 4, 3);
    ASSERT_EQ(small_number % 5, 0);

    ASSERT_EQ(huge_number_1 % 2, 1);
    ASSERT_EQ(huge_number_1 % 3, 0);
    ASSERT_EQ(huge_number_1 % 4, 1);
    ASSERT_EQ(huge_number_1 % 5, 4);

    ASSERT_EQ(huge_number_1 % small_number, 4834);
}

TEST(BigInt_test_Addition_Tests_Test, Speed_Tests)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::microseconds;
    using std::chrono::duration_cast;
    for (int number : {10 ,20, 30, 40, 50 ,60 ,70, 80, 90 ,100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200}) {


        size_t number_count = 10;
        size_t number_size = number;

        std::vector<bigint> huge_numbers;
        huge_numbers.reserve(number_count);
        for (int i = 0; i < 10; ++i) {
            huge_numbers.emplace_back(bigint::random(number_size));
        }
        std::sort(huge_numbers.begin(), huge_numbers.end(), std::greater<>());

        bigint answer = 0;

        // Addition timing
        auto t1 = high_resolution_clock::now();
        for (int i = 0; i < huge_numbers.size() - 1; ++i) {
            answer = huge_numbers[i] + huge_numbers[i + 1];
//        std::cout << huge_numbers[i] << " + " << huge_numbers[i + 1] << " = " << answer << std::endl;
        }
        auto t2 = high_resolution_clock::now();

        std::cout << number_count - 1 << " Additions: " << "[" << number_size << "] "
                  << duration_cast<microseconds>(t2 - t1).count() ;

        // Subtraction timing
        t1 = high_resolution_clock::now();
        for (int i = 0; i < huge_numbers.size() - 1; ++i) {
            answer = huge_numbers[i] - huge_numbers[i + 1];
        }
        t2 = high_resolution_clock::now();
        std::cout << number_count - 1 << " Subtractions: " << "[" << number_size << "] "
                  << duration_cast<microseconds>(t2 - t1).count() ;

        // Multiplication timing
        t1 = high_resolution_clock::now();
        for (int i = 0; i < huge_numbers.size() - 1; ++i) {
            answer = huge_numbers[i] * huge_numbers[i + 1];
        }
        t2 = high_resolution_clock::now();
        std::cout << number_count - 1 << " Multiplications: " << "[" << number_size << "] "
                  << duration_cast<microseconds>(t2 - t1).count() ;

        // Division timing
        t1 = high_resolution_clock::now();
        for (const auto &huge_number: huge_numbers) {
            answer = huge_number / 2;
        }
        t2 = high_resolution_clock::now();
        std::cout << number_count - 1 << " Division: " << "[" << number_size << "] "
                  << duration_cast<microseconds>(t2 - t1).count() << std::endl;
    }
}

