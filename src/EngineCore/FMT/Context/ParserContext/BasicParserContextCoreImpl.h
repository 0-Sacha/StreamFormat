#pragma once

#include "BasicParserContext.h"

#include "BaseFormat/BaseFormat.h"
#include "BaseFormat/BaseAnsiTextColor.h"
#include "BaseFormat/BaseAnsiTextStyle.h"
#include "BaseFormat/Chrono.h"
#include "BaseFormat/BaseSTDLib.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer>
	BasicParserContext<CharFormat, CharBuffer>::BasicParserContext(const std::basic_string_view<CharFormat>& format, const std::basic_string_view<CharBuffer>& buffer, ContextArgs&& ...args)
		: Base(format, sizeof...(ContextArgs))
		, m_BufferIn(buffer)
		, m_ContextArgsInterface(std::forward<ContextArgs>(args)...)
	{
	}

	template<typename CharFormat, typename CharBuffer>
	template<typename ParentCharFormat, typename ...ParentContextArgs>
	BasicParserContext<CharFormat, CharBuffer>::BasicParserContext(const std::basic_string_view<CharFormat>& format, BasicParserContext<ParentCharFormat, CharBuffer, ParentContextArgs...>& parentContext, ContextArgs&& ...args)
		: Base(format, parentContext, sizeof...(ContextArgs))
		, m_BufferIn(parentContext)
		, m_ContextArgsInterface(std::forward<ContextArgs>(args)...)
	{}

	template<typename CharFormat, typename CharBuffer>
	BasicParserContext<CharFormat, CharBuffer>::~BasicParserContext()
	{ }

	template<typename CharFormat, typename CharBuffer>
	void BasicParserContext<CharFormat, CharBuffer>::Run() {
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

	template<typename CharFormat, typename CharBuffer>
	template<typename NewCharFormat, typename ...Args>
	void BasicParserContext<CharFormat, CharBuffer>::SubContext(const std::basic_string_view<NewCharFormat>& format, Args&& ...args) {
		BasicParserContext<NewCharFormat, CharBuffer> child(format, *this, std::forward<Args>(args)...);
		child.Run();
	}

}