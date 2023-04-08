#pragma once

#include "Detail.h"
#include <future>

namespace ProjectCore::LoggerManager::Detail
{
    enum class AsyncSink
    {
        Sync,
        Async
    };

    template<typename Severity, typename CharType>
    class BasicLoggerSink
    {
    public:
        using PatternType = std::basic_string<CharType>;
        using PatternTransfertType = std::basic_string_view<CharType>;
        using NameType = std::basic_string<CharType>;
        using BufferType = std::basic_string_view<CharType>;

        using SeverityValueType = typename Severity::Value;

    public:
        BasicLoggerSink(NameType&& name)
                : Name(std::forward<NameType>(name))
                , IsAsync(AsyncSink::Sync)
            {}

        BasicLoggerSink(NameType&& name, AsyncSink isAsync)
                : Name(std::forward<NameType>(name))
                , IsAsync(isAsync)
            {}

        virtual ~BasicLoggerSink() = default;

    public:
        NameType Name = "";
        PatternType Pattern = "{name} >> {data}";
        SeverityValueType SinkSeverity{SeverityValueType::DefaultSeverity};
        typename Severity::PatternOverride SeverityPatternOverride;
        AsyncSink IsAsync;
    
    protected:
        std::future<void> m_AsyncWaiter;

    public:
        bool NeedToLog(const SeverityValueType& severity) { return severity >= SinkSeverity; }
        void WriteToSink(const SeverityValueType& severity, const BufferType& bufferToPrint) { if (NeedToLog(severity)) WriteToSink(bufferToPrint); }

    public:
        PatternTransfertType GetPattern(const typename Severity::Value& severity) const 
        {
            PatternTransfertType customPattern = SeverityPatternOverride.GetPattern(severity);
            if (customPattern.data() == nullptr || customPattern.size() == 0)
                return Pattern;
            return customPattern;
        }

    protected:
        virtual void WriteImpl(const BufferType& bufferToPrint) = 0;

    public:
        void WriteToSinkSync(const BufferType& bufferToPrint)       { WriteImpl(bufferToPrint); }
        void WriteToSinkAsync(const BufferType& bufferToPrint)
        {
            m_AsyncWaiter = std::async(std::launch::async, &BasicLoggerSink<Severity, CharType>::WriteToSinkSync, this, bufferToPrint);
        }
        
        void WriteToSink(const BufferType& bufferToPrint)
        {
            if (IsAsync == AsyncSink::Sync)
                WriteToSinkSync(bufferToPrint);
            else
                WriteToSinkAsync(bufferToPrint);
        }

    public:
        void WaitUnitlFinishedToWrite()
        {
            if (IsAsync == AsyncSink::Async)
                return m_AsyncWaiter.get();
        }

        void FormatAndWriteToSinkSync(PatternTransfertType pattern, const NameType& loggerName, const BufferType& formatBuffer)
        {
            auto formatPatternStr = FMT::Detail::FormatAndGetBufferOut(pattern,
                                                                       FORMAT_SV("name", ConcateNameAndSinkName(loggerName, Name)),
                                                                       FORMAT_SV("data", formatBuffer));
            BufferType buffer(*formatPatternStr);
            WriteToSinkSync(buffer);
        }

        void FormatAndWriteToSinkAsync(PatternTransfertType pattern, const NameType& loggerName, const BufferType& formatBuffer)
        {
            m_AsyncWaiter = std::async(std::launch::async, &BasicLoggerSink<Severity, CharType>::FormatAndWriteToSinkSync, this, pattern, loggerName, formatBuffer);
        }

        void FormatAndWriteToSink(PatternTransfertType pattern, const NameType& loggerName, const BufferType& formatBuffer)
        {
            if (IsAsync == AsyncSink::Sync)
                FormatAndWriteToSinkSync(pattern, loggerName, formatBuffer);
            else
                FormatAndWriteToSinkAsync(pattern, loggerName, formatBuffer);
        }
    };
}
