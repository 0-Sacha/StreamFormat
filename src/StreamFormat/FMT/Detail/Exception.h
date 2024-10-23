#pragma once

#include "StreamFormat/Core/Core.h"

#include <exception>

// TODO: Better error msg
namespace StreamFormat::FMT::Detail
{
    class FMTException : public std::exception
    {
    };
    class FMTError : public FMTException
    {
    public:
        const char* what() const noexcept override { return "FMTError"; }
    };

    class FMTParseError : public FMTError
    {
    public:
        const char* what() const noexcept override { return "FMTParseError"; }
    };
    class FMTGivenTypeError : public FMTParseError
    {
    public:
        const char* what() const noexcept override { return "FMTGivenTypeError"; }
    };
    class FMTGivenIndexError : public FMTParseError
    {
    public:
        const char* what() const noexcept override { return "FMTGivenIndexError"; }
    };

    class FMTImplError : public FMTError
    {
    public:
        const char* what() const noexcept override { return "FMTImplError"; }
    };
    class FMTShouldNotEndHere : public FMTImplError
    {
    public:
        const char* what() const noexcept override { return "FMTShouldNotEndHere"; }
    };
    class FMTNotImplYet : public FMTImplError
    {
    public:
        const char* what() const noexcept override { return "FMTNotImplYet"; }
    };
}
