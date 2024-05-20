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
    void SetUp() override {
        bigint huge_number_1 = "1234567890132456789";
        bigint huge_number_2 = "9999999999999999999";
    }
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
    ASSERT_EQ(bigint(my_string), 100);
}

TEST(BigInt_test, Addition_Tests)
{

}

