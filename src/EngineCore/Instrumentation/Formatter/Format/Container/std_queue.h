#pragma once

#include "CPPTools/Formatter/Formatter.h"
#include <queue>

namespace EngineCore::Fmt {

	template<typename T, typename FormatContext>
	struct FormatType<std::queue<T>, FormatContext>
	{
		static void Write(const std::queue<T>& t, FormatContext& context) {
		}
	};

}