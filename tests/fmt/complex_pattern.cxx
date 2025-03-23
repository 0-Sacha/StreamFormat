#include "stream/fmt.h"
#include "stream/tester/test_suite/all_test_suite.h"

#include "base_fmt_tests.h"

// NOLINTBEGIN(misc-const-correctness)
// NOLINTBEGIN(readability-magic-numbers)
SFT_TEST_GROUP(FMT, COMPLEX_PATTERN);

#define TEST_FMT(fmt_test, expected, ...) SFT_EQ(stream::fmt::format_string(fmt_test, __VA_ARGS__).value(), std::string(expected))

SFT_TEST_FUNC(COMPLEX_PATTERN, UNESCAPED_ESCAPE_PATTERN) {
    TEST_FMT("{0}", "9", 9);
    TEST_FMT("{{0}|", "{9|", 9);
    TEST_FMT("{{0},", "{9,", 9);
}
// NOLINTEND(readability-magic-numbers)
// NOLINTEND(misc-const-correctness)
