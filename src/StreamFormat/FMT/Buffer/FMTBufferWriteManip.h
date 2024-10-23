#pragma once

#include "BufferInfo.h"
#include "FMTBufferOutManip.h"
#include "Utils/BufferShiftManip.h"
#include "BufferOutManip.h"
#include "BufferWriteManip.h"

#include <type_traits>

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class FMTBufferWriteManip
    {
    public:
        FMTBufferWriteManip(FMTBufferOutInfo<TChar>& buffer) : Buffer(buffer) {}
    public:
        FMTBufferOutInfo<TChar>& Buffer;

    public:
        template <typename T>
        void WriteInteger(T i, Detail::ShiftInfo shift = Detail::ShiftInfo{})
        {
            shift.Print.ValidateForNumber();

            std::int32_t nbDigit = BufferWriteUtils::GetNumberOfDigitDec(i);

            shift.Size -= nbDigit;
            if (i < 0) --shift.Size;

            if (shift.Size <= 0) return BufferWriteManip(Buffer).FastWriteInteger(i);

            if (!shift.Print.BeforeIsADigit()) BufferShiftWriteManip(Buffer).WriteShiftBegin(shift);
            if (i < 0)
            {
                BufferOutManip(Buffer).Pushback('-');
                i = -i;
            }
            if (shift.Print.BeforeIsADigit()) BufferShiftWriteManip(Buffer).WriteShiftRightAll(shift);

            if (i == 0)
                BufferOutManip(Buffer).Pushback('0');
            else
            {
                BufferOutManip(Buffer).Forward(nbDigit);
                std::int32_t nbDigit_ = nbDigit;
                while (nbDigit_ > 0)
                {
                    BufferOutManip(Buffer).ForceSetInverse(i % 10 + '0');
                    i /= 10;
                    nbDigit_--;
                }
                BufferOutManip(Buffer).Forward(nbDigit);
            }

            BufferShiftWriteManip(Buffer).WriteShiftEnd(shift);
        }

    public:
        template <typename T>
        void WriteFloat(T i, std::int32_t floatPrecision = 2, Detail::ShiftInfo shift = Detail::ShiftInfo{})
        {
            shift.Print.ValidateForNumber();

            std::int32_t nbDigit = BufferWriteUtils::GetNumberOfDigitDec(std::trunc(i));

            shift.Size -= nbDigit + floatPrecision + 1;
            if (i < 0) --shift.Size;

            if (shift.Size <= 0) return BufferWriteManip(Buffer).FastWriteFloat(i, floatPrecision);

            if (!shift.Print.BeforeIsADigit()) BufferShiftWriteManip(Buffer).WriteShiftBegin(shift);
            if (i < 0)
            {
                BufferOutManip(Buffer).Pushback('-');
                i = -i;
            }
            if (shift.Print.BeforeIsADigit()) BufferShiftWriteManip(Buffer).WriteShiftRightAll(shift);

            T k = std::trunc(i);
            if (k == 0)
                BufferOutManip(Buffer).Pushback('0');
            else
            {
                BufferOutManip(Buffer).Forward(nbDigit);
                std::int32_t nbDigit_ = nbDigit;
                while (nbDigit_ > 0)
                {
                    BufferOutManip(Buffer).ForceSetInverse(char(std::fmod(i, 10)) + '0');
                    k /= 10;
                    nbDigit_--;
                }
                BufferOutManip(Buffer).Forward(nbDigit);
            }

            BufferOutManip(Buffer).Pushback('.');
            i -= k;
            while (floatPrecision-- != 0)
            {
                T decimal = std::trunc(i *= 10);
                BufferOutManip(Buffer).Pushback((char)decimal + '0');
                i -= decimal;
            }

            BufferShiftWriteManip(Buffer).WriteShiftEnd(shift);
        }

    public:
        template <typename T>
        void WriteIntegerH(T i, std::uint8_t digitSize, const TChar* const lut, TChar base_prefix = '\0', ShiftInfo shift = ShiftInfo{})
        {
            BufferOutManip manip(Buffer);

            std::int32_t digitCount = sizeof(T) * 8;
            {
                // Remove leading 0
                std::int32_t lastPosWithData = 0;
                std::int32_t k               = digitCount + 1;
                T            cpyI            = i;
                while (--k != 0)
                {
                    if ((cpyI & (0b1 << digitSize)) != 0) lastPosWithData = k;
                    cpyI = cpyI >> digitSize;
                }
                digitCount -= lastPosWithData;
            }

            if (base_prefix != '\0')
            {
                BufferOutManip(Buffer).Pushback('0');
                BufferOutManip(Buffer).Pushback(base_prefix);
            }

            manip.Forward(digitCount);
            std::int32_t k = digitCount + 1;
            while (--k != 0)
            {
                manip.ForceSetInverse(lut[i & (0b1 << digitSize)]);
                i = i >> digitSize;
            }
            manip.Forward(digitCount);
        }

    public:
        template <typename T>
        void WriteIntegerFormatData(T i, const FormatData<TChar>& formatData)
        {
            if (formatData.HasSpec)
            {
                switch (formatData.IntegerPrint)
                {
                    case IntegerPrintBase::Dec:
                        if (formatData.Shift.Type == ShiftInfo::ShiftType::Nothing)
                            return BufferWriteManip(Buffer).FastWriteInteger(i);
                        else
                            return WriteInteger(i, formatData.Shift);
                    case IntegerPrintBase::Bin:
                    case IntegerPrintBase::BinUpper:
                        return WriteIntegerH(i, 1, BufferWriteManip<TChar>::BIN, formatData.PrefixSuffix ? (char)formatData.IntegerPrint : '\0', formatData.Shift);
                    case IntegerPrintBase::Oct:
                    case IntegerPrintBase::OctUpper:
                        return WriteIntegerH(i, 3, BufferWriteManip<TChar>::OCT, formatData.PrefixSuffix ? (char)formatData.IntegerPrint : '\0', formatData.Shift);
                    case IntegerPrintBase::Hex:
                        return WriteIntegerH(i, 4, BufferWriteManip<TChar>::LOWER_HEX, formatData.PrefixSuffix ? (char)formatData.IntegerPrint : '\0', formatData.Shift);
                    case IntegerPrintBase::HexUpper:
                        return WriteIntegerH(i, 4, BufferWriteManip<TChar>::UPPER_HEX, formatData.PrefixSuffix ? (char)formatData.IntegerPrint : '\0', formatData.Shift);
                    
                }
            }
            return BufferWriteManip(Buffer).FastWriteInteger(i);
        }
        template <typename T>
        void WriteFloatFormatData(T i, const FormatData<TChar>& formatData)
        {
            if (formatData.HasSpec)
            {
                if (formatData.Shift.Type != ShiftInfo::ShiftType::Nothing)
                    return WriteFloat(i, formatData.FloatPrecision, formatData.Shift);
            }

            return BufferWriteManip(Buffer).FastWriteFloat(i, formatData.FloatPrecision);
        }

    public:
        template <typename CharStr>
        inline void WriteIndentCharPtr(const CharStr* str, std::size_t size)
        {
            while (size > 0)
            {
                const CharStr* const begin = str;
                while (size > 0 && *str != '\n')
                {
                    ++str, --size;
                }
                const CharStr* const end = str;

                BufferWriteManip(Buffer).FastWriteCharArray(begin, end - begin);

                if (size > 0 && *str == '\n')
                {
                    FMTBufferOutManip(Buffer).NewLineIndent();
                    ++str;
                    --size;
                }
            }
        }
        template <typename CharStr>
        inline void WriteIndentCharBound(const CharStr* begin, const CharStr* end)
        {
            WriteIndentCharPtr(begin, end - begin);
        }
        template <typename CharStr>
        inline void WriteIndentString(std::basic_string_view<CharStr> str)
        {
            WriteIndentCharPtr(str.data(), str.size());
        }

        template <typename CharStr>
        inline void WriteCharPtr(const CharStr* str, std::size_t size, ShiftInfo& shift)
        {
            if (shift.Size <= 0)
                return BufferWriteManip(Buffer).FastWriteCharArray(str, size);
            
            BufferOutManip(Buffer).Reserve(std::max(static_cast<std::size_t>(shift.Size), size)).ThrowIfFailed();

            if (static_cast<std::size_t>(shift.Size) > size)
            {
                shift.Size -= static_cast<std::int32_t>(size);

                BufferShiftWriteManip(Buffer).WriteShiftBegin(shift);

                BufferWriteManip(Buffer).FastWriteCharArray(str, size);

                BufferShiftWriteManip(Buffer).WriteShiftEnd(shift);
            }
            else
            {
                BufferWriteManip(Buffer).FastWriteCharArray(str, size);
            }
        }
        template <typename CharStr>
        inline void WriteCharBound(const CharStr* begin, const CharStr* end, ShiftInfo& shift)
        {
            WriteCharPtr(begin, end - begin, shift);
        }
        template <typename CharStr>
        inline void WriteString(std::basic_string_view<CharStr> str, ShiftInfo& shift)
        {
            WriteCharPtr(str.data(), str.size(), shift);
        }
    };
}
