#pragma once

#include "stream/flog/detail/detail.h"
#include "stream/flog/backends/basic_logger.h"
#include "stream/flog/backends/logger_multi_sink_fast.h"
#include "stream/flog/backends/logger_multi_sink_safe.h"
#include "stream/flog/sinks/file_sink.h"

namespace stream::flog {
    struct LogSeverity {
    public:
        enum class Value : int {
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
        class PatternOverride {
        public:
            std::basic_string<char> trace_pattern = "";
            std::basic_string<char> debug_pattern = "";
            std::basic_string<char> info_pattern  = "";
            std::basic_string<char> warn_pattern  = "";
            std::basic_string<char> error_pattern = "";
            std::basic_string<char> fatal_pattern = "";

            std::basic_string_view<char> get_pattern(const Value& severity) const {
                switch (severity) {
                    case Value::Trace:
                        if (trace_pattern.empty() == false) return trace_pattern;
                        break;
                    case Value::Debug:
                        if (debug_pattern.empty() == false) return debug_pattern;
                        break;
                    case Value::Info:
                        if (info_pattern.empty() == false) return info_pattern;
                        break;
                    case Value::Warn:
                        if (warn_pattern.empty() == false) return warn_pattern;
                        break;
                    case Value::Error:
                        if (error_pattern.empty() == false) return error_pattern;
                        break;
                    case Value::Fatal:
                        if (fatal_pattern.empty() == false) return fatal_pattern;
                        break;
                }
                return std::basic_string_view<char>{nullptr, 0};
            }
        };
    };
}  // namespace stream::flog

namespace stream::flog::detail {
    template <typename Master>
    class XLogger : public Master {
    public:
        template <typename... Args>
        XLogger(Args&&... args) : Master(std::forward<Args>(args)...) {}

        ~XLogger() override = default;

    public:
        template <typename Severity, typename Format = std::string_view, typename... Args>
            requires fmt::buf::convertible_to_buffer_info_view<Format>
        [[nodiscard]] std::expected<void, fmt::FMTResult> log(Severity status, Format&& format, Args&&... args) {
            return Master::template log<Format, Args...>(status, format, std::forward<Args>(args)...);
        }

        template <typename Severity, typename T>
        [[nodiscard]] std::expected<void, fmt::FMTResult> log(Severity status, T&& t) {
            return Master::template log<T>(status, std::forward<T>(t));
        }

    public:
        /////---------- logger Severity with array as format ----------/////
        template <typename Format = std::string_view, typename... Args>
            requires fmt::buf::convertible_to_buffer_info_view<Format>
        inline std::expected<void, fmt::FMTResult> trace(Format&& format, Args&&... args) {
            return log(LogSeverity::Trace, format, std::forward<Args>(args)...);
        }
        template <typename Format = std::string_view, typename... Args>
            requires fmt::buf::convertible_to_buffer_info_view<Format>
        inline std::expected<void, fmt::FMTResult> debug(Format&& format, Args&&... args) {
            return log(LogSeverity::Debug, format, std::forward<Args>(args)...);
        }
        template <typename Format = std::string_view, typename... Args>
            requires fmt::buf::convertible_to_buffer_info_view<Format>
        inline std::expected<void, fmt::FMTResult> info(Format&& format, Args&&... args) {
            return log(LogSeverity::Info, format, std::forward<Args>(args)...);
        }
        template <typename Format = std::string_view, typename... Args>
            requires fmt::buf::convertible_to_buffer_info_view<Format>
        inline std::expected<void, fmt::FMTResult> warn(Format&& format, Args&&... args) {
            return log(LogSeverity::Warn, format, std::forward<Args>(args)...);
        }
        template <typename Format = std::string_view, typename... Args>
            requires fmt::buf::convertible_to_buffer_info_view<Format>
        inline std::expected<void, fmt::FMTResult> error(Format&& format, Args&&... args) {
            return log(LogSeverity::Error, format, std::forward<Args>(args)...);
        }
        template <typename Format = std::string_view, typename... Args>
            requires fmt::buf::convertible_to_buffer_info_view<Format>
        inline std::expected<void, fmt::FMTResult> fatal(Format&& format, Args&&... args) {
            return log(LogSeverity::Fatal, format, std::forward<Args>(args)...);
        }

        /////---------- NO-FORMAT logger Severity ----------/////
        template <typename T>
        inline std::expected<void, fmt::FMTResult> trace(T&& t) {
            return log(LogSeverity::Trace, std::forward<T>(t));
        }
        template <typename T>
        inline std::expected<void, fmt::FMTResult> debug(T&& t) {
            return log(LogSeverity::Debug, std::forward<T>(t));
        }
        template <typename T>
        inline std::expected<void, fmt::FMTResult> info(T&& t) {
            return log(LogSeverity::Info, std::forward<T>(t));
        }
        template <typename T>
        inline std::expected<void, fmt::FMTResult> warn(T&& t) {
            return log(LogSeverity::Warn, std::forward<T>(t));
        }
        template <typename T>
        inline std::expected<void, fmt::FMTResult> error(T&& t) {
            return log(LogSeverity::Error, std::forward<T>(t));
        }
        template <typename T>
        inline std::expected<void, fmt::FMTResult> fatal(T&& t) {
            return log(LogSeverity::Fatal, std::forward<T>(t));
        }
    };
}  // namespace stream::flog::detail

namespace stream::fmt {
    template <typename FormatterExecutor>
    struct FormatterType<stream::flog::LogSeverity::Value, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::flog::LogSeverity::Value t, FormatterExecutor& executor) {
            executor.data.keep_new_style = true;
            switch (t) {
                case stream::flog::LogSeverity::Trace:
                    return FormatterType<detail::TextProperties::TextColor::BasicColorFG, FormatterExecutor>::format(detail::TextProperties::TextColor::BasicColorFG::BrightBlack,
                                                                                                                     executor);
                case stream::flog::LogSeverity::Debug:
                    return FormatterType<detail::TextProperties::TextColor::BasicColorFG, FormatterExecutor>::format(detail::TextProperties::TextColor::BasicColorFG::Blue,
                                                                                                                     executor);
                case stream::flog::LogSeverity::Info:
                    return FormatterType<detail::TextProperties::TextColor::BasicColorFG, FormatterExecutor>::format(detail::TextProperties::TextColor::BasicColorFG::Green,
                                                                                                                     executor);
                case stream::flog::LogSeverity::Warn:
                    return FormatterType<detail::TextProperties::TextColor::BasicColorFG, FormatterExecutor>::format(detail::TextProperties::TextColor::BasicColorFG::Yellow,
                                                                                                                     executor);
                case stream::flog::LogSeverity::Error:
                    return FormatterType<detail::TextProperties::TextColor::BasicColorFG, FormatterExecutor>::format(detail::TextProperties::TextColor::BasicColorFG::Red,
                                                                                                                     executor);
                case stream::flog::LogSeverity::Fatal:
                    return FormatterType<detail::TextProperties::TextColor::BasicColorFG, FormatterExecutor>::format(detail::TextProperties::TextColor::BasicColorFG::BrightMagenta,
                                                                                                                     executor);
            }
            return {};
        }
    };
}  // namespace stream::fmt

namespace stream::flog {
    using BasicLogger         = detail::XLogger<detail::BasicLoggerImpl<LogSeverity>>;
    using LoggerMultiSinkFast = detail::XLogger<detail::BasicLoggerMultiSinkFastImpl<LogSeverity, char>>;
    using LoggerMultiSinkSafe = detail::XLogger<detail::BasicLoggerMultiSinkSafeImpl<LogSeverity, char>>;

    extern template class detail::XLogger<detail::BasicLoggerImpl<LogSeverity>>;
    extern template class detail::XLogger<detail::BasicLoggerMultiSinkFastImpl<LogSeverity, char>>;
    extern template class detail::XLogger<detail::BasicLoggerMultiSinkSafeImpl<LogSeverity, char>>;
}  // namespace stream::flog

namespace stream::flog::Sinks {
    using ConsoleSink = BasicConsoleSink<LogSeverity, char>;
    using FileSink    = BasicFileSink<LogSeverity, char>;

    extern template class BasicConsoleSink<LogSeverity, char>;
    extern template class BasicFileSink<LogSeverity, char>;
}  // namespace stream::flog::Sinks
