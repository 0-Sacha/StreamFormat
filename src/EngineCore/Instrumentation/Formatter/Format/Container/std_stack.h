#pragma once

#include "../../Formatter.h"
#include <stack>

namespace EngineCore::Fmt {

	template<typename T, typename FormatContext>
	struct FormatType<std::stack<T>, FormatContext>
	{
		static void Write(const std::stack<T>& t, FormatContext& context) {

		}
	};

}