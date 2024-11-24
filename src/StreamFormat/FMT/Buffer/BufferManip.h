#pragma once

#include "BufferInfo.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class BufferAccess
    {
    public:
        constexpr inline BufferAccess(const BufferInfo<TChar>& buffer) noexcept : Buffer(buffer) {}
    public:
        const BufferInfo<TChar>& Buffer;
        
    public:
        constexpr inline std::size_t GetBufferTotalSize() const noexcept { return static_cast<std::size_t>(Buffer.BufferEnd - Buffer.Buffer); }
        constexpr inline std::size_t GetBufferCurrentSize() const noexcept { return static_cast<std::size_t>(Buffer.CurrentPos - Buffer.Buffer); }
        constexpr inline std::size_t GetBufferRemainingSize() const noexcept { return static_cast<std::size_t>(Buffer.BufferEnd - Buffer.CurrentPos); }

    public:
        constexpr inline bool CanMoveForward(const std::size_t count = 1) const noexcept { return Buffer.CurrentPos + count <= Buffer.BufferEnd; }
        constexpr inline bool CanMoveBackward(const std::size_t count = 1) const noexcept { return Buffer.CurrentPos - count >= Buffer.Buffer; }

        constexpr inline bool IsOutOfBound() const noexcept { return Buffer.CurrentPos < Buffer.Buffer || Buffer.CurrentPos >= Buffer.BufferEnd; }
        constexpr inline bool IsEmpty() const noexcept { return Buffer.CurrentPos >= Buffer.BufferEnd; }
        constexpr inline bool IsEndOfString() const noexcept { return IsEmpty() || Buffer.Get() == 0; }

        [[nodiscard]] constexpr inline std::expected<std::remove_cv_t<TChar>, FMTResult> GetNext(const std::size_t count = 1) const
        {
            if (BufferAccess(Buffer).CanMoveForward(count) == false)
                return std::unexpected(FMTResult::Buffer_OutOfBoundAccess);
            return BufferManip(Buffer).GetNextForce(count);
        }
        [[nodiscard]] constexpr inline std::expected<std::remove_cv_t<TChar>, FMTResult> GetPrev(const std::size_t count = 1) const
        {
            if (BufferAccess(Buffer).CanMoveBackward(count) == false)
                return std::unexpected(FMTResult::Buffer_OutOfBoundAccess);
            return BufferManip(Buffer).GetPrevForce(count);
        }

        constexpr inline TChar GetNextForce(const std::size_t count = 1) const noexcept { return *(Buffer.CurrentPos + count); }
        constexpr inline TChar GetPrevForce(const std::size_t count = 1) const noexcept { return *(Buffer.CurrentPos - count); }
    };

    template <typename TChar>
    class BufferManip
    {
    public:
        constexpr inline BufferManip(BufferInfo<TChar>& buffer) noexcept : Buffer(buffer) {}
    public:
        BufferInfo<TChar>& Buffer;
        
    public:
        constexpr inline void Set(TChar* const buffer, const std::size_t size) noexcept
        {
            Buffer.Buffer     = buffer;
            Buffer.CurrentPos = buffer;
            Buffer.BufferEnd  = buffer + size;
        }

        constexpr inline void Reload(BufferInfo<TChar>& buffer) noexcept
        {
            Buffer.Buffer     = buffer.Buffer;
            Buffer.CurrentPos = buffer.CurrentPos;
            Buffer.BufferEnd  = buffer.BufferEnd;
        }

        BufferAccess<TChar> Access() { return BufferAccess(Buffer); }

    public:
        constexpr inline void ForceForward(const std::size_t count = 1) noexcept { Buffer.CurrentPos += count; }
        [[nodiscard]] constexpr inline std::expected<void, FMTResult> Forward(const std::size_t count = 1) noexcept
        {
            if (!Access().CanMoveForward(count))
                return std::unexpected(FMTResult::Buffer_OutOfBoundAccess);
            Buffer.CurrentPos += count;
            return {};
        }

        constexpr inline void ForceBackward(const std::size_t count = 1) noexcept { Buffer.CurrentPos -= count; }
        [[nodiscard]] constexpr inline std::expected<void, FMTResult> Backward(const std::size_t count = 1) noexcept
        {
            if (!Access().CanMoveBackward(count))
                return std::unexpected(FMTResult::Buffer_OutOfBoundAccess);
            Buffer.CurrentPos -= count;
            return {};
        }

        [[nodiscard]] constexpr inline std::expected<std::remove_cv_t<TChar>, FMTResult> GetAndForward()
        {
            if (BufferAccess(Buffer).CanMoveForward(1) == false)
                return std::unexpected(FMTResult::Buffer_OutOfBoundAccess);
            return *Buffer.CurrentPos++;
        }
        [[nodiscard]] constexpr inline std::expected<std::remove_cv_t<TChar>, FMTResult> GetAndBackward()
        {
            if (BufferAccess(Buffer).CanMoveBackward(1) == false)
                return std::unexpected(FMTResult::Buffer_OutOfBoundAccess);
            return *Buffer.CurrentPos--;
        }

        constexpr inline TChar GetAndForceForward() noexcept { return *Buffer.CurrentPos++; }
        constexpr inline TChar GetAndForceBackward() noexcept { return *Buffer.CurrentPos--; }
    };
}
