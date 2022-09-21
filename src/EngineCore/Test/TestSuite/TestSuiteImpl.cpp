#include "EngineCore/Core/Core.h"
#include "EngineCorepch.h"

#include "TestSuiteImpl.h"

namespace EngineCore::Test {

	MasterTestSuite::MasterTestSuite()
		: Logger("TestSuite-Logger", "{color} {test_name} >> {data}")
	{}

	MasterTestSuite& MasterTestSuite::GetInstance()
	{
		static MasterTestSuite instance;
		return instance;
	}
	
	void MasterTestSuite::ExecAllTestSuitesImpl()
	{
		for (auto i : TestSuitesList)
		{
			Logger.Basic("{C:+black}----- {:C:white} -------------------------", i, FORMAT_SV("test_name", "BEGIN"));

			i->ExecAllFunctions();
			
			Logger.Basic("{C:+black}----- {:C:white} => TestDone {:C:white} | TestCheck {:C:green} | TestFail {:C:red} | TestCrash {:C:magenta} -------------------", i, i->TestDone, i->TestCheck, i->TestFail, i->TestCrash, FORMAT_SV("test_name", " END "));

			TestDone += i->TestDone;
			TestCheck += i->TestCheck;
			TestFail += i->TestFail;
			TestCrash += i->TestCrash;
		}
		Logger.Basic("{C:+black}----- TestDone {:C:white} | TestCheck {:C:green} | TestFail {:C:red} | TestCrash {:C:magenta} -------------------", TestDone, TestCheck, TestFail, TestCrash, FORMAT_SV("test_name", "TOTAL"));
	}

	void TestSuite::ExecAllFunctions()
	{
		for (auto i : TestFuncsList)
			i->Exec(*i);
	}

	void TestSuite::TestFunc::TestAssert(bool assert, std::string_view assertView, CompilerDataPack compilerData)
	{
		++Link.TestDone;
		if (assert == true)
		{
			MasterTestSuite::GetLogger().Ok("{:C:green}", assertView, FORMAT_SV("test_name", *this));
			++Link.TestCheck;
		}
		else
		{
			MasterTestSuite::GetLogger().Fail("{:C:red}", assertView, FORMAT_SV("test_name", *this));
			++Link.TestFail;
		}
	}
}
