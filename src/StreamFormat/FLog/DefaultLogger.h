#pragma once

#include "LoggerImpl/XLogger.h"

#ifndef STREAMFORMAT_BASE_LOGGER_NAME
#undef STREAMFORMAT_BASE_LOGGER_NAME
#define STREAMFORMAT_BASE_LOGGER_NAME "APP"
#endif

namespace StreamFormat::FLog
{
    class DefaultLogger
    {
    public:
        [[maybe_unused]] static BasicLogger& Core()
        {
            static BasicLogger instance(STREAMFORMAT_BASE_LOGGER_NAME "-Core", LogSeverity::Trace);
            return instance;
        }
        [[maybe_unused]] static BasicLogger& Client()
        {
            static BasicLogger instance(STREAMFORMAT_BASE_LOGGER_NAME "-Client", LogSeverity::Trace);
            return instance;
        }
    };
}

#ifdef STREAMFORMAT_LOGGER_ENABLE
    #define CORE_TRACE(...) StreamFormat::FLog::BasicLogger::Core().Trace(__VA_ARGS__)
    #define CORE_DEBUG(...) StreamFormat::FLog::BasicLogger::Core().Debug(__VA_ARGS__)
    #define CORE_INFO(...)  StreamFormat::FLog::BasicLogger::Core().Info(__VA_ARGS__)
    #define CORE_WARN(...)  StreamFormat::FLog::BasicLogger::Core().Warn(__VA_ARGS__)
    #define CORE_ERROR(...) StreamFormat::FLog::BasicLogger::Core().Error(__VA_ARGS__)
    #define CORE_FATAL(...) StreamFormat::FLog::BasicLogger::Core().Fatal(__VA_ARGS__)
#else
    #define CORE_TRACE(...)
    #define CORE_DEBUG(...)
    #define CORE_INFO(...)
    #define CORE_WARN(...)
    #define CORE_ERROR(...)
    #define CORE_FATAL(...)
#endif
