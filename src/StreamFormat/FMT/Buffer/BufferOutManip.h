#pragma once

#include "BufferInfo.h"
#include "BufferManip.h"

#include "BufferOutManager/BasicBufferOutManager.h"

namespace StreamFormat::FMT::Detail
{
    template <typename CharType>
    class BufferOutInfo : public BufferInfo<CharType>
    {
    public:
        using typename BufferInfo<CharType>::TChar;

        using BufferInfo<CharType>::Buffer;
        using BufferInfo<CharType>::CurrentPos;
        using BufferInfo<CharType>::BufferEnd;

        using BufferInfo<CharType>::Get;
        using BufferInfo<CharType>::Manip;
        
    protected:
        BufferOutInfo(BasicBufferOutManager<CharType>& bufferOutManager) noexcept
            : BufferInfo<CharType>()
            , Manager(bufferOutManager)
        {}

    protected:
        [[nodiscard]] static std::expected<void, FMTResult> Init(BufferOutInfo<CharType>& in)
        {
            SF_TRY(in.Manager.BeginContext());
            BufferManip(in).Set(in.Manager.GetBuffer(), in.Manager.GetBufferSize());
            return {};
        }

    public:
        [[nodiscard]] static std::expected<BufferOutInfo<CharType>, FMTResult> Create(BasicBufferOutManager<CharType>& bufferOutManager)
        {
            BufferOutInfo<CharType> res(bufferOutManager);
            SF_TRY(Init(res));
            return res;
        }

    public:
        BasicBufferOutManager<CharType>& Manager;
    };

    template <typename T>
    concept ConvertibleToBufferOutInfo = requires(T&& t)
    {
        BufferOutInfo(std::forward<T>(t));
    };

    template <typename TChar>
    class BufferOutManip
    {
    public:
        constexpr inline BufferOutManip(BufferOutInfo<TChar>& buffer) noexcept : Buffer(buffer) {}
    public:
        BufferOutInfo<TChar>& Buffer;

    public:
        void ComputeGeneratedSize() noexcept { Buffer.Manager.ComputeGeneratedSize(BufferAccess(Buffer).GetBufferCurrentSize()); }

    public:
        [[nodiscard]] std::expected<void, FMTResult> AddSize(const std::size_t count) noexcept
        {
            std::size_t currentSize = BufferAccess(Buffer).GetBufferCurrentSize();
            SF_TRY(Buffer.Manager.AddSize(count))
            BufferManip(Buffer).Set(Buffer.Manager.GetBuffer(), Buffer.Manager.GetBufferSize());
            Buffer.CurrentPos = Buffer.Manager.GetBuffer() + currentSize;
            return {};
        }

        [[nodiscard]] inline std::expected<void, FMTResult> Reserve(const std::size_t count = 1) noexcept
        {
            if (Buffer.CurrentPos + count <= Buffer.BufferEnd)
                return {};
            return AddSize(static_cast<std::size_t>(count));
        }

        [[nodiscard]] inline std::expected<void, FMTResult> Forward(const std::size_t count = 1) noexcept
        {
            SF_TRY(Reserve(count));
            Buffer.CurrentPos += count;
            return {};
        }

    public:
        inline void SetChar(const TChar c) noexcept { *Buffer.CurrentPos = c; }
        [[nodiscard]] inline std::expected<void, FMTResult> Pushback(const TChar c) noexcept
        {
            SF_TRY(Reserve(1));
            *Buffer.CurrentPos++ = c;
            return {};
        }
        [[nodiscard]] inline std::expected<void, FMTResult> SetInverse(const TChar c) noexcept
        {
            SF_TRY(BufferAccess(Buffer).CanMoveBackward(1));
            *--Buffer.CurrentPos = c;
            return {};
        }
        inline void ForcePushback(const TChar c) noexcept { *Buffer.CurrentPos++ = c; }
        inline void ForceSetInverse(const TChar c) noexcept { *--Buffer.CurrentPos = c; }

    public:
        [[nodiscard]] inline std::expected<void, FMTResult> Pushback(const TChar c, auto count) noexcept
        {
            SF_TRY(Reserve(count))
            while (count-- > 0)
                ForcePushback(c);
            return {};
        }

    public:
        [[nodiscard]] inline std::expected<void, FMTResult> AddSpaces(const auto count) noexcept
        {
            return Pushback(' ', count);
        }

    private:
        template <typename... Rest>
        inline void PushbackSeqImpl(const TChar c, const Rest... rest) noexcept
        {
            ForcePushback(c);
            if constexpr (sizeof...(rest) > 0) PushbackSeqImpl(rest...);
        }

    public:
        template <typename... CharToPush>
        [[nodiscard]] inline std::expected<void, FMTResult> PushbackSeq(const CharToPush... ele) noexcept
        {
            SF_TRY(Reserve(sizeof...(ele)))
            PushbackSeqImpl(ele...);
            return {};
        }
    };
}
