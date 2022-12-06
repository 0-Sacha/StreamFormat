#pragma once

#include "BasicLogger.h"

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
class LoggerSink
{
    public:
        virtual void PrintToSink(const FMT::Detail::BasicFormatterMemoryBufferOutCopy<CharType>& bufferToPrint);

    public:
        std::basic_string<CharType>& GetName() { return m_Name; }
        std::basic_string<CharType>& GetPattern() { return m_Pattern; }
        LogSeverity& GetSeverity() { return m_Severity; }
        PatternOverride<CharType>& GetPatternOverride() { return m_PatternOverride; }

    public:
        std::basic_string<CharType> m_Name;
        std::basic_string<CharType> m_Pattern;
        PatternOverride<CharType> m_PatternOverride;
        LogSeverity m_Severity;

    public:
        void PrintToSink(LogSeverity severity, const FMT::Detail::BasicFormatterMemoryBufferOutCopy<CharType>& bufferToPrint)   { if (severity < m_Severity) return; return PrintToSink(bufferToPrint); }
        void PrintToSink(LogStatus status, const FMT::Detail::BasicFormatterMemoryBufferOutCopy<CharType>& bufferToPrint)       { return PrintToSink(bufferToPrint); }
        void PrintToSink(LogBasic, const FMT::Detail::BasicFormatterMemoryBufferOutCopy<CharType>& bufferToPrint)               { return PrintToSink(bufferToPrint); }

    public:
        void FormatAndPrintToSink(LogSeverity severity, const FMT::Detail::BasicFormatterMemoryBufferOutCopy<CharType>& bufferToPrint)
        {
            if (severity < m_Severity)
                return;

            std::basic_string<CharType>* pattern = &m_Pattern;
            switch(severity)
            {
                case LogSeverity::Trace:    if (m_PatternOverride.TracePattern.empty()) pattern = &m_PatternOverride.TracePattern;
                case LogSeverity::Debug:    if (m_PatternOverride.DebugPattern.empty()) pattern = &m_PatternOverride.DebugPattern;
                case LogSeverity::Info:     if (m_PatternOverride.InfoPattern.empty()) pattern = &m_PatternOverride.InfoPattern;
                case LogSeverity::Warn:     if (m_PatternOverride.WarnPattern.empty()) pattern = &m_PatternOverride.WarnPattern;
                case LogSeverity::Error:    if (m_PatternOverride.ErrorPattern.empty()) pattern = &m_PatternOverride.ErrorPattern;
                case LogSeverity::Fatal:    if (m_PatternOverride.FatalPattern.empty()) pattern = &m_PatternOverride.FatalPattern;
            }

            auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(*pattern, FORMAT_SV("color", severity), FORMAT_SV("name", m_Name), FORMAT_SV("data", static_cast<std::basic_string_view<CharType>>(bufferToPrint)));
            PrintToSink(formatBuffer);
        }

        void FormatAndPrintToSink(LogStatus status, const FMT::Detail::BasicFormatterMemoryBufferOutCopy<CharType>& bufferToPrint)
        {
            std::basic_string<CharType>* pattern = &m_Pattern;
            switch(severity)
            {
                case LogStatus::OK:     if (m_PatternOverride.OkPattern.empty()) pattern = &m_PatternOverride.OkPattern;
                case LogStatus::FAIL:   if (m_PatternOverride.FailPattern.empty()) pattern = &m_PatternOverride.FailPattern;
            }

            auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(*pattern, FORMAT_SV("color", status), FORMAT_SV("name", m_Name), FORMAT_SV("data", static_cast<std::basic_string_view<CharType>>(bufferToPrint)));
            PrintToSink(formatBuffer);
        }

        void FormatAndPrintToSink(LogBasic, const FMT::Detail::BasicFormatterMemoryBufferOutCopy<CharType>& bufferToPrint)
        {
            std::basic_string<CharType>* pattern = &m_Pattern;
            if (m_PatternOverride.BasicPattern.empty())
                pattern = &m_PatternOverride.BasicPattern;

            auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(*pattern, FORMAT_SV("color", ""), FORMAT_SV("name", m_Name), FORMAT_SV("data", static_cast<std::basic_string_view<CharType>>(bufferToPrint)));
            PrintToSink(formatBuffer);
        }
};
}
