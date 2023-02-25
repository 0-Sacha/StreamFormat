#pragma once

#include "EngineCore/Tester/TestSuite/AllTestSuite.h"
#include "EngineCore/FMT/FMT.h"

#include "BaseFMTTests.h"

ECT_TEST_GROUP(FMT, SPECIFIERS);

#define TEST_FMT_SHIFT_ARRAY_SPECIFIERS(fmt_test, test_data, expected)  ECT_EQ(EngineCore::FMT::FormatString(fmt_test, test_data), expected);

ECT_TEST_FUNC(SPECIFIERS, Array)
{
	int data[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	TEST_FMT_SHIFT_ARRAY_SPECIFIERS("{}", data, "{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }");

	TEST_FMT_SHIFT_ARRAY_SPECIFIERS("{:begin=6}", data, "{ 6, 7, 8, 9 }");
	TEST_FMT_SHIFT_ARRAY_SPECIFIERS("{:size=5}", data, "{ 0, 1, 2, 3, 4 }");
	TEST_FMT_SHIFT_ARRAY_SPECIFIERS("{:begin=3, size=5}", data, "{ 3, 4, 5, 6, 7 }");

	TEST_FMT_SHIFT_ARRAY_SPECIFIERS("{:begin='{', begin=3, size=5}", data, "{3, 4, 5, 6, 7 }");
	TEST_FMT_SHIFT_ARRAY_SPECIFIERS("{:end='}', begin=3, size=5}", data, "{ 3, 4, 5, 6, 7}");
	TEST_FMT_SHIFT_ARRAY_SPECIFIERS("{:begin='{', end='}', begin=3, size=5}", data, "{3, 4, 5, 6, 7}");
	TEST_FMT_SHIFT_ARRAY_SPECIFIERS("{:begin='[', end='}', begin=3, size=5}", data, "[3, 4, 5, 6, 7}");
	TEST_FMT_SHIFT_ARRAY_SPECIFIERS("{:begin='[', end=']', begin=3, size=5}", data, "[3, 4, 5, 6, 7]");

	TEST_FMT_SHIFT_ARRAY_SPECIFIERS("{:join=' ', begin='[', end=']', begin=3, size=5}", data, "[3 4 5 6 7]");

	TEST_FMT_SHIFT_ARRAY_SPECIFIERS("{:join=' | ', begin='[', end=']', begin=3, size=5}", data, "[3 | 4 | 5 | 6 | 7]");
}
