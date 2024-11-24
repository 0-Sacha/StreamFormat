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
        [[nodiscard]] constexpr std::expected<void, FMTResult> FastReadInteger(T& t) noexcept
        {
            bool sign = false;
            if constexpr (std::is_signed_v<T>)
                { sign = BufferTestManip(Buffer).IsEqualToForward('-'); }

            if (!BufferTestAccess(Buffer).IsADigit())
                { return std::unexpected(FMTResult::Parse_NonValidDigit); }
            
            T value = static_cast<T>(0);
            while (BufferTestAccess(Buffer).IsADigit())
            {
                char c = SF_TRY(BufferManip(Buffer).GetAndForward());
                value = value * static_cast<T>(10) + static_cast<T>(c - static_cast<TChar>('0'));
            }

            t = sign ? -value : value;
            return {};
        }

    public:
        template <typename T>
        [[nodiscard]] constexpr inline std::expected<void, FMTResult> FastReadFloat(T& t, std::int32_t floatPrecision = -1) noexcept
        {
            T intpart = static_cast<T>(0);

            BufferTestAccess access(Buffer);
            BufferTestManip manip(Buffer);

            bool sign = SF_TRY(manip.IsEqualToForward('-'));

            if (access.IsADigit())
            {
                SF_TRY(FastReadInteger<T>(intpart));
            }
            else if (access.IsEqualTo('.') == false)
            {
                SF_TRY(manip.Forward());
                return std::unexpected(FMTResult::Parse_NonValidDigit);
            }

            if (floatPrecision < 0)
            {
                while (access.IsADigit() && BufferAccess(Buffer).IsEndOfString() == false)
                    { BufferManip(Buffer).ForceForward(); }
            }
            else
            {
                while (access.IsADigit() && floatPrecision > 0 && BufferAccess(Buffer).IsEndOfString() == false)
                {
                    BufferManip(Buffer).ForceForward();
                    floatPrecision--;
                }
            }
            BufferManip(Buffer).ForceBackward();

            T dec = static_cast<T>(0);
            while (access.IsADigit())
            {
                dec += static_cast<T>(BufferManip(Buffer).GetAndForceBackward() - '0');
                dec /= 10;
            }

            t = sign ? - intpart - dec : intpart + dec;
            return {};
        }

    public:
        template <typename CharPtr>
        [[nodiscard]] std::expected<void, FMTResult> FastReadCharPtr(const CharPtr* str, std::size_t sizeToCopy, bool isZeroEnded = true)
        {
            if (BufferAccess(Buffer).CanMoveForward(sizeToCopy) == false)
            {
                return BufferReadManip(Buffer).FastReadCharPtr(str, BufferAccess(Buffer).GetBufferRemainingSize(), isZeroEnded);
            }

            // TODO : Opti with bigger types
            while (sizeToCopy-- != 0)
                { *str++ = BufferManip(Buffer).GetAndForward(); }
            if (isZeroEnded) { *str = 0; }

            return {};
        }
        template <typename CharStr, std::size_t SIZE>
        [[nodiscard]] inline std::expected<void, FMTResult> FastReadCharArray(const CharStr (&str)[SIZE], bool isZeroEnded = true)
        {
            return FastReadCharPtr(str, SIZE);
        }
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> FastReadCharBound(const CharStr* begin, const CharStr* end, bool isZeroEnded = true)
        {
            return FastReadCharPtr(begin, end - begin - (isZeroEnded ? 1 : 0), isZeroEnded);
        }
    };
}
