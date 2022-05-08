#pragma once

#include "../BasicBufferIn.h"

namespace EngineCore::Fmt::Detail {

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::FastReadInt(T& i) {
		T res = static_cast<T>(0);

		bool sign = IsEqualForward('-');
		
		IsADigitThrow();

		while (IsADigit())
			res = res * static_cast<T>(10) + (GetAndForward() - '0');

		i = sign ? -res : res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::FastReadUInt(T& i) {
		T res = static_cast<T>(0);

		IsADigitThrow();

		while (IsADigit())
			res = res * static_cast<T>(10) + (GetAndForward() - '0');

		i = res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::FastReadFloat(T& i, FormatDataType nbDecimal) {
		typename Detail::ValuesDetail::FloatDetail<T>::IntType iInt;

		FastReadInt(iInt);

		T res = static_cast<T>(0);
		T dec = static_cast<T>(0.1);

		IsEqualForwardThrow('.');
		
		++nbDecimal;
		while (IsADigit() && --nbDecimal != 0) {
			res += (GetAndForward() - '0') * dec;
			dec *= static_cast<T>(0.1);
		}

		i = iInt + res;
	}


	//---------------------------------------------//
	//---------------------------------------------//
	//---------------------------------------------//

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::BasicReadInt(T& i, ShiftType st, FormatDataType shift, ShiftPrint sp) {
		T res = static_cast<T>(0);

		SkipShiftBeginSpace(st, sp, shift);

		bool sign = IsEqualForward('-'); 
		if (sign) --shift;
	
		IsADigitThrow();

		while (IsADigit()) {
			res = res * static_cast<T>(10) + (GetAndForward() - '0');
			--shift;
		}

		SkipShiftEnd(st, sp, shift);

		if (shift > 0)
			throw FormatParseError();
		
		i = sign ? -res : res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::BasicReadUInt(T& i, ShiftType st, FormatDataType shift, ShiftPrint sp) {
		T res = static_cast<T>(0);

		SkipShiftBeginSpace(st, sp, shift);

		IsADigitThrow();

		while (IsADigit()) {
			res = res * static_cast<T>(10) + (GetAndForward() - '0');
			--shift;
		}

		SkipShiftEnd(st, sp, shift);

		if (shift > 0)
			throw FormatParseError();

		i = res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::BasicReadFloat(T& i, FormatDataType nbDecimal, ShiftType st, FormatDataType shift, ShiftPrint sp) {

		typename Detail::ValuesDetail::FloatDetail<T>::IntType iInt = 0;

		SkipShiftBeginSpace(st, sp, shift);

		bool sign = IsEqualForward('-');
		if (sign) --shift;

		IsADigitThrow();

		while (IsADigit()) {
			iInt = iInt * 10 + (GetAndForward() - '0');
			--shift;
		}


		T res = static_cast<T>(0);
		T dec = static_cast<T>(0.1);

		IsEqualForwardThrow('.');
		--shift;
			
		++nbDecimal;
		while (IsADigit() && --nbDecimal != 0) {
			res += (GetAndForward() - '0') * dec;
			dec *= static_cast<T>(0.1);
			--shift;
		}

		SkipShiftEnd(st, sp, shift);

		if (shift > 0)
			throw FormatParseError();

		sign ? i = -iInt - res : i = iInt + res;
	}

	//---------------------------------------------//
	//---------------------------------------------//
	//---------------------------------------------//

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::BasicReadIntAsBin(T& i, FormatDataType digitSize, ShiftType st, FormatDataType shift, ShiftPrint sp, bool trueValue) {
		if (digitSize == Detail::DIGIT_SIZE_NOT_SPECIFIED) digitSize = sizeof(T) * 8;

		shift -= digitSize;
		if (trueValue) shift -= 2;

		SkipShiftBeginSpace(st, sp, shift);
		
		if (trueValue)
			IsEqualForwardThrow('0', 'b');

		T res = static_cast<T>(0);

		while (IsEqualTo('0', '1')) {
			res = res << 1;
			res += Get() - '0';
			Forward();
		}

		SkipShiftEnd(st, sp, shift);

		if (shift > 0)
			throw FormatParseError();

		i = res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::BasicReadIntAsHex(T& i, FormatDataType digitSize, ShiftType st, FormatDataType shift, ShiftPrint sp, bool trueValue, Detail::PrintStyle valueDes) {
		if (digitSize == Detail::DIGIT_SIZE_NOT_SPECIFIED) digitSize = sizeof(T) * 2;

		shift -= digitSize;
		if (trueValue) shift -= 2;

		SkipShiftBeginSpace(st, sp, shift);

		if (trueValue)
			IsEqualForwardThrow('0', 'x');

		T res = static_cast<T>(0);

		while (IsADigit() || (Get() >= 'A' && Get() <= 'F') || (Get() >= 'a' && Get() <= 'f')) {
			res = res << 4;
			if (IsADigit())								res += Get() - '0';
			else if (Get() >= 'A' && Get() <= 'F')	res += Get() - 'A' + 10;
			else if (Get() >= 'a' && Get() <= 'f')	res += Get() - 'a' + 10;
			Forward();
		}

		SkipShiftEnd(st, sp, shift);

		if (shift > 0)
			throw FormatParseError();

		i = res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::BasicReadIntAsOct(T& i, FormatDataType digitSize, ShiftType st, FormatDataType shift, ShiftPrint sp, bool trueValue) {
		if (digitSize == Detail::DIGIT_SIZE_NOT_SPECIFIED) digitSize = static_cast<FormatDataType>(std::ceil(static_cast<float>(sizeof(T) * 8) / 3));

		shift -= digitSize;
		if (trueValue) shift -= 2;

		SkipShiftBeginSpace(st, sp, shift);

		if (trueValue)
			IsEqualForwardThrow('0', 'o');

		T res = static_cast<T>(0);

		while (Get() >= '0' && Get() <= '8') {
			res = res << 3;
			res += Get() - '0';
			Forward();
		}

		SkipShiftEnd(st, sp, shift);

		if (shift > 0)
			throw FormatParseError();

		i = res;
	}

}