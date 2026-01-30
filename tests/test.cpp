//
// Created by SamHerts on 5/19/2024.
//

#include <gtest/gtest.h>
#include <string>
#include <climits>
#include <chrono>
#include <string_view>
#include <sstream>
#include <unordered_set>

#include "../bigint.h"

using namespace BigInt;
using std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::duration_cast;

// bool SKIP_PERFORMANCE_TESTS = true;
bool SKIP_PERFORMANCE_TESTS = false;

constexpr std::string_view kNines = "9999999999999999999";
constexpr std::string_view kHugeA =
        "37744193401458640707539380267899264828998907634573602318662036836618621958669475225851195876029606479769348216875016014259295382637670116067802415326896673540817149305648020275612344553440582481192266196913778504499507839960073829863258118424953008896871971652295554512459916848335206655076766027606195514199793888542571641680917367253163346581387963223123048507895574406540841752099433832902520291592993232666589290350588973179516741959648948892906581313716663682087787058913539002195482835009516853";
constexpr std::string_view kHugeB =
        "9843174278608822755442867695930794030260633344831664962118526669621620352474231493840674921513269404";

constexpr std::string_view AplusB =
        "37744193401458640707539380267899264828998907634573602318662036836618621958669475225851195876029606479769348216875016014259295382637670116067802415326896673540817149305648020275612344553440582481192266196913778504499507839960073829863258118424953008896871971652295554512459916848335206655076766027606195514199793888542571641680917367253163346581387963223123048507895574406540841752099433832902520291602836406945198113106031840875447535989909582237738246275835190351709407411387770496036157756522786257";
constexpr std::string_view AminusB =
        "37744193401458640707539380267899264828998907634573602318662036836618621958669475225851195876029606479769348216875016014259295382637670116067802415326896673540817149305648020275612344553440582481192266196913778504499507839960073829863258118424953008896871971652295554512459916848335206655076766027606195514199793888542571641680917367253163346581387963223123048507895574406540841752099433832902520291583150058387980467595146105483585947929388315548074916351598137012466166706439307508354807913496247449";
constexpr std::string_view AmulB =
        "371522673656074543721939903145636335168668810492059508909919665306024609291590328396789563611909881956692074164896572222014925589282684907671824165394055196075714622557089856059685618270608317568409327841248791007327091177305027733796385625358604009972642833675600135432852203678357550499911005775538860759946390549681453248681292307393576029610404491475299486834429621773400380504580240368032838923535804505697336440062521338464979118468824407819968770248251010402682462172033117899977017721981977515651526349027968047250058213343537761879103544485699067309526235122799512472963309861508662467265612";
constexpr std::string_view AdivB =
        "3834555025961928452480859540164628181402139687101087313422864247768110206281588207268817088767383084425857331782324292423438870254834351784862584845557954696973368973237622555423975476296891710599837880699585094449938105117601882807098249270619115466337592065938882369152755194714547350194277427676672295574028506048275631567039158386540348169130522428891371330855740227809243175650789881054423775986";
constexpr std::string_view AmodB =
        "2156048695288816089284014643351839933776226311026153430599415874278141145999872948608252665245784509";

constexpr std::string_view BminusA =
        "-37744193401458640707539380267899264828998907634573602318662036836618621958669475225851195876029606479769348216875016014259295382637670116067802415326896673540817149305648020275612344553440582481192266196913778504499507839960073829863258118424953008896871971652295554512459916848335206655076766027606195514199793888542571641680917367253163346581387963223123048507895574406540841752099433832902520291583150058387980467595146105483585947929388315548074916351598137012466166706439307508354807913496247449";

struct TestCase
{
    std::string lhs;
    std::string rhs;
    std::string expected;

    TestCase(const std::string_view lhs, const std::string_view rhs,
             const std::string_view expected) : lhs(lhs), rhs(rhs), expected(expected) {}
};

class Test_BigInt : public ::testing::Test {};

static auto formatTime = [](const long long micros) -> std::string {
    if (micros >= 1000000) return std::to_string(micros / 1000000.0) + " s";
    if (micros >= 1000) return std::to_string(micros / 1000.0) + " ms";
    return std::to_string(micros) + " us";
};

static auto measure_execution = [](const int count, const char* label, const size_t size, auto func) {
    const auto t1 = steady_clock::now();
    func();
    const auto t2 = steady_clock::now();

    const long long duration = duration_cast<microseconds>(t2 - t1).count();
    const double avg_per_op = static_cast<double>(duration) / count;

    std::cout << std::setw(14) << std::left << label << " [" << size << " digits]: "
            << formatTime(duration)
            << " (Avg: " << avg_per_op << " us/op)" << std::endl;
};

class Test_BigInt_Performance : public ::testing::Test
{
protected:
    static constexpr size_t number_count = 500;
    const std::vector<size_t> sizes = {5, 20, 50, 100, 1000, 10'000, 100'000, 1'000'000};
    volatile int dce_sink = 0;

    void SetUp() override {
        if (SKIP_PERFORMANCE_TESTS)
            GTEST_SKIP() << "Skipping performance tests for this fixture";
    }
};

class Test_BigInt_F : public ::testing::Test
{
protected:
    bigint A{std::string(kHugeA)};
    bigint B{std::string(kHugeB)};
    bigint C{std::string(kNines)};
};
class BigInt_AddParamTest : public ::testing::TestWithParam<TestCase>{};
class BigInt_SubParamTest : public ::testing::TestWithParam<TestCase>{};
class BigInt_MulParamTest : public ::testing::TestWithParam<TestCase>{};
class BigInt_DivParamTest : public ::testing::TestWithParam<TestCase>{};
class BigInt_ModParamTest : public ::testing::TestWithParam<TestCase>{};

TEST(Test_BigInt, Invalid_Tests) {
    EXPECT_THROW(bigint('a'), std::runtime_error);
    EXPECT_THROW(bigint(static_cast<char>(0)), std::runtime_error);
    EXPECT_THROW(bigint(static_cast<char>(-1)), std::runtime_error);
    EXPECT_THROW(bigint("a"), std::runtime_error);
    EXPECT_THROW(bigint("?"), std::runtime_error);
    EXPECT_THROW(bigint(""), std::runtime_error);
    EXPECT_THROW(bigint("123456a7"), std::runtime_error);
    EXPECT_THROW(bigint("-123456a7"), std::runtime_error);
    EXPECT_THROW(bigint("01234567"), std::runtime_error);
    EXPECT_THROW(bigint("007"), std::runtime_error);
    ASSERT_THROW(bigint("1234567.9"), std::runtime_error);
    ASSERT_THROW(bigint("+1234567"), std::runtime_error);
    ASSERT_THROW(bigint(" 1234567"), std::runtime_error);
    ASSERT_THROW(bigint("1234567 "), std::runtime_error);
    EXPECT_THROW(bigint("-0"), std::runtime_error);
    EXPECT_THROW(bigint("-"), std::runtime_error);
    EXPECT_THROW(bigint("-00"), std::runtime_error);
    EXPECT_THROW(bigint("00"), std::runtime_error);
    EXPECT_THROW(bigint("0.0"), std::runtime_error);
}

TEST(Test_BigInt, Creation_Tests) {
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
}

TEST(Test_BigInt, Unary_Tests) {
    bigint A{std::string(kHugeA)};
    bigint B{std::string(kHugeA)};

    A++;
    EXPECT_EQ(A, B + 1);
    A--;
    EXPECT_EQ(A, B);
    EXPECT_EQ(++A, B + 1);
    EXPECT_EQ(--A, B);
}

TEST(Test_BigInt, Hash_Tests) {
    const std::hash<bigint> hasher;
    bigint A{std::string(kHugeA)};
    bigint B{std::string(kHugeB)};

    EXPECT_EQ(hasher(bigint(0)), hasher(bigint(0)));
    EXPECT_EQ(hasher(bigint(1)), hasher(bigint(1)));
    EXPECT_EQ(hasher(bigint(-1)), hasher(bigint(-1)));
    EXPECT_EQ(hasher(A), hasher(A));

    EXPECT_NE(hasher(bigint(0)), hasher(bigint(1)));
    EXPECT_NE(hasher(bigint(-1)), hasher(bigint(1)));
    EXPECT_NE(hasher(A), hasher(A + 1));

    std::unordered_set<bigint> set;

    set.insert(A);
    set.insert(B);
    EXPECT_EQ(set.size(), 2);
    EXPECT_EQ(set.count(A), 1);
    EXPECT_EQ(set.count(B), 1);

    EXPECT_EQ(set.find(A), set.find(A));
    set.insert(A);
    EXPECT_EQ(set.count(A), 1);
}

TEST(Test_BigInt, Stream_Tests) {
    std::stringstream my_stream;
    my_stream << bigint(55);
    EXPECT_EQ(my_stream.str(), "55");

    my_stream = std::stringstream();
    my_stream.clear();

    my_stream << bigint(-55);
    EXPECT_EQ(my_stream.str(), "-55");
    my_stream = std::stringstream();
    my_stream << bigint(std::string{kHugeA});
    EXPECT_EQ(my_stream.str(), std::string{kHugeA});
}

TEST(Test_BigInt, Bool_Tests) {
    EXPECT_EQ(static_cast<bool>(bigint(1)), true);
    EXPECT_EQ(static_cast<bool>(bigint(0)), false);
    EXPECT_EQ(static_cast<bool>(bigint()), false);
    EXPECT_EQ(static_cast<bool>(bigint(-1)), true);
    EXPECT_EQ(static_cast<bool>(bigint(2)), true);
    EXPECT_EQ(static_cast<bool>(bigint(std::string{kHugeA})), true);
}

TEST(Test_BigInt, Negate_Tests) {
    EXPECT_EQ(-bigint(0), 0);
    EXPECT_EQ(-bigint(1), -1);
    EXPECT_EQ(-bigint(-1), 1);
    EXPECT_EQ(-bigint(std::string{kHugeA}), bigint("-" + std::string{kHugeA}));
}

TEST_P(BigInt_AddParamTest, Addition_Tests) {
    const auto& [lhs, rhs, expected] = GetParam();
    const bigint a{lhs};
    const bigint b{rhs};
    const bigint sum = a + b;
    // EXPECT_EQ(sum, bigint{expected}) << lhs << " + " << rhs;
    EXPECT_EQ(sum, bigint{expected});
}

TEST_P(BigInt_SubParamTest, Subtraction_Tests) {
    const auto& [lhs, rhs, expected] = GetParam();
    const bigint a{lhs};
    const bigint b{rhs};
    const bigint sub = a - b;
    // EXPECT_EQ(sum, bigint{expected}) << lhs << " - " << rhs;
    EXPECT_EQ(sub, bigint{expected});
}

TEST_P(BigInt_MulParamTest, Multiplication_Tests) {
    const auto& [lhs, rhs, expected] = GetParam();
    const bigint a{lhs};
    const bigint b{rhs};
    const bigint mul = a * b;
    // EXPECT_EQ(sum, bigint{expected}) << lhs << " * " << rhs;
    EXPECT_EQ(mul, bigint{expected});
}

TEST_P(BigInt_DivParamTest, Division_Tests) {
    const auto& [lhs, rhs, expected] = GetParam();
    const bigint a{lhs};
    const bigint b{rhs};
    const bigint div = a / b;
    // EXPECT_EQ(sum, bigint{expected}) << lhs << " / " << rhs;
    EXPECT_EQ(div, bigint{expected});
}

TEST_P(BigInt_ModParamTest, Modulus_Tests) {
    const auto& [lhs, rhs, expected] = GetParam();
    const bigint a{lhs};
    const bigint b{rhs};
    const bigint mod = a % b;
    // EXPECT_EQ(sum, bigint{expected}) << lhs << " % " << rhs;
    EXPECT_EQ(mod, bigint{expected});
}

INSTANTIATE_TEST_SUITE_P(SmallValueAdd, BigInt_AddParamTest, ::testing::Values(
                             TestCase{"0", "0", "0"},
                             TestCase{"0", "5", "5"},
                             TestCase{"5", "0", "5"},
                             TestCase{"123", "456", "579"},
                             TestCase{"999", "1", "1000"},

                             TestCase{"7", "-3", "4"},
                             TestCase{"-7", "3", "-4"},
                             TestCase{"-7", "-3", "-10"},
                             TestCase{"-10", "10", "0"},
                             TestCase{"10", "-10", "0"}
                         ));

INSTANTIATE_TEST_SUITE_P(SmallValueSub, BigInt_SubParamTest, ::testing::Values(
                             TestCase{"0", "0", "0"},
                             TestCase{"0", "5", "-5"},
                             TestCase{"5", "0", "5"},
                             TestCase{"999", "1", "998"},
                             TestCase{"1000", "1", "999"},

                             TestCase{"7", "-3", "10"},
                             TestCase{"-7", "3", "-10"},
                             TestCase{"-7", "-3", "-4"},
                             TestCase{"-10", "10", "-20"},
                             TestCase{"10", "-10", "20"},
                             TestCase{"-10", "-10", "0"}
                         ));

INSTANTIATE_TEST_SUITE_P(SmallValueMul, BigInt_MulParamTest, ::testing::Values(
                             TestCase{"0", "0", "0"},
                             TestCase{"0", "5", "0"},
                             TestCase{"5", "0", "0"},
                             TestCase{"999", "1", "999"},

                             TestCase{"7", "-3", "-21"},
                             TestCase{"-7", "3", "-21"},
                             TestCase{"-7", "-3", "21"}
                         ));

INSTANTIATE_TEST_SUITE_P(SmallValueDiv, BigInt_DivParamTest, ::testing::Values(
                             TestCase{"0", "5", "0"},
                             TestCase{"999", "1", "999"},

                             TestCase{"7", "-3", "-2"},
                             TestCase{"-7", "3", "-2"},
                             TestCase{"-7", "-3", "2"}
                         ));

INSTANTIATE_TEST_SUITE_P(LargeValuesAdd, BigInt_AddParamTest, ::testing::Values(
                             TestCase{kHugeA, kHugeB, AplusB},
                             TestCase{kHugeB, kHugeA, AplusB},
                             TestCase{kHugeA, "0", kHugeA}
                         ));

INSTANTIATE_TEST_SUITE_P(LargeValueSub, BigInt_SubParamTest, ::testing::Values(
                             TestCase{kHugeA, kHugeB, AminusB},
                             TestCase{kHugeB, kHugeA, BminusA},
                             TestCase{kHugeA, kHugeA, "0"},
                             TestCase{kHugeA, "0", kHugeA},
                             TestCase{"0", kHugeA, "-" + std::string{kHugeA}},
                             TestCase{kNines, "9900000000000000000", "99999999999999999"}
                         ));

INSTANTIATE_TEST_SUITE_P(LargeValueMul, BigInt_MulParamTest, ::testing::Values(
                             TestCase{kHugeA, kHugeB, AmulB},
                             TestCase{kHugeB, kHugeA, AmulB}
                         ));

INSTANTIATE_TEST_SUITE_P(LargeValueDiv, BigInt_DivParamTest, ::testing::Values(
                             TestCase{kHugeA, kHugeB, AdivB},
                             TestCase{kHugeA, kHugeA, "1"},
                             TestCase{"0", kHugeA, "0"},
                             TestCase{kHugeA, "-" + std::string{kHugeB}, "-" + std::string{AdivB}},
                             TestCase{kHugeB, kHugeA, "0"}
                         ));

INSTANTIATE_TEST_SUITE_P(LargeValueMod, BigInt_ModParamTest, ::testing::Values(
                             TestCase{kHugeA, kHugeB, AmodB},
                             TestCase{kHugeB, kHugeA, kHugeB},
                             TestCase{kHugeA, kHugeA, "0"},
                             TestCase{kHugeA, "1", "0"}
                         ));

TEST_F(Test_BigInt_F, Commutivity_Tests) {
    EXPECT_EQ(A + B, B + A);
    EXPECT_EQ((A + B) + C, A + (B + C));
    EXPECT_EQ(A * B, B * A);
    EXPECT_EQ((A * B) * C, A * (B * C));
}

TEST_F(Test_BigInt_F, Distributivity_Tests) {
    EXPECT_EQ(A * (B + C), (A * B) + (A * C));
}

TEST(Test_BigInt, Domain_Tests) {
    EXPECT_THROW(bigint{0} / 0, std::domain_error);
    EXPECT_THROW(bigint{77} / 0, std::domain_error);
    EXPECT_THROW(bigint{std::string{kHugeA}} / 0, std::domain_error);
    EXPECT_THROW(bigint{77} % 0, std::domain_error);
}

TEST(Test_BigInt, Comparison_Tests) {
    bigint small_number = 9955;
    bigint huge_number1{std::string{kHugeA}};
    bigint huge_number2{std::string{kHugeB}};
    EXPECT_TRUE(small_number > 5);
    EXPECT_TRUE(small_number > 0);
    EXPECT_TRUE(small_number > -10);
    EXPECT_TRUE(huge_number1 > 0);
    EXPECT_TRUE(huge_number1 > "0");
    EXPECT_TRUE(huge_number1 > "-1");

    EXPECT_TRUE(small_number > huge_number1 * -1);
    EXPECT_FALSE(small_number > huge_number1);
    EXPECT_FALSE(small_number > small_number);
    EXPECT_FALSE(huge_number1 > huge_number1);

    EXPECT_TRUE(small_number < huge_number1);
    EXPECT_TRUE(huge_number2 < huge_number1);

    EXPECT_TRUE(small_number == small_number);
    EXPECT_TRUE(huge_number1 == huge_number1);
    EXPECT_TRUE(small_number >= small_number);
    EXPECT_TRUE(small_number <= small_number);
    EXPECT_TRUE(huge_number1 >= huge_number1);
    EXPECT_TRUE(huge_number1 <= huge_number1);

    EXPECT_TRUE(bigint(0) == 0);
    EXPECT_TRUE(bigint(0) >= 0);
    EXPECT_TRUE(bigint(0) <= 0);

    EXPECT_TRUE(bigint(1) == 1);
    EXPECT_TRUE(bigint(1) >= 1);
    EXPECT_TRUE(bigint(1) <= 1);

    EXPECT_TRUE(1 < huge_number1);
    EXPECT_FALSE(1 > huge_number1);
    EXPECT_TRUE(10 < huge_number1);
    EXPECT_TRUE("99" < huge_number1);
    EXPECT_TRUE(123456789 <= huge_number1);
    EXPECT_FALSE(123456789 == huge_number1);
    EXPECT_FALSE(123456789 >= huge_number1);
}

TEST_F(Test_BigInt_Performance, Addition_Speed_Tests) {
    std::cout << "--- Starting Performance Tests (Sample size: " << number_count << ") ---" << std::endl;
    for (const size_t number_size : sizes) {
        std::vector<bigint> huge_numbers;
        huge_numbers.reserve(number_count);
        for (int i = 0; i < number_count; ++i) {
            huge_numbers.emplace_back(bigint::random(number_size));
        }
        // Ensure values stay defined
        std::sort(huge_numbers.begin(), huge_numbers.end(), std::greater<>());

        bigint answer = 0;

        measure_execution(number_count, "Addition", number_size, [&]() {
            for (size_t i = 0; i < huge_numbers.size() - 1; ++i) {
                answer = huge_numbers[i] + huge_numbers[i + 1];
                // Tiny check to force evaluation
                if (answer == 0) dce_sink++;
            }
        });

        std::cout << std::endl;
    }
}

TEST_F(Test_BigInt_Performance, Subtraction_Speed_Tests) {
    std::cout << "--- Starting Performance Tests (Sample size: " << number_count << ") ---" << std::endl;
    for (const size_t number_size : sizes) {
        std::vector<bigint> huge_numbers;
        huge_numbers.reserve(number_count);
        for (int i = 0; i < number_count; ++i) {
            huge_numbers.emplace_back(bigint::random(number_size));
        }
        // Ensure values stay defined
        std::sort(huge_numbers.begin(), huge_numbers.end(), std::greater<>());

        bigint answer = 0;

        measure_execution(number_count, "Subtraction", number_size, [&]() {
            for (size_t i = 0; i < huge_numbers.size() - 1; ++i) {
                answer = huge_numbers[i] - huge_numbers[i + 1];
                // Tiny check to force evaluation
                if (answer == 0) dce_sink++;
            }
        });

        std::cout << std::endl;
    }
}

TEST_F(Test_BigInt_Performance, Multiplication_Speed_Tests) {
    std::cout << "--- Starting Performance Tests (Sample size: " << number_count << ") ---" << std::endl;
    for (const size_t number_size : sizes) {
        std::vector<bigint> huge_numbers;
        huge_numbers.reserve(number_count);
        for (int i = 0; i < number_count; ++i) {
            huge_numbers.emplace_back(bigint::random(number_size));
        }
        // Ensure values stay defined
        std::sort(huge_numbers.begin(), huge_numbers.end(), std::greater<>());

        bigint answer = 0;

        measure_execution(number_count, "Multiplication", number_size, [&]() {
            for (size_t i = 0; i < huge_numbers.size() - 1; ++i) {
                answer = huge_numbers[i] * huge_numbers[i + 1];
                // Tiny check to force evaluation
                if (answer == 0) dce_sink++;
            }
        });

        std::cout << std::endl;
    }
}

TEST_F(Test_BigInt_Performance, Division_Speed_Tests) {
    std::cout << "--- Starting Performance Tests (Sample size: " << number_count << ") ---" << std::endl;
    for (const size_t number_size : sizes) {
        std::vector<bigint> huge_numbers;
        huge_numbers.reserve(number_count);
        for (int i = 0; i < number_count; ++i) {
            huge_numbers.emplace_back(bigint::random(number_size));
        }
        // Ensure values stay defined
        std::sort(huge_numbers.begin(), huge_numbers.end(), std::greater<>());

        bigint answer = 0;

        measure_execution(number_count, "Division", number_size, [&]() {
            for (size_t i = 0; i < huge_numbers.size() - 1; ++i) {
                answer = huge_numbers[i] / 55;
                // Tiny check to force evaluation
                if (answer == 0) dce_sink++;
            }
        });

        std::cout << std::endl;
    }
}
