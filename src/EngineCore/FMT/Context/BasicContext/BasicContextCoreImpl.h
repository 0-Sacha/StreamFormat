#pragma once

#include "BasicContext.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename ContextPackageSaving>
	BasicContext<CharFormat, ContextPackageSaving>::BasicContext(const std::basic_string_view<CharFormat>& format, const std::size_t maxIndex)
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
			if (m_Format.ReadUInt(i))
				return;

		Detail::FormatIndex formatIdx = GetFormatIndexThrow();
		m_Format.IsEqualToForwardThrow('}');
		i = GetTypeAtIndexThrow<T>(formatIdx);

		// FIXME WTF
		// TRY 		const CharFormat* const mainSubFormat = m_Format.GetBufferCurrentPos();
		// CATCH 	m_Format.SetBufferCurrentPos(mainSubFormat);
	}

	template<typename CharFormat, typename ContextPackageSaving>
	void BasicContext<CharFormat, ContextPackageSaving>::FormatDataApplyNextOverride() {
		if (m_FormatData.NextOverride.size() == 0)
			return;
	
		FormatBufferType overrideAsFormat(m_FormatData.NextOverride);
		FormatBufferType formatCopy = m_Format;
		m_Format = overrideAsFormat;
		ParseFormatData();
		m_Format = formatCopy;
	}
}
