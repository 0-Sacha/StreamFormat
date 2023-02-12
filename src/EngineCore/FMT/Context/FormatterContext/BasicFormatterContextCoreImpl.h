#pragma once

#include "BasicFormatterContext.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(Detail::BasicBufferManager<CharBuffer>& bufferManager)
		: Base()
		, m_BufferOut(bufferManager)
		, m_TextPropertiesParser(*this)
	{}

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(Detail::BasicBufferManager<CharBuffer>& bufferManager, const Detail::TextProperties::Properties* parentContextProperties)
		: Base()
		, m_BufferOut(bufferManager)
		, m_TextPropertiesParser(*this, parentContextProperties)
	{}

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::~BasicFormatterContext()
	{
		m_BufferOut.PushEndChar();
		m_BufferOut.GetBufferManager().EndContext(m_BufferOut.GetBufferCurrentSize() - 1);
	}

	template<typename CharFormat, typename CharBuffer>
	template<typename NewCharFormat, typename ...Args>
    void BasicFormatterContext<CharFormat, CharBuffer>::SubContextFormat(const NewCharFormat* const formatStr, const std::size_t formatStrSize, Args&& ...args)
	{
		using ContextType = BasicFormatterContext<NewCharFormat, CharBuffer>;
		auto childContextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		Detail::FMTFormatBuffer<NewCharFormat> format(formatStr, formatStrSize);
		
		if constexpr (std::is_same_v<NewCharFormat, CharFormat>)
		{
			Run(format, &childContextArgsInterface);
		}
		else
		{
			ContextType child(m_BufferOut.GetBufferManager(), &m_TextPropertiesParser);
			child.BufferOut().SetBufferCurrentPos(m_BufferOut.GetBufferCurrentPos());
			child.Run(format, &childContextArgsInterface);
			m_BufferOut.SetBufferCurrentPos(child.BufferOut().GetBufferCurrentPos());
		}
	}
}