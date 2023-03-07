#pragma once

#include "FMTFormatBuffer.h"

namespace ProjectCore::FMT::Detail {
	template<typename CharFormat>
	template<typename T>
	bool FMTFormatBuffer<CharFormat>::ReadInt(T& i) {
		T res{};
		bool sign		= IsEqualToForward('-');
		bool isValid	= IsADigit();

		while (IsADigit())
			res = res * 10 + static_cast<T>(GetAndForward() - '0');

		if (isValid)
			i = sign ? -res : res;

		return isValid;
	}

	template<typename CharFormat>
	template<typename T>
	bool FMTFormatBuffer<CharFormat>::ReadUInt(T& i) {
		T res{};
		bool isValid = IsADigit();

		while (IsADigit())
			res = res * 10 + static_cast<T>(GetAndForward() - '0');

		if (isValid) i = res;

		return isValid;
	}
}
