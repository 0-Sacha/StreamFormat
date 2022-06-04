#pragma once

#include "Integer.h"

namespace EngineCore::FMT::Detail {

	template<typename CharBuffer>
	template<typename T, typename FormatDataCharType>
	void BasicFormatterMemoryBufferOut<CharBuffer>::WriteIntFormatData(T i, const FormatData<FormatDataCharType>& formatData) {
		if (formatData.HasSpec) {
			switch (formatData.IntPrint) {
			case ValueIntPrint::Int:
				if (formatData.ShiftType == ShiftType::Nothing) return FastWriteInt(i);
				else											return BasicWriteInt(i, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
			case ValueIntPrint::Bin:
				return BasicWriteIntAsBin(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
			case ValueIntPrint::Hex:
				return BasicWriteIntAsHex(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue, formatData.PrintStyle);
			case ValueIntPrint::Oct:
				return BasicWriteIntAsOct(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
			}
		}
		return FastWriteInt(i);
	}

	template<typename CharBuffer>
	template<typename T, typename FormatDataCharType>
	void BasicFormatterMemoryBufferOut<CharBuffer>::WriteUIntFormatData(T i, const FormatData<FormatDataCharType>& formatData) {
		if (formatData.HasSpec) {
			switch (formatData.IntPrint) {
			case ValueIntPrint::Int:
				if (formatData.ShiftType == ShiftType::Nothing) return FastWriteUInt(i);
				else											return BasicWriteUInt(i, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
			case ValueIntPrint::Bin:
				return BasicWriteIntAsBin(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
			case ValueIntPrint::Hex:
				return BasicWriteIntAsHex(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue, formatData.PrintStyle);
			case ValueIntPrint::Oct:
				return BasicWriteIntAsOct(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
			}
		}
		return FastWriteUInt(i);
	}

	template<typename CharBuffer>
	template<typename T, typename FormatDataCharType>
	void BasicFormatterMemoryBufferOut<CharBuffer>::WriteFloatFormatData(T i, const FormatData<FormatDataCharType>& formatData) {
		if (formatData.HasSpec) {
			if (formatData.ShiftType == ShiftType::Nothing)	return FastWriteFloat(i, formatData.FloatPrecision);
			else											return BasicWriteFloat(i, formatData.FloatPrecision, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
		} else
			return FastWriteFloat(i, formatData.FloatPrecision);
	}
}