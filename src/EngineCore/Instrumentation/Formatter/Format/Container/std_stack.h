#pragma once

#include "Formatter/Context/FormatContext/Utils/FormatType.h"
#include <stack>

namespace EngineCore::FMT {

	template<typename T, typename FormatContext>
	struct FormatType<std::stack<T>, FormatContext>
	{
		static void Write(const std::stack<T>& t, FormatContext& context) {

		}
	};

}