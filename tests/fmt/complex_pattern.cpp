#include "stream/fmt.h"
#include "stream/Tester/TestSuite/AllTestSuite.h"

#include "BaseFMTTests.h"

SFT_TEST_GROUP(FMT, COMPLEX_PATTERN);

#define TEST_FMT(fmt_test, expected, ...) SFT_EQ(stream::fmt::FormatString(fmt_test, __VA_ARGS__).value(), std::string(expected))

SFT_TEST_FUNC(COMPLEX_PATTERN, UNESCAPED_ESCAPE_PATTERN)
{
    TEST_FMT("{0}", "9", 9);
    TEST_FMT("{{0}|", "{9|", 9);
    TEST_FMT("{{0},", "{9,", 9);
}
