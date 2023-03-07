#pragma once

#include "BasicFormatterContext.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(Detail::BasicBufferOutManager<CharBuffer>& BufferOutManager, Detail::IFormatterTextPropertiesExecutor<BufferOutType>& textPropertiesExecutor, const Detail::TextProperties::Properties* parentContextProperties)
		: Base(textPropertiesExecutor, parentContextProperties)
		, m_BufferOut(BufferOutManager)
	{
		textPropertiesExecutor.SetBuffer(&m_BufferOut);
	}

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::~BasicFormatterContext()
	{
		m_BufferOut.EndContext();
		m_BufferOut.PushBackEndChar();
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
			Detail::IFormatterTextPropertiesExecutor<BufferOutType>& cm_TextPropertiesExecutor = reinterpret_cast<Detail::IFormatterTextPropertiesExecutor<BufferOutType>&>(m_TextPropertiesParser.GetTextPropertiesExecutor());

			ContextType child(m_BufferOut.GetBufferOutManager(), cm_TextPropertiesExecutor, &m_TextPropertiesParser.GetCurrentContextProperties());
			child.BufferOut().ReloadBuffer(m_BufferOut);
			child.Run(format, &childContextArgsInterface);
			m_BufferOut.ReloadBuffer(child.BufferOut());
			cm_TextPropertiesExecutor.SetBuffer(&m_BufferOut);
		}
	}
}