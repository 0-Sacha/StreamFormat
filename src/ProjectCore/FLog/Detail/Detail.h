#pragma once

#include "ProjectCore/FMT.h"

namespace ProjectCore::FLog
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

namespace ProjectCore::FMT
{
    template <typename FormatterContext, typename FormatStr>
    struct FormatterType<ProjectCore::FLog::AddIndentInFormat<FormatStr>, FormatterContext>
    {
        static void Format(const ProjectCore::FLog::AddIndentInFormat<FormatStr>& format, FormatterContext& context)
        {
            context.BufferOut().FastWriteCharArray("{K:indent}");
            context.RunType(format.Format);
        }
    };

    template <typename FormatterContext, typename CharType>
    struct FormatterType<ProjectCore::FLog::ConcateNameAndSinkName<CharType>, FormatterContext>
    {
        static void Format(const ProjectCore::FLog::ConcateNameAndSinkName<CharType>& names, FormatterContext& context)
        {
            context.SubContext(names.LoggerName, FORMAT_SV("sink", names.SinkName));
        }
    };

    template <typename FormatterContext, typename CharType>
    struct FormatterType<ProjectCore::FLog::FuturConcateNameAndSinkName<CharType>, FormatterContext>
    {
        static void Format(const ProjectCore::FLog::FuturConcateNameAndSinkName<CharType>& names, FormatterContext& context)
        {
            context.SubContext(names.LoggerName, "sink");
        }
    };
}
