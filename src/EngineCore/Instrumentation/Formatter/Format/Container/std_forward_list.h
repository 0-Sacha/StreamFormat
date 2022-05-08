#pragma once

#include "../../Formatter.h"
#include <forward_list>

namespace EngineCore::Instrumentation::Fmt {
	template<typename T, typename FormatContext>
	struct FormatType<std::forward_list<T>, FormatContext>
	{
		static void Write(const std::forward_list<T>& t, FormatContext& context) {
			FormatType<ForwardAsSTDEnumerable<std::forward_list<T>>, FormatContext>::Write(t, context);
		}
	};
}