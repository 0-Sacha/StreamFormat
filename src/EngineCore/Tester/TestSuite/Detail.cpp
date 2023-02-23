#pragma once

#include "Detail.h"

namespace EngineCore::Tester
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
		if (status.IsAllOk())
			logger.Info("{C:+black}----- {} -------------------", status);
		else
			logger.Error("{C:+black}----- {} -------------------", status);

		return status.IsAllOk();
	}
}
namespace EngineCore::Tester::Detail
{
	TestStatusBank TestSuite::ExecAllTests()
	{
		if (TestSuitesManager::Verbose == false)
		{
			Logger.SetSeverity(LoggerManager::LogSeverity::Debug);
			TestLogger.SetSeverity(LoggerManager::LogSeverity::Debug);
		}
		else
		{
			Logger.SetSeverity(LoggerManager::LogSeverity::Trace);
			TestLogger.SetSeverity(LoggerManager::LogSeverity::Trace);
		}

		TestStatusBank res;
		
		for (auto& [name, test] : Tests)
		{
			TestStatus status = test->Run();
			res.AddTestStatus(status);
			Logger.Debug("{} -> {}", status, name);
		}

		if (res.IsAllOk())
			Logger.Info("{C:+black}----- {} -------------------", res);
		else
			Logger.Error("{C:+black}----- {} -------------------", res);

		return res;
	}
}
