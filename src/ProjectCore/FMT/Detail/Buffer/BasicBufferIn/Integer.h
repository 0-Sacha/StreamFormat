#pragma once

#include "BasicBufferIn.h"

#include <cmath>

namespace ProjectCore::FMT::Detail {

	template<typename CharBuffer>
	template<typename T>
	bool BasicBufferIn<CharBuffer>::FastReadInt(T& i) {
		T res = 0;

		bool sign = IsEqualToForward('-');
		if (!IsADigit())
			return false;

		while (IsADigit())
			res = res * 10 + (GetAndForward() - '0');

		i = sign ? -res : res;
		return true;
	}

	template<typename CharBuffer>
	template<typename T>
	bool BasicBufferIn<CharBuffer>::FastReadUInt(T& i) {
		T res = (T)0;

		if(!IsADigit())
			return false;

		while (IsADigit())
			res = res * 10 + (GetAndForward() - '0');

		i = res;
		return true;
	}

	template<typename CharBuffer>
	template<typename T>
	bool BasicBufferIn<CharBuffer>::FastReadFloat(T& i, FloatPrecision floatPrecision) {
		typename Detail::TypesInfo::FloatDetail<T>::IntType iInt;
		FastReadIntThrow(iInt);

		T dec = 0;
		T decIdx = 0.1f;

		if (IsEqualToForward('.') == false)
		{
			if (floatPrecision == 0 || floatPrecision.IsDefault())
			{
				i = static_cast<T>(iInt);
				return true;
			}
			return false;
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
		return true;
	}
}
