#pragma once

#include <utility>

namespace StreamFormat::FMT::Detail
{
    template <typename T>
    struct ForwardAsInt;
    template <typename T>
    struct ForwardAsUInt;
    template <typename T>
    struct ForwardAsFloat;
    template <typename CharType>
    struct ForwardAsChar
    {
    };
    template <typename CharType, std::size_t SIZE>
    struct ForwardAsCharArray
    {
    };
    template <typename CharType>
    struct ForwardAsCharPointer
    {
    };
}
