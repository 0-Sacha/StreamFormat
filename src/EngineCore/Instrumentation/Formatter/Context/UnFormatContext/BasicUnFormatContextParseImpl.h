#pragma once

#include "BasicUnFormatContext.h"
#include "BasicUnFormatContextCoreImpl.h"


namespace EngineCore::FMT::Context {

	template<typename T, typename CharName, typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	struct UnFormatType<StringViewNamedArgs<T, CharName>, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>>
	{
		inline static void Read(StringViewNamedArgs<T, CharName>& t, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>& context) {
			UnFormatType<Detail::GetBaseType<T>, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>>::Read(t.GetValue(), context);
		}
	};

	template<typename T, typename CharName, typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	struct UnFormatType<StringNamedArgs<T, CharName>, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>>
	{
		inline static void Read(StringNamedArgs<T, CharName>& t, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>& context) {
			UnFormatType<Detail::GetBaseType<T>, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>>::Read(t.GetValue(), context);
		}
	};

	/////---------- AAHHHHHHHHH ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParseTimer() {
		std::chrono::nanoseconds ns = std::chrono::high_resolution_clock::now() - GetAPI().GetTimeShift();
		RunType(ns);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParseDate() {
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()) + GetAPI().GetHoursShift();
		RunType(ns);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParseSetter() {
	}

}