#pragma once

#include "BasicFormatContext.h"

#include "BaseFormat/BaseFormat.h"
#include "BaseFormat/BaseAnsiTextColor.h"
#include "BaseFormat/BaseAnsiTextStyle.h"
#include "BaseFormat/BaseAnsiTextFront.h"
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
	bool BasicContext<CharFormat>::FormatReadParameter(T& i) {
		if (!m_Format.IsEqualTo('{'))	return Format().ReadUInt(i);

		const CharFormat* const mainSubFormat = m_Format.GetBufferCurrentPos();
		Detail::FormatIndex formatIdx;
		if (GetFormatIdx(formatIdx)) {
			m_Format.Forward();
			m_ContextArgs.GetFormatValueAt(i, formatIdx);
			return true;
		}
		m_Format.SetBufferCurrentPos(mainSubFormat);
		return false;
	}

}