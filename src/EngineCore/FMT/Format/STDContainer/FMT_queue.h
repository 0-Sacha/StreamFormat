#pragma once

#include "EngineCore/FMT/Context/FormatterContext/FormatterType.h"
#include <queue>

namespace EngineCore::FMT {

	template<typename T, typename FormatterContext>
	struct FormatterType<std::queue<T>, FormatterContext>
	{
		static void Write(const std::queue<T>& t, FormatterContext& context) {
		}
	};

}