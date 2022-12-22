#pragma once

#include "BasicParserContext.h"
#include "BasicParserContextCoreImpl.h"


namespace EngineCore::FMT {

	template<typename T, typename CharName>
	struct ParserType<StringViewNamedArgs<T, CharName>>
	{
		template <typename CharFormat, typename CharBuffer, typename ...ContextArgs>
		inline static void Read(StringViewNamedArgs<T, CharName>& t, BasicParserContext<CharFormat, CharBuffer, ContextArgs...>& context) {
			ParserType<Detail::GetBaseType<T>, BasicParserContext<CharFormat, CharBuffer, ContextArgs...>>::Read(t.GetValue(), context);
		}
	};

	template<typename T, typename CharName>
	struct ParserType<StringNamedArgs<T, CharName>>
	{
		template <typename CharFormat, typename CharBuffer, typename ...ContextArgs>
		inline static void Read(StringNamedArgs<T, CharName>& t, BasicParserContext<CharFormat, CharBuffer, ContextArgs...>& context) {
			ParserType<Detail::GetBaseType<T>, BasicParserContext<CharFormat, CharBuffer, ContextArgs...>>::Read(t.GetValue(), context);
		}
	};
}

namespace EngineCore::FMT::Context {
	/////---------- AAHHHHHHHHH ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicParserContext<CharFormat, CharBuffer, ContextArgs...>::ParseTimer() {
		std::chrono::nanoseconds ns = std::chrono::high_resolution_clock::now() - GetAPI().GetTimeShift();
		RunType(ns);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicParserContext<CharFormat, CharBuffer, ContextArgs...>::ParseDate() {
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()) + GetAPI().GetHoursShift();
		RunType(ns);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicParserContext<CharFormat, CharBuffer, ContextArgs...>::ParseSetter() {
	}

}