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
        
    public:
        BufferOutInfo(BasicBufferOutManager<CharType>& bufferOutManager) noexcept
            : BufferInfo<CharType>()
        {
            SetManager(bufferOutManager);
        }

    public:
        BasicBufferOutManager<CharType>* Manager;

    public:
        [[nodiscard]] std::expected<void, FMTResult> SetManager(BasicBufferOutManager<CharType>& bufferOutManager)
        {
            Manager = &bufferOutManager;
            Manager->BeginContext();
            BufferManip(*this).Set(Manager->GetBuffer(), Manager->GetBufferSize());
        }
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
        [[nodiscard]] void SetManager(BasicBufferOutManager<TChar>& bufferOutManager) noexcept
        {
            return Buffer.SetManager(bufferOutManager);
        }

        void ComputeGeneratedSize() noexcept { Buffer.Manager->ComputeGeneratedSize(BufferAccess(Buffer).GetBufferCurrentSize()); }

    public:
        [[nodiscard]] std::expected<void, FMTResult> AddSize(const std::size_t count) noexcept
        {
            if (Buffer.Manager == nullptr)
                return std::unexpected(FMTResult::NonValidBuffer);
            std::size_t currentSize = BufferAccess(Buffer).GetBufferCurrentSize();
            if (not Buffer.Manager->AddSize(count))
                return std::unexpected(FMTResult::Buffer_UnableToReserveMemory);
            BufferManip(Buffer).Set(Buffer.Manager->GetBuffer(), Buffer.Manager->GetBufferSize());
            Buffer.CurrentPos = Buffer.Manager->GetBuffer() + currentSize;
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
        [[nodiscard]] inline std::expected<void, FMTResult> AddSpaces(const auto count) noexcept { return Pushback(' ', count); }

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
