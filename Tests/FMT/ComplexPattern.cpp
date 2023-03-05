#include "EngineCore/Tester/TestSuite/AllTestSuite.h"
#include "EngineCore/FMT/FMT.h"

#include "BaseFMTTests.h"

ECT_TEST_GROUP(FMT, COMPLEX_PATTERN);

#define TEST_FMT(fmt_test, expected, ...)  ECT_EQ(EngineCore::FMT::FormatString(fmt_test, __VA_ARGS__), expected);

ECT_TEST_FUNC(COMPLEX_PATTERN, UNESCAPED_ESCAPE_PATTERN)
{
    TEST_FMT("{0}", "9", 9);
    TEST_FMT("{{0}|", "{9|", 9);
    TEST_FMT("{{0},", "{9,", 9);
}
