#pragma once

#include "BasicParserContext.h"

#include "BaseFormat/BaseFormat.h"
#include "BaseFormat/BaseAnsiTextColor.h"
#include "BaseFormat/BaseAnsiTextStyle.h"
#include "BaseFormat/Chrono.h"
#include "BaseFormat/BaseSTDLib.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicParserContext<CharFormat, CharBuffer, ContextArgs...>::BasicParserContext(const std::basic_string_view<CharFormat>& format, const std::basic_string_view<CharBuffer>& buffer, ContextArgs&& ...args)
		: Base(format, sizeof...(ContextArgs))
		, m_BufferIn(buffer)
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
	{
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename ParentCharFormat, typename ...ParentContextArgs>
	BasicParserContext<CharFormat, CharBuffer, ContextArgs...>::BasicParserContext(const std::basic_string_view<CharFormat>& format, BasicParserContext<ParentCharFormat, CharBuffer, ParentContextArgs...>& parentContext, ContextArgs&& ...args)
		: Base(format, parentContext, sizeof...(ContextArgs))
		, m_BufferIn(parentContext)
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
	{}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicParserContext<CharFormat, CharBuffer, ContextArgs...>::~BasicParserContext()
	{ }

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicParserContext<CharFormat, CharBuffer, ContextArgs...>::Run() {
		while (!m_Format.IsEnd()) {

			if (CheckUntilNextParameter())
			{
				if (m_Format.IsEqualTo('{'))
					if (Parse() == false)
						throw Detail::FormatParseError();
			}
			else if (!Check())
				throw Detail::FormatParseError();
		}
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename NewCharFormat, typename ...Args>
	void BasicParserContext<CharFormat, CharBuffer, ContextArgs...>::SubContext(const std::basic_string_view<NewCharFormat>& format, Args&& ...args) {
		BasicParserContext<NewCharFormat, CharBuffer, Args...> child(format, *this, std::forward<Args>(args)...);
		child.Run();
	}

}