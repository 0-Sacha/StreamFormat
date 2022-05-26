#pragma once

#include "BasicFormatContext.h"

#include "BaseFormat/BaseFormat.h"
#include "BaseFormat/BaseAnsiTextColor.h"
#include "BaseFormat/BaseAnsiTextStyle.h"
#include "BaseFormat/BaseAnsiTextFront.h"
#include "BaseFormat/Chrono.h"
#include "BaseFormat/BaseSTDLib.h"

namespace EngineCore::Instrumentation::FMT {

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::BasicFormatContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, ContextArgs&& ...args)
		: m_BufferOut(buffer, bufferSize)
		, m_Format(format)
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
		, m_ValuesIdx()
	{
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::BasicFormatContext(const bool bufferIsAutoResize, const std::basic_string_view<CharFormat>& format, ContextArgs &&...args)
		: m_BufferOut()
		, m_Format(format)
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
		, m_ValuesIdx()
	{
	}

	// Used for LittleFormat | Clone
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename ParentCharFormat, typename ...ParentContextArgs>
	BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::BasicFormatContext(const std::basic_string_view<CharFormat>& format, BasicFormatContext<ParentCharFormat, CharBuffer, ParentContextArgs...>& parentContext, ContextArgs&& ...args)
		: m_BufferOut(parentContext.BufferOut())
		, m_Format(format)
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
		, m_ValuesIdx()
	{
		m_FormatData.Clone(parentContext.GetFormatData());
		m_AnsiTextCurrentColor	= parentContext.GetAnsiTextCurrentColor();
		m_AnsiStyle	= parentContext.GetAnsiStyle();
	}


	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::~BasicFormatContext()
	{
		m_AnsiManager.Reload(Detail::AnsiData{});
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::Run() {
		while (!m_Format.IsEnd()) {

			WriteUntilNextParameter();

			if (m_Format.IsEqualTo('{'))
				if (!ParameterParse())
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