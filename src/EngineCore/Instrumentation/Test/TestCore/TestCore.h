#pragma once

#include "../../LogSystem/LogSystem.h"

#define ENGINE_CORE_TEST_TRACE(...)	EngineCore::Test::TestCore::GetLogger().LogTrace(__VA_ARGS__)
#define ENGINE_CORE_TEST_INFO(...)	EngineCore::Test::TestCore::GetLogger().LogInfo(__VA_ARGS__)
#define ENGINE_CORE_TEST_WARN(...)	EngineCore::Test::TestCore::GetLogger().LogWarn(__VA_ARGS__)
#define ENGINE_CORE_TEST_ERROR(...)	EngineCore::Test::TestCore::GetLogger().LogError(__VA_ARGS__)
#define ENGINE_CORE_TEST_FATAL(...)	EngineCore::Test::TestCore::GetLogger().LogFatal(__VA_ARGS__)

#define ENGINE_CORE_TEST_OK(...)	EngineCore::Test::TestCore::GetLogger().LogOk(__VA_ARGS__)
#define ENGINE_CORE_TEST_FAIL(...)	EngineCore::Test::TestCore::GetLogger().LogFail(__VA_ARGS__)

#define ENGINE_CORE_TEST_BASIC(...)	EngineCore::Test::TestCore::GetLogger().LogBasic(__VA_ARGS__)


namespace EngineCore::Test {
	class TestCore
	{
	public:
		static LogSystem& GetLogger()	{ static LogSystem instance("EngineCore-Test"); return instance; }
	};
}
