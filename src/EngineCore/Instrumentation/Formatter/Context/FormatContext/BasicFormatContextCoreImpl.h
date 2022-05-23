#pragma once

#include "BasicFormatContext.h"

#include "BaseFormat/BaseFormat.h"
#include "BaseFormat/BaseAnsiTextColor.h"
#include "BaseFormat/BaseAnsiTextStyle.h"
#include "BaseFormat/BaseAnsiTextFront.h"
#include "BaseFormat/Chrono.h"
#include "BaseFormat/BaseSTDLib.h"

namespace EngineCore::Instrumentation::FMT {

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::BasicFormatContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, ContextArgs&& ...args)
		: m_BufferOut(buffer, bufferSize)
		, m_Format(format)
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
		, m_ValuesIdx()
	{
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::BasicFormatContext(const bool bufferIsAutoResize, const std::basic_string_view<CharFormat>& format, ContextArgs &&...args)
		: m_BufferOut()
		, m_Format(format)
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
		, m_ValuesIdx()
	{
	}

	// Used for LittleFormat | Clone
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename ParentCharFormat, typename ...ParentContextArgs>
	BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::BasicFormatContext(const std::basic_string_view<CharFormat>& format, BasicFormatContext<ParentCharFormat, CharBuffer, ParentContextArgs...>& parentContext, ContextArgs&& ...args)
		: m_BufferOut(parentContext.BufferOut())
		, m_Format(format)
		, m_ContextArgs(std::forward<ContextArgs>(args)...)
		, m_ValuesIdx()
	{
		m_FormatData.Clone(parentContext.GetFormatData());
		m_AnsiTextCurrentColor	= parentContext.GetAnsiTextCurrentColor();
		m_AnsiStyle	= parentContext.GetAnsiStyle();
	}



	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::Run() {
		while (!m_Format.IsEnd()) {

			WriteUntilNextParameter();

			if (m_Format.IsEqualTo('{'))
				if (!ParameterParse())
					m_BufferOut.PushBack('{');
		}
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::SafeRun() {
		try {
			Run();
		}
		catch (...) {}

		CheckEndStr();
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename NewCharFormat, typename ...Args>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::LittleFormat(const std::basic_string_view<NewCharFormat>& format, Args&& ...args) {
		BasicFormatContext<NewCharFormat, CharBuffer, Args...> child(format, *this, std::forward<Args>(args)...);
		child.Run();
		UpdateContextFromChild(child);
	}



	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::CheckEndStr() {
		if(m_AnsiFormatterChange.HasMadeChange)
			WriteType(Detail::RESET_ANSI_ALL_PARAMETERS);
	}

	/////---------- ReadTimerParameter ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ReadTimerParameter() {
		std::chrono::nanoseconds ns = std::chrono::high_resolution_clock::now() - GetAPI().GetTimeShift();
		WriteType(ns);
	}

	/////---------- ReadDateParameter ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ReadDateParameter() {
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()) + GetAPI().GetHoursShift();
		WriteType(ns);
	}

	/////---------- ReadAnsiTextColorParameter ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ReadAnsiTextColorParameter() {
		if (m_Format.IsEqualForward(':')) {
			m_Format.IgnoreSpace();
			if (m_Format.IsEqualForward('{')) {
				FormatIdx idx = 0;
				if (GetFormatIdx(idx))
					m_ContextArgs.FormatTypeFromIdx(*this, idx);
				m_Format.IsEqualForward('}');
			}
			else {
				Detail::AnsiTextColorFG colorFg;
				colorFg = (Detail::AnsiTextColorFG)GetColorFG();
				m_Format.ParamGoTo('-', ',');
				if (m_Format.IsEqualForward('-')) {
					Detail::AnsiTextColorBG colorBg;
					m_Format.IgnoreSpace();
					colorBg = (Detail::AnsiTextColorBG)GetColorBG();
					WriteType(Detail::AnsiTextColor{ colorFg, colorBg });
				}
				else {
					WriteType(colorFg);
				}
			}
		}
		else
			WriteType(Detail::RESET_ANSI_COLOR);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	std::uint8_t BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::GetColorCode() {
		static constexpr std::string_view colorCode[] = {
			"black",
			"red",
			"green",
			"yellow",
			"blue",
			"magenta",
			"cyan",
			"white",
			"      ",
			"default"
		};

		return (std::uint8_t)GetWordFromList(colorCode);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	std::uint8_t BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::GetColorFG() {
		std::uint8_t step = (std::uint8_t)(Format().IsEqualForward('+') ? Detail::AnsiTextColorFG::BaseBStep : Detail::AnsiTextColorFG::BaseStep);
		std::uint8_t code = GetColorCode();
		if (code == (std::numeric_limits<std::uint8_t>::max)()) code = (std::uint8_t)Detail::AnsiTextColorFG::Default;
		else													code += step;
		return code;
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	std::uint8_t BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::GetColorBG() {
		std::uint8_t step = (std::uint8_t)(Format().IsEqualForward('+') ? Detail::AnsiTextColorBG::BaseBStep : Detail::AnsiTextColorBG::BaseStep);
		std::uint8_t code = GetColorCode();
		if (code == (std::numeric_limits<std::uint8_t>::max)())	code = (std::uint8_t)Detail::AnsiTextColorBG::Default;
		else													code += step;
		return code;
	}
	
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ReloadColor(const Detail::AnsiTextCurrentColor& targetColor, const Detail::AnsiTextColorChange& changeColor)
	{
		if (changeColor.HasChangeColor) {
			if (changeColor.HasSetFg && changeColor.HasSetBg && targetColor.FgType == targetColor.BgType) {
				switch (targetColor.FgType) {
				case Detail::AnsiTextColorDataType::AnsiTextColor:
					WriteType(targetColor.Color);
					break;
				case Detail::AnsiTextColorDataType::AnsiNColor:
					WriteType(targetColor.ColorN);
					break;
				case Detail::AnsiTextColorDataType::AnsiColor24b:
					WriteType(targetColor.Color24bits);
					break;
				case Detail::AnsiTextColorDataType::Default:
					WriteType(Detail::RESET_ANSI_COLOR);
					break;
				}
			}
			else {
				if (changeColor.HasSetFg)
					switch (targetColor.FgType) {
					case Detail::AnsiTextColorDataType::AnsiTextColor:
						WriteType(targetColor.Color.Fg);
						break;
					case Detail::AnsiTextColorDataType::AnsiNColor:
						WriteType(targetColor.ColorN.Fg);
						break;
					case Detail::AnsiTextColorDataType::AnsiColor24b:
						WriteType(targetColor.Color24bits.Fg);
						break;
					case Detail::AnsiTextColorDataType::Default:
						WriteType(Detail::AnsiTextColorFG::Default);
						break;
					}

				if (changeColor.HasSetBg)
					switch (targetColor.BgType) {
					case Detail::AnsiTextColorDataType::AnsiTextColor:
						WriteType(targetColor.Color.Bg);
						break;
					case Detail::AnsiTextColorDataType::AnsiNColor:
						WriteType(targetColor.ColorN.Bg);
						break;
					case Detail::AnsiTextColorDataType::AnsiColor24b:
						WriteType(targetColor.Color24bits.Bg);
						break;
					case Detail::AnsiTextColorDataType::Default:
						WriteType(Detail::AnsiTextColorBG::Default);
						break;
					}
			}
		}
	}



	/////---------- ReadTextFormatStyleParameter ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ReadAnsiTextStyleParameter() {
		if (m_Format.IsEqualForward(':')) {
			if (!m_Format.IsEqualTo('}', ',')) {
				bool l = true;
				while (l) {
					m_Format.IgnoreSpace();
					if (m_Format.IsEqualForward('{')) {
						FormatIdx idx = 0;
						if (GetFormatIdx(idx))
							m_ContextArgs.FormatTypeFromIdx(*this, idx);
						m_Format.IsEqualForward('}');
					} else {
						WriteStyleParameter();
					}
					m_Format.ParamGoTo('|', ',');
					l = m_Format.IsEqualForward('|');
					m_Format.IgnoreSpace();
				}
			}
			else {
				WriteType(Detail::RESET_ANSI_STYLE);
			}
		}
		else
			WriteType(Detail::RESET_ANSI_COLOR);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::WriteStyleParameter() {
		static constexpr std::string_view styleCode[] = {
			"bold",
			"dim",
			"n-intensity",
			"italic",
			"n-italic",
			"underlined",
			"d-underlined",
			"n-underlined",
			"c-underlined",
			"slowblink",
			"fastblink",
			"n-blink",
			"inverted",
			"n-inverted",
			"i-underlined",
			"i-d-underlined",
			"i-overlined",
			"i-d-overlined",
			"i-stress",
			"n-i",
			"superscript",
			"subscript",
			"n-script"
		};

		static constexpr Detail::AnsiBasicTextStyle styleLookUpTable[] = {
			Detail::AnsiBasicTextStyle::Intensity_Bold,				// bold
			Detail::AnsiBasicTextStyle::Intensity_Dim,				// dim
			Detail::AnsiBasicTextStyle::Intensity_Normal,			// n-intensity
			Detail::AnsiBasicTextStyle::Italic_Enable,				// italic
			Detail::AnsiBasicTextStyle::Italic_Disable,				// n-italic
			Detail::AnsiBasicTextStyle::Underline_Underlined,		// underline
			Detail::AnsiBasicTextStyle::Underline_DoubleUnerlined,	// d-underline
			Detail::AnsiBasicTextStyle::Underline_Disable,			// n-underline
			Detail::AnsiBasicTextStyle::Underline_SelectColor,		// c-underline
			Detail::AnsiBasicTextStyle::Blink_SlowBlink,			// slowblink
			Detail::AnsiBasicTextStyle::Blink_FastBlink,			// fastblink
			Detail::AnsiBasicTextStyle::Blink_Disable,				// n-blink
			Detail::AnsiBasicTextStyle::Inverted_Enable,			// inverted
			Detail::AnsiBasicTextStyle::Inverted_Disable,			// n-inverted
			Detail::AnsiBasicTextStyle::Ideogram_Underlined,		// i-underlined
			Detail::AnsiBasicTextStyle::Ideogram_DoubleUnderlined,	// i-d-underlined
			Detail::AnsiBasicTextStyle::Ideogram_Overlined,			// i-overlined
			Detail::AnsiBasicTextStyle::Ideogram_DoubleOverlined,	// i-d-overlined
			Detail::AnsiBasicTextStyle::Ideogram_StressMarking,		// i-stress
			Detail::AnsiBasicTextStyle::Ideogram_AllDisable,		// n-i
			Detail::AnsiBasicTextStyle::Script_Superscript,			// superscript
			Detail::AnsiBasicTextStyle::Script_Subscript,			// subscript
			Detail::AnsiBasicTextStyle::Script_AllDisable			// n-script
		};

		Detail::AnsiBasicTextStyle val = styleLookUpTable[GetWordFromList(styleCode)];
		if (val == Detail::AnsiBasicTextStyle::Underline_SelectColor) {
			m_Format.IgnoreSpace();
			m_Format.IsEqualForward(':');
			m_Format.IgnoreSpace();
			std::uint8_t step = (std::uint8_t)(Format().IsEqualForward('+') ? Detail::AnsiNColorType::MinBrightColor : Detail::AnsiNColorType::MinNormalColor);
			std::uint8_t code = GetColorCode();
			if (code == (std::numeric_limits<std::uint8_t>::max)())		WriteType(Detail::RESET_ANSI_UNDERLINE_COLOR);
			else														WriteType(Detail::AnsiNColorUnderline(code + step));
		} else {
			WriteType(val);
		}
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ReloadStyle(const Detail::AnsiStyle& targetStyle, const Detail::AnsiStyleChange& changeStyle) {
		if (changeStyle.HasChangeStyle) {
			if (changeStyle.HasSetIntensity)	WriteType(targetStyle.Intensity);
			if (changeStyle.HasSetItalic)		WriteType(targetStyle.Italic);
			if (changeStyle.HasSetBlink)		WriteType(targetStyle.Blink);
			if (changeStyle.HasSetInverted)		WriteType(targetStyle.Inverted);
			if (changeStyle.HasSetIdeogram)		WriteType(targetStyle.Ideogram);
			if (changeStyle.HasSetScript)		WriteType(targetStyle.Script);

			if (changeStyle.HasSetUnderline)	WriteType(targetStyle.Underline);

			if (changeStyle.HasSetUnderlineColor) {
				switch (targetStyle.UnderlineColorType) {
				case Detail::AnsiColorUnderlineType::AnsiNColor:
					WriteType(targetStyle.UnderlineColorN);
					break;
				case Detail::AnsiColorUnderlineType::AnsiColor24b:
					WriteType(targetStyle.UnderlineColor24bits);
					break;
				case Detail::AnsiColorUnderlineType::Default:
					WriteType(Detail::RESET_ANSI_UNDERLINE_COLOR);
					break;
				}
			}
		}
	}


	/////---------- ReadAnsiTextFrontParameter ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ReadAnsiTextFrontParameter() {
		if (m_Format.IsEqualForward(':')) {
			m_Format.IgnoreSpace();
			WriteType(Detail::AnsiTextFront(GetFrontCode()));
		}
	}


	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	std::uint8_t BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::GetFrontCode() {
		// TODO : change to specific os
		static constexpr std::string_view frontCode[] = {
			"default",
			"front0",
			"front1",
			"front2",
			"front3",
			"front4",
			"front5",
			"front6",
			"front7",
			"front8",
			"front9"
		};

		return (std::uint8_t)GetWordFromList(frontCode);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ReloadFront(const Detail::AnsiTextCurrentFront& targetFront, const Detail::AnsiTextFrontChange& changeFront) {
		if (changeFront.HasChangeFront)
			WriteType(targetFront.Front);
	}

	
	
	/////---------- ReadSetterParameter ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ReadSetterParameter() {
		static constexpr std::string_view keys[] = {
			"indent"
		};
		m_Format.ParamGoTo(':');
		m_Format.IsEqualForward(':');
		m_Format.IgnoreSpace();
		auto idx = GetWordFromList(keys);
		if (idx == 0)
		{
			m_Format.ParamGoTo('=');
			if (m_Format.IsEqualForward('='))
			{
				m_Format.IgnoreSpace();
				Detail::DataType value = 0;
				m_Format.ReadInt(value);
				m_Indent = value;
			}
			else
				SetIndent();
		}
	}
}