#pragma once

#include "StreamFormat/FMT/Buffer/BufferInfo.h"
#include "StreamFormat/FMT/Buffer/BufferManip.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class BufferReadManip
    {
    public:
        constexpr inline BufferReadManip(BufferInfo<TChar>& buffer) noexcept : Buffer(buffer) {}
    public:
        BufferInfo<TChar>& Buffer;
    
    public:
        template <typename T>
        constexpr BufferManipResult FastReadInteger(T& i) noexcept
        {
            T res = 0;

            bool sign = false;
            if constexpr (std::is_signed_v<T>)
            {
                sign = BufferTestManip(Buffer).IsEqualToForward('-');
                if (!BufferTestAccess(Buffer).IsADigit()) return false;
            }

            while (BufferTestAccess(Buffer).IsADigit())
                res = res * static_cast<T>(10) + static_cast<T>(BufferManip(Buffer).ThrowIfFailed().GetAndForward() - static_cast<TChar>('0'));

            i = sign ? -res : res;
            return true;
        }

    public:
        template <typename T>
        constexpr inline BufferManipResult FastReadFloat(T& i, std::int32_t floatPrecision = -1) noexcept
        {
            BufferTestAccess access(Buffer);
            BufferTestManip manip(Buffer);

            bool sign = manip.IsEqualToForward('-');

            bool hasIntPart = false;
            if (access.IsNotEqualTo('.'))
            {
                hasIntPart = access.IsADigit();
                if (hasIntPart == false) return false;
                T res = 0;
                while (access.IsADigit())
                    res = res * static_cast<T>(10) + static_cast<T>(BufferManipException(Buffer).GetAndForward() - static_cast<TChar>('0'));
                i = sign ? -res : res;
            }

            if (manip.IsEqualToForward('.') == false) return hasIntPart;

            if (floatPrecision < 0)
                while (access.IsADigit() && BufferAccess(Buffer).IsEndOfString() == false)
                    BufferManip(Buffer).ForceForward();
            else
            {
                while (access.IsADigit() && floatPrecision > 0 && BufferAccess(Buffer).IsEndOfString() == false)
                {
                    BufferManip(Buffer).ForceForward();
                    floatPrecision--;
                }
            }
            BufferManip(Buffer).ForceBackward();

            T dec = (T)0;
            while (access.IsADigit())
            {
                dec += static_cast<T>(BufferManip(Buffer).GetAndForceBackward() - '0');
                dec /= 10;
            }
            i += dec;
            return true;
        }

    public:
        template <typename CharPtr>
        BufferManipResult FastReadCharPtr(const CharPtr* str, std::size_t sizeToCopy, bool isZeroEnded = true)
        {
            if (BufferAccess(Buffer).CanMoveForward(sizeToCopy) == false)
                return BufferReadManip(Buffer).FastReadCharPtr(str, BufferAccess(Buffer).GetBufferRemainingSize(), isZeroEnded);

            // TODO : Opti with bigger types
            while (sizeToCopy-- != 0)
                *str++ = BufferManip(Buffer).GetAndForward();
            if (isZeroEnded) *str = 0;

            return true;
        }
        template <typename CharStr, std::size_t SIZE>
        inline BufferManipResult FastReadCharArray(const CharStr (&str)[SIZE], bool isZeroEnded = true)
        {
            return FastReadCharPtr(str, SIZE);
        }
        template <typename CharStr>
        inline BufferManipResult FastReadCharBound(const CharStr* begin, const CharStr* end, bool isZeroEnded = true)
        {
            return FastReadCharPtr(begin, end - begin - (isZeroEnded ? 1 : 0), isZeroEnded);
        }
    };
}
