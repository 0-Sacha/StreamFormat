#pragma once

#include "BasicFormatterContext.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(const std::basic_string_view<CharFormat>& format, Detail::BasicBufferManager<CharBuffer>& bufferManager, Detail::BasicContextArgsTupleInterface<M_Type>* argsInterface)
		: Base(format, static_cast<ContextArgsInterface*>(argsInterface))
		, m_BufferOut(bufferManager)
		, m_TextPropertiesParser(*this)
	{
		argsInterface->SetContext(this);
	}

	// Used for SubContext | Clone
	template<typename CharFormat, typename CharBuffer>
	template<typename ParentCharFormat>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(const std::basic_string_view<CharFormat>& format, BasicFormatterContext<ParentCharFormat, CharBuffer>& parentContext, Detail::BasicContextArgsTupleInterface<M_Type>* argsInterface)
		: Base(format, static_cast<ContextArgsInterface*>(argsInterface))
		, m_BufferOut(parentContext.BufferOut())
		, m_TextPropertiesParser(*this, parentContext)
	{
		argsInterface->SetContext(this);
	}

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::~BasicFormatterContext() {}

	template<typename CharFormat, typename CharBuffer>
	void BasicFormatterContext<CharFormat, CharBuffer>::Run() {
		while (!m_Format.IsEnd()) {

			WriteUntilNextParameterOr();

			if (m_Format.IsEqualTo('{'))
				if (!Parse())
					m_BufferOut.PushBack('{');
		}
	}

	template<typename CharFormat, typename CharBuffer>
	template<typename NewCharFormat, typename ...Args>
	void BasicFormatterContext<CharFormat, CharBuffer>::SubContext(const std::basic_string_view<NewCharFormat>& format, Args&& ...args) {
		using ContextType = BasicFormatterContext<NewCharFormat, CharBuffer>;
		auto childContextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		ContextType child(format, *this, &childContextArgsInterface);
		child.Run();
	}
}