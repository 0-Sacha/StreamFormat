#pragma once

#include "EngineCore/FMT/Context/FormatterContext/FormatterType.h"
#include <stack>

namespace EngineCore::FMT {

	template<typename T, typename FormatterContext>
	struct FormatterType<std::stack<T>, FormatterContext>
	{
		static void Format(const std::stack<T>& t, FormatterContext& context) {

		}
	};

}