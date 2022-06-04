#pragma once

#include "BasicFormatContext.h"
#include "BasicFormatContextCoreImpl.h"

namespace EngineCore::FMT::Context {

	/////---------- AAHHHHHHHHH ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParseTimer() {
		std::chrono::nanoseconds ns = std::chrono::high_resolution_clock::now() - GetAPI().GetTimeShift();
		WriteType(ns);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParseDate() {
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()) + GetAPI().GetHoursShift();
		WriteType(ns);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParseSetter() {
		static constexpr std::string_view keys[] = {
			"indent"
		};
		m_Format.ParamGoTo(':');
		m_Format.IsEqualForward(':');
		m_Format.IgnoreSpace();
		auto idx = m_Format.GetWordFromList(keys);
		if (idx == 0)
		{
			m_Format.ParamGoTo('=');
			if (m_Format.IsEqualForward('='))
			{
				m_Format.IgnoreSpace();
				Detail::DataType value;
				FormatReadParameterThrow(value);
				BufferOut().SetIndent(value);
			}
			else
				BufferOut().SetIndent();
		}
	}

}


