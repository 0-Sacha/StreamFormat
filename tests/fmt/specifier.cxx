#include "stream/fmt.hxx"
#include "stream/tester/test_suite/all_test_suite.hxx"

#include "base_fmt_tests.hxx"

// NOLINTBEGIN(misc-const-correctness)
// NOLINTBEGIN(readability-magic-numbers)
SFT_TEST_GROUP(FMT, SPECIFIER);

#define TEST_FMT_ARRAY_SPECIFIERS(fmt_test, test_data, expected) SFT_EQ(stream::fmt::format_string(fmt_test, test_data), expected)

SFT_TEST_FUNC(SPECIFIER, BEGIN_END) {
    int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TEST_FMT_ARRAY_SPECIFIERS("{}", data, "{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }");

    TEST_FMT_ARRAY_SPECIFIERS("{:begin=6}", data, "{ 6, 7, 8, 9 }");
    TEST_FMT_ARRAY_SPECIFIERS("{:size=5}", data, "{ 0, 1, 2, 3, 4 }");
    TEST_FMT_ARRAY_SPECIFIERS("{:begin=3, size=5}", data, "{ 3, 4, 5, 6, 7 }");

    TEST_FMT_ARRAY_SPECIFIERS("{:begin='{', begin=3, size=5}", data, "{3, 4, 5, 6, 7 }");
    TEST_FMT_ARRAY_SPECIFIERS("{:end='}', begin=3, size=5}", data, "{ 3, 4, 5, 6, 7}");
    TEST_FMT_ARRAY_SPECIFIERS("{:begin='{', end='}', begin=3, size=5}", data, "{3, 4, 5, 6, 7}");
    TEST_FMT_ARRAY_SPECIFIERS("{:begin='[', end='}', begin=3, size=5}", data, "[3, 4, 5, 6, 7}");
    TEST_FMT_ARRAY_SPECIFIERS("{:begin='[', end=']', begin=3, size=5}", data, "[3, 4, 5, 6, 7]");

    TEST_FMT_ARRAY_SPECIFIERS("{:join=' ', begin='[', end=']', begin=3, size=5}", data, "[3 4 5 6 7]");

    TEST_FMT_ARRAY_SPECIFIERS("{:join=' | ', begin='[', end=']', begin=3, size=5}", data, "[3 | 4 | 5 | 6 | 7]");
}
// NOLINTEND(readability-magic-numbers)
// NOLINTEND(misc-const-correctness)
