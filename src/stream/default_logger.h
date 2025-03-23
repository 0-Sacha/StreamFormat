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
        [[maybe_unused]] static BasicLogger& core()
        {
            static BasicLogger instance(STREAMFORMAT_BASE_LOGGER_NAME "-core", LogSeverity::Trace);
            return instance;
        }
        [[maybe_unused]] static BasicLogger& client()
        {
            static BasicLogger instance(STREAMFORMAT_BASE_LOGGER_NAME "-client", LogSeverity::Trace);
            return instance;
        }
    };
}

#ifdef STREAMFORMAT_LOGGER_ENABLE
    #define CORE_TRACE(...) stream::flog::BasicLogger::core().trace(__VA_ARGS__)
    #define CORE_DEBUG(...) stream::flog::BasicLogger::core().debug(__VA_ARGS__)
    #define CORE_INFO(...)  stream::flog::BasicLogger::core().info(__VA_ARGS__)
    #define CORE_WARN(...)  stream::flog::BasicLogger::core().warn(__VA_ARGS__)
    #define CORE_ERROR(...) stream::flog::BasicLogger::core().error(__VA_ARGS__)
    #define CORE_FATAL(...) stream::flog::BasicLogger::core().fatal(__VA_ARGS__)
#else
    #define CORE_TRACE(...)
    #define CORE_DEBUG(...)
    #define CORE_INFO(...)
    #define CORE_WARN(...)
    #define CORE_ERROR(...)
    #define CORE_FATAL(...)
#endif
