#pragma once

#include "StreamFormat/FLog/Detail/Detail.h"
#include "StreamFormat/FLog/Loggers/BasicLogger.h"
#include "StreamFormat/FLog/Loggers/LoggerMultiSinkFast.h"
#include "StreamFormat/FLog/Loggers/LoggerMultiSinkSafe.h"
#include "StreamFormat/FLog/Sinks/FileSink.h"

namespace StreamFormat::FLog
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
        static constexpr Value Trace{Value::Trace};
        static constexpr Value Debug{Value::Debug};
        static constexpr Value Info{Value::Info};
        static constexpr Value Warn{Value::Warn};
        static constexpr Value Error{Value::Error};
        static constexpr Value Fatal{Value::Fatal};
        static constexpr Value DefaultSeverity = Trace;

    public:
        class PatternOverride
        {
        public:
            std::basic_string<char> TracePattern = "";
            std::basic_string<char> DebugPattern = "";
            std::basic_string<char> InfoPattern  = "";
            std::basic_string<char> WarnPattern  = "";
            std::basic_string<char> ErrorPattern = "";
            std::basic_string<char> FatalPattern = "";

            std::basic_string_view<char> GetPattern(const Value& severity) const
            {
                switch (severity)
                {
                    case Value::Trace:
                        if (TracePattern.empty() == false) return TracePattern;
                        break;
                    case Value::Debug:
                        if (DebugPattern.empty() == false) return DebugPattern;
                        break;
                    case Value::Info:
                        if (InfoPattern.empty() == false) return InfoPattern;
                        break;
                    case Value::Warn:
                        if (WarnPattern.empty() == false) return WarnPattern;
                        break;
                    case Value::Error:
                        if (ErrorPattern.empty() == false) return ErrorPattern;
                        break;
                    case Value::Fatal:
                        if (FatalPattern.empty() == false) return FatalPattern;
                        break;
                }
                return std::basic_string_view<char>{nullptr, 0};
            }
        };
    };
}

namespace StreamFormat::FLog::Detail
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
        template <typename Severity, typename Format = std::string_view, typename... Args>
        requires FMT::Detail::ConvertibleToBufferInfoView<Format>
        void Log(Severity status, Format&& format, Args&&... args) { Master::template Log(status, format, std::forward<Args>(args)...); }

        template <typename Severity, typename T>
        void Log(Severity status, T&& t)
        {
            Master::template Log(status, std::forward<T>(t));
        }

    public:
        /////---------- Logger Severity with array as format ----------/////
        template <typename Format = std::string_view, typename... Args>
        requires FMT::Detail::ConvertibleToBufferInfoView<Format>
        inline void Trace(Format&& format, Args&&... args) { return Log(LogSeverity::Trace, format, std::forward<Args>(args)...); }
        template <typename Format = std::string_view, typename... Args>
        requires FMT::Detail::ConvertibleToBufferInfoView<Format>
        inline void Debug(Format&& format, Args&&... args) { return Log(LogSeverity::Debug, format, std::forward<Args>(args)...); }
        template <typename Format = std::string_view, typename... Args>
        requires FMT::Detail::ConvertibleToBufferInfoView<Format>
        inline void Info(Format&& format, Args&&... args) { return Log(LogSeverity::Info, format, std::forward<Args>(args)...); }
        template <typename Format = std::string_view, typename... Args>
        requires FMT::Detail::ConvertibleToBufferInfoView<Format>
        inline void Warn(Format&& format, Args&&... args) { return Log(LogSeverity::Warn, format, std::forward<Args>(args)...); }
        template <typename Format = std::string_view, typename... Args>
        requires FMT::Detail::ConvertibleToBufferInfoView<Format>
        inline void Error(Format&& format, Args&&... args) { return Log(LogSeverity::Error, format, std::forward<Args>(args)...); }
        template <typename Format = std::string_view, typename... Args>
        requires FMT::Detail::ConvertibleToBufferInfoView<Format>
        inline void Fatal(Format&& format, Args&&... args) { return Log(LogSeverity::Fatal, format, std::forward<Args>(args)...); }

        /////---------- NO-FORMAT Logger Severity ----------/////
        template <typename T>
        inline void Trace(T&& t)
        {
            return Log(LogSeverity::Trace, std::forward<T>(t));
        }
        template <typename T>
        inline void Debug(T&& t)
        {
            return Log(LogSeverity::Debug, std::forward<T>(t));
        }
        template <typename T>
        inline void Info(T&& t)
        {
            return Log(LogSeverity::Info, std::forward<T>(t));
        }
        template <typename T>
        inline void Warn(T&& t)
        {
            return Log(LogSeverity::Warn, std::forward<T>(t));
        }
        template <typename T>
        inline void Error(T&& t)
        {
            return Log(LogSeverity::Error, std::forward<T>(t));
        }
        template <typename T>
        inline void Fatal(T&& t)
        {
            return Log(LogSeverity::Fatal, std::forward<T>(t));
        }
    };
}

namespace StreamFormat::FMT
{
    template <typename FormatterExecutor>
    struct FormatterType<StreamFormat::FLog::LogSeverity::Value, FormatterExecutor>
    {
        static void Format(const StreamFormat::FLog::LogSeverity::Value t, FormatterExecutor& executor)
        {
            executor.Data.KeepNewStyle = true;
            switch (t)
            {
                case StreamFormat::FLog::LogSeverity::Trace:
                    FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterExecutor>::Format(Detail::TextProperties::TextColor::BasicColorFG::BrightBlack, executor);
                    break;
                case StreamFormat::FLog::LogSeverity::Debug:
                    FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterExecutor>::Format(Detail::TextProperties::TextColor::BasicColorFG::Blue, executor);
                    break;
                case StreamFormat::FLog::LogSeverity::Info:
                    FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterExecutor>::Format(Detail::TextProperties::TextColor::BasicColorFG::Green, executor);
                    break;
                case StreamFormat::FLog::LogSeverity::Warn:
                    FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterExecutor>::Format(Detail::TextProperties::TextColor::BasicColorFG::Yellow, executor);
                    break;
                case StreamFormat::FLog::LogSeverity::Error:
                    FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterExecutor>::Format(Detail::TextProperties::TextColor::BasicColorFG::Red, executor);
                    break;
                case StreamFormat::FLog::LogSeverity::Fatal:
                    FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterExecutor>::Format(Detail::TextProperties::TextColor::BasicColorFG::BrightMagenta, executor);
                    break;
            }
        }
    };
}

namespace StreamFormat::FLog
{
    using BasicLogger         = Detail::XLogger<Detail::BasicLoggerImpl<LogSeverity>>;
    using LoggerMultiSinkFast = Detail::XLogger<Detail::BasicLoggerMultiSinkFastImpl<LogSeverity, char>>;
    using LoggerMultiSinkSafe = Detail::XLogger<Detail::BasicLoggerMultiSinkSafeImpl<LogSeverity, char>>;

    extern template class Detail::XLogger<Detail::BasicLoggerImpl<LogSeverity>>;
    extern template class Detail::XLogger<Detail::BasicLoggerMultiSinkFastImpl<LogSeverity, char>>;
    extern template class Detail::XLogger<Detail::BasicLoggerMultiSinkSafeImpl<LogSeverity, char>>;
}

namespace StreamFormat::FLog::Sinks
{
    using ConsoleSink = BasicConsoleSink<LogSeverity, char>;
    using FileSink    = BasicFileSink<LogSeverity, char>;

    extern template class BasicConsoleSink<LogSeverity, char>;
    extern template class BasicFileSink<LogSeverity, char>;
}
