#pragma once

#include "BufferInfo.h"
#include "BufferOutManip.h"
#include "BufferTestManip.h"

namespace StreamFormat::FMT::Detail
{
    template <typename CharType>
    class FMTBufferOutInfo : public BufferOutInfo<CharType>
    {
    public:
        using BufferOutInfo<CharType>::TChar;

        using BufferOutInfo<CharType>::Buffer;
        using BufferOutInfo<CharType>::CurrentPos;
        using BufferOutInfo<CharType>::BufferEnd;

        using BufferOutInfo<CharType>::Get;
        using BufferOutInfo<CharType>::Manip;

        using BufferOutInfo<CharType>::Manager;
        
    public:
        FMTBufferOutInfo(BasicBufferOutManager<CharType>& bufferOutManager) noexcept
            : BufferOutInfo<CharType>(bufferOutManager)
        {}

    public:
        std::size_t NoStride = 0;
        std::size_t Indent = 0;
    };

    template <typename TChar>
    class FMTBufferOutManip
    {
    public:
        FMTBufferOutManip(FMTBufferOutInfo<TChar>& buffer) : Buffer(buffer) {}
    public:
        FMTBufferOutInfo<TChar>& Buffer;

    public:
        constexpr inline void        AddNoStride(const std::size_t noStride) noexcept { Buffer.NoStride += noStride; }

        constexpr inline void        AddIndent(const std::size_t indent) noexcept { Buffer.Indent += indent; }
        constexpr inline void        RemoveIndent(const std::size_t indent) noexcept { Buffer.Indent -= indent; }
        constexpr inline void        SetIndent() noexcept { Buffer.Indent = BufferManip(Buffer).GetBufferCurrentSize() - Buffer.NoStride; }
    
    public:
        constexpr inline void NewLineIndent()
        {
            BufferOutManip(Buffer).Pushback('\n');
            BufferOutManip(Buffer).Pushback(' ', Buffer.Indent);
        }

        constexpr inline void PushbackCheckIndent(const TChar c)
        {
            BufferOutManip(Buffer).Pushback(c);
            if (c == '\n') BufferOutManip(Buffer).Pushback(' ', Buffer.Indent);
        }
    };

    template <typename TChar>
    class FMTBufferParamsManip
    {
    public:
        FMTBufferParamsManip(BufferInfo<TChar>& buffer) : Buffer(buffer) {}
    public:
        BufferInfo<TChar>& Buffer;

    public:
        template <typename... CharToTest>
        inline void ParamGoTo(const CharToTest... ele)
        {
            BufferTestManip(Buffer).GoTo(ele..., '}');
        }
        template <typename... CharToTest>
        inline void ParamGoToForward(const CharToTest... ele)
        {
            BufferTestManip(Buffer).GoToForward(ele..., '}');
        }

        inline BufferManipResult IsBeginOfParameter()
        {
            return BufferTestAccess(Buffer).IsEqualTo('{');
        }
        inline BufferManipResult IsEndOfParameter()
        {
            return BufferTestAccess(Buffer).IsEqualTo('}');
        }

    public:
        template <typename CharToTest>
        bool NextIsNamedArgs(const std::basic_string_view<CharToTest>& sv)
        {
            BufferTestAccess access(Buffer);
            BufferTestManip manip(Buffer);

            TChar* const oldpos = Buffer.CurrentPos;
            if (manip.IsSameForward(sv) && (access.IsEqualTo(':') || access.IsEqualTo('}'))) return true;
            Buffer.CurrentPos = oldpos;
            return false;
        }
    };
}
