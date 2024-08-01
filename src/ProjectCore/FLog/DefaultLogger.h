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
        [[maybe_unused]] static BasicLogger& Core()
        {
            static BasicLogger instance(PROJECTCORE_BASE_LOGGER_NAME "-Core", LogSeverity::Trace);
            return instance;
        }
        [[maybe_unused]] static BasicLogger& Client()
        {
            static BasicLogger instance(PROJECTCORE_BASE_LOGGER_NAME "-Client", LogSeverity::Trace);
            return instance;
        }
    };
}

#ifdef PROJECTCORE_LOGGER_ENABLE
    #define CORE_TRACE(...) ProjectCore::FLog::BasicLogger::Core().Trace(__VA_ARGS__)
    #define CORE_DEBUG(...) ProjectCore::FLog::BasicLogger::Core().Debug(__VA_ARGS__)
    #define CORE_INFO(...)  ProjectCore::FLog::BasicLogger::Core().Info(__VA_ARGS__)
    #define CORE_WARN(...)  ProjectCore::FLog::BasicLogger::Core().Warn(__VA_ARGS__)
    #define CORE_ERROR(...) ProjectCore::FLog::BasicLogger::Core().Error(__VA_ARGS__)
    #define CORE_FATAL(...) ProjectCore::FLog::BasicLogger::Core().Fatal(__VA_ARGS__)
#else
    #define CORE_TRACE(...)
    #define CORE_DEBUG(...)
    #define CORE_INFO(...)
    #define CORE_WARN(...)
    #define CORE_ERROR(...)
    #define CORE_FATAL(...)
#endif
