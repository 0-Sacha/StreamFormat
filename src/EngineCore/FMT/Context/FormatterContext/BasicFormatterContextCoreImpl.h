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
	template<typename ParentCharFormat>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(BasicFormatterContext<ParentCharFormat, CharBuffer>& parentContext)
		: Base()
		, m_BufferOut(parentContext.BufferOut())
		, m_TextPropertiesParser(*this, parentContext)
	{}

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::~BasicFormatterContext() {}

	template<typename CharFormat, typename CharBuffer>
	void BasicFormatterContext<CharFormat, CharBuffer>::RunImpl()
	{
		while (!m_Format.IsEnd()) {

			WriteUntilNextParameterOr();

			if (m_Format.IsEqualTo('{'))
				if (!Parse())
					m_BufferOut.PushBack('{');
		}
	}

	template<typename CharFormat, typename CharBuffer>
	template<typename NewCharFormat, typename ...Args>
	void BasicFormatterContext<CharFormat, CharBuffer>::SubContext(const std::basic_string_view<NewCharFormat>& formatStr, Args&& ...args)
	{
		using ContextType = BasicFormatterContext<NewCharFormat, CharBuffer>;
		auto childContextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		Detail::FormatterMemoryFormat<NewCharFormat> format(formatStr);
		
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