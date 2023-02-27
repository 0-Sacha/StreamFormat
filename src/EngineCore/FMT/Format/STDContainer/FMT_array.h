#pragma once

#include "EngineCore/FMT/Context/FormatterContext/FormatterType.h"
#include <array>

namespace EngineCore::FMT {

	template<std::size_t SIZE, typename T, typename FormatterContext>
	struct FormatterType<std::array<T, SIZE>, FormatterContext>
	{
		static void Format(const std::array<T, SIZE>& t, FormatterContext& context) {
			FormatterType<ForwardAsSTDEnumerable<std::array<T, SIZE>>, FormatterContext>::Format(t, context);
		}
	};

}