#pragma once

#include "FMT/Detail/Detail.h"
#include "EngineCore/Tools/MapMacro.h"

#define ENGINECORE_FORMATTER_DECLARED
namespace EngineCore::FMT {

	template<typename T, typename FormatterContext = Context::BasicFormatterContext<char, char>>
	struct FormatterType {
		static inline void Write(const T& t, FormatterContext& context) {
			context.SubContext("({C:red}FMT unknow type: {}{C})", typeid(T).name());
			throw Detail::FMTShouldNotEndHere{};
		}
	};
}


#define ENGINECORE_INTERNAL_ADDVALUE(x) value.x
#define ENGINECORE_AUTO_FORMATTER_X(Type, fmt, ...)	template<typename FormatterContext>\
													struct EngineCore::FMT::FormatterType<Type, FormatterContext> {\
														static void Write(const Type& value, FormatterContext& context) {\
															context.SubContext(fmt, FOR_EACH(ENGINECORE_INTERNAL_ADDVALUE, __VA_ARGS__));\
														}\
													};

#define ENGINECORE_AUTO_FORMATTER(Type, fmt, ...)	template<typename FormatterContext>\
													struct EngineCore::FMT::FormatterType<Type, FormatterContext> {\
														static void Write(const Type& value, FormatterContext& context) {\
															context.SubContext(fmt, __VA_ARGS__);\
														}\
													};
