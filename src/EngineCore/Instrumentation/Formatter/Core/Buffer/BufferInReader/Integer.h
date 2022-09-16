#pragma once

#include "Formatter/Core/Buffer/BasicBufferIn.h"

namespace EngineCore::FMT::Detail {

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::FastReadInt(T& i) {
		T res = 0;

		bool sign = IsEqualToForward('-');
		if (!IsADigit())
			throw FormatParseError();

		while (IsADigit())
			res = res * 10 + (GetAndForward() - '0');

		i = sign ? -res : res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::FastReadUInt(T& i) {
		T res = (T)0;

		if(!IsADigit())
			throw FormatParseError();

		while (IsADigit())
			res = res * 10 + (GetAndForward() - '0');

		i = res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::FastReadFloat(T& i, FloatPrecision floatPrecision) {
		typename Detail::ValuesDetail::FloatDetail<T>::IntType iInt;
		FastReadInt(iInt);

		T res = 0;
		T dec = 0.1f;

		IsEqualToForwardThrow('.');
		
		++floatPrecision;
		while (IsADigit() && --floatPrecision != 0) {
			res += (GetAndForward() - '0') * dec;
			dec *= 0.1f;
		}

		i = iInt + res;
	}


	//---------------------------------------------//
	//---------------------------------------------//
	//---------------------------------------------//

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::BasicReadInt(T& i, ShiftType st, ShiftSize shift, ShiftPrint sp) {
		T res = 0;

		SkipShiftBeginSpace(st, sp, shift);

		bool sign = IsEqualToForward('-'); 
		if (sign) --shift;
	
		IsADigitThrow();

		while (IsADigit()) {
			res = res * 10 + (GetAndForward() - '0');
			--shift;
		}

		SkipShiftEnd(st, sp, shift);

		if (shift > 0) throw FormatParseError();
		
		i = sign ? -res : res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::BasicReadUInt(T& i, ShiftType st, ShiftSize shift, ShiftPrint sp) {
		T res = 0;

		SkipShiftBeginSpace(st, sp, shift);

		IsADigitThrow();

		while (IsADigit()) {
			res = res * 10 + (GetAndForward() - '0');
			--shift;
		}

		SkipShiftEnd(st, sp, shift);

		if (shift > 0) throw FormatParseError();

		i = res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::BasicReadFloat(T& i, FloatPrecision floatPrecision, ShiftType st, ShiftSize shift, ShiftPrint sp) {
		typename Detail::ValuesDetail::FloatDetail<T>::IntType iInt = 0;

		SkipShiftBeginSpace(st, sp, shift);

		bool sign = IsEqualToForward('-');
		if (sign) --shift;

		IsADigitThrow();

		while (IsADigit()) {
			iInt = iInt * 10 + (GetAndForward() - '0');
			--shift;
		}

		T res = 0;
		T dec = 0.1f;

		IsEqualToForwardThrow('.');
		--shift;
			
		++floatPrecision;
		while (IsADigit() && --floatPrecision != 0) {
			res += (GetAndForward() - '0') * dec;
			dec *= 0.1f;
			--shift;
		}

		SkipShiftEnd(st, sp, shift);

		if (shift > 0) throw FormatParseError();

		sign ? i = -iInt - res : i = iInt + res;
	}

	//---------------------------------------------//
	//---------------------------------------------//
	//---------------------------------------------//

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::BasicReadIntAsBin(T& i, DigitSize digitSize, ShiftType st, ShiftSize shift, ShiftPrint sp, bool trueValue) {
		if (digitSize.IsDefault())
			digitSize = sizeof(T) * 8;

		shift -= digitSize;
		if (trueValue) shift -= 2;

		SkipShiftBeginSpace(st, sp, shift);
		
		if (trueValue) {
			IsEqualToForwardThrow('0');
			IsEqualToForwardThrow('b');
		}

		T res = 0;

		while (IsEqualTo('0', '1')) {
			res = res << 1;
			res += Get() - '0';
			Forward();
		}

		SkipShiftEnd(st, sp, shift);

		if (shift > 0) throw FormatParseError();

		i = res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::BasicReadIntAsHex(T& i, DigitSize digitSize, ShiftType st, ShiftSize shift, ShiftPrint sp, bool trueValue, Detail::PrintStyle valueDes) {
		if (digitSize.IsDefault())
			digitSize = sizeof(T) * 2;

		shift -= digitSize;
		if (trueValue) shift -= 2;

		SkipShiftBeginSpace(st, sp, shift);

		if (trueValue) {
			IsEqualToForwardThrow('0');
			IsEqualToForwardThrow('x');
		}

		T res = 0;

		while (IsADigit() || (Get() >= 'A' && Get() <= 'F') || (Get() >= 'a' && Get() <= 'f')) {
			res = res << 4;
			if (IsADigit())								res += Get() - '0';
			else if (Get() >= 'A' && Get() <= 'F')	res += Get() - 'A' + 10;
			else if (Get() >= 'a' && Get() <= 'f')	res += Get() - 'a' + 10;
			Forward();
		}

		SkipShiftEnd(st, sp, shift);

		if (shift > 0) throw FormatParseError();

		i = res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicFormatterMemoryBufferIn<CharBuffer>::BasicReadIntAsOct(T& i, DigitSize digitSize, ShiftType st, ShiftSize shift, ShiftPrint sp, bool trueValue) {
		if (digitSize.IsDefault())
			digitSize = std::ceil(static_cast<float>(sizeof(T) * 8) / 3);

		shift -= digitSize;
		if (trueValue) shift -= 2;

		SkipShiftBeginSpace(st, sp, shift);

		if (trueValue) {
			IsEqualToForwardThrow('0');
			IsEqualToForwardThrow('o');
		}

		T res = 0;

		while (Get() >= '0' && Get() <= '8') {
			res = res << 3;
			res += Get() - '0';
			Forward();
		}

		SkipShiftEnd(st, sp, shift);

		if (shift > 0) throw FormatParseError();

		i = res;
	}

}