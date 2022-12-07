#pragma once

#include "FMT/Context/FormatContext/Utils/FormatType.h"
#include <forward_list>

namespace EngineCore::FMT {
	template<typename T, typename FormatContext>
	struct FormatType<std::forward_list<T>, FormatContext>
	{
		static void Write(const std::forward_list<T>& t, FormatContext& context) {
			FormatType<ForwardAsSTDEnumerable<std::forward_list<T>>, FormatContext>::Write(t, context);
		}
	};
}