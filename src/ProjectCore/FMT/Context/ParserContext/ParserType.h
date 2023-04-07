#pragma once

#include "ProjectCore/FMT/Detail/Detail.h"

#define PROJECTCORE_PARSER_DECLARED
namespace ProjectCore::FMT {

	template<typename T, typename ParserContext = Context::BasicParserContext<char, char>>
	struct ParserType {
		static inline auto Read(T&, ParserContext&) {
			// PROJECTCORE_IF_MSVC(static_assert(false, __FUNCSIG__));
			return false;
		}
	};

}

#define PROJECTCORE_AUTO_PARSER(Type, fmt, ...)	template<typename ParserContext>\
												struct ProjectCore::FMT::ParserType<Type, ParserContext> {\
													static bool Read(Type& value, ParserContext& context) {\
														return context.SubContext(fmt, __VA_ARGS__);\
													}\
												};
