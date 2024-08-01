#pragma once

#include "FMTBufferIn.h"

namespace ProjectCore::FMT::Detail
{
    //------------------ Buffer Read Int ------------------//
    template <typename CharBuffer>
    template <typename T, typename FormatDataCharType>
    void FMTBufferIn<CharBuffer>::ReadIntFormatData(T& i, const FormatData<FormatDataCharType>& formatData)
    {
        if (formatData.HasSpec)
        {
            switch (formatData.IntPrint)
            {
                case ValueIntPrint::Dec:
                    if (formatData.ShiftType == ShiftType::Nothing)
                        return FastReadIntThrow(i);
                    else
                        return ReadInt(i, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
                case ValueIntPrint::Bin:
                    return ReadIntAsBin(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
                case ValueIntPrint::Hex:
                    return ReadIntAsHex(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue, formatData.PrintStyle);
                case ValueIntPrint::Oct:
                    return ReadIntAsOct(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
            }
        }
        return FastReadIntThrow(i);
    }

    //------------------ Buffer Read UInt ------------------//
    template <typename CharBuffer>
    template <typename T, typename FormatDataCharType>
    void FMTBufferIn<CharBuffer>::ReadUIntFormatData(T& i, const FormatData<FormatDataCharType>& formatData)
    {
        if (formatData.HasSpec)
        {
            switch (formatData.IntPrint)
            {
                case ValueIntPrint::Dec:
                    if (formatData.ShiftType == ShiftType::Nothing)
                        return FastReadUIntThrow(i);
                    else
                        return ReadUInt(i, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
                case ValueIntPrint::Bin:
                    return ReadIntAsBin(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
                case ValueIntPrint::Hex:
                    return ReadIntAsHex(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue, formatData.PrintStyle);
                case ValueIntPrint::Oct:
                    return ReadIntAsOct(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
            }
        }
        return FastReadUIntThrow(i);
    }

    //------------------ Buffer Read Float ------------------//
    template <typename CharBuffer>
    template <typename T, typename FormatDataCharType>
    void FMTBufferIn<CharBuffer>::ReadFloatFormatData(T& i, const FormatData<FormatDataCharType>& formatData)
    {
        if (formatData.HasSpec)
        {
            if (formatData.ShiftType == ShiftType::Nothing)
                return FastReadFloatThrow(i, formatData.FloatPrecision);
            else
                return ReadFloat(i, formatData.FloatPrecision, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
        }
        return FastReadFloatThrow(i, formatData.FloatPrecision);
    }
}
