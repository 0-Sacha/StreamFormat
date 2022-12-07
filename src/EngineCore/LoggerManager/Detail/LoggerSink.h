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
        virtual void PrintToSink(const FMT::Detail::BasicFormatterMemoryBufferOutCopy<CharType>& bufferToPrint) = 0;

    public:
        std::basic_string<CharType>& GetName() { return m_Name; }
        LogSeverity& GetSeverity() { return m_Severity; }
        PatternOverride<CharType>& GetPatternOverride() { return m_PatternOverride; }

    public:
        std::basic_string<CharType> m_Name;
        std::basic_string<CharType> m_Pattern;
        PatternOverride<CharType> m_PatternOverride;
        LogSeverity m_Severity;

    public:
        bool NeedToLog(const LogSeverity& severity) { return severity >= m_Severity; }
        bool NeedToLog(const LogStatus& status)     { return true; }
        bool NeedToLog(const LogBasic&)             { return true; }

        
    public:
        template<typename T>
        void PrintToSink(const T& severity, const FMT::Detail::BasicFormatterMemoryBufferOutCopy<CharType>& bufferToPrint)   { if (NeedToLog(severity)) PrintToSink(bufferToPrint); }

    public:
        const std::basic_string_view<CharType>& GetPattern() { return m_Pattern; }

        const std::basic_string<CharType>& GetPattern(const LogSeverity& severity)
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

        const std::basic_string<CharType>& GetPattern(const LogStatus& status)
        {
            switch(status)
            {
                case LogStatus::OK:     if (m_PatternOverride.OkPattern.empty() == false) return m_PatternOverride.OkPattern;
                case LogStatus::FAIL:   if (m_PatternOverride.FailPattern.empty() == false) return m_PatternOverride.FailPattern;
            }

            return m_Pattern;
        }

        const std::basic_string<CharType>& GetPattern(const LogBasic&)
        {
            if (m_PatternOverride.BasicPattern.empty() == false)
                return m_PatternOverride.BasicPattern;
            return m_Pattern;
        }
    };
}
