#pragma once

#include "BasicFormatterContext.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer>
	template<typename ...ContextArgs>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, [[maybe_unused]] bool k, ContextArgs&& ...args)
		: Base(format)
		, m_BufferOut(buffer, bufferSize)
		, m_AnsiManager(*this)
	{
		auto argsInterface = new Detail::FormatterContextArgsTupleInterface<M_Type, ContextArgs...>(std::forward<ContextArgs>(args)...);
		argsInterface->SetContext(this);
		SetContextArgsInterface(static_cast<ContextArgsInterface*>(argsInterface), true);
	}

	template<typename CharFormat, typename CharBuffer>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, Detail::BasicContextArgsTupleInterface<M_Type>* argsInterface)
		: Base(format, static_cast<ContextArgsInterface*>(argsInterface), false)
		, m_BufferOut(buffer, bufferSize)
		, m_AnsiManager(*this)
	{
		argsInterface->SetContext(this);
	}

	// Used for SubContext | Clone
	template<typename CharFormat, typename CharBuffer>
	template<typename ParentCharFormat>
	BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(const std::basic_string_view<CharFormat>& format, BasicFormatterContext<ParentCharFormat, CharBuffer>& parentContext, Detail::BasicContextArgsTupleInterface<M_Type>* argsInterface)
		: Base(format, static_cast<ContextArgsInterface*>(argsInterface), false)
		, m_BufferOut(parentContext.BufferOut())
		, m_AnsiManager(*this, parentContext.GetAnsiManager())
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

		m_AnsiManager.Kill();
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