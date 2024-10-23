#pragma once

#include "BufferInfo.h"
#include "StreamFormat/FMT/Detail/Exception.h"

namespace StreamFormat::FMT::Detail
{
    class FMTBufferManipError : public FMTError
    {
    public:
        const char* what() const noexcept override { return "FMTBufferManipError"; }
    };

    struct BufferManipResult
    {
        bool Result = false;
        constexpr inline BufferManipResult(bool result) noexcept : Result(result) {}
        constexpr inline operator bool() const noexcept { return Result; }

        bool HasFailed() const noexcept { return !Result; }

        void ThrowIfFailed() const
        {
            if (Result == false)
                throw FMTBufferManipError{};
        }
    };

    template <typename TChar>
    class BufferManipException;

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
        constexpr inline BufferManipResult CanMoveForward(const std::size_t count = 1) const noexcept { return Buffer.CurrentPos + count <= Buffer.BufferEnd; }
        constexpr inline BufferManipResult CanMoveBackward(const std::size_t count = 1) const noexcept { return Buffer.CurrentPos - count >= Buffer.Buffer; }

        constexpr inline BufferManipResult IsOutOfBound() const noexcept { return Buffer.CurrentPos < Buffer.Buffer || Buffer.CurrentPos >= Buffer.BufferEnd; }
        constexpr inline BufferManipResult IsEmpty() const noexcept { return Buffer.CurrentPos >= Buffer.BufferEnd; }
        constexpr inline BufferManipResult IsEndOfString() const noexcept { return IsEmpty() || Buffer.Get() == 0; }

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
        BufferManipException<TChar> ThrowIfFailed() { return BufferManipException<TChar>(Buffer); }
    
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
        constexpr inline BufferManipResult Forward(const std::size_t count = 1) noexcept
        {
            if (!Access().CanMoveForward(count)) return false;
            Buffer.CurrentPos += count;
            return true;
        }

        constexpr inline void ForceBackward(const std::size_t count = 1) noexcept { Buffer.CurrentPos -= count; }
        constexpr inline BufferManipResult Backward(const std::size_t count = 1) noexcept
        {
            if (!Access().CanMoveBackward(count)) return false;
            Buffer.CurrentPos -= count;
            return true;
        }

        constexpr inline TChar GetAndForceForward() noexcept { return *Buffer.CurrentPos++; }
        constexpr inline TChar GetAndForceBackward() noexcept { return *Buffer.CurrentPos--; }
    };

    template <typename TChar>
    class BufferManipException
    {
    public:
        BufferManipException(BufferInfo<TChar>& buffer) : Buffer(buffer) {}
    public:
        BufferInfo<TChar>& Buffer;

    public:
        inline void Forward(const std::size_t count = 1)
        {
            BufferAccess(Buffer).Forward(count).ThrowIfFailed();
        }
        inline void Backward(const std::size_t count = 1)
        {
            BufferAccess(Buffer).Backward(count).ThrowIfFailed();
        }

        inline TChar GetAndForward()
        {
            BufferAccess(Buffer).CanMoveForward(1).ThrowIfFailed();
            return *Buffer.CurrentPos++;
        }
        inline TChar GetAndBackward()
        {
            BufferAccess(Buffer).CanMoveBackward(1).ThrowIfFailed();
            return *Buffer.CurrentPos--;
        }
        inline TChar GetNext(const std::size_t count = 1) const
        {
            BufferAccess(Buffer).CanMoveForward(count).ThrowIfFailed();
            return BufferManip(Buffer).GetNextForce(count);
        }
        inline TChar GetPrev(const std::size_t count = 1) const
        {
            BufferAccess(Buffer).CanMoveBackward(count).ThrowIfFailed();
            return BufferManip(Buffer).GetPrevForce(count);
        }
    };
}
