#pragma once

#include "../../Formatter.h"
#include <deque>

namespace EngineCore::FMT {

	template<typename T, typename FormatContext>
	struct FormatType<std::deque<T>, FormatContext>
	{
		static void Write(const std::deque<T>& t, FormatContext& context) {
			FormatType<ForwardAsSTDEnumerable<std::deque<T>>, FormatContext>::Write(t, context);
		}
	};

}