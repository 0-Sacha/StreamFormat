#pragma once

#include "LoggerImpl/XLogger.h"

#ifndef PROJECTCORE_BASE_LOGGER_NAME
    #undef PROJECTCORE_BASE_LOGGER_NAME
    #define PROJECTCORE_BASE_LOGGER_NAME "APP"
#endif

namespace ProjectCore::FLog
{
    class DefaultLogger
    {
    public:
        [[maybe_unused]] static BasicLogger& Core()    { static BasicLogger instance(PROJECTCORE_BASE_LOGGER_NAME "-Core", LogSeverity::Trace); return instance; }
        [[maybe_unused]] static BasicLogger& Client()  { static BasicLogger instance(PROJECTCORE_BASE_LOGGER_NAME "-Client", LogSeverity::Trace); return instance; }
    };
}

#ifdef PROJECTCORE_LOGGER_ENABLE
    #define PROJECTCORE_TRACE(...)  ProjectCore::FLog::BasicLogger::Core().Trace(__VA_ARGS__)
    #define PROJECTCORE_DEBUG(...)  ProjectCore::FLog::BasicLogger::Core().Debug(__VA_ARGS__)
    #define PROJECTCORE_INFO(...)   ProjectCore::FLog::BasicLogger::Core().Info(__VA_ARGS__)
    #define PROJECTCORE_WARN(...)   ProjectCore::FLog::BasicLogger::Core().Warn(__VA_ARGS__)
    #define PROJECTCORE_ERROR(...)  ProjectCore::FLog::BasicLogger::Core().Error(__VA_ARGS__)
    #define PROJECTCORE_FATAL(...)  ProjectCore::FLog::BasicLogger::Core().Fatal(__VA_ARGS__)
#else
    #define PROJECTCORE_TRACE(...)
    #define PROJECTCORE_DEBUG(...)
    #define PROJECTCORE_INFO(...)
    #define PROJECTCORE_WARN(...)
    #define PROJECTCORE_ERROR(...)
    #define PROJECTCORE_FATAL(...)
#endif
