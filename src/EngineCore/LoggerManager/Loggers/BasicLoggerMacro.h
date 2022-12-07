#pragma once

#include "BasicLogger.h"

#ifndef ENGINECORE_BASE_LOGGER_NAME
	#define ENGINECORE_BASE_LOGGER_NAME "APP"
#endif

namespace EngineCore::LoggerManager
{
	static BasicLogger& GetLoggerCore()		{ static BasicLogger instance(ENGINECORE_BASE_LOGGER_NAME "-Core", LogSeverity::Trace); return instance; }
	static BasicLogger& GetLoggerClient()	{ static BasicLogger instance(ENGINECORE_BASE_LOGGER_NAME "-Client", LogSeverity::Trace); return instance; }
}


#ifdef ENGINECORE_LOGGER_ENABLE
#define ENGINECORE_TRACE(...)	EngineCore::LoggerManager::BasicLogger::GetCoreInstance().Trace(__VA_ARGS__)
#define ENGINECORE_INFO(...)	EngineCore::LoggerManager::BasicLogger::GetCoreInstance().Info(__VA_ARGS__)
#define ENGINECORE_WARN(...)	EngineCore::LoggerManager::BasicLogger::GetCoreInstance().Warn(__VA_ARGS__)
#define ENGINECORE_ERROR(...)	EngineCore::LoggerManager::BasicLogger::GetCoreInstance().Error(__VA_ARGS__)
#define ENGINECORE_FATAL(...)	EngineCore::LoggerManager::BasicLogger::GetCoreInstance().Fatal(__VA_ARGS__)

#define ENGINECORE_OK(...)		EngineCore::LoggerManager::BasicLogger::GetCoreInstance().Ok(__VA_ARGS__)
#define ENGINECORE_FAIL(...)	EngineCore::LoggerManager::BasicLogger::GetCoreInstance().Fail(__VA_ARGS__)

#define ENGINECORE_BASIC(...)	EngineCore::LoggerManager::BasicLogger::GetCoreInstance().Basic(__VA_ARGS__)
#else
#define ENGINECORE_TRACE(...)
#define ENGINECORE_INFO(...)
#define ENGINECORE_WARN(...)
#define ENGINECORE_ERROR(...)
#define ENGINECORE_FATAL(...)

#define ENGINECORE_OK(...)
#define ENGINECORE_FAIL(...)

#define ENGINECORE_BASIC(...)
#endif

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
