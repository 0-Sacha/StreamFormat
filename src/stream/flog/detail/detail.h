#pragma once

#include "stream/fmt.h"

#include "stream/fmt/buffer/buffer_manip.h"
#include "stream/fmt/buffer/buffer_write_manip.h"

namespace stream::flog
{
    template <typename FormatStr>
    struct AddIndentInFormat
    {
        AddIndentInFormat(const FormatStr& format)
            : format(format)
        {}
        const FormatStr& Format;
    };

    template <typename CharType>
    struct ConcateNameAndSinkName
    {
        ConcateNameAndSinkName(const std::basic_string<CharType>& loggerName, const std::basic_string<CharType>& sinkName)
            : LoggerName(loggerName)
            , SinkName(sinkName)
        {}
        const std::basic_string<CharType>& LoggerName;
        const std::basic_string<CharType>& SinkName;
    };

    template <typename CharType>
    struct FuturConcateNameAndSinkName
    {
        FuturConcateNameAndSinkName(const std::basic_string<CharType>& loggerName)
            : LoggerName(loggerName)
        {}
        const std::basic_string<CharType>& LoggerName;
    };
}

namespace stream::fmt
{
    template <typename FormatterExecutor, typename FormatStr>
    struct FormatterType<stream::flog::AddIndentInFormat<FormatStr>, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::flog::AddIndentInFormat<FormatStr>& format, FormatterExecutor& executor)
        {
            SF_TRY(detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("{K:indent}"));
            return executor.WriteType(format.Format);
        }
    };

    template <typename FormatterExecutor, typename CharType>
    struct FormatterType<stream::flog::ConcateNameAndSinkName<CharType>, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::flog::ConcateNameAndSinkName<CharType>& names, FormatterExecutor& executor)
        {
            return executor.Run(names.LoggerName, FORMAT_SV("sink", names.SinkName));
        }
    };

    template <typename FormatterExecutor, typename CharType>
    struct FormatterType<stream::flog::FuturConcateNameAndSinkName<CharType>, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::flog::FuturConcateNameAndSinkName<CharType>& names, FormatterExecutor& executor)
        {
            return executor.Run(names.LoggerName, "sink");
        }
    };
}
