#pragma once

#include "BasicLogger.h"

#ifndef PROJECTCORE_BASE_LOGGER_NAME
	#define PROJECTCORE_BASE_LOGGER_NAME "APP"
#endif

namespace ProjectCore::LoggerManager
{
	static BasicLogger& GetLoggerCore()		{ static BasicLogger instance(PROJECTCORE_BASE_LOGGER_NAME "-Core", LogSeverity::Trace); return instance; }
	static BasicLogger& GetLoggerClient()	{ static BasicLogger instance(PROJECTCORE_BASE_LOGGER_NAME "-Client", LogSeverity::Trace); return instance; }
}


#ifdef PROJECTCORE_LOGGER_ENABLE
#define PROJECTCORE_TRACE(...)	ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Trace(__VA_ARGS__)
#define PROJECTCORE_INFO(...)	ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Info(__VA_ARGS__)
#define PROJECTCORE_WARN(...)	ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Warn(__VA_ARGS__)
#define PROJECTCORE_ERROR(...)	ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Error(__VA_ARGS__)
#define PROJECTCORE_FATAL(...)	ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Fatal(__VA_ARGS__)

#define PROJECTCORE_OK(...)		ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Ok(__VA_ARGS__)
#define PROJECTCORE_FAIL(...)	ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Fail(__VA_ARGS__)

#define PROJECTCORE_BASIC(...)	ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Basic(__VA_ARGS__)
#else
#define PROJECTCORE_TRACE(...)
#define PROJECTCORE_INFO(...)
#define PROJECTCORE_WARN(...)
#define PROJECTCORE_ERROR(...)
#define PROJECTCORE_FATAL(...)

#define PROJECTCORE_OK(...)
#define PROJECTCORE_FAIL(...)

#define PROJECTCORE_BASIC(...)
#endif

#ifdef PROJECTCORE_EC_ENABLE
#define EC_TRACE(...)	PROJECTCORE_TRACE(...)
#define EC_INFO(...)	PROJECTCORE_INFO(...
#define EC_WARN(...)	PROJECTCORE_WARN(...)
#define EC_ERROR(...)	PROJECTCORE_ERROR(...)
#define EC_FATAL(...)	PROJECTCORE_FATAL(...)

#define EC_OK(...)		PROJECTCORE_OK(...)
#define EC_FAIL(...)	PROJECTCORE_FAIL(...)

#define EC_BASIC(...)	PROJECTCORE_BASIC(...)
#endif /* PROJECTCORE_EC_ENABLE */
