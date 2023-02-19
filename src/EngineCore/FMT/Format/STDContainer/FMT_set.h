#pragma once

#include "EngineCore/FMT/Context/FormatterContext/FormatterType.h"
#include <set>

namespace EngineCore::FMT {
	template<typename T, typename FormatterContext>
	struct FormatterType<std::set<T>, FormatterContext>
	{
		static void Write(const std::set<T>& t, FormatterContext& context) {
			FormatterType<ForwardAsSTDEnumerable<std::set<T>>, FormatterContext>::Write(t, context);
		}
	};

	template<typename T, typename FormatterContext>
	struct FormatterType<std::multiset<T>, FormatterContext>
	{
		static void Write(const std::multiset<T>& t, FormatterContext& context) {
			FormatterType<ForwardAsSTDEnumerable<std::multiset<T>>, FormatterContext>::Write(t, context);
		}
	};
}