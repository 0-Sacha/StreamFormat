#pragma once

#include "Detail.h"
#include <future>

namespace EngineCore::LoggerManager::Detail {

template<typename CharType>
struct PatternOverride
{
    std::basic_string<CharType> TracePattern = "";
    std::basic_string<CharType> DebugPattern = "";
    std::basic_string<CharType> InfoPattern = "";
    std::basic_string<CharType> WarnPattern = "";
    std::basic_string<CharType> ErrorPattern = "";
    std::basic_string<CharType> FatalPattern = "";

    std::basic_string<CharType> OkPattern = "";
    std::basic_string<CharType> FailPattern = "";
};

enum class AsyncSink
{
    Sync,
    Async
};

template<typename CharType>
class BasicLoggerSink
{
    public:
        using PatternType = std::basic_string<CharType>;
        using NameType = std::basic_string<CharType>;
        using BufferType = std::basic_string_view<CharType>;

    public:
        BasicLoggerSink(NameType&& name)
                : Name(std::forward<NameType>(name))
                , IsAsync(AsyncSink::Sync)
            {}

        BasicLoggerSink(NameType&& name, AsyncSink isAsync)
                : Name(std::forward<NameType>(name))
                , IsAsync(isAsync)
            {}

    protected:
        virtual void WriteImpl(const BufferType& bufferToPrint) {}

    public:
        void WriteToSinkSync(const BufferType& bufferToPrint)       { WriteImpl(bufferToPrint); }
        void WriteToSinkAsync(const BufferType& bufferToPrint)
        {
            m_AsyncWaiter = std::async(std::launch::async, &WriteToSinkSync, this, bufferToPrint);
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

        void FormatAndWriteToSinkSync(const PatternType& pattern, const NameType& loggerName, const BufferType& formatBuffer)
        {
            auto formatPatternStr = FMT::Detail::FormatAndGetBufferOut(pattern,
                                                                       FORMAT_SV("name", ConcateNameAndSinkName(loggerName, Name)),
                                                                       FORMAT_SV("data", formatBuffer));
	        WriteToSinkSync(formatPatternStr);
        }

        void FormatAndWriteToSinkAsync(const PatternType& pattern, const NameType& loggerName, const BufferType& formatBuffer)
        {
            m_AsyncWaiter = std::async(std::launch::async, &FormatAndWriteToSinkSync, this, pattern, loggerName, formatBuffer);
        }

        void FormatAndWriteToSink(const PatternType& pattern, const NameType& loggerName, const BufferType& formatBuffer)
        {
            if (IsAsync == AsyncSink::Sync)
                FormatAndWriteToSinkSync(pattern, loggerName, formatBuffer);
            else
                FormatAndWriteToSinkAsync(pattern, loggerName, formatBuffer);
        }

    public:
        NameType Name = "";
        PatternType Pattern = "{name} >> {data}";
        PatternOverride<CharType> PatternOverride;
        LogSeverity Severity = LogSeverity::Trace;
        AsyncSink IsAsync;
    
    protected:
        std::future<void> m_AsyncWaiter;

    public:
        template<typename T>
        void WriteToSink(const T& severity, const BufferType& bufferToPrint) { if (NeedToLog(severity)) WriteToSink(bufferToPrint); }

    public:
        bool NeedToLog(const LogSeverity& severity) const   { return severity >= Severity; }
        bool NeedToLog(const LogStatus& status) const       { return true; }
        bool NeedToLog(const LogBasic&) const               { return true; }


    public:
        const PatternType& GetPattern() const { return Pattern; }

        const PatternType& GetPattern(const LogSeverity& severity) const 
        {
            switch(severity)
            {
                case LogSeverity::Trace:    if (PatternOverride.TracePattern.empty() == false) return PatternOverride.TracePattern;
                case LogSeverity::Debug:    if (PatternOverride.DebugPattern.empty() == false) return PatternOverride.DebugPattern;
                case LogSeverity::Info:     if (PatternOverride.InfoPattern.empty() == false) return PatternOverride.InfoPattern;
                case LogSeverity::Warn:     if (PatternOverride.WarnPattern.empty() == false) return PatternOverride.WarnPattern;
                case LogSeverity::Error:    if (PatternOverride.ErrorPattern.empty() == false) return PatternOverride.ErrorPattern;
                case LogSeverity::Fatal:    if (PatternOverride.FatalPattern.empty() == false) return PatternOverride.FatalPattern;
            }

            return Pattern;
        }

        const PatternType& GetPattern(const LogStatus& status) const 
        {
            switch(status)
            {
                case LogStatus::OK:     if (PatternOverride.OkPattern.empty() == false) return PatternOverride.OkPattern;
                case LogStatus::FAIL:   if (PatternOverride.FailPattern.empty() == false) return PatternOverride.FailPattern;
            }

            return Pattern;
        }

        const PatternType& GetPattern(const LogBasic&) const 
        {
            if (PatternOverride.BasicPattern.empty() == false)
                return PatternOverride.BasicPattern;
            return Pattern;
        }
    };
}
