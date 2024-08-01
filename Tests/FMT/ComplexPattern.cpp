#include "StreamFormat/FMT.h"
#include "StreamFormat/Tester/TestSuite/AllTestSuite.h"

#include "BaseFMTTests.h"

PCT_TEST_GROUP(FMT, COMPLEX_PATTERN);

#define TEST_FMT(fmt_test, expected, ...) PCT_EQ(StreamFormat::FMT::FormatString(fmt_test, __VA_ARGS__), expected)

PCT_TEST_FUNC(COMPLEX_PATTERN, UNESCAPED_ESCAPE_PATTERN)
{
    TEST_FMT("{0}", "9", 9);
    TEST_FMT("{{0}|", "{9|", 9);
    TEST_FMT("{{0},", "{9,", 9);
}
