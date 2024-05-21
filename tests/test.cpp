//
// Created by SamHerts on 5/19/2024.
//

#include <gtest/gtest.h>
#include <string>
#include "../bigint.h"

using namespace bigint_ns;

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
    bigint max_ll = LLONG_MAX;
    ASSERT_EQ(bigint("10") + bigint("20"), "30");
    ASSERT_EQ(small_number + 5, 9960);
    ASSERT_EQ(small_number + small_number, 19910);
    ASSERT_EQ(huge_number_1 + 1, "123456790");
    ASSERT_EQ(huge_number_2 + 1, "10000000000000000000");

    ASSERT_EQ( max_ll + 1, "9223372036854775808");
    ASSERT_EQ(huge_number_2 + 1, "10000000000000000000");
}

TEST(BigInt_test, Subtraction_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "10000000000000000000";
    bigint min_ll = LLONG_MIN;
    ASSERT_EQ(bigint("30") - bigint("20"), "10");
    ASSERT_EQ(small_number - 5, 9950);
    ASSERT_EQ(small_number - small_number, 0);
    ASSERT_EQ(min_ll - 1, bigint("-9223372036854775809"));
    ASSERT_EQ(huge_number_1 - 1, "123456788");
    ASSERT_EQ(huge_number_2 - 1, "9999999999999999999");
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
    ASSERT_EQ(small_number * max_ll, "91818668626889293158685");
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

