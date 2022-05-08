#pragma once

#include "../../Formatter.h"
#include <vector>

namespace EngineCore::Instrumentation::Fmt {

	template<typename T, typename FormatContext>
	struct FormatType<std::vector<T>, FormatContext>
	{
		static void Write(const std::vector<T>& t, FormatContext& context) {
			FormatType<ForwardAsSTDEnumerable<std::vector<T>>, FormatContext>::Write(t, context);
		}
	};

}