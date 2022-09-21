#pragma once

#include "EngineCore/Core/Core.h"

#include "Instrumentation/Formatter/Formatter.h"
#include "Instrumentation/LogManager/LogManager.h"
#include "Instrumentation/Formatter/Format/Container/AllContainer.h"
#include "Instrumentation/Profiler/Profiler.h"

#include "Test/Test.h"

// #include "Maths/Maths.h"

#ifdef ENGINECORE_LOGGER_ENABLE
#define ENGINECORE_TRACE(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Trace(__VA_ARGS__)
#define ENGINECORE_INFO(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Info(__VA_ARGS__)
#define ENGINECORE_WARN(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Warn(__VA_ARGS__)
#define ENGINECORE_ERROR(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Error(__VA_ARGS__)
#define ENGINECORE_FATAL(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Fatal(__VA_ARGS__)

#define ENGINECORE_OK(...)		EngineCore::LogManager::BasicLogger::GetCoreInstance().Ok(__VA_ARGS__)
#define ENGINECORE_FAIL(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Fail(__VA_ARGS__)

#define ENGINECORE_BASIC(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Basic(__VA_ARGS__)
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
