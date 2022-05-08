#pragma once

#include "../../Core/Detail.h"

#define ENGINECORE_FORMAT_DECLARED

namespace EngineCore::Instrumentation::Fmt {

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	class BasicUnFormatContext;

	template<typename T, typename UnFormatContext = BasicUnFormatContext<char, char>>
	struct UnFormatType {
		template<class K = T>
		static inline auto Read(K& t, UnFormatContext& context) {
			// ENGINECORE_IF_MSVC(static_assert(false, __FUNCSIG__));
			return false;
		}
	};

}

#define ENGINECORE_AUTO_UNFORMAT(Type, fmt, ...)	template<typename UnFormatContext>\
													struct EngineCore::Instrumentation::Fmt::UnFormatType<Type, UnFormatContext> {\
														static bool Read(Type& value, UnFormatContext& context) {\
															return context.LittleUnFormat(fmt, __VA_ARGS__);\
														}\
													};








