#pragma once

#include "FMTBufferIn.h"
#include "Integer.h"

namespace ProjectCore::FMT::Detail {

	//------------------ Buffer Read Int ------------------//
	template<typename CharBuffer>
	template<typename T, typename FormatDataCharType>
	void FMTBufferIn<CharBuffer>::ReadIntFormatData(T& i, const FormatData<FormatDataCharType>& formatData) {
		if (formatData.HasSpec) {
			switch (formatData.IntPrint) {
			case ValueIntPrint::Dec:
				if (formatData.ShiftType == ShiftType::Nothing) FastReadIntThrow(i);
				else											ReadInt(i, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
			case ValueIntPrint::Bin:
				ReadIntAsBin(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
			case ValueIntPrint::Hex:
				ReadIntAsHex(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue, formatData.PrintStyle);
			case ValueIntPrint::Oct:
				ReadIntAsOct(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
			}
		}
		FastReadIntThrow(i);
	}

	//------------------ Buffer Read UInt ------------------//
	template<typename CharBuffer>
	template<typename T, typename FormatDataCharType>
	void FMTBufferIn<CharBuffer>::ReadUIntFormatData(T& i, const FormatData<FormatDataCharType>& formatData) {
		if (formatData.HasSpec) {
			switch (formatData.IntPrint) {
			case ValueIntPrint::Dec:
				if (formatData.ShiftType == ShiftType::Nothing) FastReadUIntThrow(i);
				else											ReadUInt(i, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
			case ValueIntPrint::Bin:
				ReadIntAsBin(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
			case ValueIntPrint::Hex:
				ReadIntAsHex(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue, formatData.PrintStyle);
			case ValueIntPrint::Oct:
				ReadIntAsOct(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
			}
		}
		FastReadUIntThrow(i);
	}

	//------------------ Buffer Read Float ------------------//
	template<typename CharBuffer>
	template<typename T, typename FormatDataCharType>
	void FMTBufferIn<CharBuffer>::ReadFloatFormatData(T& i, const FormatData<FormatDataCharType>& formatData) {
		if (formatData.HasSpec) {
			if (formatData.ShiftType == ShiftType::Nothing)	FastReadFloatThrow(i, formatData.FloatPrecision);
			else											ReadFloat(i, formatData.FloatPrecision, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
		}
		FastReadFloatThrow(i, formatData.FloatPrecision);
	}
}
