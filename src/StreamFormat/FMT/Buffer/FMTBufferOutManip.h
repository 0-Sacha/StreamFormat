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
        using typename BufferOutInfo<CharType>::TChar;

        using BufferOutInfo<CharType>::Buffer;
        using BufferOutInfo<CharType>::CurrentPos;
        using BufferOutInfo<CharType>::BufferEnd;

        using BufferOutInfo<CharType>::Get;
        using BufferOutInfo<CharType>::Manip;

        using BufferOutInfo<CharType>::Manager;
        
    protected:
        FMTBufferOutInfo(BasicBufferOutManager<CharType>& bufferOutManager) noexcept
            : BufferOutInfo<CharType>(bufferOutManager)
        {}

    public:
        [[nodiscard]] static std::expected<FMTBufferOutInfo<CharType>, FMTResult> Create(BasicBufferOutManager<CharType>& bufferOutManager)
        {
            FMTBufferOutInfo<CharType> res(bufferOutManager);
            SF_TRY(BufferOutInfo<CharType>::Init(res));
            return res;
        }

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
        constexpr inline void AddNoStride(const std::size_t noStride) noexcept { Buffer.NoStride += noStride; }

        constexpr inline void AddIndent(const std::size_t indent) noexcept { Buffer.Indent += indent; }
        constexpr inline void RemoveIndent(const std::size_t indent) noexcept { Buffer.Indent -= indent; }
        constexpr inline void SetIndent() noexcept { Buffer.Indent = BufferManip(Buffer).GetBufferCurrentSize() - Buffer.NoStride; }
    
    public:
        [[nodiscard]] constexpr inline std::expected<void, FMTResult> NewLineIndent()
        {
            SF_TRY(BufferOutManip(Buffer).Pushback('\n'));
            return BufferOutManip(Buffer).Pushback(' ', Buffer.Indent);
        }

        [[nodiscard]] constexpr inline std::expected<void, FMTResult> PushbackCheckIndent(const TChar c)
        {
            SF_TRY(BufferOutManip(Buffer).Pushback(c));
            if (c == '\n')
                { return BufferOutManip(Buffer).Pushback(' ', Buffer.Indent); }
            return {};
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
        [[nodiscard]] inline std::expected<void, FMTResult> ParamGoToForward(const CharToTest... ele)
        {
            return BufferTestManip(Buffer).GoToForward(ele..., '}');
        }

        inline bool IsBeginOfParameter()
        {
            return BufferTestAccess(Buffer).IsEqualTo('{');
        }
        inline bool IsEndOfParameter()
        {
            return BufferTestAccess(Buffer).IsEqualTo('}');
        }

    public:
        template <typename CharToTest>
        [[nodiscard]] std::expected<bool, FMTResult> NextIsNamedArgs(const std::basic_string_view<CharToTest>& sv)
        {
            BufferTestAccess access(Buffer);
            BufferTestManip manip(Buffer);

            TChar* const oldpos = Buffer.CurrentPos;
            auto isSame = SF_TRY(manip.IsSameForward(sv));
            if (isSame && (access.IsEqualTo(':') || access.IsEqualTo('}')))
            {
                return true;
            }
            Buffer.CurrentPos = oldpos;
            return false;
        }
    };
}
