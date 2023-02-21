#pragma once

#include "EngineCore/FMT/FMT.h"
#include "EngineCore/LoggerManager/LoggerManager.h"

#include <concepts>
#include <string>
#include <unordered_map>

namespace EngineCore::Tests
{
	class TestFailure {};

	enum class TestStatus : int
	{
		Ok,
		Fail,
		Crash
	};
}

namespace EngineCore::Tests::Detail
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

		std::uint32_t TestsDone = 0;
		std::uint32_t TestsOk = 0;
		std::uint32_t TestsFail = 0;
		std::uint32_t TestsCrash = 0;	
	};

	class TestSuite;
}
namespace EngineCore::Tests
{
	class TestSuitesManager
	{
	public:
		static bool ExecTestSuitesManagers();
		static inline std::unordered_map<std::string_view, Detail::TestSuite*> TestSuites;

	public:
		static inline bool Verbose = false;
	};
}
namespace EngineCore::Tests::Detail
{
	class TestSuite
	{
	public:
		struct ExtraData
		{
			bool Redirect_stdout = false;
			bool Redirect_stdin = false;
			bool Redirect_stderr = false;
		};

	public:
		TestSuite(std::string&& name, ExtraData extra)
			: Name(std::move(name))
			, Tests()
			, Extra(extra)
			, Logger("TestSuite::" + Name)
			, TestLogger("TestSuite::" + Name + "{test_name}")
		{
			TestSuitesManager::TestSuites.insert({ Name, this });
			Logger.SetRealPattern("{C:+black}[{T:pattern='%h:%m:%s:%ms'}] {name} >> {color}{data}");
			TestLogger.SetRealPattern("{C:+black}[{T:pattern='%h:%m:%s:%ms'}] {name} >> {color}{data}");
			if (TestSuitesManager::Verbose == false)
			{
				Logger.SetSeverity(LoggerManager::LogSeverity::Debug);
				TestLogger.SetSeverity(LoggerManager::LogSeverity::Debug);
			}
		}

		std::string Name;
		std::unordered_map<std::string_view, Test*> Tests;
		ExtraData Extra;
		LoggerManager::BasicLogger Logger;
		LoggerManager::BasicLogger TestLogger;
		
	public:
		TestStatusBank ExecAllTests();
	};
}

namespace EngineCore::FMT {
	template<typename FormatContext>
	struct FormatterType<EngineCore::Tests::Detail::TestSuite, FormatContext>
	{
		static void Write(const EngineCore::Tests::Detail::TestSuite& t, FormatContext& context)
		{
			context.Print(t.Name);
		}
	};

	template<typename FormatContext>
	struct FormatterType<EngineCore::Tests::Detail::Test, FormatContext>
	{
		static void Write(const EngineCore::Tests::Detail::Test& t, FormatContext& context) {
			context.Print(t.Link.Name);
			context.Print("::");
			context.Print(t.Name);
		}
	};

	template<typename FormatContext>
	struct FormatterType<EngineCore::Tests::TestStatus, FormatContext>
	{
		static void Write(const EngineCore::Tests::TestStatus& status, FormatContext& context) {
			switch (status)
			{
				case EngineCore::Tests::TestStatus::Ok 		: context.SubContext("[  {C:green}OK{C}  ]"); break;
				case EngineCore::Tests::TestStatus::Fail 	: context.SubContext("[ {C:red}FAIL{C} ]"); break;
				case EngineCore::Tests::TestStatus::Crash 	: context.SubContext("[{C:magenta}Crash{C} ]"); break;
			}
		}
	};

	template<typename FormatContext>
	struct FormatterType<EngineCore::Tests::Detail::TestStatusBank, FormatContext>
	{
		static void Write(const EngineCore::Tests::Detail::TestStatusBank& statusBank, FormatContext& context) {
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
