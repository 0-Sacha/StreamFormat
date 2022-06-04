#pragma once

#include "../../Formatter.h"
#include <list>

namespace EngineCore::FMT {

	template<typename T, typename FormatContext>
	struct FormatType<std::list<T>, FormatContext>
	{
		static void Write(const std::list<T>& t, FormatContext& context) {
			FormatType<ForwardAsSTDEnumerable<std::list<T>>, FormatContext>::Write(t, context);
		}
	};
}