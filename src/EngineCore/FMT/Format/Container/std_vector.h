#pragma once

#include "EngineCore/FMT/Context/FormatterContext/Utils/FormatterType.h"
#include <vector>

namespace EngineCore::FMT {

	template<typename T, typename FormatterContext>
	struct FormatterType<std::vector<T>, FormatterContext>
	{
		static void Write(const std::vector<T>& t, FormatterContext& context) {
			FormatterType<ForwardAsSTDEnumerable<std::vector<T>>, FormatterContext>::Write(t, context);
		}
	};

}