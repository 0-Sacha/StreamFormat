#pragma once

#include "Detail.h"

namespace EngineCore::Tests
{
	bool TestSuitesManager::ExecTestSuitesManagers()
	{
		ENGINECORE_FORMATTER_TIME_BEGIN();
		Detail::TestStatusBank status;

		for (auto& [name, testSuite] : TestSuites)
		{
			testSuite->Logger.Info("{C:+black}----- {C:white}BEGIN{C:+black} -------------------------");
			status.Add(testSuite->ExecAllTests());
			testSuite->Logger.Info("{C:+black}----- {C:white}END{C:+black} -------------------------");
		}

		LoggerManager::BasicLogger logger("TestSuite");
		logger.Info("{C:+black}----- {} -------------------", status);

		return status.TestsOk == status.TestsDone;
	}
}
namespace EngineCore::Tests::Detail
{
	TestStatusBank TestSuite::ExecAllTests()
	{
		TestStatusBank res;
		
		for (auto& [name, test] : Tests)
		{
			TestStatus status = test->Run();
			res.AddTestStatus(status);
			Logger.Debug("{} -> {}", status, name);
		}

		Logger.Info("{C:+black}----- {} -------------------", res);

		return res;
	}
}
