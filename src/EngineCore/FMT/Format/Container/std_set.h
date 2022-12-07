#pragma once

#include "FMT/Context/FormatContext/Utils/FormatType.h"
#include <set>

namespace EngineCore::FMT {
	template<typename T, typename FormatContext>
	struct FormatType<std::set<T>, FormatContext>
	{
		static void Write(const std::set<T>& t, FormatContext& context) {
			FormatType<ForwardAsSTDEnumerable<std::set<T>>, FormatContext>::Write(t, context);
		}
	};

	template<typename T, typename FormatContext>
	struct FormatType<std::multiset<T>, FormatContext>
	{
		static void Write(const std::multiset<T>& t, FormatContext& context) {
			FormatType<ForwardAsSTDEnumerable<std::multiset<T>>, FormatContext>::Write(t, context);
		}
	};
}