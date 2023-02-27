#pragma once

#include "EngineCore/FMT/FMT.h"
#include "EngineCore/LoggerManager/LoggerManager.h"
#include "EngineCore/Instrumentation/ProfilerManger/ProfilerManger.h"

#include <concepts>
#include <string>
#include <unordered_map>

namespace EngineCore::Tester
{
	class TestFailure {};

	enum class TestStatus : int
	{
		Ok,
		Fail,
		Crash
	};
}

namespace EngineCore::Tester::Detail
{
	class TestSuite;
	class Test
	{
	public:
		Test(std::string&& name, TestSuite& link, const FMT::Detail::FileLocation& location)
			: Name(std::move(name))
			, Link(link)
			, Location(location)
		{}

	protected:
		virtual TestStatus RunImpl() = 0;

	public:
		TestStatus Run()
		{
			try
			{
				return LastStatus = RunImpl();
			}
			catch (const TestFailure& onFailure)
			{
				return LastStatus = TestStatus::Fail;
			}
			catch (...)
			{
				return LastStatus = TestStatus::Crash;
			}
		}

	public:
		std::string Name;
		TestSuite& Link;
		FMT::Detail::FileLocation Location;
		TestStatus LastStatus;
	};

	struct TestStatusBank
	{
		void Reset()
		{
			TestsDone = 0;
			TestsOk = 0;
			TestsFail = 0;
			TestsCrash = 0;
		}

		void AddTestStatus(TestStatus status)
		{
			TestsDone++;
			switch (status)
			{
				case TestStatus::Ok 	: TestsOk++; break;
				case TestStatus::Fail 	: TestsFail++; break;
				case TestStatus::Crash 	: TestsCrash++; break;
			}
		}

		void Add(TestStatusBank status)
		{
			TestsDone += status.TestsDone;
			TestsOk += status.TestsOk;
			TestsFail += status.TestsFail;
			TestsCrash += status.TestsCrash;
		}

		bool IsAllOk() { return TestsDone == TestsOk && TestsCrash == 0 && TestsFail == 0; }

		std::uint32_t TestsDone = 0;
		std::uint32_t TestsOk = 0;
		std::uint32_t TestsFail = 0;
		std::uint32_t TestsCrash = 0;	
	};

	class TestSuite;
}
namespace EngineCore::Tester
{
	struct PerformanceTestData
	{
		bool Enable = false;
		std::uint32_t NbSamples = 10;
	};

	class TestSuitesManager
	{
	public:
		static bool ExecAllTestSuites();
		static inline std::unordered_map<std::string_view, Detail::TestSuite*> TestSuites;

	public:
		static inline bool Verbose = false;
		static inline PerformanceTestData PerformanceTest = PerformanceTestData{};
	};
}
namespace EngineCore::Tester::Detail
{
	struct TestSuiteData
	{
		bool Redirect_stdout = false;
		bool Redirect_stdin = false;
		bool Redirect_stderr = false;
	};

	class TestSuite
	{
	public:
		TestSuite(std::string&& name, TestSuiteData extra = TestSuiteData{}, TestSuite* parent = nullptr)
			: Name(std::move(name))
			, Tests()
			, Extra(extra)
			, Logger()
			, TestLogger()
			, Profiler(nullptr)
			, Parent(parent)
		{
			if (parent == nullptr)
				TestSuitesManager::TestSuites.insert({ Name, this });
			else
				Parent->TestSuitesLinked.insert({ Name, this });
		}

		std::string Name;
		std::unordered_map<std::string_view, Test*> Tests;
		std::unordered_map<std::string_view, TestSuite*> TestSuitesLinked;

		TestSuiteData Extra;
		LoggerManager::BasicLogger Logger;
		LoggerManager::BasicLogger TestLogger;
		Instrumentation::Profiler* Profiler;

		TestSuite* Parent;

	public:
		void InitLogger();

	private:
		std::string GetIndent();
		std::string GetFullName();
		std::string GetCorrectedSizeName();
		Instrumentation::Profiler& GetProfiler();

	public:
		TestStatusBank ExecAllTests();
	};
}

namespace EngineCore::FMT {
	template<typename FormatContext>
	struct FormatterType<EngineCore::Tester::Detail::TestSuite, FormatContext>
	{
		static void Format(const EngineCore::Tester::Detail::TestSuite& t, FormatContext& context)
		{
			context.Print(t.Name);
		}
	};

	template<typename FormatContext>
	struct FormatterType<EngineCore::Tester::Detail::Test, FormatContext>
	{
		static void Format(const EngineCore::Tester::Detail::Test& t, FormatContext& context) {
			context.Print(t.Link.Name);
			context.Print("::");
			context.Print(t.Name);
		}
	};

	template<typename FormatContext>
	struct FormatterType<EngineCore::Tester::TestStatus, FormatContext>
	{
		static void Format(const EngineCore::Tester::TestStatus& status, FormatContext& context) {
			switch (status)
			{
				case EngineCore::Tester::TestStatus::Ok 		: context.SubContext("[  {C:green}OK{C}  ]"); break;
				case EngineCore::Tester::TestStatus::Fail 	: context.SubContext("[ {C:red}FAIL{C} ]"); break;
				case EngineCore::Tester::TestStatus::Crash 	: context.SubContext("[{C:magenta}Crash{C} ]"); break;
			}
		}
	};

	template<typename FormatContext>
	struct FormatterType<EngineCore::Tester::Detail::TestStatusBank, FormatContext>
	{
		static void Format(const EngineCore::Tester::Detail::TestStatusBank& statusBank, FormatContext& context) {
			context.Print("TestsDone ");
			context.SubContext("{:C:white}", statusBank.TestsDone);

			context.Print(" | TestsOK ");
			if (statusBank.TestsOk == statusBank.TestsDone)
				context.SubContext("{:C:green}", statusBank.TestsOk);
			else
				context.SubContext("{:C:yellow}", statusBank.TestsOk);

			context.Print(" | TestsFAIL ");
			if (statusBank.TestsFail == 0)
				context.SubContext("{:C:green}", statusBank.TestsFail);
			else
				context.SubContext("{:C:red}", statusBank.TestsFail);

			context.Print(" | TestCrash ");
			if (statusBank.TestsCrash == 0)
				context.SubContext("{:C:green}", statusBank.TestsCrash);
			else
				context.SubContext("{:C:magenta}", statusBank.TestsCrash);
		}
	};
}

//-------------------- Base --------------------//
#define ENGINECORE_TESTINTERNAL_SUITE_NAME(TestSuiteName)                 	TestSuite_ ## TestSuiteName
#define ENGINECORE_TESTINTERNAL_FUNC_NAME(TestSuiteName, TestName)        	TestSuite_ ## TestSuiteName ## TestName
#define ENGINECORE_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName) 	TestSuite_ ## TestSuiteName ## TestName ## _ExecMethod
#define ENGINECORE_TESTINTERNAL_SUITE_EXTRA(...)							EngineCore::Tester::Detail::TestSuiteData{ __VA_ARGS__ }

//-------------------- TestSuite --------------------//
#define ECT_TEST_SUITE(TestSuiteName, ...)				EngineCore::Tester::Detail::TestSuite ENGINECORE_TESTINTERNAL_SUITE_NAME(TestSuiteName)(#TestSuiteName, ENGINECORE_TESTINTERNAL_SUITE_EXTRA(__VA_ARGS__))
#define ECT_TEST_GROUP(TestSuiteName, GroupName, ...)	EngineCore::Tester::Detail::TestSuite ENGINECORE_TESTINTERNAL_SUITE_NAME(GroupName)(#GroupName, ENGINECORE_TESTINTERNAL_SUITE_EXTRA(__VA_ARGS__), &ENGINECORE_TESTINTERNAL_SUITE_NAME(TestSuiteName))
