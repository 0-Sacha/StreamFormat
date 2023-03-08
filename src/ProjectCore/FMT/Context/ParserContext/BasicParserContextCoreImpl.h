#pragma once

#include "BasicParserContext.h"

namespace ProjectCore::FMT::Context
{
	template<typename CharFormat, typename CharBuffer>
	BasicParserContext<CharFormat, CharBuffer>::BasicParserContext(Detail::BufferInProperties<CharBuffer> bufferProperties, Detail::IParserTextPropertiesExecutor<BufferInType>& textPropertiesExecutor, const Detail::TextProperties::Properties* parentContextProperties)
		: Base(textPropertiesExecutor, parentContextProperties)
		, m_BufferIn(bufferProperties)
	{
		textPropertiesExecutor.SetBuffer(m_BufferIn);
	}
	
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
			Detail::IParserTextPropertiesExecutor<BufferInType>& cm_TextPropertiesExecutor = reinterpret_cast<Detail::IParserTextPropertiesExecutor<BufferInType>&>(m_TextPropertiesParser.GetTextPropertiesExecutor());;

			Detail::BufferInProperties<CharBuffer> properties(m_BufferIn.GetBuffer(), m_BufferIn.GetBufferSize());
			ContextType child(properties, cm_TextPropertiesExecutor, &m_TextPropertiesParser.GetCurrentContextProperties());
			child.BufferIn().ReloadBuffer(m_BufferIn);
			child.Run(format, &childContextArgsInterface);
			m_BufferIn.ReloadBuffer(child.BufferIn());

			cm_TextPropertiesExecutor.SetBuffer(&m_BufferIn);
		}
	}
}
