#pragma once

#include "ProjectCore/Core/Core.h"
#include "ProjectCore/FLog.h"

namespace ProjectCore::FMT::Detail
{
    struct FileLocation
    {
        FileLocation(std::string_view fileName,
                     int fileLine = 0)
            : FileName(fileName)
            , FileLine(fileLine)
        {}

        std::string_view FileName;  // __FILE__
        int FileLine;               // __LINE__
    };

    struct FunctionProperties
    {
        FunctionProperties(std::string_view fileName,
                           int fileLine = 0,
                           std::string_view functionName = "",
                           std::string_view functionSignature = "",
                           std::string_view functionAssemblyName = "")
            : Location(fileName, fileLine)
            , FunctionName(functionName)
            , FunctionSignature(functionSignature)
            , FunctionAssemblyName(functionAssemblyName)
        {}

        FunctionProperties(FileLocation location,
                           std::string_view functionName = "",
                           std::string_view functionSignature = "",
                           std::string_view functionAssemblyName = "")
            : Location(location)
            , FunctionName(functionName)
            , FunctionSignature(functionSignature)
            , FunctionAssemblyName(functionAssemblyName)
        {}

        FileLocation        Location;
        std::string_view    FunctionName;          // __FUNCTION__
        std::string_view    FunctionSignature;     // __FUNCSIG__ -- __PRETTY_FUNCTION__
        std::string_view    FunctionAssemblyName;  // __FUNCDNAME__
    };
}

#define PROJECTCORE_FMT_FILE_LOCATION()         ProjectCore::FMT::Detail::FileLocation(__FILE__, __LINE__)
#define PROJECTCORE_FMT_FUNCTION_PROPERTIES()   ProjectCore::FMT::Detail::FunctionProperties(PROJECTCORE_FMT_FILE_LOCATION(), __FUNCTION__, __FUNCSIG__, __FUNCDNAME__)

namespace ProjectCore::FMT
{
    template <typename FormatterContext>
    struct FormatterType<Detail::FileLocation, FormatterContext>
    {
        static void Format(const Detail::FileLocation& t, FormatterContext& context)
        {
            context.RunType(t.FileName);
            context.BufferOut().PushBack(':');
            context.RunType(t.FileLine);
        }
    };

    template <typename FormatterContext>
    struct FormatterType<Detail::FunctionProperties, FormatterContext>
    {
        static void Format(const Detail::FunctionProperties& t, FormatterContext& context)
        {
            context.RunType(t.Location);
            context.BufferOut().WriteCharArray(" @ ");
            context.RunType(t.FunctionName);
        }
    };
}
