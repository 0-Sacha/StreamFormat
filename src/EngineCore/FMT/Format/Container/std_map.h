#pragma once

#include "FMT/Context/FormatterContext/Utils/FormatterType.h"
#include <map>

#include "std_tuple.h"

namespace EngineCore::FMT {
	template<typename T1, typename T2, typename FormatterContext>
	struct FormatterType<std::map<T1, T2>, FormatterContext>
	{
		static void Write(const std::map<T1, T2>& t, FormatterContext& context) {
			FormatterType<ForwardAsSTDEnumerable<std::map<T1, T2>>, FormatterContext>::Write(t, context);
		}
	};

	template<typename T1, typename T2, typename FormatterContext>
	struct FormatterType<std::multimap<T1, T2>, FormatterContext>
	{
		static void Write(const std::multimap<T1, T2>& t, FormatterContext& context) {
			FormatterType<ForwardAsSTDEnumerable<std::multimap<T1, T2>>, FormatterContext>::Write(t, context);
		}
	};
}