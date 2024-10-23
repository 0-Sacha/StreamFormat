#pragma once

#include "BufferInfo.h"
#include "BufferManip.h"
#include "BufferTestManip.h"
#include "BufferOutManip.h"

#include <type_traits>
#include <cmath>

namespace StreamFormat::FMT::Detail
{
    class BufferWriteUtils
    {
    public:
        template <typename T>
        static std::int32_t GetNumberOfDigitDec(T value)
        {
            if constexpr (std::numeric_limits<T>::is_signed)
            {
                if (value < 0) value = -value;
            }
            std::int32_t nb = 0;
            while (true)
            {
                if (value < 10)
                    return nb + 1;
                else if (value < 100)
                    return nb + 2;
                else if (value < 1000)
                    return nb + 3;
                else if (value < 10000)
                    return nb + 4;
                else
                {
                    value /= static_cast<T>(10000);
                    nb += 4;
                }
            }
        }
    };

    template <typename TChar>
    class BufferWriteManip
    {
    public:
        constexpr inline BufferWriteManip(BufferOutInfo<TChar>& buffer) noexcept : Buffer(buffer) {}
    public:
        BufferOutInfo<TChar>& Buffer;
    
    public:
        static constexpr TChar BIN[2] = {'0', '1'};
        static constexpr TChar OCT[8] = {'0', '1', '2', '3', '4', '5', '6', '7'};
        static constexpr TChar UPPER_HEX[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
        static constexpr TChar LOWER_HEX[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    public:
        template <typename T>
        requires std::is_integral_v<T>
        constexpr void FastWriteInteger(T i)
        {
            BufferOutManip manip(Buffer);

            if (i == 0) { manip.Pushback('0'); return; }

            if constexpr (std::is_signed_v<T>)
            {
                if (i < 0) { manip.Pushback('-'); i = -i; }
            }

            std::int32_t nbDigit = BufferWriteUtils::GetNumberOfDigitDec(i);
            manip.Forward(nbDigit).ThrowIfFailed();
            while (i > 0)
            {
                if (BufferAccess(Buffer).IsOutOfBound())
                    BufferAccess(Buffer).IsOutOfBound();
                manip.ForceSetInverse(i % 10 + '0');
                i /= 10;
            }
            manip.Forward(nbDigit).ThrowIfFailed();
        }

    public:
        template <typename T>
        requires std::is_floating_point_v<T>
        void FastWriteFloat(T i, std::int32_t floatPrecision = 2)
        {
            BufferOutManip manip(Buffer);

            if (i == 0)
                { manip.Pushback('0'); return; }
            if (i < 0)
                { manip.Pushback('-'); i = -i; }

            T k = std::trunc(i);
            i = i - k;
            std::int32_t nbDigit = BufferWriteUtils::GetNumberOfDigitDec(k);
            manip.Forward(nbDigit);
            std::int32_t nbDigit_ = nbDigit;
            while (nbDigit_ > 0)
            {
                manip.ForceSetInverse(char(std::fmod(k, 10)) + '0');
                k /= 10;
                nbDigit_--;
            }
            manip.Forward(nbDigit);
            manip.Pushback('.');

            while (floatPrecision-- >= 0)
            {
                TChar intPart = static_cast<TChar>(std::trunc(i *= 10));
                manip.Pushback(intPart + '0');
                i -= intPart;
            }
        }

    public:
        template <typename CharInput>
        void FastWriteCharArray(const CharInput* str, std::size_t size)
        {
            if (BufferOutManip(Buffer).Reserve(size) == false) 
                return FastWriteCharArray(str, BufferAccess(Buffer).GetBufferRemainingSize());

            // TODO: Opti with bigger types
            while (size-- != 0 && *str != 0)
                BufferOutManip(Buffer).ForcePushback(*str++);
        }
        template <typename CharInput>
        inline void FastWriteString(std::basic_string_view<CharInput> sv)
        {
            FastWriteCharArray(sv.data(), sv.size());
        }
        inline void FastWriteString(std::basic_string_view<TChar> sv)
        {
            FastWriteCharArray(sv.data(), sv.size());
        }
        template <typename CharInput, std::size_t SIZE>
        inline void FastWriteStringLitteral(CharInput (&str)[SIZE])
        {
            std::size_t size = SIZE;
            while (str[size - 1] == 0) --size;
            FastWriteCharArray(str, size);
        }

    public:
        template <typename CharInput> inline void BasicWriteType(std::basic_string_view<CharInput> str) { FastWriteString(str); }
        template <typename CharInput, std::size_t SIZE> inline void BasicWriteType(CharInput (&str)[SIZE]) { FastWriteStringLitteral(str); }
        template <typename T> requires std::is_integral_v<T> void BasicWriteType(T t) { FastWriteInteger(t); }
        template <typename T> requires std::is_floating_point_v<T> void BasicWriteType(T t) { FastWriteFloat(t); }

        template <typename Type, typename... Rest>
        inline void BasicWriteType(Type&& type, Rest&&... rest)
        {
            BasicWriteType(type);
            if constexpr (sizeof...(rest) > 0)
                BasicWriteType(std::forward<Rest>(rest)...);
        }
    };
}
