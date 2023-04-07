#pragma once

#include "BasicLogger.h"

#ifndef PROJECTCORE_BASE_LOGGER_NAME
	#define PROJECTCORE_BASE_LOGGER_NAME "APP"
#endif

namespace ProjectCore::LoggerManager
{
	[[maybe_unused]] static BasicLogger& GetLoggerCore()		{ static BasicLogger instance(PROJECTCORE_BASE_LOGGER_NAME "-Core", LogSeverity::Trace); return instance; }
	[[maybe_unused]] static BasicLogger& GetLoggerClient()	{ static BasicLogger instance(PROJECTCORE_BASE_LOGGER_NAME "-Client", LogSeverity::Trace); return instance; }
}


#ifdef PROJECTCORE_LOGGER_ENABLE
#define PROJECTCORE_TRACE(...)	ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Trace(__VA_ARGS__)
#define PROJECTCORE_INFO(...)	ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Info(__VA_ARGS__)
#define PROJECTCORE_WARN(...)	ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Warn(__VA_ARGS__)
#define PROJECTCORE_ERROR(...)	ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Error(__VA_ARGS__)
#define PROJECTCORE_FATAL(...)	ProjectCore::LoggerManager::BasicLogger::GetCoreInstance().Fatal(__VA_ARGS__)
#else
#define PROJECTCORE_TRACE(...)
#define PROJECTCORE_INFO(...)
#define PROJECTCORE_WARN(...)
#define PROJECTCORE_ERROR(...)
#define PROJECTCORE_FATAL(...)
#endif
