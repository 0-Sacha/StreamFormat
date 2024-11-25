#pragma once

#include "StreamFormat/Core/Prelude.h"
#include "StreamFormat/FLog.h"

namespace StreamFormat::FMT::Detail
{
    struct FileLocation
    {
        FileLocation(std::string_view fileName, int fileLine = 0)
            : FileName(fileName)
            , FileLine(fileLine)
        {}

        std::string_view FileName;  // __FILE__
        int              FileLine;  // __LINE__
    };

    struct FunctionProperties
    {
        FunctionProperties(std::string_view fileName, int fileLine = 0, std::string_view functionName = "", std::string_view functionSignature = "",
                           std::string_view functionAssemblyName = "")
            : Location(fileName, fileLine)
            , FunctionName(functionName)
            , FunctionSignature(functionSignature)
            , FunctionAssemblyName(functionAssemblyName)
        {}

        FunctionProperties(FileLocation location, std::string_view functionName = "", std::string_view functionSignature = "", std::string_view functionAssemblyName = "")
            : Location(location)
            , FunctionName(functionName)
            , FunctionSignature(functionSignature)
            , FunctionAssemblyName(functionAssemblyName)
        {}

        FileLocation     Location;
        std::string_view FunctionName;          // __FUNCTION__
        std::string_view FunctionSignature;     // __FUNCSIG__ -- __PRETTY_FUNCTION__
        std::string_view FunctionAssemblyName;  // __FUNCDNAME__
    };
}

#define STREAMFORMAT_FMT_FILE_LOCATION()       StreamFormat::FMT::Detail::FileLocation(__FILE__, __LINE__)
#define STREAMFORMAT_FMT_FUNCTION_PROPERTIES() StreamFormat::FMT::Detail::FunctionProperties(STREAMFORMAT_FMT_FILE_LOCATION(), __FUNCTION__, __FUNCSIG__, __FUNCDNAME__)

namespace StreamFormat::FMT
{
    template <typename FormatterExecutor>
    struct FormatterType<Detail::FileLocation, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const Detail::FileLocation& t, FormatterExecutor& executor)
        {
            SF_TRY(executor.WriteType(t.FileName));
            SF_TRY(executor.BufferOut.Pushback(':'));
            return executor.WriteType(t.FileLine);
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<Detail::FunctionProperties, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const Detail::FunctionProperties& t, FormatterExecutor& executor)
        {
            SF_TRY(executor.WriteType(t.Location));
            SF_TRY(executor.BufferOut.WriteCharArray(" @ "));
            return executor.WriteType(t.FunctionName);
        }
    };
}
