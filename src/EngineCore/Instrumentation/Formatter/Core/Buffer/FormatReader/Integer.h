#pragma once

#include "Formatter/Core/Buffer/Format.h"

namespace EngineCore::FMT::Detail {
	template<typename CharFormat>
	template<typename T>
	bool FormatterMemoryFormat<CharFormat>::ReadInt(T& i) {
		T res{};
		bool sign		= IsEqualForward('-');
		bool isValid	= IsADigit();

		while (IsADigit())
			res = res * 10 + static_cast<T>(GetAndForward() - '0');

		if (isValid)
			i = sign ? -res : res;

		return isValid;
	}

	template<typename CharFormat>
	template<typename T>
	bool FormatterMemoryFormat<CharFormat>::ReadUInt(T& i) {
		T res{};
		bool isValid = IsADigit();

		while (IsADigit())
			res = res * 10 + static_cast<T>(GetAndForward() - '0');

		if (isValid) i = res;

		return isValid;
	}
}