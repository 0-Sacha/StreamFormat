#pragma once

#include "../../Formatter.h"
#include <stack>

namespace EngineCore::Instrumentation::FMT {

	template<typename T, typename FormatContext>
	struct FormatType<std::stack<T>, FormatContext>
	{
		static void Write(const std::stack<T>& t, FormatContext& context) {

		}
	};

}