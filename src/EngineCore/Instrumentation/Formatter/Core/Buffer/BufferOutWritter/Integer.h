#pragma once

#include "../BasicBufferOut.h"

namespace EngineCore::Instrumentation::FMT::Detail {

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferOut<CharBuffer>::FastWriteInt(T i) {
		if (i == 0) { PushBack('0'); return; }
		if (i < 0)	{ PushBack('-'); i = -i; }

		DataType nbDigit = GetNumberOfDigitDec(i);
		Forward(nbDigit - 1);
		while (i > 0) { PushReverseNoCheck(i % 10 + '0'); i /= 10; }
		Forward(nbDigit + 1);
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferOut<CharBuffer>::FastWriteUInt(T i) {
		if (i == 0) { PushBack('0'); return; }

		DataType nbDigit = GetNumberOfDigitDec(i);
		Forward(nbDigit - 1);
		while (i > 0) { PushReverseNoCheck(i % 10 + '0'); i /= 10; }
		Forward(nbDigit + 1);
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferOut<CharBuffer>::FastWriteFloat(T i, DataType nbDecimal) {
		FastWriteInt<typename Detail::ValuesDetail::FloatDetail<T>::IntType>(static_cast<typename Detail::ValuesDetail::FloatDetail<T>::IntType>(i));
		PushBack('.');
		if (i < 0)	i = -i;
		i = i - (typename Detail::ValuesDetail::FloatDetail<T>::IntType)i;
		while (nbDecimal-- != 0) {
			char intPart = static_cast<char>(i *= 10);
			PushBack(intPart + '0');
			i -= intPart;
		}
	}

	//---------------------------------------------//
	//---------------------------------------------//
	//---------------------------------------------//

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferOut<CharBuffer>::BasicWriteInt(T i, ShiftType st, DataType shift, ShiftPrint sp) {

		DataType nbDigit = GetNumberOfDigitDec(i);

		shift -= nbDigit;
		if (i < 0) --shift;

		if(sp == ShiftPrint::Space)		PrintShiftBegin(st, ShiftPrint::Space, shift);
		if (i < 0) { PushBack('-'); i = -i; }
		if (sp == ShiftPrint::Zeros)	PrintShiftRight(st, ShiftPrint::Zeros, shift);

		if (i == 0)		PushBack('0');
		else {
			Forward(nbDigit - 1);
			while (i > 0) { PushReverseNoCheck(i % 10 + '0'); i /= 10; }
			Forward(nbDigit + 1);
		}

		PrintShiftEnd(st, ShiftPrint::Space, shift);
	}


	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferOut<CharBuffer>::BasicWriteUInt(T i, ShiftType st, DataType shift, ShiftPrint sp) {
		DataType nbDigit = GetNumberOfDigitDec(i);
		shift -= nbDigit;

		PrintShiftBegin(st, sp, shift);

		if (i == 0)		PushBack('0');
		else {
			Forward(nbDigit - 1);
			while (i > 0) { PushReverseNoCheck(i % 10 + '0'); i /= 10; }
			Forward(nbDigit + 1);
		}

		PrintShiftEnd(st, ShiftPrint::Space, shift);
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferOut<CharBuffer>::BasicWriteFloat(T i, DataType nbDecimal, ShiftType st, DataType shift, ShiftPrint sp) {

		typename Detail::ValuesDetail::FloatDetail<T>::IntType iInt = static_cast<typename Detail::ValuesDetail::FloatDetail<T>::IntType>(i);

		DataType nbDigit = GetNumberOfDigitDec(iInt);

		shift -= nbDigit + nbDecimal + 1;
		if (iInt < 0) --shift;

		if (sp == ShiftPrint::Space)	PrintShiftBegin(st, ShiftPrint::Space, shift);
		if (iInt < 0) { PushBack('-'); iInt = -iInt; }
		if (sp == ShiftPrint::Zeros)	PrintShiftRight(st, ShiftPrint::Zeros, shift);

		if (iInt == 0)		PushBack('0');
		else {
			Forward(nbDigit - 1);
			while (iInt > 0) { PushReverseNoCheck(iInt % 10 + '0'); iInt /= 10; }
			Forward(nbDigit + 1);
		}

		PushBack('.');
		if (i < 0)	i = -i;
		i = i - (typename Detail::ValuesDetail::FloatDetail<T>::IntType)i;
		while (nbDecimal-- != 0) {
			const char intPart = static_cast<const char>(i *= 10);
			PushBack(intPart + '0');
			i -= intPart;
		}
		
		PrintShiftEnd(st, ShiftPrint::Space, shift);
	}


	//---------------------------------------------//
	//---------------------------------------------//
	//---------------------------------------------//

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferOut<CharBuffer>::BasicWriteIntAsBin(T i, DataType digitSize, ShiftType st, DataType shift, ShiftPrint sp, bool trueValue) {
		// Compute shift and "TureValue" print
		if (digitSize == Detail::DIGIT_SIZE_NOT_SPECIFIED) digitSize = sizeof(T) * 8;
		shift -= digitSize;
		if (trueValue) shift -= 2;

		if (sp == ShiftPrint::Space) PrintShiftBegin(st, sp, shift);
		if (trueValue) {
			PushBack('0');
			PushBack('b');
		}
		if (sp == ShiftPrint::Zeros) PrintShiftBegin(st, sp, shift);

		// Print value
		Forward(digitSize - 1);
		DataType k = digitSize + 1;
		while (--k != 0) {
			if (i & 1)	PushReverseNoCheck('1');
			else		PushReverseNoCheck('0');
			i = i >> 1;
		}
		Forward(digitSize + 1);

		PrintShiftEnd(st, ShiftPrint::Space, shift);
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferOut<CharBuffer>::BasicWriteIntAsHex(T i, DataType digitSize, ShiftType st, DataType shift, ShiftPrint sp, bool trueValue, Detail::PrintStyle valueDes) {
		// Compute shift and "TureValue" print
		if (digitSize == Detail::DIGIT_SIZE_NOT_SPECIFIED) digitSize = sizeof(T) * 2;
		shift -= digitSize;
		if (trueValue) shift -= 2;

		if (sp == ShiftPrint::Space) PrintShiftBegin(st, sp, shift);
		if (trueValue) {
			PushBack('0');
			PushBack('x');
		}
		if (sp == ShiftPrint::Zeros) PrintShiftBegin(st, sp, shift);

		// Print value
		Forward(digitSize - 1);
		DataType k = digitSize + 1;
		if(valueDes == PrintStyle::LowerCase)
			while (--k != 0) { PushReverseNoCheck(LOWER_HEX[i & 0b1111]); i = i >> 4; }
		else
			while (--k != 0) { PushReverseNoCheck(UPPER_HEX[i & 0b1111]); i = i >> 4; }
		Forward(digitSize + 1);

		PrintShiftEnd(st, ShiftPrint::Space, shift);
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferOut<CharBuffer>::BasicWriteIntAsOct(T i, DataType digitSize, ShiftType st, DataType shift, ShiftPrint sp, bool trueValue) {
		// Compute shift and "TureValue" print
		if (digitSize == Detail::DIGIT_SIZE_NOT_SPECIFIED) digitSize = static_cast<DataType>(std::ceil(static_cast<float>(sizeof(T) * 8) / 3));
		shift -= digitSize;
		if (trueValue) shift -= 2;

		if (sp == ShiftPrint::Space) PrintShiftBegin(st, sp, shift);
		if (trueValue) {
			PushBack('0');
			PushBack('o');
		}
		if (sp == ShiftPrint::Zeros) PrintShiftBegin(st, sp, shift);

		// Print value
		Forward(digitSize - 1);
		DataType k = digitSize + 1;
		while (--k != 0) { PushReverseNoCheck((i & 0b111) + '0'); i = i >> 3; }
		Forward(digitSize + 1);

		PrintShiftEnd(st, ShiftPrint::Space, shift);
	}
}