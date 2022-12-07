#pragma once

#include "FMT/Context/FormatContext/Utils/FormatType.h"
#include <vector>

namespace EngineCore::FMT {

	template<typename T, typename FormatContext>
	struct FormatType<std::vector<T>, FormatContext>
	{
		static void Write(const std::vector<T>& t, FormatContext& context) {
			FormatType<ForwardAsSTDEnumerable<std::vector<T>>, FormatContext>::Write(t, context);
		}
	};

}