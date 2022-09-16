#pragma once

#include "BasicContext.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	BasicContext<CharFormat, ContextPackageSaving, Master>::BasicContext(const std::basic_string_view<CharFormat>& format, const std::size_t maxIndex)
		: m_Format(format)
		, m_ValuesIndex(0, maxIndex)
		, m_FormatData()
		, m_IsChild(false)
	{}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	template<typename ParentFormat, typename ParentMaster>
	BasicContext<CharFormat, ContextPackageSaving, Master>::BasicContext(const std::basic_string_view<CharFormat>& format, BasicContext<ParentFormat, ContextPackageSaving, ParentMaster>& parent, const std::size_t maxIndex)
		: m_Format(format)
		, m_ValuesIndex(0, maxIndex)
		, m_FormatData()
		, m_IsChild(true)
	{}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::SafeRun() {
		try {
			Run();
		}
		catch (const Detail::FormatError&) {}
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	template<typename T>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::FormatReadParameterThrow(T& i) {
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

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::FormatDataApplyNextOverride() {
		if (m_FormatData.NextOverride.size() == 0)
			return;
	
		FormatBufferType overrideAsFormat(m_FormatData.NextOverride);
		FormatBufferType formatCopy = m_Format;
		m_Format = overrideAsFormat;
		ParseFormatData();
		m_Format = formatCopy;
	}
}