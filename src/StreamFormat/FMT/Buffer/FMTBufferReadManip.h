#pragma once

#include "StreamFormat/FMT/Buffer/BufferInfo.h"
#include "StreamFormat/FMT/Buffer/Utils/BufferShiftManip.h"
#include "StreamFormat/FMT/Buffer/BufferManip.h"
#include "StreamFormat/FMT/Buffer/BufferTestManip.h"
#include "StreamFormat/FMT/Buffer/BufferReadManip.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class FMTBufferReadManip
    {
    public:
        FMTBufferReadManip(BufferInfo<TChar>& buffer) : Buffer(buffer) {}
    public:
        BufferInfo<TChar>& Buffer;

    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> ReadInteger(T& i, ShiftInfo shift = ShiftInfo{})
        {
            BufferShiftReadManip shiftManip(Buffer);
            Detail::BufferTestAccess access(Buffer);
            Detail::BufferTestManip manip(Buffer);
            T res = 0;

            shiftManip.SkipShiftBeginSpace(shift);

            bool sign = false;
            if constexpr (std::is_signed_v<T>)
            {
                sign = SF_TRY(manip.IsEqualToForward('-'));
                if (sign) --shift.Size;
            }

            access.IsADigit();

            while (access.IsADigit())
            {
                char c = SF_TRY(BufferManip(Buffer).GetAndForward());
                res = res * 10 + (c - '0');
                --shift.Size;
            }

            shiftManip.SkipShiftEnd(shift);

            i = sign ? -res : res;
        }
    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> ReadFloat(T& t, std::int32_t floatPrecision = -1, ShiftInfo shift = ShiftInfo{})
        {
            BufferShiftReadManip shiftManip(Buffer);
            Detail::BufferTestAccess access(Buffer);
            Detail::BufferTestManip manip(Buffer);
            
            shiftManip.SkipShiftBeginSpace(shift);

            bool sign = manip.IsEqualToForward('-');
            if (sign) --shift.Size;

            T intpart = static_cast<T>(0);
            if (access.IsADigit())
            {
                while (access.IsADigit())
                {
                    char c = SF_TRY(BufferManip(Buffer).GetAndForward());
                    intpart = intpart * 10 + (c - '0');
                    --shift.Size;
                }
            }
            else if (access.IsEqualTo('.'))
                { SF_TRY(Detail::BufferManip(Buffer).Forward()); }
            else
                { return std::unexpected(FMTResult::Parse_NonValidDigit); }

            if (floatPrecision <= 0)
                while (access.IsADigit() && access.IsEndOfString() == false)
                {
                    BufferManip(Buffer).ForceForward();
                    --shift.Size;
                }
            else
            {
                while (BufferAccess(Buffer).IsADigit() && floatPrecision > 0 && BufferAccess(Buffer).IsEndOfString() == false)
                {
                    BufferManip(Buffer).ForceForward();
                    floatPrecision--;
                    --shift.Size;
                }
            }
            BufferManip(Buffer).ForceBackward();

            T dec = (T)0;
            while (access.IsADigit())
            {
                dec += static_cast<T>(BufferManip(Buffer).GetAndForceBackward() - '0');
                dec /= 10;
            }

            shiftManip.SkipShiftEnd(shift);

            t = sign ? - intpart - dec : intpart + dec;
            return {};
        }

    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> ReadIntegerH(T& i, std::uint8_t digitSize, std::uint8_t (&digitLUT)(TChar), TChar base_prefix = '\0', ShiftInfo shift = ShiftInfo{})
        {
            BufferShiftReadManip shiftManip(Buffer);
            Detail::BufferTestAccess access(Buffer);
            Detail::BufferTestManip manip(Buffer);

            shift.Size -= sizeof(T) * 8;
            if (base_prefix != '\0') shift.Size -= 2;

            shiftManip.SkipShiftBeginSpace(shift);

            if (base_prefix != '\0')
                { manip.SkipOneOf('0'); manip.SkipOneOf(base_prefix); }

            T res = 0;

            while (digitLUT(Buffer.Get()) != std::numeric_limits<std::uint8_t>::max())
            {
                res = res << digitSize;
                res += digitLUT(Buffer.Get());
                BufferManip(Buffer).ForceForward();
            }

            shiftManip.SkipShiftEnd(shift);

            i = res;
        }

    protected:
        static constexpr std::uint8_t DigitLUT_BIN(TChar in)
        {
            if (in == '0') return 0;
            if (in == '1') return 1;
            return std::numeric_limits<std::uint8_t>::max();
        }
        static constexpr std::uint8_t DigitLUT_OCT(TChar in)
        {
            if (in >= '0' && in <= '7')
                return in - '0';
            return std::numeric_limits<std::uint8_t>::max();
        }
        static constexpr std::uint8_t DigitLUT_DEC(TChar in)
        {
            if (in >= '0' && in <= '9')
                return in - '0';
            return std::numeric_limits<std::uint8_t>::max();
        }
        static constexpr std::uint8_t DigitLUT_HEXUPPER(TChar in)
        {
            if (in >= '0' && in <= '9')
                return in - '0';
            if (in >= 'A' && in <= 'F')
                return in - 'A';
            return std::numeric_limits<std::uint8_t>::max();
        }
        static constexpr std::uint8_t DigitLUT_HEXLOWER(TChar in)
        {
            if (in >= '0' && in <= '9')
                return in - '0';
            if (in >= 'a' && in <= 'f')
                return in - 'a';
            return std::numeric_limits<std::uint8_t>::max();
        }

    public:
        template <typename T, typename FormatDataCharType>
        [[nodiscard]] std::expected<void, FMTResult> ReadIntegerFormatData(T& i, const FormatData<FormatDataCharType>& formatData)
        {
            if (formatData.HasSpec)
            {
                switch (formatData.IntegerPrint)
                {
                    case IntegerPrintBase::Dec:
                        if (formatData.Shift.Type == ShiftInfo::ShiftType::Nothing)
                            return BufferReadManip(Buffer).FastReadInteger(i);
                        else
                            return ReadInteger(i, formatData.Shift);
                    case IntegerPrintBase::Bin:
                    case IntegerPrintBase::BinUpper:
                        return ReadIntegerH(i, 1, DigitLUT_BIN, formatData.PrefixSuffix ? (char)formatData.IntegerPrint : '\0', formatData.Shift);
                    case IntegerPrintBase::Oct:
                    case IntegerPrintBase::OctUpper:
                        return ReadIntegerH(i, 3, DigitLUT_OCT, formatData.PrefixSuffix ? (char)formatData.IntegerPrint : '\0', formatData.Shift);
                    case IntegerPrintBase::Hex:
                        return ReadIntegerH(i, 4, DigitLUT_HEXLOWER, formatData.PrefixSuffix ? (char)formatData.IntegerPrint : '\0', formatData.Shift);
                    case IntegerPrintBase::HexUpper:
                        return ReadIntegerH(i, 4, DigitLUT_HEXUPPER, formatData.PrefixSuffix ? (char)formatData.IntegerPrint : '\0', formatData.Shift);
                }
            }
            return BufferReadManip(Buffer).FastReadInteger(i);
        }
        template <typename T, typename FormatDataCharType>
        [[nodiscard]] std::expected<void, FMTResult> ReadFloatFormatData(T& i, const FormatData<FormatDataCharType>& formatData)
        {
            if (formatData.HasSpec)
            {
                if (formatData.ShiftType == ShiftInfo::ShiftType::Nothing)
                    return BufferReadManip(Buffer).FastReadFloat(i, formatData.FloatPrecision);
                else
                    return ReadFloat(i, formatData.FloatPrecision, formatData.Shift);
            }
            return BufferReadManip(Buffer).FastReadFloat(i, formatData.FloatPrecision);
        }

    public:
        template <typename CharStr>
        [[nodiscard]] std::expected<void, FMTResult> ReadCharPtr(const CharStr* str, std::size_t sizeContainer, std::size_t sizeToWrite, ShiftInfo shift = ShiftInfo{})
        {
            // FIXME
            // TODO
            return std::unexpected(FMTResult::FunctionNotImpl);
        }

        template <typename CharStr, std::size_t SIZE>
        [[nodiscard]] inline std::expected<void, FMTResult> ReadCharArray(const CharStr (&str)[SIZE], ShiftInfo shift = ShiftInfo{})
        {
            ReadCharPtr(str, SIZE, 0, shift);
        }
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> ReadCharBound(const CharStr* begin, const CharStr* end, ShiftInfo shift = ShiftInfo{})
        {
            ReadCharPtr(begin, end - begin, 0, shift);
        }
    };
}
