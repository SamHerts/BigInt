//
// Created by SamHerts on 5/19/2024.
//

#include <gtest/gtest.h>
#include <string>
#include <climits>
#include <chrono>
#include <string_view>

#include "../bigint.h"

using namespace BigInt;

constexpr std::string_view kNines = "9999999999999999999";
constexpr std::string_view kHugeA = "37744193401458640707539380267899264828998907634573602318662036836618621958669475225851195876029606479769348216875016014259295382637670116067802415326896673540817149305648020275612344553440582481192266196913778504499507839960073829863258118424953008896871971652295554512459916848335206655076766027606195514199793888542571641680917367253163346581387963223123048507895574406540841752099433832902520291592993232666589290350588973179516741959648948892906581313716663682087787058913539002195482835009516853";
constexpr std::string_view kHugeB = "9843174278608822755442867695930794030260633344831664962118526669621620352474231493840674921513269404";
constexpr std::string_view AplusB = "37744193401458640707539380267899264828998907634573602318662036836618621958669475225851195876029606479769348216875016014259295382637670116067802415326896673540817149305648020275612344553440582481192266196913778504499507839960073829863258118424953008896871971652295554512459916848335206655076766027606195514199793888542571641680917367253163346581387963223123048507895574406540841752099433832902520291602836406945198113106031840875447535989909582237738246275835190351709407411387770496036157756522786257";

struct TestCase
{
    std::string lhs;
    std::string rhs;
    std::string expected;

    TestCase(std::string_view lhs, std::string_view rhs, std::string_view expected);
};

class BigInt_test : public ::testing::Test{};
class BigInt_AddParamTest : public ::testing::TestWithParam<TestCase>{};

TEST(BigInt_test, Invalid_Tests)
{
    EXPECT_THROW(bigint('a'),std::runtime_error);
    EXPECT_THROW(bigint(static_cast<char>(0)),std::runtime_error);
    EXPECT_THROW(bigint(static_cast<char>(-1)),std::runtime_error);
    EXPECT_THROW(bigint("a"),std::runtime_error);
    EXPECT_THROW(bigint("?"),std::runtime_error);
    EXPECT_THROW(bigint(""),std::runtime_error);
    EXPECT_THROW(bigint("123456a7"),std::runtime_error);
    EXPECT_THROW(bigint("-123456a7"),std::runtime_error);
    EXPECT_THROW(bigint("01234567"),std::runtime_error);
    EXPECT_THROW(bigint("-0"),std::runtime_error);
    EXPECT_THROW(bigint("-00"),std::runtime_error);
    EXPECT_THROW(bigint("00"),std::runtime_error);
}

TEST(BigInt_test, Creation_Tests)
{
    int my_int = 100;
    long my_long = 100;
    long long my_longlong = 100;
    long long my_longlong2 = LLONG_MAX;
    long long my_longlong3 = LLONG_MIN;
    unsigned long long my_ulonglong = 1000;
    double my_double = 100.0;
    char my_char = '7';
    std::string my_string = "100";
    std::string my_string3 = "-9223372036854775808";
    std::string my_string4 = "-9223372036854775809";

    EXPECT_EQ(bigint(my_int), 100);
    EXPECT_EQ(bigint(-my_int), -100);

    EXPECT_EQ(bigint(my_long), 100);
    EXPECT_EQ(bigint(-my_long), -100);

    EXPECT_EQ(bigint(my_longlong), 100);
    EXPECT_EQ(bigint(-my_longlong), -100);
    EXPECT_EQ(bigint(my_longlong2), LLONG_MAX);
    EXPECT_EQ(bigint(my_longlong3), LLONG_MIN);

    EXPECT_EQ(bigint(my_ulonglong), 1000);

    EXPECT_EQ(bigint(my_double), 100);
    EXPECT_EQ(bigint(-my_double), -100);

    EXPECT_EQ(bigint(my_char), 7);

    EXPECT_EQ(bigint(my_string), "100");
    EXPECT_EQ(bigint(my_string3), "-9223372036854775808");
    EXPECT_EQ(bigint(my_string4), "-9223372036854775809");
    std::cout << bigint(my_string4) << std::endl;
}

TEST_P(BigInt_AddParamTest, Addition_Tests)
{
    const auto&[lhs, rhs, expected] = GetParam();
    const bigint a{lhs};
    const bigint b{rhs};
    const bigint sum = a + b;
    EXPECT_EQ(sum, bigint{expected}) << lhs << " + " << rhs;
}

INSTANTIATE_TEST_SUITE_P(SmallValuesCases, BigInt_AddParamTest, ::testing::Values(
TestCase{"0", "0", "0"},
TestCase{"0", "5", "5"},
TestCase{"5", "0", "5"},
TestCase{"123", "456", "579"},
TestCase{"999", "1", "1000"},

TestCase{"7", "-3", "4"},
TestCase{"-7", "3", "-4"},
TestCase{"-7", "-3", "-10"}
));

INSTANTIATE_TEST_SUITE_P(LargeValuesCases, BigInt_AddParamTest, ::testing::Values(
TestCase{kHugeA, kHugeB, AplusB},
TestCase{kHugeB, kHugeA, AplusB}

));

TEST(BigInt_test, temp){
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2{std::string{kNines}};
    bigint huge_number_3{std::string{kHugeA}};
    bigint huge_number_4{std::string{kHugeB}};
    bigint negative_number = "-9876543210123456789314159";
    bigint max_ll = LLONG_MAX;

    EXPECT_EQ(huge_number_4 + 0, huge_number_4);

    EXPECT_EQ(bigint(10) + bigint(20), "30");
    EXPECT_EQ(huge_number_2 + 1, "10000000000000000000");
    EXPECT_EQ(huge_number_3 + huge_number_4, "");

    EXPECT_EQ(max_ll + 1, "9223372036854775808");
    EXPECT_EQ(huge_number_2 + 1, "10000000000000000000");

    EXPECT_EQ(negative_number + small_number, "-9876543210123456789304204");
    EXPECT_EQ(small_number + negative_number, "-9876543210123456789304204");
    EXPECT_EQ(negative_number + negative_number, "-19753086420246913578628318");
}

TEST_P(BigInt_test_p, Subtraction_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "10000000000000000000";
    bigint huge_number_3 = "37744193401458640707539380267899264828998907634573602318662036836618621958669475225851195876029606479769348216875016014259295382637670116067802415326896673540817149305648020275612344553440582481192266196913778504499507839960073829863258118424953008896871971652295554512459916848335206655076766027606195514199793888542571641680917367253163346581387963223123048507895574406540841752099433832902520291592993232666589290350588973179516741959648948892906581313716663682087787058913539002195482835009516853";
    bigint huge_number_4 = "9843174278608822755442867695930794030260633344831664962118526669621620352474231493840674921513269404";
    bigint negative_number = "-9876543210123456789314159";
    bigint min_ll = LLONG_MIN;

    EXPECT_EQ(huge_number_4 - 0, huge_number_4);

    EXPECT_EQ(bigint(30) - bigint(20), "10");
    EXPECT_EQ(small_number - 5, 9950);
    EXPECT_EQ(small_number - small_number, 0);
    EXPECT_EQ(min_ll - 1, bigint("-9223372036854775809"));
    EXPECT_EQ(huge_number_1 - 1, "123456788");
    EXPECT_EQ(huge_number_2 - 1, "9999999999999999999");
    EXPECT_EQ(huge_number_3 - huge_number_4, "37744193401458640707539380267899264828998907634573602318662036836618621958669475225851195876029606479769348216875016014259295382637670116067802415326896673540817149305648020275612344553440582481192266196913778504499507839960073829863258118424953008896871971652295554512459916848335206655076766027606195514199793888542571641680917367253163346581387963223123048507895574406540841752099433832902520291583150058387980467595146105483585947929388315548074916351598137012466166706439307508354807913496247449");

    EXPECT_EQ(negative_number - small_number, "-9876543210123456789324114");
    EXPECT_EQ(small_number - negative_number, "9876543210123456789324114");
    EXPECT_EQ(negative_number - negative_number, "0");
}

TEST_P(BigInt_test_p, Multiplication_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "9999999999999999999";
    bigint huge_number_3 = "37744193401458640707539380267899264828998907634573602318662036836618621958669475225851195876029606479769348216875016014259295382637670116067802415326896673540817149305648020275612344553440582481192266196913778504499507839960073829863258118424953008896871971652295554512459916848335206655076766027606195514199793888542571641680917367253163346581387963223123048507895574406540841752099433832902520291592993232666589290350588973179516741959648948892906581313716663682087787058913539002195482835009516853";
    bigint huge_number_4 = "9843174278608822755442867695930794030260633344831664962118526669621620352474231493840674921513269404";
    bigint huge_number_5 = "600000000000000000000000000500000000000000000004";
    bigint negative_number = "-678345123987345645559001";
    bigint max_ll = LLONG_MAX;
    EXPECT_EQ(bigint(30) * bigint(20), "600");
    EXPECT_EQ(small_number * 0, 0);
    EXPECT_EQ(small_number * 1, 9955);
    EXPECT_EQ(small_number * 5, 49775);
    EXPECT_EQ(small_number * small_number, 99102025);
    EXPECT_EQ(small_number * max_ll, "91818668626889293158685");
    EXPECT_EQ(huge_number_1 * 2, "246913578");
    EXPECT_EQ(huge_number_2 * huge_number_2, "99999999999999999980000000000000000001");
    EXPECT_EQ(huge_number_3 * huge_number_4, "371522673656074543721939903145636335168668810492059508909919665306024609291590328396789563611909881956692074164896572222014925589282684907671824165394055196075714622557089856059685618270608317568409327841248791007327091177305027733796385625358604009972642833675600135432852203678357550499911005775538860759946390549681453248681292307393576029610404491475299486834429621773400380504580240368032838923535804505697336440062521338464979118468824407819968770248251010402682462172033117899977017721981977515651526349027968047250058213343537761879103544485699067309526235122799512472963309861508662467265612");
    EXPECT_EQ(huge_number_5 * 1000, "600000000000000000000000000500000000000000000004000");

    EXPECT_EQ(negative_number * small_number, "-6752925709294025901539854955");
    EXPECT_EQ(small_number * negative_number, "-6752925709294025901539854955");
    EXPECT_EQ(negative_number * negative_number, "460152107237407336735321298008566431113772118001");
}

TEST_P(BigInt_test_p, Division_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "9999999999999999999";
    bigint huge_number_3 = "37744193401458640707539380267899264828998907634573602318662036836618621958669475225851195876029606479769348216875016014259295382637670116067802415326896673540817149305648020275612344553440582481192266196913778504499507839960073829863258118424953008896871971652295554512459916848335206655076766027606195514199793888542571641680917367253163346581387963223123048507895574406540841752099433832902520291592993232666589290350588973179516741959648948892906581313716663682087787058913539002195482835009516853";
    bigint huge_number_4 = "9843174278608822755442867695930794030260633344831664962118526669621620352474231493840674921513269404";
    EXPECT_EQ(bigint(30) / bigint(20), 1);
    EXPECT_EQ(small_number / 5, 1991);
    EXPECT_EQ(small_number / 181, 55);
    EXPECT_EQ(huge_number_1 / 2, 61728394);
    EXPECT_EQ(huge_number_1 / 3, 41152263);
    EXPECT_THROW(small_number / 0, std::domain_error);
    EXPECT_THROW(huge_number_1 / 0, std::domain_error);
    EXPECT_THROW(huge_number_4 / 0, std::domain_error);
    EXPECT_EQ(huge_number_2 / huge_number_1, 81000000737);
    EXPECT_EQ(huge_number_3 / huge_number_4, bigint("3834555025961928452480859540164628181402139687101087313422864247768110206281588207268817088767383084425857331782324292423438870254834351784862584845557954696973368973237622555423975476296891710599837880699585094449938105117601882807098249270619115466337592065938882369152755194714547350194277427676672295574028506048275631567039158386540348169130522428891371330855740227809243175650789881054423775986"));
}

TEST(BigInt_test, Comparison_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "9999999999999999999";
    EXPECT_TRUE(small_number > 5);
    EXPECT_TRUE(small_number > 0);
    EXPECT_TRUE(small_number > -10);
    EXPECT_TRUE(small_number > "-123456789");
    EXPECT_FALSE(small_number > huge_number_1);

    EXPECT_TRUE(small_number < huge_number_1);
    EXPECT_TRUE(small_number < huge_number_2);
    EXPECT_TRUE(huge_number_1 < huge_number_2);

    EXPECT_TRUE(small_number == small_number);
    EXPECT_TRUE(small_number >= small_number);
    EXPECT_TRUE(small_number <= small_number);
    EXPECT_TRUE(huge_number_2 == huge_number_2);
    EXPECT_TRUE(huge_number_2 >= huge_number_2);
    EXPECT_TRUE(huge_number_2 <= huge_number_2);

    EXPECT_TRUE(huge_number_2 > 0);
    EXPECT_TRUE(huge_number_2 > "0");
    EXPECT_TRUE(huge_number_2 > "-1");

    EXPECT_TRUE(bigint(0) == 0);
    EXPECT_TRUE(bigint(0) >= 0);
    EXPECT_TRUE(bigint(0) <= 0);
    EXPECT_TRUE(bigint(0) == "0");
    EXPECT_TRUE(bigint(0) >= "0");
    EXPECT_TRUE(bigint(0) <= "0");

    EXPECT_TRUE(bigint(1) == 1);
    EXPECT_TRUE(bigint(1) >= 1);
    EXPECT_TRUE(bigint(1) <= 1);
    EXPECT_TRUE(bigint(1) == "1");
    EXPECT_TRUE(bigint(1) >= "1");
    EXPECT_TRUE(bigint(1) <= "1");

    EXPECT_TRUE(1 < huge_number_1);
    EXPECT_FALSE(1 > huge_number_1);
    EXPECT_TRUE(10 < huge_number_1);
    EXPECT_TRUE("99" < huge_number_1);
    EXPECT_TRUE(123456789 <= huge_number_1);
    EXPECT_TRUE(123456789 == huge_number_1);
    EXPECT_TRUE(123456789 >= huge_number_1);
}

TEST(BigInt_test, Modulus_Tests)
{
    bigint small_number = 9955;
    bigint huge_number_1 = "123456789";
    bigint huge_number_2 = "9999999999999999999";
    EXPECT_EQ(small_number % 2, 1);
    EXPECT_EQ(small_number % 3, 1);
    EXPECT_EQ(small_number % 4, 3);
    EXPECT_EQ(small_number % 5, 0);

    EXPECT_EQ(huge_number_1 % 2, 1);
    EXPECT_EQ(huge_number_1 % 3, 0);
    EXPECT_EQ(huge_number_1 % 4, 1);
    EXPECT_EQ(huge_number_1 % 5, 4);

    EXPECT_THROW(huge_number_1 % 0, std::domain_error);

    EXPECT_EQ(huge_number_1 % small_number, 4834);
    EXPECT_EQ(small_number % huge_number_1, 9955);
}

TEST(BigInt_test, Speed_Tests)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::microseconds;
    using std::chrono::duration_cast;
    for (size_t number_size : {5, 10 ,20, 30, 40, 50 ,60 ,70, 80, 90 ,100, 110, 120, 160, 190, 200, 500, 1000}) {

        size_t number_count = 10;

        std::vector<bigint> huge_numbers;
        huge_numbers.reserve(number_count);
        for (int i = 0; i < number_count; ++i) {
            huge_numbers.emplace_back(bigint::random(number_size));
        }
        std::sort(huge_numbers.begin(), huge_numbers.end(), std::greater<>());

        bigint answer = 0;

        auto formatTime = [](int64_t microseconds) -> std::string {
            std::ostringstream result;

            if (microseconds >= 1000000) {
                result << (microseconds / 1000000.0) << " seconds";
            } else if (microseconds >= 1000) {
                result << (microseconds / 1000.0) << " milliseconds";
            } else {
                result << microseconds << " microseconds";
            }

            return result.str();
        };

        // Addition timing
        auto t1 = high_resolution_clock::now();
        for (int i = 0; i < huge_numbers.size() - 1; ++i) {
            answer = huge_numbers[i] + huge_numbers[i + 1];
        }
        auto t2 = high_resolution_clock::now();

        std::cout << number_count - 1 << " Additions: " << "[" << number_size << "] "
                  << formatTime(duration_cast<microseconds>(t2 - t1).count()) ;

        // Subtraction timing
        t1 = high_resolution_clock::now();
        for (int i = 0; i < huge_numbers.size() - 1; ++i) {
            answer = huge_numbers[i] - huge_numbers[i + 1];
        }
        t2 = high_resolution_clock::now();
        std::cout  << " Subtractions: " << "[" << number_size << "] "
                   << formatTime(duration_cast<microseconds>(t2 - t1).count()) ;

        // Multiplication timing
        t1 = high_resolution_clock::now();
        for (int i = 0; i < huge_numbers.size() - 1; ++i) {
            answer = huge_numbers[i] * huge_numbers[i + 1];
        }
        t2 = high_resolution_clock::now();
        std::cout  << " Multiplications: " << "[" << number_size << "] "
                  << formatTime(duration_cast<microseconds>(t2 - t1).count()) ;

        // Division timing
        t1 = high_resolution_clock::now();
        for (const auto &huge_number: huge_numbers) {
            answer = huge_number / 2;
        }
        t2 = high_resolution_clock::now();
        std::cout  << " Division: " << "[" << number_size << "] "
                   << formatTime(duration_cast<microseconds>(t2 - t1).count()) << std::endl;
    }
}

