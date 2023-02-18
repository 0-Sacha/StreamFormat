#pragma once

#include "EngineCore/FMT/Context/FormatterContext/FormatterType.h"
#include <deque>

namespace EngineCore::FMT {

	template<typename T, typename FormatterContext>
	struct FormatterType<std::deque<T>, FormatterContext>
	{
		static void Write(const std::deque<T>& t, FormatterContext& context) {
			FormatterType<ForwardAsSTDEnumerable<std::deque<T>>, FormatterContext>::Write(t, context);
		}
	};

}