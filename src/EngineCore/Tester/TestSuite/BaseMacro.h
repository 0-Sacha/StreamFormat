#pragma once

#include "Detail.h"

//-------------------- Base --------------------//
#define ENGINECORE_TESTINTERNAL_SUITE_NAME(TestSuiteName)                 	TestSuite_ ## TestSuiteName
#define ENGINECORE_TESTINTERNAL_FUNC_NAME(TestSuiteName, TestName)        	TestSuite_ ## TestSuiteName ## TestName
#define ENGINECORE_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName) 	TestSuite_ ## TestSuiteName ## TestName ## _ExecMethod
#define ENGINECORE_TESTINTERNAL_SUITE_EXTRA(...)							EngineCore::Tester::Detail::TestSuite::ExtraData{ __VA_ARGS__ }

//-------------------- TestSuite --------------------//
#define ECT_TEST_SUITE(TestSuiteName, ...)		EngineCore::Tester::Detail::TestSuite ENGINECORE_TESTINTERNAL_SUITE_NAME(TestSuiteName)(#TestSuiteName, ENGINECORE_TESTINTERNAL_SUITE_EXTRA(__VA_ARGS__))
