#pragma once

#include "BasicParserContext.h"

namespace EngineCore::FMT::Context
{
	template<typename CharFormat, typename CharBuffer>
	BasicParserContext<CharFormat, CharBuffer>::BasicParserContext(const CharBuffer* const buffer, const std::size_t size)
		: Base()
		, m_BufferIn(buffer, size)
	{}
	
	template<typename CharFormat, typename CharBuffer>
	template <std::size_t SIZE>
	BasicParserContext<CharFormat, CharBuffer>::BasicParserContext(const CharBuffer (&buffer)[SIZE])
		: Base()
		, m_BufferIn(buffer, SIZE)
	{}

	template<typename CharFormat, typename CharBuffer>
	BasicParserContext<CharFormat, CharBuffer>::BasicParserContext(const std::basic_string_view<CharBuffer>& buffer)
		: Base()
		, m_BufferIn(buffer.data(), buffer.size())
	{}

	template<typename CharFormat, typename CharBuffer>
	BasicParserContext<CharFormat, CharBuffer>::~BasicParserContext()
	{}

	template<typename CharFormat, typename CharBuffer>
	void BasicParserContext<CharFormat, CharBuffer>::Terminate()
	{}

	template<typename CharFormat, typename CharBuffer>
	template<typename NewCharFormat, typename ...Args>
	void BasicParserContext<CharFormat, CharBuffer>::SubContext(const Detail::BufferInProperties<NewCharFormat>& bufferInProperties, Args&& ...args) {
		using ContextType = BasicParserContext<NewCharFormat, CharBuffer>;
		auto childContextArgsInterface = Detail::ParserContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		Detail::FMTFormatBuffer<NewCharFormat> format(bufferInProperties);
		
		// TODO : Disable because cause TextProperties to not be restore correctly
		if constexpr (false && std::is_same_v<NewCharFormat, CharFormat>)
		{
			Run(format, &childContextArgsInterface);
		}
		else
		{
			ContextType child(m_BufferIn.GetBuffer(), m_BufferIn.GetBufferSize());
			child.BufferIn().ReloadBuffer(m_BufferIn);
			child.Run(format, &childContextArgsInterface);
			m_BufferIn.ReloadBuffer(child.BufferIn());
		}
	}
}
