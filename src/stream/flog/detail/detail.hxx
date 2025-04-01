#pragma once

#include "stream/fmt.hxx"

#include "stream/fmt/buf/manip.hxx"
#include "stream/fmt/buf/write_manip.hxx"

namespace stream::flog {
    template <typename FormatStr>
    struct AddIndentInFormat {
        AddIndentInFormat(const FormatStr& format) : format(format) {}
        const FormatStr& format;
    };

    template <typename CharType>
    struct ConcatNameAndSinkName {
        ConcatNameAndSinkName(const std::basic_string<CharType>& logger_name, const std::basic_string<CharType>& sinkName) : LoggerName(logger_name), SinkName(sinkName) {}
        const std::basic_string<CharType>& LoggerName;
        const std::basic_string<CharType>& SinkName;
    };

    template <typename CharType>
    struct FutureConcatNameAndSinkName {
        FutureConcatNameAndSinkName(const std::basic_string<CharType>& logger_name) : LoggerName(logger_name) {}
        const std::basic_string<CharType>& LoggerName;
    };
}  // namespace stream::flog

namespace stream::fmt {
    template <typename FormatterExecutor, typename FormatStr>
    struct FormatterType<stream::flog::AddIndentInFormat<FormatStr>, FormatterExecutor> {
        static void format(const stream::flog::AddIndentInFormat<FormatStr>& format, FormatterExecutor& executor) {
            buf::WriteManip(executor.ostream).fast_write_literal("{K:indent}");
            return executor.write_type(format.format);
        }
    };

    template <typename FormatterExecutor, typename CharType>
    struct FormatterType<stream::flog::ConcatNameAndSinkName<CharType>, FormatterExecutor> {
        static void format(const stream::flog::ConcatNameAndSinkName<CharType>& names, FormatterExecutor& executor) {
            return executor.run(names.LoggerName, FORMAT_SV("sink", names.SinkName));
        }
    };

    template <typename FormatterExecutor, typename CharType>
    struct FormatterType<stream::flog::FutureConcatNameAndSinkName<CharType>, FormatterExecutor> {
        static void format(const stream::flog::FutureConcatNameAndSinkName<CharType>& names, FormatterExecutor& executor) {
            return executor.run(names.LoggerName, "sink");
        }
    };
}  // namespace stream::fmt
