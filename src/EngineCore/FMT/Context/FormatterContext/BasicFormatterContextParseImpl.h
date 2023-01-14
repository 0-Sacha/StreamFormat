#pragma once

#include "BasicFormatterContext.h"
#include "BasicFormatterContextCoreImpl.h"

namespace EngineCore::FMT::Context {

	/////---------- AAHHHHHHHHH ----------/////
	template<typename CharFormat, typename CharBuffer>
	void BasicFormatterContext<CharFormat, CharBuffer>::ParseTimer() {
			ParseFormatData();
		std::chrono::nanoseconds ns = std::chrono::high_resolution_clock::now() - Detail::FormatterHandler::GetInstance().GetTimeShift();
		m_FormatData.AddSpecifier("pattern", "%h:%m:%s.%ms", true);
		WriteType(ns);
	}

	template<typename CharFormat, typename CharBuffer>
	void BasicFormatterContext<CharFormat, CharBuffer>::ParseDate() {
			ParseFormatData();
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()) + Detail::FormatterHandler::GetInstance().GetHoursShift();
		m_FormatData.AddSpecifier("pattern", "%h:%m:%s.%ms", true);
		WriteType(ns);
	}

	template<typename CharFormat, typename CharBuffer>
	void BasicFormatterContext<CharFormat, CharBuffer>::ParseSetter() {
		ParseFormatData();

		// Indent
		auto indent = m_FormatData.GetSpecifier("indent");
		if (indent != nullptr)
		{
			if (indent->ValueHasNumber == true)
				BufferOut().SetIndent(indent->ValueAsNumber);
			else
				BufferOut().SetIndent();
		}
	}

}


