#pragma once

#include "TestSuiteImpl.h"

//-------------------- Base --------------------//

#define ENGINECORE_TESTSUITE_SUITE_NAME(TestSuiteName)                 TestSuite_ ## TestSuiteName
#define ENGINECORE_TESTSUITE_FUNC_NAME(TestSuiteName, TestName)        TestSuite_ ## TestSuiteName ## TestName
#define ENGINECORE_TESTSUITE_FUNC_EXEC_NAME(TestSuiteName, TestName)   TestSuite_ ## TestSuiteName ## TestName ## _ExecMethod

#define ENGINECORE_TESTSUITE_SUITE_EXTRA(...)	EngineCore::TestCore::TestSuite::TestSuiteExtra{ __VA_ARGS__ }
#define ENGINECORE_TESTSUITE_FUNC_EXTRA(...)	EngineCore::TestCore::TestSuite::TestFuncExtra{ __VA_ARGS__ }


//-------------------- TestSuite --------------------//

#define ENGINECORE_TESTSUITE_TEST_SUITE(TestSuiteName, ...)	EngineCore::TestCore::TestSuite ENGINECORE_TESTSUITE_SUITE_NAME(TestSuiteName)(#TestSuiteName, ENGINECORE_TESTSUITE_SUITE_EXTRA(__VA_ARGS__))


//-------------------- TestFunc --------------------//

#define ENGINECORE_TESTSUITE_FUNC_DECLARE_EXEC(TestSuiteName, TestName)	void ENGINECORE_TESTSUITE_FUNC_EXEC_NAME(TestSuiteName, TestName)(EngineCore::TestCore::TestSuite::TestFunc &TestFuncLink);
#define ENGINECORE_TESTSUITE_FUNC_CREATE(TestSuiteName, TestName, ...)		volatile EngineCore::TestCore::TestSuite::TestFunc ENGINECORE_TESTSUITE_FUNC_NAME(TestSuiteName, TestName)(#TestName, ENGINECORE_TESTSUITE_SUITE_NAME(TestSuiteName), ENGINECORE_TESTSUITE_FUNC_EXEC_NAME(TestSuiteName, TestName), ENGINECORE_TESTSUITE_FUNC_EXTRA(__VA_ARGS__))

#define ENGINECORE_TESTSUITE_TEST_FUNC(TestSuiteName, TestName)	ENGINECORE_TESTSUITE_FUNC_DECLARE_EXEC(TestSuiteName, TestName) \
																	ENGINECORE_TESTSUITE_FUNC_CREATE(TestSuiteName, TestName);	\
																	void ENGINECORE_TESTSUITE_FUNC_EXEC_NAME(TestSuiteName, TestName)(EngineCore::TestCore::TestSuite::TestFunc &TestFuncLink)


//-------------------- Test tools --------------------//

#define ENGINECORE_TESTSUITE_ASSERT(Test)				TestFuncLink.TestAssert(Test, #Test, ENGINECORE_GET_COMPILER_DATA())

#define ENGINECORE_TESTSUITE_EQ(Test, Expected)		TestFuncLink.TestEq(Test, Expected, #Test, #Expected, ENGINECORE_GET_COMPILER_DATA())
#define ENGINECORE_TESTSUITE_NEQ(Test, NotExpected)	TestFuncLink.TestNotEq(Test, NotExpected, #Test, #NotExpected, ENGINECORE_GET_COMPILER_DATA())


//-------------------- ECTS --------------------//

#ifdef ENGINECORE_ECTS_ENABLE
#define ECTS_TEST_SUITE(TestSuiteName, ...)		ENGINECORE_TESTSUITE_TEST_SUITE(TestSuiteName, __VA_ARGS__)
#define ECTS_TEST_FUNC(TestSuiteName, TestName) ENGINECORE_TESTSUITE_TEST_FUNC(TestSuiteName, TestName)

#define ECTS_EQ(Test, Expected)					ENGINECORE_TESTSUITE_EQ(Test, Expected)
#endif