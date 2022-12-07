#pragma once

#include "LoggerSink.h"
#include <future>

namespace EngineCore::LoggerManager::Detail {
    template<typename Sink>
    class AsyncSink : public Sink
    {
    public:
        template <typename... Args>
        AsyncSink(Args&&... args)
            : Sink(std::forward<Args>(args)...)
        {}
        
    public:
        void PrintToSink(const typename Sink::BufferType& bufferToPrint)
        {
            std::async(std::launch::async, &Sink::PrintToSink, this, bufferToPrint);
        }

        void FormatAndPrintToSink(const typename Sink::PatternType& pattern, const typename Sink::NameType& loggerName, const typename Sink::BufferType& formatBuffer)
        {
            std::async(std::launch::async, &Sink::FormatAndPrintToSink, this, pattern, loggerName, formatBuffer);
        }
    };
}
