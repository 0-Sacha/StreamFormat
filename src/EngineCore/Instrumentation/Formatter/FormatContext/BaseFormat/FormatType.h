#pragma once

#include "../../Core/Detail.h"

#define ENGINE_CORE_FORMAT_DECLARED
namespace EngineCore::Fmt {

	template<typename CharFormat, typename CharBuffer, typename ...Args>
	class BasicFormatContext;

	template<typename T, typename FormatContext = BasicFormatContext<char, char>>
	struct FormatType {
		template<class K = T>
		static inline void Write(const K& t, FormatContext& context) {
			// ENGINE_CORE_IF_MSVC(static_assert(false, __FUNCSIG__));
		}
	};
}

#define ENGINE_CORE_AUTO_FORMAT(Type, fmt, ...)	template<typename FormatContext>\
													struct EngineCore::Fmt::FormatType<Type, FormatContext> {\
														static void Write(const Type& value, FormatContext& context) {\
															context.LittleFormat(fmt, __VA_ARGS__);\
														}\
													};\
												}



												