#pragma once

#include "../../Formatter.h"
#include <array>

namespace EngineCore::FMT {

	template<std::size_t SIZE, typename T, typename FormatContext>
	struct FormatType<std::array<T, SIZE>, FormatContext>
	{
		static void Write(const std::array<T, SIZE>& t, FormatContext& context) {
			FormatType<ForwardAsSTDEnumerable<std::array<T, SIZE>>, FormatContext>::Write(t, context);
		}
	};

}