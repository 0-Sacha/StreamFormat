#pragma once

#include "BasicFormatContext.h"

#include "BaseFormat/BaseFormat.h"
#include "BaseFormat/BaseAnsiTextColor.h"
#include "BaseFormat/BaseAnsiTextStyle.h"
#include "BaseFormat/BaseAnsiFront.h"
#include "BaseFormat/Chrono.h"
#include "BaseFormat/BaseSTDLib.h"

namespace EngineCore::Instrumentation::FMT::Context {

	template<typename CharFormat>
	BasicFormatContext<CharFormat>::BasicFormatContext(const std::basic_string_view<CharFormat>& format)
		: m_Format(format)
		, m_ValuesIndex()
		, m_FormatData()
	{}

	template<typename CharFormat>
	void BasicContext<CharFormat>::SafeRun() {
		try {
			Run();
		}
		catch (const Detail::FormatError&) {}
	}

	template<typename CharFormat>
	template<typename T>
	void BasicContext<CharFormat>::FormatReadParameterThrow(T& i) {
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