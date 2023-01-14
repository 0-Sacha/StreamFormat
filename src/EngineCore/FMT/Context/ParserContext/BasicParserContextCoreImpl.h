#pragma once

#include "BasicParserContext.h"

#include "BaseFormat/BaseFormat.h"
#include "BaseFormat/BaseAnsiTextColor.h"
#include "BaseFormat/BaseAnsiTextStyle.h"
#include "BaseFormat/Chrono.h"
#include "BaseFormat/BaseSTDLib.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer>
	BasicParserContext<CharFormat, CharBuffer>::BasicParserContext(const std::basic_string_view<CharFormat>& format, const std::basic_string_view<CharBuffer>& buffer, Detail::BasicContextArgsTupleInterface<M_Type>* argsInterface)
		: Base(format, static_cast<ContextArgsInterface*>(argsInterface))
		, m_BufferIn(buffer)
	{
		argsInterface->SetContext(this);
	}

	template<typename CharFormat, typename CharBuffer>
	template<typename ParentCharFormat>
	BasicParserContext<CharFormat, CharBuffer>::BasicParserContext(const std::basic_string_view<CharFormat>& format, BasicParserContext<ParentCharFormat, CharBuffer>& parentContext, Detail::BasicContextArgsTupleInterface<M_Type>* argsInterface)
		: Base(format, static_cast<ContextArgsInterface*>(argsInterface))
		, m_BufferIn(parentContext.BufferIn())
	{
		argsInterface->SetContext(this);
	}

	template<typename CharFormat, typename CharBuffer>
	BasicParserContext<CharFormat, CharBuffer>::~BasicParserContext() {}

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
		using ContextType = BasicParserContext<NewCharFormat, CharBuffer>;
		auto childContextArgsInterface = Detail::ParserContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		ContextType child(format, *this, &childContextArgsInterface);
		child.Run();
	}

}