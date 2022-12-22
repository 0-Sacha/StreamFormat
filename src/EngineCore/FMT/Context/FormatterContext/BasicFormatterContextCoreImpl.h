#pragma once

#include "BasicFormatterContext.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicFormatterContext<CharFormat, CharBuffer, ContextArgs...>::BasicFormatterContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, ContextArgs&& ...args)
		: Base(format, sizeof...(ContextArgs))
		, m_BufferOut(buffer, bufferSize)
		, m_AnsiManager(*this)
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
	{}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicFormatterContext<CharFormat, CharBuffer, ContextArgs...>::BasicFormatterContext([[maybe_unused]] const bool bufferIsAutoResize, const std::basic_string_view<CharFormat>& format, ContextArgs &&...args)
		: Base(format, sizeof...(ContextArgs))
		, m_BufferOut()
		, m_AnsiManager(*this)
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
	{}

	// Used for SubContext | Clone
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename ParentCharFormat, typename ...ParentContextArgs>
	BasicFormatterContext<CharFormat, CharBuffer, ContextArgs...>::BasicFormatterContext(const std::basic_string_view<CharFormat>& format, BasicFormatterContext<ParentCharFormat, CharBuffer, ParentContextArgs...>& parentContext, ContextArgs&& ...args)
		: Base(format, parentContext, sizeof...(ContextArgs))
		, m_BufferOut(parentContext.BufferOut())
		, m_AnsiManager(*this, parentContext.GetAnsiManager())
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
	{}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicFormatterContext<CharFormat, CharBuffer, ContextArgs...>::~BasicFormatterContext() {}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatterContext<CharFormat, CharBuffer, ContextArgs...>::Run() {
		while (!m_Format.IsEnd()) {

			WriteUntilNextParameterOr();

			if (m_Format.IsEqualTo('{'))
				if (!Parse())
					m_BufferOut.PushBack('{');
		}

		m_AnsiManager.Kill();
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename NewCharFormat, typename ...Args>
	void BasicFormatterContext<CharFormat, CharBuffer, ContextArgs...>::SubContext(const std::basic_string_view<NewCharFormat>& format, Args&& ...args) {
		BasicFormatterContext<NewCharFormat, CharBuffer, Args...> child(format, *this, std::forward<Args>(args)...);
		child.Run();
	}
}