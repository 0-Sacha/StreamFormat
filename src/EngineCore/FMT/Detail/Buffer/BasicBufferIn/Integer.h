#pragma once

#include "BasicBufferIn.h"

#include <cmath>

namespace EngineCore::FMT::Detail {

	template<typename CharBuffer>
	template<typename T>
	void BasicBufferIn<CharBuffer>::FastReadInt(T& i) {
		T res = 0;

		bool sign = IsEqualToForward('-');
		if (!IsADigit())
			throw FMTParseError();

		while (IsADigit())
			res = res * 10 + (GetAndForward() - '0');

		i = sign ? -res : res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicBufferIn<CharBuffer>::FastReadUInt(T& i) {
		T res = (T)0;

		if(!IsADigit())
			throw FMTParseError();

		while (IsADigit())
			res = res * 10 + (GetAndForward() - '0');

		i = res;
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicBufferIn<CharBuffer>::FastReadFloat(T& i, FloatPrecision floatPrecision) {
		typename Detail::TypesInfo::FloatDetail<T>::IntType iInt;
		FastReadInt(iInt);

		T dec = 0;
		T decIdx = 0.1f;

		if (IsEqualToForward('.') == false)
		{
			if (floatPrecision == 0 || floatPrecision.IsDefault())
			{
				i = iInt;
				return;
			}
			throw Detail::FMTParseError{};
		}

		if (floatPrecision.IsDefault())
		{
			while (IsADigit() && IsEnd() == false) {
				dec += (GetAndForward() - '0') * decIdx;
				decIdx *= 0.1f;
			}
		}
		else
		{
			++floatPrecision;
			while (IsADigit() && --floatPrecision != 0) {
				dec += (GetAndForward() - '0') * decIdx;
				decIdx *= 0.1f;
			}
		}

		i = iInt + dec;
	}
}
