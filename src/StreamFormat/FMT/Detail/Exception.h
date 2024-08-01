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

    class FMTBufferError : public FMTError
    {
    public:
        const char* what() const noexcept override { return "FMTBufferError"; }
    };
    class FMTBufferFull : public FMTBufferError
    {
    public:
        const char* what() const noexcept override { return "FMTBufferFull"; }
    };
    class FMTBufferLock : public FMTBufferError
    {
    public:
        const char* what() const noexcept override { return "FMTBufferLock"; }
    };
    class FMTBufferEnd : public FMTBufferError
    {
    public:
        const char* what() const noexcept override { return "FMTBufferEnd"; }
    };

    class FMTIndexError : public FMTError
    {
    public:
        const char* what() const noexcept override { return "FMTIndexError"; }
    };
    class FMTBufferWrongIndex : public FMTIndexError
    {
    public:
        const char* what() const noexcept override { return "FMTBufferWrongIndex"; }
    };
    class FMTBufferIndexOutOfRange : public FMTIndexError
    {
    public:
        const char* what() const noexcept override { return "FMTBufferIndexOutOfRange"; }
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
