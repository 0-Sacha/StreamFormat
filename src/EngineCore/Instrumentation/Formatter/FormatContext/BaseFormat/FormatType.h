#pragma once

#include "EngineCore/Instrumentation/Formatter/Core/Detail/Detail.h"

#define ENGINECORE_FORMAT_DECLARED
namespace EngineCore::Instrumentation::FMT {

	template<typename CharFormat, typename CharBuffer, typename ...Args>
	class BasicFormatContext;

	template<typename T, typename FormatContext = BasicFormatContext<char, char>>
	struct FormatType {
		template<class K = T>
		static inline void Write(const K& t, FormatContext& context) {
			// ENGINECORE_IF_MSVC(static_assert(false, __FUNCSIG__));
		}
	};
}

#define ENGINECORE_AUTO_FORMAT(Type, fmt, ...)	template<typename FormatContext>\
													struct EngineCore::Instrumentation::FMT::FormatType<Type, FormatContext> {\
														static void Write(const Type& value, FormatContext& context) {\
															context.LittleFormat(fmt, __VA_ARGS__);\
														}\
													};\
												}



												