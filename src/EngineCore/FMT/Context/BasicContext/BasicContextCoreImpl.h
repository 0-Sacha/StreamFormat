#pragma once

#include "BasicContext.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename ContextPackageSaving>
	BasicContext<CharFormat, ContextPackageSaving>::BasicContext(const std::basic_string_view<CharFormat>& format, ContextArgsInterface* argsInterface)
		: m_Format(format)
		, m_ValuesIndex(0, argsInterface->Size())
		, m_FormatData()
		, m_ContextArgsInterface(argsInterface)
	{}

	template<typename CharFormat, typename ContextPackageSaving>
	BasicContext<CharFormat, ContextPackageSaving>::BasicContext(const std::basic_string_view<CharFormat>& format)
		: m_Format(format)
		, m_ValuesIndex(0, 0)
		, m_FormatData()
		, m_ContextArgsInterface(nullptr)
	{}

	template<typename CharFormat, typename ContextPackageSaving>
	BasicContext<CharFormat, ContextPackageSaving>::~BasicContext() { }

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
		if constexpr (std::is_convertible_v<T, int64_t>)
			i = static_cast<T>(m_ContextArgsInterface->GetIntAt(formatIdx));
		else if constexpr (std::is_convertible_v<T, StringViewFormat>)
			i = static_cast<T>(m_ContextArgsInterface->GetStringAt(formatIdx));

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
