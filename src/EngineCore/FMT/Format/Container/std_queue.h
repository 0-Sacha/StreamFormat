#pragma once

#include "FMT/Context/FormatContext/Utils/FormatType.h"
#include <queue>

namespace EngineCore::FMT {

	template<typename T, typename FormatContext>
	struct FormatType<std::queue<T>, FormatContext>
	{
		static void Write(const std::queue<T>& t, FormatContext& context) {
		}
	};

}