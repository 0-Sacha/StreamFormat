#pragma once

#include "Detail.h"

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

template<typename CharType>
class BasicLoggerSink
{
    public:
        using PatternType = std::basic_string<CharType>;
        using NameType = std::basic_string<CharType>;
        using BufferType = std::basic_string_view<CharType>;

    public:
        BasicLoggerSink(NameType&& name)
                : m_Name(std::forward<NameType>(name))
            {}

    public:
        virtual void Write(const BufferType& bufferToPrint)    {}
        void PrintToSink(const BufferType& bufferToPrint)      { Write(bufferToPrint); }

    public:
        NameType& GetName() { return m_Name; }
        LogSeverity& GetSeverity() { return m_Severity; }
        PatternOverride<CharType>& GetPatternOverride() { return m_PatternOverride; }

    public:
        NameType m_Name = "";
        PatternType m_Pattern = "{name} >> {data}";
        PatternOverride<CharType> m_PatternOverride;
        LogSeverity m_Severity = LogSeverity::Trace;

    public:
        void FormatAndPrintToSink(const PatternType& pattern, const NameType& loggerName, const BufferType& formatBuffer)
        {
            auto formatPatternStr = FMT::Detail::FormatAndGetBufferOut(pattern,
                                                                       FORMAT_SV("name", ConcateNameAndSinkName(loggerName, m_Name)),
                                                                       FORMAT_SV("data", formatBuffer));
	        PrintToSink(formatPatternStr);
        }

    public:
        bool NeedToLog(const LogSeverity& severity) const   { return severity >= m_Severity; }
        bool NeedToLog(const LogStatus& status) const       { return true; }
        bool NeedToLog(const LogBasic&) const               { return true; }

    public:
        template<typename T>
        void PrintToSink(const T& severity, const BufferType& bufferToPrint) { if (NeedToLog(severity)) PrintToSink(bufferToPrint); }

    public:
        const PatternType& GetPattern() const { return m_Pattern; }

        const PatternType& GetPattern(const LogSeverity& severity) const 
        {
            switch(severity)
            {
                case LogSeverity::Trace:    if (m_PatternOverride.TracePattern.empty() == false) return m_PatternOverride.TracePattern;
                case LogSeverity::Debug:    if (m_PatternOverride.DebugPattern.empty() == false) return m_PatternOverride.DebugPattern;
                case LogSeverity::Info:     if (m_PatternOverride.InfoPattern.empty() == false) return m_PatternOverride.InfoPattern;
                case LogSeverity::Warn:     if (m_PatternOverride.WarnPattern.empty() == false) return m_PatternOverride.WarnPattern;
                case LogSeverity::Error:    if (m_PatternOverride.ErrorPattern.empty() == false) return m_PatternOverride.ErrorPattern;
                case LogSeverity::Fatal:    if (m_PatternOverride.FatalPattern.empty() == false) return m_PatternOverride.FatalPattern;
            }

            return m_Pattern;
        }

        const PatternType& GetPattern(const LogStatus& status) const 
        {
            switch(status)
            {
                case LogStatus::OK:     if (m_PatternOverride.OkPattern.empty() == false) return m_PatternOverride.OkPattern;
                case LogStatus::FAIL:   if (m_PatternOverride.FailPattern.empty() == false) return m_PatternOverride.FailPattern;
            }

            return m_Pattern;
        }

        const PatternType& GetPattern(const LogBasic&) const 
        {
            if (m_PatternOverride.BasicPattern.empty() == false)
                return m_PatternOverride.BasicPattern;
            return m_Pattern;
        }
    };
}
