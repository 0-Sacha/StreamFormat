#pragma once

#include "FMT/Context/FormatterContext/Utils/FormatterType.h"
#include <array>

namespace EngineCore::FMT {

	template<std::size_t SIZE, typename T, typename FormatterContext>
	struct FormatterType<std::array<T, SIZE>, FormatterContext>
	{
		static void Write(const std::array<T, SIZE>& t, FormatterContext& context) {
			FormatterType<ForwardAsSTDEnumerable<std::array<T, SIZE>>, FormatterContext>::Write(t, context);
		}
	};

}