#pragma once

#include "EngineCore/FMT/Detail/Detail.h"

#define ENGINECORE_PARSER_DECLARED
namespace EngineCore::FMT {

	template<typename T, typename ParserContext = Context::BasicParserContext<char, char>>
	struct ParserType {
		static inline auto Read(T& t, ParserContext& context) {
			// ENGINECORE_IF_MSVC(static_assert(false, __FUNCSIG__));
			return false;
		}
	};

}

#define ENGINECORE_AUTO_PARSER(Type, fmt, ...)	template<typename ParserContext>\
													struct EngineCore::FMT::ParserType<Type, ParserContext> {\
														static bool Read(Type& value, ParserContext& context) {\
															return context.SubContext(fmt, __VA_ARGS__);\
														}\
													};








