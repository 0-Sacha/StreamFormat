#pragma once

#include "../BasicBufferIn.h"
#include "Integer.h"

namespace EngineCore::Fmt::Detail {

	//------------------ Buffer Read Int ------------------//
	template<typename CharBuffer>
	template<typename T, typename FormatDataCharType>
	void BasicFormatterMemoryBufferIn<CharBuffer>::ReadIntFormatData(T& i, const FormatData<FormatDataCharType>& formatData) {
		if (formatData.HasSpec) {
			switch (formatData.IntPrint) {
			case ValueIntPrint::Int:
				if (formatData.ShiftType == ShiftType::Nothing) FastReadInt(i);
				else											BasicReadInt(i, formatData.ShiftType, formatData.ShiftValue, formatData.ShiftPrint);
			case ValueIntPrint::Bin:
				BasicReadIntAsBin(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftValue, formatData.ShiftPrint, formatData.TrueValue);
			case ValueIntPrint::Hex:
				BasicReadIntAsHex(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftValue, formatData.ShiftPrint, formatData.TrueValue, formatData.PrintStyle);
			case ValueIntPrint::Oct:
				BasicReadIntAsOct(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftValue, formatData.ShiftPrint, formatData.TrueValue);
			}
		}
		FastReadInt(i);
	}

	//------------------ Buffer Read UInt ------------------//
	template<typename CharBuffer>
	template<typename T, typename FormatDataCharType>
	void BasicFormatterMemoryBufferIn<CharBuffer>::ReadUIntFormatData(T& i, const FormatData<FormatDataCharType>& formatData) {
		if (formatData.HasSpec) {
			switch (formatData.IntPrint) {
			case ValueIntPrint::Int:
				if (formatData.ShiftType == ShiftType::Nothing) FastReadUInt(i);
				else											BasicReadUInt(i, formatData.ShiftType, formatData.ShiftValue, formatData.ShiftPrint);
			case ValueIntPrint::Bin:
				BasicReadIntAsBin(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftValue, formatData.ShiftPrint, formatData.TrueValue);
			case ValueIntPrint::Hex:
				BasicReadIntAsHex(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftValue, formatData.ShiftPrint, formatData.TrueValue, formatData.PrintStyle);
			case ValueIntPrint::Oct:
				BasicReadIntAsOct(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftValue, formatData.ShiftPrint, formatData.TrueValue);
			}
		}
		FastReadUInt(i);
	}

	//------------------ Buffer Read Float ------------------//
	template<typename CharBuffer>
	template<typename T, typename FormatDataCharType>
	void BasicFormatterMemoryBufferIn<CharBuffer>::ReadFloatFormatData(T& i, const FormatData<FormatDataCharType>& formatData) {
		if (formatData.HasSpec) {
			if (formatData.ShiftType == ShiftType::Nothing)	FastReadFloat(i, formatData.FloatPrecision);
			else											BasicReadFloat(i, formatData.FloatPrecision, formatData.ShiftType, formatData.ShiftValue, formatData.ShiftPrint);
		}
		FastReadFloat(i, formatData.FloatPrecision);
	}

}