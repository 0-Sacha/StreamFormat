#pragma once

#include "TestSuiteImpl.h"

//-------------------- Base --------------------//

#define ENGINE_CORE_TESTSUITE_SUITE_NAME(TestSuiteName)                 TestSuite_ ## TestSuiteName
#define ENGINE_CORE_TESTSUITE_FUNC_NAME(TestSuiteName, TestName)        TestSuite_ ## TestSuiteName ## TestName
#define ENGINE_CORE_TESTSUITE_FUNC_EXEC_NAME(TestSuiteName, TestName)   TestSuite_ ## TestSuiteName ## TestName ## _ExecMethod

#define ENGINE_CORE_TESTSUITE_SUITE_EXTRA(...)	EngineCore::TestCore::TestSuite::TestSuiteExtra{ __VA_ARGS__ }
#define ENGINE_CORE_TESTSUITE_FUNC_EXTRA(...)	EngineCore::TestCore::TestSuite::TestFuncExtra{ __VA_ARGS__ }


//-------------------- TestSuite --------------------//

#define ENGINE_CORE_TESTSUITE_TEST_SUITE(TestSuiteName, ...)	EngineCore::TestCore::TestSuite ENGINE_CORE_TESTSUITE_SUITE_NAME(TestSuiteName)(#TestSuiteName, ENGINE_CORE_TESTSUITE_SUITE_EXTRA(__VA_ARGS__))


//-------------------- TestFunc --------------------//

#define ENGINE_CORE_TESTSUITE_FUNC_DECLARE_EXEC(TestSuiteName, TestName)	void ENGINE_CORE_TESTSUITE_FUNC_EXEC_NAME(TestSuiteName, TestName)(EngineCore::TestCore::TestSuite::TestFunc &TestFuncLink);
#define ENGINE_CORE_TESTSUITE_FUNC_CREATE(TestSuiteName, TestName, ...)		volatile EngineCore::TestCore::TestSuite::TestFunc ENGINE_CORE_TESTSUITE_FUNC_NAME(TestSuiteName, TestName)(#TestName, ENGINE_CORE_TESTSUITE_SUITE_NAME(TestSuiteName), ENGINE_CORE_TESTSUITE_FUNC_EXEC_NAME(TestSuiteName, TestName), ENGINE_CORE_TESTSUITE_FUNC_EXTRA(__VA_ARGS__))

#define ENGINE_CORE_TESTSUITE_TEST_FUNC(TestSuiteName, TestName)	ENGINE_CORE_TESTSUITE_FUNC_DECLARE_EXEC(TestSuiteName, TestName) \
																	ENGINE_CORE_TESTSUITE_FUNC_CREATE(TestSuiteName, TestName);	\
																	void ENGINE_CORE_TESTSUITE_FUNC_EXEC_NAME(TestSuiteName, TestName)(EngineCore::TestCore::TestSuite::TestFunc &TestFuncLink)


//-------------------- Test tools --------------------//

#define ENGINE_CORE_TESTSUITE_ASSERT(Test)				TestFuncLink.TestAssert(Test, #Test, ENGINE_CORE_GET_COMPILER_DATA())

#define ENGINE_CORE_TESTSUITE_EQ(Test, Expected)		TestFuncLink.TestEq(Test, Expected, #Test, #Expected, ENGINE_CORE_GET_COMPILER_DATA())
#define ENGINE_CORE_TESTSUITE_NEQ(Test, NotExpected)	TestFuncLink.TestNotEq(Test, NotExpected, #Test, #NotExpected, ENGINE_CORE_GET_COMPILER_DATA())


//-------------------- ECTS --------------------//

#ifdef ENGINE_CORE_ECTS_ENABLE
#define ECTS_TEST_SUITE(TestSuiteName, ...)		ENGINE_CORE_TESTSUITE_TEST_SUITE(TestSuiteName, __VA_ARGS__)
#define ECTS_TEST_FUNC(TestSuiteName, TestName) ENGINE_CORE_TESTSUITE_TEST_FUNC(TestSuiteName, TestName)

#define ECTS_EQ(Test, Expected)					ENGINE_CORE_TESTSUITE_EQ(Test, Expected)
#endif