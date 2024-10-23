#pragma once

#include "StreamFormat/FMT.h"

#include "StreamFormat/FMT/Buffer/BufferManip.h"
#include "StreamFormat/FMT/Buffer/BufferWriteManip.h"

namespace StreamFormat::FLog
{
    template <typename FormatStr>
    struct AddIndentInFormat
    {
        AddIndentInFormat(const FormatStr& format)
            : Format(format)
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

namespace StreamFormat::FMT
{
    template <typename FormatterExecutor, typename FormatStr>
    struct FormatterType<StreamFormat::FLog::AddIndentInFormat<FormatStr>, FormatterExecutor>
    {
        static void Format(const StreamFormat::FLog::AddIndentInFormat<FormatStr>& format, FormatterExecutor& executor)
        {
            Detail::BufferWriteManip(executor.BufferOut).FastWriteStringLitteral("{K:indent}");
            executor.WriteType(format.Format);
        }
    };

    template <typename FormatterExecutor, typename CharType>
    struct FormatterType<StreamFormat::FLog::ConcateNameAndSinkName<CharType>, FormatterExecutor>
    {
        static void Format(const StreamFormat::FLog::ConcateNameAndSinkName<CharType>& names, FormatterExecutor& executor)
        {
            executor.Run(names.LoggerName, FORMAT_SV("sink", names.SinkName));
        }
    };

    template <typename FormatterExecutor, typename CharType>
    struct FormatterType<StreamFormat::FLog::FuturConcateNameAndSinkName<CharType>, FormatterExecutor>
    {
        static void Format(const StreamFormat::FLog::FuturConcateNameAndSinkName<CharType>& names, FormatterExecutor& executor) { executor.Run(names.LoggerName, "sink"); }
    };
}
