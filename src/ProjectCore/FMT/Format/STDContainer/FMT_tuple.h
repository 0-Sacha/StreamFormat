#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/FormatterType.h"
#include <tuple>
#include <utility>

namespace ProjectCore::FMT::TupleDetail {

	template<uint32_t N, typename ...Args> using NthTypeOf =
		typename std::tuple_element<N, std::tuple<Args...>>::type;

	template<uint32_t N, typename ...Args>
	constexpr NthTypeOf<N, Args...>& Get(Args&& ...args) {
		std::tuple<Args...> tuple(args...);
		return std::get<N>(tuple);
	}

	template<typename FormatterContext>
	static void TupleFormatRec(FormatterContext& context) { }

	template<typename T, typename FormatterContext>
	static void TupleFormatRec(FormatterContext& context, const T& t) {
		context.WriteType(t);
	}

	template<typename T, typename FormatterContext, typename ...Args>
	static void TupleFormatRec(FormatterContext& context, const T& t, Args&& ...args) {
		context.WriteType(t);
		context.BufferOut().PushBack(',');
		context.BufferOut().PushBack(' ');
		TupleFormatRec(context, args...);
	}

}

namespace ProjectCore::FMT {

	template<typename ...T, typename FormatterContext>
	struct FormatterType<std::tuple<T...>, FormatterContext>
	{
		static void Format(const std::tuple<T...>& t, FormatterContext& context) {
			context.BufferOut().PushBack('<');
			std::apply([&context](auto&&... args) { TupleDetail::TupleFormatRec(context, args...); }, t);
			context.BufferOut().PushBack('>');
		}
	};



	template<typename T1, typename T2, typename FormatterContext>
	struct FormatterType<std::pair<T1, T2>, FormatterContext>
	{
		static void Format(const std::pair<T1, T2>& t, FormatterContext& context) {
			context.BufferOut().PushBack('<');
			context.WriteType(t.first);
			context.BufferOut().PushBack(':');
			context.WriteType(t.second);
			context.BufferOut().PushBack('>');
		}
	};
}
