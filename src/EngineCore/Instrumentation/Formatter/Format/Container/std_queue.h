#pragma once

#include "../../Formatter.h"
#include <queue>

namespace EngineCore::Instrumentation::Fmt {

	template<typename T, typename FormatContext>
	struct FormatType<std::queue<T>, FormatContext>
	{
		static void Write(const std::queue<T>& t, FormatContext& context) {
		}
	};

}