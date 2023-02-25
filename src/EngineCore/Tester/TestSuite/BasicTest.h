#pragma once

#include "TestSuite.h"

#include "EngineCore/FMT/Format/CompilationData.h"

namespace EngineCore::Tester::Detail
{
	struct TestFunction : public Test
	{
	public:
		using FuncType = std::function<void(TestFunction& link)>;

	public:
		TestFunction(std::string&& name, TestSuite& link, FuncType func, const FMT::Detail::FileLocation& location)
			: Test(std::move(name), link, location)
			, Func(func)
		{
			Link.Tests.insert({Name, this});
		}

	protected:
		TestStatus RunImpl() override
		{
			Func(*this);
			return TestStatus::Ok;
		}

	public:
		void TestAssert(bool assert, const std::string_view assertView, int line);
		template <typename T>
		void TestEq(T result, std::equality_comparable_with<T> auto expected, const std::string_view resultView, const std::string_view expectedView, int line);
		template <typename T>
		void TestNotEq(T result, std::equality_comparable_with<T> auto notExpected, const std::string_view resultView, const std::string_view notExpectedView, int line);

	public:
		FuncType Func;
	};


	template <typename T>
	void TestFunction::TestEq(T result, std::equality_comparable_with<T> auto expected, const std::string_view resultView, const std::string_view expectedView, int line)
	{
		if (result != expected)
		{
			Link.TestLogger.Error("{C:red}{} return {} instead of {} ; Expected was : {}", resultView, result, expected, expectedView, FORMAT_SV("test_name", Name));
			throw TestFailure{};
		}

		Link.TestLogger.Trace("{C:green}{} return {}", resultView, result, FORMAT_SV("test_name", Name));
	}

	template <typename T>
	void TestFunction::TestNotEq(T result, std::equality_comparable_with<T> auto notExpected, const std::string_view resultView, const std::string_view notExpectedView, int line)
	{
		if (result == notExpected)
		{
			Link.TestLogger.Error("{C:red}{} return {} but this result was prohibited", resultView, result, FORMAT_SV("test_name", Name));
			throw TestFailure{};
		}

		Link.TestLogger.Trace("{C:green}{} return {} and {} was prohibited", resultView, result, notExpected, FORMAT_SV("test_name", Name));
	}

	inline void TestFunction::TestAssert(bool assert, std::string_view assertView, int line)
	{
		if (assert == false)
		{
			Link.TestLogger.Error("{C:red}ASSERT FAILED : {}", assertView, FORMAT_SV("test_name", Name));
			throw TestFailure{};
		}

		Link.TestLogger.Trace("{C:green}ASSERT SUCCED : {}", assertView, FORMAT_SV("test_name", Name));
	}
}


#define ENGINECORE_TESTINTERNAL_FUNC_DECLARE_EXEC(TestSuiteName, TestName)	void ENGINECORE_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName)(EngineCore::Tester::Detail::TestFunction &link);
#define ENGINECORE_TESTINTERNAL_FUNC_CREATE(TestSuiteName, TestName, ...)	volatile EngineCore::Tester::Detail::TestFunction ENGINECORE_TESTINTERNAL_FUNC_NAME(TestSuiteName, TestName)(#TestName, ENGINECORE_TESTINTERNAL_SUITE_NAME(TestSuiteName), ENGINECORE_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName), ENGINECORE_FMT_FILE_LOCATION())

#define ECT_TEST_FUNC(TestSuiteName, TestName)	ENGINECORE_TESTINTERNAL_FUNC_DECLARE_EXEC(TestSuiteName, TestName) \
												ENGINECORE_TESTINTERNAL_FUNC_CREATE(TestSuiteName, TestName);	\
												void ENGINECORE_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName)(EngineCore::Tester::Detail::TestFunction &link)


#define ECT_ASSERT(Test)			link.TestAssert(Test, #Test, __LINE__)
#define ECT_EQ(Test, Expected)		link.TestEq(Test, Expected, #Test, #Expected, __LINE__)
#define ECT_NEQ(Test, NotExpected)	link.TestNotEq(Test, NotExpected, #Test, #NotExpected, __LINE__)

