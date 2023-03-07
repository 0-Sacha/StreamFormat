#pragma once

#include "BasicBufferOut.h"

#include <cmath>

namespace ProjectCore::FMT::Detail {

	template<typename CharBuffer>
	template<typename T>
	void BasicBufferOut<CharBuffer>::FastWriteInt(T i) {
		if (i == 0) { PushBack('0'); return; }
		if (i < 0)	{ PushBack('-'); i = -i; }

		DataType nbDigit = GetNumberOfDigitDec(i);
		Reserve(nbDigit);
		while (i > 0) { PushReverseNoCheck(i % 10 + '0'); i /= 10; }
		Forward(nbDigit + 1);
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicBufferOut<CharBuffer>::FastWriteUInt(T i) {
		if (i == 0) { PushBack('0'); return; }

		DataType nbDigit = GetNumberOfDigitDec(i);
		Reserve(nbDigit);
		while (i > 0) { PushReverseNoCheck(i % 10 + '0'); i /= 10; }
		Forward(nbDigit + 1);
	}

	template<typename CharBuffer>
	template<typename T>
	void BasicBufferOut<CharBuffer>::FastWriteFloat(T i, FloatPrecision nbDecimal) {
		FastWriteInt<typename Detail::TypesInfo::FloatDetail<T>::IntType>(static_cast<typename Detail::TypesInfo::FloatDetail<T>::IntType>(i));
		PushBack('.');
		if (i < 0)	i = -i;
		i = i - (typename Detail::TypesInfo::FloatDetail<T>::IntType)i;

		nbDecimal.SetToBasicSizeIfDefault();

		while (nbDecimal-- != 0) {
			char intPart = static_cast<char>(i *= 10);
			PushBack(intPart + '0');
			i -= intPart;
		}
	}
}
