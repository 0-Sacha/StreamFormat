#pragma once

#include "BasicParserContext.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer>
	BasicParserContext<CharFormat, CharBuffer>::BasicParserContext(const std::basic_string_view<CharBuffer>& buffer)
		: Base()
		, m_BufferIn(buffer)
	{}
	
	template<typename CharFormat, typename CharBuffer>
	template<typename ParentCharFormat>
	BasicParserContext<CharFormat, CharBuffer>::BasicParserContext(BasicParserContext<ParentCharFormat, CharBuffer>& parentContext)
		: Base()
		, m_BufferIn(parentContext.BufferIn())
	{}

	template<typename CharFormat, typename CharBuffer>
	BasicParserContext<CharFormat, CharBuffer>::~BasicParserContext() {}

	template<typename CharFormat, typename CharBuffer>
	template<typename NewCharFormat, typename ...Args>
	void BasicParserContext<CharFormat, CharBuffer>::SubContextFormat(const NewCharFormat* const formatStr, const std::size_t formatStrSize, Args&& ...args) {
		using ContextType = BasicParserContext<NewCharFormat, CharBuffer>;
		auto childContextArgsInterface = Detail::ParserContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		Detail::FormatterMemoryFormat<NewCharFormat> format(formatStr, formatStrSize);
		
		if constexpr (std::is_same_v<NewCharFormat, CharFormat>)
		{
			Run(format, &childContextArgsInterface);
		}
		else
		{
			ContextType child(*this);
			child.Run(format, &childContextArgsInterface);
		}
	}
}
