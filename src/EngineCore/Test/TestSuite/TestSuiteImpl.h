#pragma once

#include "../TestCore.h"

namespace EngineCore::Test {
	class TestSuite;

	class MasterTestSuite
	{
	public:
		static MasterTestSuite& GetInstance();

	public:
		static inline LogSystem& GetLogger()			{ return GetInstance().Logger; }
		static inline std::vector<TestSuite*>& GetTestSuitesList()	{ return GetInstance().TestSuitesList; }
		static inline void ExecAllTestSuites()						{ GetInstance().ExecAllTestSuitesImpl(); }

	private:
		MasterTestSuite();
	
	private:
		void ExecAllTestSuitesImpl();
	
	private:
		LogSystem Logger;
		std::vector<TestSuite*> TestSuitesList;

		std::uint32_t TestDone = 0;
		std::uint32_t TestCheck = 0;
		std::uint32_t TestFail = 0;
		std::uint32_t TestCrash = 0;
	};

	class TestSuite
	{
	public:
		struct TestSuiteExtra
		{
			std::string_view File;
			std::string_view Line;
			bool Redirect_stdout = false;
			bool Redirect_stdin = false;
			bool Redirect_stderr = false;
		};

		struct TestFuncExtra
		{
			std::string_view File;
			std::string_view Line;
		};

		struct TestFunc
		{
		public:
			TestFunc(const std::string& name, TestSuite& link, std::function<void(TestFunc& TestFuncLink)> exec, TestFuncExtra extra)
				: Name(name)
				, ExtraData(extra)
				, Exec(exec)
				, Link(link)
			{
				Link.TestFuncsList.push_back(this);
			}

		public:
			void TestAssert(bool assert, const std::string_view assertView, CompilerDataPack compilerData);
			template <typename T>
			void TestEq(T result, std::equality_comparable_with<T> auto expected, const std::string_view resultView, const std::string_view expectedView, CompilerDataPack compilerData);
			template <typename T>
			void TestNotEq(T result, std::equality_comparable_with<T> auto notExpected, const std::string_view resultView, const std::string_view notExpectedView, CompilerDataPack compilerData);

		public:
			std::function<void(TestFunc &TestFuncLink)> Exec;

			std::string Name;
			TestFuncExtra ExtraData;
			TestSuite& Link;
		};
			
	public:
		TestSuite(const std::string& name, TestSuiteExtra extra)
			: Name(name)
			, ExtraData(extra)
		{
			MasterTestSuite::GetTestSuitesList().push_back(this);
		}

		std::uint32_t TestDone = 0;
		std::uint32_t TestCheck = 0;
		std::uint32_t TestFail = 0;
		std::uint32_t TestCrash = 0;

		std::string Name;

		std::vector<TestFunc*> TestFuncsList;

		TestSuiteExtra ExtraData;

	public:
		void ExecAllFunctions();
	};
}


namespace EngineCore::Test {

	template <typename T>
	void TestSuite::TestFunc::TestEq(T result, std::equality_comparable_with<T> auto expected, const std::string_view resultView, const std::string_view expectedView, CompilerDataPack compilerData)
	{
		++Link.TestDone;
		if (result == expected)
		{
			MasterTestSuite::GetLogger().LogOk("{C:green}{} return {} ; Expected was : {}", resultView, result, expectedView, FORMAT_SV("test_name", *this));
			++Link.TestCheck;
		}
		else
		{
			MasterTestSuite::GetLogger().LogFail("{C:red}{} return {} instead of {} ; Expected was : {}", resultView, result, expected, expectedView, FORMAT_SV("test_name", *this));
			++Link.TestFail;
		}
	}

	template <typename T>
	void TestSuite::TestFunc::TestNotEq(T result, std::equality_comparable_with<T> auto notExpected, const std::string_view resultView, const std::string_view notExpectedView, CompilerDataPack compilerData)
	{
		++Link.TestDone;
		if (result == notExpected)
		{
			MasterTestSuite::GetLogger().LogOk("{C:green}{} return {} and {} was prohibited ; Expected was : {}", resultView, result, notExpected, notExpectedView, FORMAT_SV("test_name", *this));
			++Link.TestCheck;
		}
		else
		{
			MasterTestSuite::GetLogger().LogFail("{C:red}{} return {} but this result was prohibited ; Expected was : {}", resultView, result, notExpected, notExpectedView, FORMAT_SV("test_name", *this));
			++Link.TestFail;
		}
	}

}


namespace EngineCore::FMT {
	template<typename FormatContext>
	struct FormatType<EngineCore::Test::TestSuite, FormatContext>
	{
		static void Write(const EngineCore::Test::TestSuite& t, FormatContext& context) {
			context.Print(t.Name);
		}
	};

	template<typename FormatContext>
	struct FormatType<EngineCore::Test::TestSuite::TestFunc, FormatContext>
	{
		static void Write(const EngineCore::Test::TestSuite::TestFunc& t, FormatContext& context) {
			context.Print(t.Link.Name);
			context.Print("::");
			context.Print(t.Name);
		}
	};
}
