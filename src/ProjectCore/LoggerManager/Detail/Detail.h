#pragma once

#include "ProjectCore/FMT/FMT.h"

namespace ProjectCore::LoggerManager
{
    template<typename FormatStr>
    struct AddIndentInFormat
    {
        AddIndentInFormat(const FormatStr& format)
            : Format(format)
        {}
        const FormatStr& Format;
    };

    template<typename CharType>
    struct ConcateNameAndSinkName
    {
        ConcateNameAndSinkName(const std::basic_string<CharType>& loggerName, const std::basic_string<CharType>& sinkName)
            : LoggerName(loggerName)
            , SinkName(sinkName)
        {}
        const std::basic_string<CharType>& LoggerName;
        const std::basic_string<CharType>& SinkName;
    };
}

namespace ProjectCore::FMT
{
    template<typename FormatterContext, typename FormatStr>
    struct FormatterType<ProjectCore::LoggerManager::AddIndentInFormat<FormatStr>, FormatterContext>
    {
        static void Format(const ProjectCore::LoggerManager::AddIndentInFormat<FormatStr>& format, FormatterContext& context) {
            context.BufferOut().FastWriteCharArray("{K:indent}");
            context.RunType(format.Format);
        }
    };

    template<typename FormatterContext, typename CharType>
    struct FormatterType<ProjectCore::LoggerManager::ConcateNameAndSinkName<CharType>, FormatterContext>
    {
        static void Format(const ProjectCore::LoggerManager::ConcateNameAndSinkName<CharType>& names, FormatterContext& context) {
            context.SubContext(names.LoggerName, FORMAT_SV("sink", names.SinkName));
        }
    };
}
