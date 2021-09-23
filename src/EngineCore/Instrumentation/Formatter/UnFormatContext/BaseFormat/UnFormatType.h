#pragma once

#include "../../Core/Detail.h"

#define ENGINE_CORE_FORMAT_DECLARED

namespace EngineCore::Fmt {

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	class BasicUnFormatContext;

	template<typename T, typename UnFormatContext = BasicUnFormatContext<char, char>>
	struct UnFormatType {
		template<class K = T>
		static inline auto Read(K& t, UnFormatContext& context) {
			// ENGINE_CORE_IF_MSVC(static_assert(false, __FUNCSIG__));
			return false;
		}
	};

}

#define ENGINE_CORE_AUTO_UNFORMAT(Type, fmt, ...)	template<typename UnFormatContext>\
													struct EngineCore::Fmt::UnFormatType<Type, UnFormatContext> {\
														static bool Read(Type& value, UnFormatContext& context) {\
															return context.LittleUnFormat(fmt, __VA_ARGS__);\
														}\
													};\
												}








