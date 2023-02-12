#pragma once

#include "BasicContext.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename ContextPackage>
	BasicContext<CharFormat, ContextPackage>::BasicContext()
		: m_Format()
		, m_ValuesIndex(0, 0)
		, m_FormatData()
		, m_ContextArgsInterface(nullptr)
	{}

	template<typename CharFormat, typename ContextPackage>
	BasicContext<CharFormat, ContextPackage>::~BasicContext() { }

	template<typename CharFormat, typename ContextPackage>
	void BasicContext<CharFormat, ContextPackage>::RunImpl()
	{
		while (!m_Format.IsEnd())
		{
			const CharFormat* beginContinousString = m_Format.GetBufferCurrentPos();
			std::size_t sizeContinousString = 0;
			while (m_Format.IsEqualTo('{') == false && m_Format.IsEnd() == false)
			{
				++sizeContinousString;
				m_Format.Forward();
			}
			FormatToParamsString(beginContinousString, sizeContinousString);

			if (m_Format.IsEqualTo('{'))
				FormatExecParams();
		}
	}

	template<typename CharFormat, typename ContextPackage>
	void BasicContext<CharFormat, ContextPackage>::Run(FormatBufferType& format, ContextArgsInterface* argsInterface)
	{
		// Save old context
		FormatBufferType oldFormat = m_Format;
		ContextArgsInterface* oldArgsInterface = m_ContextArgsInterface;
		Detail::FormatIndex oldValuesIndex = m_ValuesIndex;
		ContextPackage saveContextInfo = ContextStyleSave();
		// Set new context
		m_Format = format;
		m_ContextArgsInterface = argsInterface;
		m_ValuesIndex = Detail::FormatIndex(0, static_cast<Detail::FormatIndex::BaseType>(argsInterface->Size()));
		SetArgsInterfaceCurrentContex();
		// Run
		RunImpl();
		// Restore old context
		m_Format = oldFormat;
		m_ContextArgsInterface = oldArgsInterface;
		m_ValuesIndex = oldValuesIndex;
		ContextStyleRestore(saveContextInfo);
	}
	
	template<typename CharFormat, typename ContextPackage>
	template<typename T>
	void BasicContext<CharFormat, ContextPackage>::FormatReadParameterThrow(T& i) {
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

	template<typename CharFormat, typename ContextPackage>
	void BasicContext<CharFormat, ContextPackage>::FormatDataApplyNextOverride() {
		if (m_FormatData.NextOverride.size() == 0)
			return;
	
		FormatBufferType overrideAsFormat(m_FormatData.NextOverride);
		FormatBufferType formatCopy = m_Format;
		m_Format = overrideAsFormat;
		ParseFormatData();
		m_Format = formatCopy;
	}
}
