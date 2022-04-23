#pragma once

#include "Core.h"

#include "Instrumentation/Formatter/Formatter.h"
#include "Instrumentation/LogSystem/LogSystem.h"
#include "Instrumentation/Formatter/Format/Container/AllContainer.h"
#include "Instrumentation/Profiling/Profiling.h"

#include "Test/Test.h"

// #include "Maths/Maths.h"

#ifdef ENGINECORE_LOGGER_ENABLE
#define ENGINECORE_TRACE(...)	EngineCore::Instrumentation::LogSystem::GetCoreInstance().LogTrace(__VA_ARGS__)
#define ENGINECORE_INFO(...)	EngineCore::Instrumentation::LogSystem::GetCoreInstance().LogInfo(__VA_ARGS__)
#define ENGINECORE_WARN(...)	EngineCore::Instrumentation::LogSystem::GetCoreInstance().LogWarn(__VA_ARGS__)
#define ENGINECORE_ERROR(...)	EngineCore::Instrumentation::LogSystem::GetCoreInstance().LogError(__VA_ARGS__)
#define ENGINECORE_FATAL(...)	EngineCore::Instrumentation::LogSystem::GetCoreInstance().LogFatal(__VA_ARGS__)

#define ENGINECORE_OK(...)		EngineCore::Instrumentation::LogSystem::GetCoreInstance().LogOk(__VA_ARGS__)
#define ENGINECORE_FAIL(...)	EngineCore::Instrumentation::LogSystem::GetCoreInstance().LogFail(__VA_ARGS__)

#define ENGINECORE_BASIC(...)	EngineCore::Instrumentation::LogSystem::GetCoreInstance().LogBasic(__VA_ARGS__)
#else /* ENGINECORE_LOGGER_ENABLE */
#define ENGINECORE_TRACE(...)
#define ENGINECORE_INFO(...)
#define ENGINECORE_WARN(...)
#define ENGINECORE_ERROR(...)
#define ENGINECORE_FATAL(...)

#define ENGINECORE_OK(...)
#define ENGINECORE_FAIL(...)

#define ENGINECORE_BASIC(...)
#endif /* ENGINECORE_LOGGER_ENABLE */

#ifdef ENGINECORE_EC_ENABLE
#define EC_TRACE(...)	ENGINECORE_TRACE(...)
#define EC_INFO(...)	ENGINECORE_INFO(...
#define EC_WARN(...)	ENGINECORE_WARN(...)
#define EC_ERROR(...)	ENGINECORE_ERROR(...)
#define EC_FATAL(...)	ENGINECORE_FATAL(...)

#define EC_OK(...)		ENGINECORE_OK(...)
#define EC_FAIL(...)	ENGINECORE_FAIL(...)

#define EC_BASIC(...)	ENGINECORE_BASIC(...)
#endif /* ENGINECORE_EC_ENABLE */
