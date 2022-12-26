#pragma once

#include "FMT/Detail/Detail.h"

#define ENGINECORE_PARSER_DECLARED
namespace EngineCore::FMT {

	template<typename CharFormat, typename CharBuffer>
	class BasicParserContext;

	template<typename T, typename ParserContext = BasicParserContext<char, char>>
	struct ParserType {
		template<class K = T>
		static inline auto Read(K& t, ParserContext& context) {
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








