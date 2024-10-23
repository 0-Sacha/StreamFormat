#pragma once

#include "StreamFormat/FMT/Detail/Detail.h"

namespace StreamFormat::FMT::Detail
{
    template <typename CharType>
    class BufferInfo
    {
    public:
        using TChar = CharType;

    public:
        TChar* Buffer;
        TChar* CurrentPos;
        TChar* BufferEnd;  // Not included

    public:
        constexpr inline TChar Get() const { return *CurrentPos; }
        template<template<typename> typename TManip> constexpr inline TManip<TChar> Manip() { return TManip<TChar>(Buffer); }

    public:
        BufferInfo() noexcept
            : Buffer(nullptr)
            , CurrentPos(nullptr)
            , BufferEnd(nullptr)
        {}

        BufferInfo(TChar* const buffer, const std::size_t size) noexcept
            : Buffer(buffer)
            , CurrentPos(buffer)
            , BufferEnd(buffer + size)
        {}
    };

    template <typename CharType>
    class BufferInfoView : public BufferInfo<const CharType>
    {
    public:
        using BufferInfo<const CharType>::TChar;
        
        using BufferInfo<const CharType>::Buffer;
        using BufferInfo<const CharType>::CurrentPos;
        using BufferInfo<const CharType>::BufferEnd;

        using BufferInfo<const CharType>::Get;
        using BufferInfo<const CharType>::Manip;

    public:
        BufferInfoView() noexcept
            : BufferInfo<const CharType>()
        {}

        template <size_t SIZE>
        BufferInfoView(const CharType (&data)[SIZE]) noexcept
            : BufferInfo<const CharType>(data, SIZE)
        {
            while (BufferEnd - 1 > Buffer && *(BufferEnd - 1) == 0) 
                --BufferEnd;
        }

        BufferInfoView(std::basic_string_view<CharType> sv) noexcept
            : BufferInfo<const CharType>(sv.data(), sv.size())
        {}

        BufferInfoView(const CharType* const buffer, const std::size_t size) noexcept
            : BufferInfo<const CharType>(buffer, size)
        {}

    public:
        operator BufferInfo<const CharType>() const { return BufferInfo<const CharType> {.Buffer = Buffer, .CurrentPos = CurrentPos, .BufferEnd = BufferEnd}; }
    };

    template <typename T>
    concept ConvertibleToBufferInfo = requires(T&& t)
    {
        BufferInfo(std::forward<T>(t));
    };

    template <typename T>
    concept ConvertibleToBufferInfoView = requires(T&& t)
    {
        BufferInfoView(std::forward<T>(t));
    };
}
