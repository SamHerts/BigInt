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
    ASSERT_EQ(bigint(10) + bigint(20), 30);
    ASSERT_EQ(small_number + 5, 9960);
    ASSERT_EQ(small_number + small_number, 19910);
    ASSERT_EQ(huge_number_1 + 1, "123456790");
    ASSERT_EQ(huge_number_2 + 1, "10000000000000000000");
}

TEST(BigInt_test, Subtraction_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "10000000000000000000";
    ASSERT_EQ(bigint("30") - bigint("20"), "10");
    ASSERT_EQ(small_number - 5, 9950);
    ASSERT_EQ(small_number - small_number, 0);
    ASSERT_EQ(huge_number_1 - 1, "123456788");
    ASSERT_EQ(huge_number_2 - 1, "9999999999999999999");
}
