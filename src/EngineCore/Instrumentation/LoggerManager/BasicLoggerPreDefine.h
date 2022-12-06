#pragma once

#include "BasicLogger.h"

namespace EngineCore::LoggerManager {
	static BasicLogger& GetCoreInstance()	{ static BasicLogger instance(ENGINECORE_BASE_LOGGER_NAME "-Core", LogSeverity::Trace); return instance; }
	static BasicLogger& GetClientInstance()	{ static BasicLogger instance(ENGINECORE_BASE_LOGGER_NAME "-Client", LogSeverity::Trace); return instance; }
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