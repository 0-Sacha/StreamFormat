#pragma once

#include "BasicFormatContext.h"
#include "BasicFormatContextCoreImpl.h"

namespace EngineCore::FMT::Context {

	/////---------- AAHHHHHHHHH ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParseTimer() {
			ParseFormatData();
		std::chrono::nanoseconds ns = std::chrono::high_resolution_clock::now() - GetAPI().GetTimeShift();
		m_FormatData.AddSpecifier("pattern", "%h:%m:%s.%ms", true);
		WriteType(ns);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParseDate() {
			ParseFormatData();
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()) + GetAPI().GetHoursShift();
		m_FormatData.AddSpecifier("pattern", "%h:%m:%s.%ms", true);
		WriteType(ns);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParseSetter() {
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


