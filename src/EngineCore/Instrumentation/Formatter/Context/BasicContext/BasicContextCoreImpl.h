#pragma once

#include "BasicContext.h"

namespace EngineCore::Instrumentation::FMT::Context {

	template<typename CharFormat, typename ContextPackageSaving>
	BasicContext<CharFormat, ContextPackageSaving>::BasicContext(const std::basic_string_view<CharFormat>& format, const std::size_t maxIndex)
		: m_Format(format)
		, m_ValuesIndex(0, maxIndex)
		, m_FormatData()
	{}

	template<typename CharFormat, typename ContextPackageSaving>
	template<typename NewCharFormat>
	BasicContext<CharFormat, ContextPackageSaving>::BasicContext(const std::basic_string_view<CharFormat>& format, BasicContext<NewCharFormat, ContextPackageSaving>& parent, const std::size_t maxIndex)
		: m_Format(format)
		, m_ValuesIndex(0, maxIndex)
		, m_FormatData()
	{}

	template<typename CharFormat, typename ContextPackageSaving>
	void BasicContext<CharFormat, ContextPackageSaving>::SafeRun() {
		try {
			Run();
		}
		catch (const Detail::FormatError&) {}
	}

	template<typename CharFormat, typename ContextPackageSaving>
	template<typename T>
	void BasicContext<CharFormat, ContextPackageSaving>::FormatReadParameterThrow(T& i) {
		if (!m_Format.IsEqualTo('{'))
			if (!m_Format.ReadUInt(i))
				throw Detail::FormatParseError{};

		Detail::FormatIndex formatIdx = GetFormatIndexThrow();
		m_Format.IsEqualForwardThrow();
		i = GetTypeAtIndexThrow<T>(formatIdx);
		// TRY 		const CharFormat* const mainSubFormat = m_Format.GetBufferCurrentPos();
		// CATCH 	m_Format.SetBufferCurrentPos(mainSubFormat);
	}

}