#pragma once

#include "EngineCore/FMT/Context/FormatterContext/Utils/FormatterType.h"
#include <list>

namespace EngineCore::FMT {

	template<typename T, typename FormatterContext>
	struct FormatterType<std::list<T>, FormatterContext>
	{
		static void Write(const std::list<T>& t, FormatterContext& context) {
			FormatterType<ForwardAsSTDEnumerable<std::list<T>>, FormatterContext>::Write(t, context);
		}
	};
}