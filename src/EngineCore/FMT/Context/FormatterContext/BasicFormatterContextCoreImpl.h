#pragma once

#include "BasicFormatterContext.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(Detail::BasicBufferOutManager<CharBuffer>& BufferOutManager)
		: Base()
		, m_BufferOut(BufferOutManager)
		, m_TextPropertiesParser(*this)
	{}

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(Detail::BasicBufferOutManager<CharBuffer>& BufferOutManager, const Detail::TextProperties::Properties* parentContextProperties)
		: Base()
		, m_BufferOut(BufferOutManager)
		, m_TextPropertiesParser(*this, parentContextProperties)
	{}

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::~BasicFormatterContext()
	{
		m_BufferOut.EndContext();
		m_BufferOut.PushBackEndChar();
	}

	template<typename CharFormat, typename CharBuffer>
	void BasicFormatterContext<CharFormat, CharBuffer>::Terminate()
	{
		m_TextPropertiesParser.Terminate();
	}

	template<typename CharFormat, typename CharBuffer>
	template<typename NewCharFormat, typename ...Args>
    void BasicFormatterContext<CharFormat, CharBuffer>::SubContext(const Detail::BufferInProperties<NewCharFormat>& bufferInProperties, Args&& ...args)
	{
		using ContextType = BasicFormatterContext<NewCharFormat, CharBuffer>;
		auto childContextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		Detail::FMTFormatBuffer<NewCharFormat> format(bufferInProperties);
		
		// TODO : Disable because cause TextProperties to not be restore correctly
		if constexpr (false && std::is_same_v<NewCharFormat, CharFormat>)
		{
			Run(format, &childContextArgsInterface);
		}
		else
		{
			ContextType child(m_BufferOut.GetBufferOutManager(), &m_TextPropertiesParser.CurrentContexProperties);
			child.BufferOut().ReloadBuffer(m_BufferOut);
			child.Run(format, &childContextArgsInterface);
			m_BufferOut.ReloadBuffer(child.BufferOut());
		}
	}
}