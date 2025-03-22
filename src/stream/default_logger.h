#pragma once

#include "flog/frontends/xlogger.h"

#ifndef STREAMFORMAT_BASE_LOGGER_NAME
#undef STREAMFORMAT_BASE_LOGGER_NAME
#define STREAMFORMAT_BASE_LOGGER_NAME "APP"
#endif

namespace stream::flog
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
    #define CORE_TRACE(...) stream::flog::BasicLogger::Core().trace(__VA_ARGS__)
    #define CORE_DEBUG(...) stream::flog::BasicLogger::Core().debug(__VA_ARGS__)
    #define CORE_INFO(...)  stream::flog::BasicLogger::Core().info(__VA_ARGS__)
    #define CORE_WARN(...)  stream::flog::BasicLogger::Core().warn(__VA_ARGS__)
    #define CORE_ERROR(...) stream::flog::BasicLogger::Core().error(__VA_ARGS__)
    #define CORE_FATAL(...) stream::flog::BasicLogger::Core().fatal(__VA_ARGS__)
#else
    #define CORE_TRACE(...)
    #define CORE_DEBUG(...)
    #define CORE_INFO(...)
    #define CORE_WARN(...)
    #define CORE_ERROR(...)
    #define CORE_FATAL(...)
#endif
