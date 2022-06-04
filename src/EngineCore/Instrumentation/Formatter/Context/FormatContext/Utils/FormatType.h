#pragma once

#include "EngineCore/Instrumentation/Formatter/Core/Detail/Detail.h"

#define ENGINECORE_FORMAT_DECLARED
namespace EngineCore::FMT {

	template<typename CharFormat, typename CharBuffer, typename ...Args>
	class BasicFormatContext;

	template<typename T, typename FormatContext = BasicFormatContext<char, char>>
	struct FormatType {
		template<class K = T>
		static inline void Write(const K& t, FormatContext& context) {
			throw Detail::FormatShouldNotEndHere{};
		}
	};
}

#define ENGINECORE_AUTO_FORMAT(Type, fmt, ...)	template<typename FormatContext>\
													struct EngineCore::FMT::FormatType<Type, FormatContext> {\
														static void Write(const Type& value, FormatContext& context) {\
															context.LittleFormat(fmt, __VA_ARGS__);\
														}\
													};\
												}
