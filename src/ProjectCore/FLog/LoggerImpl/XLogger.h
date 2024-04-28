#pragma once

#include "ProjectCore/FLog/Detail/Detail.h"
#include "ProjectCore/FLog/Loggers/BasicLogger.h"
#include "ProjectCore/FLog/Loggers/LoggerMultiSinkFast.h"
#include "ProjectCore/FLog/Loggers/LoggerMultiSinkSafe.h"
#include "ProjectCore/FLog/Sinks/FileSink.h"

namespace ProjectCore::FLog
{
    struct LogSeverity
    {
    public:
        enum class Value : int
        {
            Trace,
            Debug,
            Info,
            Warn,
            Error,
            Fatal,
            DefaultSeverity = Trace
        };

    public:
        static constexpr Value Trace    {Value::Trace};
        static constexpr Value Debug    {Value::Debug};
        static constexpr Value Info     {Value::Info};
        static constexpr Value Warn     {Value::Warn};
        static constexpr Value Error    {Value::Error};
        static constexpr Value Fatal    {Value::Fatal};
        static constexpr Value DefaultSeverity = Trace;

    public:
        class PatternOverride
        {
        public:
            std::basic_string<char> TracePattern = "";
            std::basic_string<char> DebugPattern = "";
            std::basic_string<char> InfoPattern = "";
            std::basic_string<char> WarnPattern = "";
            std::basic_string<char> ErrorPattern = "";
            std::basic_string<char> FatalPattern = "";

            std::basic_string_view<char> GetPattern(const Value& severity) const 
            {
                switch(severity)
                {
                    case Value::Trace:    if (TracePattern.empty() == false)    return TracePattern;    break;
                    case Value::Debug:    if (DebugPattern.empty() == false)    return DebugPattern;    break;
                    case Value::Info:     if (InfoPattern.empty() == false)     return InfoPattern;     break;
                    case Value::Warn:     if (WarnPattern.empty() == false)     return WarnPattern;     break;
                    case Value::Error:    if (ErrorPattern.empty() == false)    return ErrorPattern;    break;
                    case Value::Fatal:    if (FatalPattern.empty() == false)    return FatalPattern;    break;
                }
                return std::basic_string_view<char>{nullptr, 0};
            }
        };
    };
}

namespace ProjectCore::FLog::Detail
{
    template <typename Master>
    class XLogger : public Master
    {
    public:
        template <typename... Args>
        XLogger(Args&&... args)
            : Master(std::forward<Args>(args)...)
        {}

        ~XLogger() override = default;

    public:
        template<typename Severity, typename Format = std::string_view, typename ...Args>
            requires FMT::Detail::CanBeUseForFMTBufferIn<Format>
        void Log(Severity status, const Format& format, Args&& ...args) { Master::template Log(status, format, std::forward<Args>(args)...); }

        template<typename Severity, typename T>
        void Log(Severity status, T&& t) { Master::template Log(status, std::forward<T>(t)); }

    public:
        /////---------- Logger Severity with array as format ----------/////
        template<typename Format = std::string_view, typename ...Args>
        requires FMT::Detail::CanBeUseForFMTBufferIn<Format>
        inline void Trace(const Format& format, Args&& ...args) { return Log(LogSeverity::Trace, format, std::forward<Args>(args)...); }
        template<typename Format = std::string_view, typename ...Args>
        requires FMT::Detail::CanBeUseForFMTBufferIn<Format>
        inline void Debug(const Format& format, Args&& ...args) { return Log(LogSeverity::Debug, format, std::forward<Args>(args)...); }
        template<typename Format = std::string_view, typename ...Args>
        requires FMT::Detail::CanBeUseForFMTBufferIn<Format>
        inline void Info(const Format& format, Args&& ...args) { return Log(LogSeverity::Info, format, std::forward<Args>(args)...); }
        template<typename Format = std::string_view, typename ...Args>
        requires FMT::Detail::CanBeUseForFMTBufferIn<Format>
        inline void Warn(const Format& format, Args&& ...args) { return Log(LogSeverity::Warn, format, std::forward<Args>(args)...); }
        template<typename Format = std::string_view, typename ...Args>
        requires FMT::Detail::CanBeUseForFMTBufferIn<Format>
        inline void Error(const Format& format, Args&& ...args) { return Log(LogSeverity::Error, format, std::forward<Args>(args)...); }
        template<typename Format = std::string_view, typename ...Args>
        requires FMT::Detail::CanBeUseForFMTBufferIn<Format>
        inline void Fatal(const Format& format, Args&& ...args) { return Log(LogSeverity::Fatal, format, std::forward<Args>(args)...); }

        /////---------- NO-FORMAT Logger Severity ----------/////
        template<typename T>
        inline void Trace(T&& t) { return Log(LogSeverity::Trace, std::forward<T>(t)); }
        template<typename T>
        inline void Debug(T&& t) { return Log(LogSeverity::Debug, std::forward<T>(t)); }
        template<typename T>
        inline void Info(T&& t) { return Log(LogSeverity::Info, std::forward<T>(t)); }
        template<typename T>
        inline void Warn(T&& t) { return Log(LogSeverity::Warn, std::forward<T>(t)); }
        template<typename T>
        inline void Error(T&& t) { return Log(LogSeverity::Error, std::forward<T>(t)); }
        template<typename T>
        inline void Fatal(T&& t) { return Log(LogSeverity::Fatal, std::forward<T>(t)); }
    };
}

namespace ProjectCore::FMT
{
    template<typename FormatterContext>
    struct FormatterType<ProjectCore::FLog::LogSeverity::Value, FormatterContext>
    {
        static void Format(const ProjectCore::FLog::LogSeverity::Value t, FormatterContext& context)
        {
            context.GetFormatData().KeepNewStyle = true;
            switch (t)
            {
            case ProjectCore::FLog::LogSeverity::Trace:
                FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>::Format(Detail::TextProperties::TextColor::BasicColorFG::BrightBlack, context);
                break;
            case ProjectCore::FLog::LogSeverity::Debug:
                FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>::Format(Detail::TextProperties::TextColor::BasicColorFG::Blue, context);
                break;
            case ProjectCore::FLog::LogSeverity::Info:
                FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>::Format(Detail::TextProperties::TextColor::BasicColorFG::Green, context);
                break;
            case ProjectCore::FLog::LogSeverity::Warn:
                FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>::Format(Detail::TextProperties::TextColor::BasicColorFG::Yellow, context);
                break;
            case ProjectCore::FLog::LogSeverity::Error:
                FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>::Format(Detail::TextProperties::TextColor::BasicColorFG::Red, context);
                break;
            case ProjectCore::FLog::LogSeverity::Fatal:
                FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>::Format(Detail::TextProperties::TextColor::BasicColorFG::BrightMagenta, context);
                break;
            }
        }
    };
}

namespace ProjectCore::FLog
{
    template <typename CharType>
    using BasicLoggerMultiSinkFast = Detail::XLogger<Detail::BasicLoggerMultiSinkFastImpl<LogSeverity, CharType>>;
    using LoggerMultiSinkFast = BasicLoggerMultiSinkFast<char>;

    template <typename CharType>
    using BasicLoggerMultiSinkSafe = Detail::XLogger<Detail::BasicLoggerMultiSinkSafeImpl<LogSeverity, CharType>>;
    using LoggerMultiSinkSafe = BasicLoggerMultiSinkSafe<char>;

    using BasicLogger = Detail::XLogger<Detail::BasicLoggerImpl<LogSeverity>>;
}

namespace ProjectCore::FLog::Sinks
{
    using ConsoleSink = Severity::ConsoleSink<LogSeverity>;
    using FileSink = Severity::FileSink<LogSeverity>;
}
