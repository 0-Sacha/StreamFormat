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
        [[nodiscard]] std::expected<void, FMTResult> WriteInteger(T i, Detail::ShiftInfo shift = Detail::ShiftInfo{})
        {
            char oldAfter = shift.Print.After;
            if (shift.Print.After >= '0' && shift.Print.After <= '9')
                shift.Print.After = ' ';

            std::int32_t nbDigit = BufferWriteUtils::GetNumberOfDigitDec(i);

            shift.Size -= nbDigit;
            if (i < 0) --shift.Size;

            if (shift.Size <= 0)
                { return BufferWriteManip(Buffer).FastWriteInteger(i); }

            if (!shift.Print.BeforeIsADigit())
                { SF_TRY(BufferShiftWriteManip(Buffer).WriteShiftBegin(shift)); }
            if (i < 0)
            {
                SF_TRY(BufferOutManip(Buffer).Pushback('-'));
                i = -i;
            }
            if (shift.Print.BeforeIsADigit())
                { SF_TRY(BufferShiftWriteManip(Buffer).WriteShiftRightAll(shift)); }

            if (i == 0)
                { SF_TRY(BufferOutManip(Buffer).Pushback('0')); }
            else
            {
                SF_TRY(BufferOutManip(Buffer).Forward(nbDigit));
                std::int32_t nbDigit_ = nbDigit;
                while (nbDigit_ > 0)
                {
                    BufferOutManip(Buffer).ForceSetInverse(i % 10 + '0');
                    i /= 10;
                    nbDigit_--;
                }
                SF_TRY(BufferOutManip(Buffer).Forward(nbDigit));
            }

            SF_TRY(BufferShiftWriteManip(Buffer).WriteShiftEnd(shift));

            shift.Print.After = oldAfter;
            return {};
        }

    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> WriteFloat(T i, std::int32_t floatPrecision = 2, Detail::ShiftInfo shift = Detail::ShiftInfo{})
        {
            char oldBefore = shift.Print.Before;
            if (shift.Print.Before >= '0' && shift.Print.Before <= '9')
                shift.Print.Before = ' ';

            std::int32_t nbDigit = BufferWriteUtils::GetNumberOfDigitDec(std::trunc(i));

            shift.Size -= nbDigit + floatPrecision + 1;
            if (i < 0) --shift.Size;

            if (shift.Size <= 0)
                { return BufferWriteManip(Buffer).FastWriteFloat(i, floatPrecision); }

            if (!shift.Print.BeforeIsADigit())
                { SF_TRY(BufferShiftWriteManip(Buffer).WriteShiftBegin(shift)); }
            if (i < 0)
            {
                SF_TRY(BufferOutManip(Buffer).Pushback('-'));
                i = -i;
            }
            if (shift.Print.BeforeIsADigit())
                { SF_TRY(BufferShiftWriteManip(Buffer).WriteShiftRightAll(shift)); }

            T k = std::trunc(i);
            if (k == 0)
                { SF_TRY(BufferOutManip(Buffer).Pushback('0')); }
            else
            {
                SF_TRY(BufferOutManip(Buffer).Forward(nbDigit));
                std::int32_t nbDigit_ = nbDigit;
                while (nbDigit_ > 0)
                {
                    BufferOutManip(Buffer).ForceSetInverse(char(std::fmod(i, 10)) + '0');
                    k /= 10;
                    nbDigit_--;
                }
                SF_TRY(BufferOutManip(Buffer).Forward(nbDigit));
            }

            SF_TRY(BufferOutManip(Buffer).Pushback('.'));
            i -= k;
            while (floatPrecision-- != 0)
            {
                T decimal = std::trunc(i *= 10);
                SF_TRY(BufferOutManip(Buffer).Pushback((char)decimal + '0'));
                i -= decimal;
            }

            SF_TRY(BufferShiftWriteManip(Buffer).WriteShiftEnd(shift));

            shift.Print.Before = oldBefore;
            return {};
        }

    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> WriteIntegerH(T i, std::uint8_t digitSize, const TChar* const lut, TChar base_prefix = '\0', ShiftInfo shift = ShiftInfo{})
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
                SF_TRY(BufferOutManip(Buffer).Pushback('0'));
                SF_TRY(BufferOutManip(Buffer).Pushback(base_prefix));
            }

            SF_TRY(manip.Forward(digitCount));
            std::int32_t k = digitCount + 1;
            while (--k != 0)
            {
                manip.ForceSetInverse(lut[i & (0b1 << digitSize)]);
                i = i >> digitSize;
            }
            SF_TRY(manip.Forward(digitCount));
            return {};
        }

    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> WriteIntegerFormatData(T i, const FormatData<TChar>& formatData)
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
        [[nodiscard]] std::expected<void, FMTResult> WriteFloatFormatData(T i, const FormatData<TChar>& formatData)
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
        [[nodiscard]] inline std::expected<void, FMTResult> WriteIndentCharPtr(const CharStr* str, std::size_t size)
        {
            while (size > 0)
            {
                const CharStr* const begin = str;
                while (size > 0 && *str != '\n')
                {
                    ++str, --size;
                }
                const CharStr* const end = str;

                SF_TRY(BufferWriteManip(Buffer).FastWriteCharArray(begin, end - begin));

                if (size > 0 && *str == '\n')
                {
                    SF_TRY(FMTBufferOutManip(Buffer).NewLineIndent());
                    ++str;
                    --size;
                }
            }
            return {};
        }
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> WriteIndentCharBound(const CharStr* begin, const CharStr* end)
        {
            return WriteIndentCharPtr(begin, end - begin);
        }
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> WriteIndentString(std::basic_string_view<CharStr> str)
        {
            return WriteIndentCharPtr(str.data(), str.size());
        }

        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> WriteCharPtr(const CharStr* str, std::size_t size, ShiftInfo& shift)
        {
            if (shift.Size <= 0)
                return BufferWriteManip(Buffer).FastWriteCharArray(str, size);
            
            SF_TRY(BufferOutManip(Buffer).Reserve(std::max(static_cast<std::size_t>(shift.Size), size)));

            if (static_cast<std::size_t>(shift.Size) > size)
            {
                shift.Size -= static_cast<std::int32_t>(size);

                SF_TRY(BufferShiftWriteManip(Buffer).WriteShiftBegin(shift));

                SF_TRY(BufferWriteManip(Buffer).FastWriteCharArray(str, size));

                SF_TRY(BufferShiftWriteManip(Buffer).WriteShiftEnd(shift));
            }
            else
            {
                SF_TRY(BufferWriteManip(Buffer).FastWriteCharArray(str, size));
            }
            return {};
        }
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> WriteCharBound(const CharStr* begin, const CharStr* end, ShiftInfo& shift)
        {
            return WriteCharPtr(begin, end - begin, shift);
        }
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> WriteString(std::basic_string_view<CharStr> str, ShiftInfo& shift)
        {
            return WriteCharPtr(str.data(), str.size(), shift);
        }
    };
}
