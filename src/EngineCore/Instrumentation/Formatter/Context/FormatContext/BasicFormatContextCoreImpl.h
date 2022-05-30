#pragma once

#include "BasicFormatContext.h"
#include "BasicFormatContextCoreImpl.h"

#include "BaseFormat\BaseAnsiTextColor.h"
#include "BaseFormat\BaseAnsiTextFront.h"
#include "BaseFormat\BaseAnsiTextStyle.h"
#include "BaseFormat\BaseFormat.h"
#include "BaseFormat\BaseSTDLib.h"
#include "BaseFormat\Chrono.h"

namespace EngineCore::Instrumentation::FMT::Context {

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::BasicFormatContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, ContextArgs&& ...args)
		: Base(format, sizeof...(ContextArgs))
		, m_BufferOut(buffer, bufferSize)
		, m_AnsiManager(*this)
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
	{}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::BasicFormatContext([[maybe_unused]] const bool bufferIsAutoResize, const std::basic_string_view<CharFormat>& format, ContextArgs &&...args)
		: Base(format, sizeof...(ContextArgs))
		, m_BufferOut()
		, m_AnsiManager(*this)
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
	{}

	// Used for LittleFormat | Clone
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename ParentCharFormat, typename ...ParentContextArgs>
	BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::BasicFormatContext(const std::basic_string_view<CharFormat>& format, BasicFormatContext<ParentCharFormat, CharBuffer, ParentContextArgs...>& parentContext, ContextArgs&& ...args)
		: Base(format, parentContext, sizeof...(ContextArgs))
		, m_BufferOut(parentContext.BufferOut())
		, m_AnsiManager(*this, parentContext.GetAnsiManager())
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
	{}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::~BasicFormatContext()
	{
		m_AnsiManager.Reload(Detail::AnsiTextData{});
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::Run() {
		while (!m_Format.IsEnd()) {

			WriteUntilNextParameter();

			if (m_Format.IsEqualTo('{'))
				if (!Parse())
					m_BufferOut.PushBack('{');
		}
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename NewCharFormat, typename ...Args>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::LittleFormat(const std::basic_string_view<NewCharFormat>& format, Args&& ...args) {
		BasicFormatContext<NewCharFormat, CharBuffer, Args...> child(format, *this, std::forward<Args>(args)...);
		child.Run();
	}
}