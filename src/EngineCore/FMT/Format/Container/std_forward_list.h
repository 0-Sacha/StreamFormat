#pragma once

#include "FMT/Context/FormatterContext/Utils/FormatterType.h"
#include <forward_list>

namespace EngineCore::FMT {
	template<typename T, typename FormatterContext>
	struct FormatterType<std::forward_list<T>, FormatterContext>
	{
		static void Write(const std::forward_list<T>& t, FormatterContext& context) {
			FormatterType<ForwardAsSTDEnumerable<std::forward_list<T>>, FormatterContext>::Write(t, context);
		}
	};
}