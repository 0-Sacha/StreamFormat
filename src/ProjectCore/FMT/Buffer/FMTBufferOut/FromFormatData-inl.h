#pragma once

#include "FMTBufferOut.h"

namespace ProjectCore::FMT::Detail
{
    template <typename CharBuffer>
    template <typename T, typename FormatDataCharType>
    void FMTBufferOut<CharBuffer>::WriteIntFormatData(T i, const FormatData<FormatDataCharType>& formatData) {
        if (formatData.HasSpec)
        {
            switch (formatData.IntPrint) {
            case ValueIntPrint::Dec:
                if (formatData.ShiftType == ShiftType::Nothing) return FastWriteInt(i);
                else                                            return WriteInt(i, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
            case ValueIntPrint::Bin:
                return WriteIntAsBin(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
            case ValueIntPrint::Hex:
                return WriteIntAsHex(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue, formatData.PrintStyle);
            case ValueIntPrint::Oct:
                return WriteIntAsOct(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
            }
        }
        return FastWriteInt(i);
    }

    template <typename CharBuffer>
    template <typename T, typename FormatDataCharType>
    void FMTBufferOut<CharBuffer>::WriteUIntFormatData(T i, const FormatData<FormatDataCharType>& formatData) {
        if (formatData.HasSpec)
        {
            switch (formatData.IntPrint) {
            case ValueIntPrint::Dec:
                if (formatData.ShiftType == ShiftType::Nothing) return FastWriteUInt(i);
                else                                            return WriteUInt(i, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
            case ValueIntPrint::Bin:
                return WriteIntAsBin(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
            case ValueIntPrint::Hex:
                return WriteIntAsHex(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue, formatData.PrintStyle);
            case ValueIntPrint::Oct:
                return WriteIntAsOct(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
            }
        }
        return FastWriteUInt(i);
    }

    template <typename CharBuffer>
    template <typename T, typename FormatDataCharType>
    void FMTBufferOut<CharBuffer>::WriteFloatFormatData(T i, const FormatData<FormatDataCharType>& formatData) {
        if (formatData.HasSpec)
        {
            if (formatData.ShiftType != ShiftType::Nothing)
                return WriteFloat(i, formatData.FloatPrecision, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
        }

        return FastWriteFloat(i, formatData.FloatPrecision);
    }
}
