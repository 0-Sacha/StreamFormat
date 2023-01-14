#pragma once

#include "FMT/Context/FormatterContext/Utils/FormatterType.h"

#include <unordered_map>
#include "std_tuple.h"

namespace EngineCore::FMT {

	template<typename T1, typename T2, typename FormatterContext>
	struct FormatterType<std::unordered_map<T1, T2>, FormatterContext>
	{
		static void Write(const std::unordered_map<T1, T2>& t, FormatterContext& context) {
			FormatterType<ForwardAsSTDEnumerable<std::unordered_map<T1, T2>>, FormatterContext>::Write(t, context);
		}
	};

	template<typename T1, typename T2, typename FormatterContext>
	struct FormatterType<std::unordered_multimap<T1, T2>, FormatterContext>
	{
		static void Write(const std::unordered_multimap<T1, T2>& t, FormatterContext& context) {
			FormatterType<ForwardAsSTDEnumerable<std::unordered_multimap<T1, T2>>, FormatterContext>::Write(t, context);
		}
	};
}