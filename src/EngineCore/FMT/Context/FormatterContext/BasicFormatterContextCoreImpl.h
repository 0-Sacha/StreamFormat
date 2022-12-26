#pragma once

#include "BasicFormatterContext.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, ContextArgs&& ...args)
		: Base(format, sizeof...(ContextArgs))
		, m_BufferOut(buffer, bufferSize)
		, m_AnsiManager(*this)
		, m_ContextArgsInterface(new Detail::FormatterContextArgsTupleInterface<M_Type>(std::forward<ContextArgs>(args)...))
		, m_NeedToFreeContextArgsInterface(true)
	{
		m_ContextArgsInterface->SetContext(this);
	}

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, ContextArgsInterface* argsInterface)
		: Base(format, sizeof...(ContextArgs))
		, m_BufferOut(buffer, bufferSize)
		, m_AnsiManager(*this)
		, m_ContextArgsInterface(argsInterface)
		, m_NeedToFreeContextArgsInterface(false)
	{
		m_ContextArgsInterface->SetContext(this);
	}

// Used for SubContext | Clone
	template<typename CharFormat, typename CharBuffer>
	template<typename ParentCharFormat>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(const std::basic_string_view<CharFormat>& format, BasicFormatterContext<ParentCharFormat, CharBuffer>& parentContext, ContextArgsInterface* argsInterface)
		: Base(format, sizeof...(ContextArgs))
		, m_BufferOut(parentContext.BufferOut())
		, m_AnsiManager(*this, parentContext.GetAnsiManager())
		, m_ContextArgsInterface(argsInterface)
		, m_NeedToFreeContextArgsInterface(false)
	{}

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::~BasicFormatterContext()
	{
		if (m_NeedToFreeContextArgsInterface)
			delete m_ContextArgsInterface;
	}

	template<typename CharFormat, typename CharBuffer>
	void BasicFormatterContext<CharFormat, CharBuffer>::Run() {
		while (!m_Format.IsEnd()) {

			WriteUntilNextParameterOr();

			if (m_Format.IsEqualTo('{'))
				if (!Parse())
					m_BufferOut.PushBack('{');
		}

		m_AnsiManager.Kill();
	}

	template<typename CharFormat, typename CharBuffer>
	template<typename NewCharFormat, typename ...Args>
	void BasicFormatterContext<CharFormat, CharBuffer>::SubContext(const std::basic_string_view<NewCharFormat>& format, Args&& ...args) {
		auto childContextArgsInterface = Detail::FormatterContextArgsTupleInterface<NewCharFormat, CharBuffer>(std::forward<ContextArgs>(args)...);
		BasicFormatterContext<NewCharFormat, CharBuffer> child(format, *this, childContextArgsInterface);
		child.Run();
	}
}