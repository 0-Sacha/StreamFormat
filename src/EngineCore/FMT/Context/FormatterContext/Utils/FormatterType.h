#pragma once

#include "FMT/Detail/Detail.h"
#include "EngineCore/Detail/MapMacro.h"

#define ENGINECORE_FORMATTER_DECLARED
namespace EngineCore::FMT {

	template<typename CharFormat, typename CharBuffer, typename ...Args>
	class BasicFormatterContext;

	template<typename T, typename FormatterContext = BasicFormatterContext<char, char>>
	struct FormatterType {
		static inline void Write(const T& t, FormatterContext& context) {
			context.SubContext("({C:red}FMT unknow type: {}{C})", typeid(T).name());
			throw Detail::FormatShouldNotEndHere{};
		}
	};
}


#define ENGINECORE_INTERNAL_ADDVALUE(x) value.x
#define ENGINECORE_AUTO_FORMATTER(Type, fmt, ...)	template<typename FormatterContext>\
													struct EngineCore::FMT::FormatterType<Type, FormatterContext> {\
														static void Write(const Type& value, FormatterContext& context) {\
															context.SubContext(fmt, FOR_EACH(ENGINECORE_INTERNAL_ADDVALUE, __VA_ARGS__));\
														}\
													};
