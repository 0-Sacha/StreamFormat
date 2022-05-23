#pragma once

#include "../Buffer/Buffer.h"
#include "AnsiHandler.h"

namespace EngineCore::Instrumentation::FMT::Detail {
	template<typename FormatContext, bool Get, bool Exec>
	struct AnsiParseur {

	public:
		AnsiManager(FormatContext& context)
			: Context(context)
		{}

	public:
		std::conditional_t<Get, AnsiColor, void> 	ParseColor();
		std::size_t 								GetColorCode();
		Detail::AnsiTextColorFG 					GetColorFG();
		Detail::AnsiTextColorBG 					GetColorBG();


	public:
		FormatContext& Context;
	};
}


namespace EngineCore::Instrumentation::FMT::Detail {
	template<typename CharFormat, bool Get, bool Exec>
	std::conditional_t<Get, AnsiColor, void> AnsiParseur<CharFormat, Get, Exec>::ParseColor() {
		if constexpr (Get)
			AnsiColor res;

		if (Context.Format().IsEqualForward(':')) {
			Context.Format().IgnoreSpace();
			if (Context.Format().IsEqualForward('{'))
			{
				Detail::FormatIndex idx = Context.GetFormatIndexThrow(idx);
				if constexpr (Get)
					AnsiColorModif(Context.GetTypeAtIndex(idx));
				else
					Context.TypeRunAtIndex(idx);
				Context.Format().IsEqualForward('}');
			}
			else
			{
				res.FgType = AnsiTextColorDataType::AnsiTextColor;
				res.Fg.Text = GetColorFG();

				m_Format.ParamGoTo('-', ',');
				if (m_Format.IsEqualForward('-')) {
					m_Format.IgnoreSpace();
					res.BgType = AnsiTextColorDataType::AnsiTextColor;
					res.Bg.Text = GetColorBG();
				}
			}
		}
	
		if constexpr (Get)
			return res;
	}


	template<typename CharFormat, bool Get, bool Exec>
	std::size_t AnsiParseur<CharFormat, Get, Exec>::GetColorCode() {
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

		return Context.Format().GetWordFromList(colorCode);
	}

	template<typename CharFormat, bool Get, bool Exec>
	Detail::AnsiTextColorFG AnsiParseur<CharFormat, Get, Exec>::GetColorFG() {
		std::size_t step = static_cast<std::size_t>(Context.Format().IsEqualForward('+') ? Detail::AnsiTextColorFG::BaseBStep : Detail::AnsiTextColorFG::BaseStep);
		std::size_t code = GetColorCode();
		if (code == GET_WORD_FROM_LIST_NOT_FOUND) 	code = static_cast<std::size_t>(Detail::AnsiTextColorFG::Default);
		return static_cast<Detail::AnsiTextColorFG>(code + step);
	}

	template<typename CharFormat, bool Get, bool Exec>
	Detail::AnsiTextColorBG AnsiParseur<CharFormat, Get, Exec>::GetColorBG() {
		std::size_t step = static_cast<std::size_t>(Context.Format().IsEqualForward('+') ? Detail::AnsiTextColorBG::BaseBStep : Detail::AnsiTextColorBG::BaseStep);
		std::size_t code = GetColorCode();
		if (code == GET_WORD_FROM_LIST_NOT_FOUND) 	code = static_cast<std::size_t>(Detail::AnsiTextColorBG::Default);
		return static_cast<Detail::AnsiTextColorBG>(code + step);
	}


	template<typename CharFormat, bool Get, bool Exec>
	std::conditional_t<Get, AnsiStyle, void> AnsiParseur<CharFormat, Get, Exec>::ParseStyle() {
		if constexpr (Get)
			AnsiStyle style;

		if (Context.Format().IsEqualForward(':')) {
			if (!Context.Format().IsEqualTo('}', ',')) {
				bool l = true;
				while (l) {
					Context.Format().IgnoreSpace();
					if (Context.Format().IsEqualForward('{')) {
						Detail::FormatIndex idx = Context.GetFormatIndexThrow(idx);
						if constexpr (Get)
							AnsiStyle.Modif(Context.GetTypeAtIndex(idx));
						else
							Context.TypeRunAtIndex(idx);
						m_Format.IsEqualForward('}');
					} else {
						if constexpr (Get)
							AnsiStyle.Modif(GetStyle());
						else
							Context.TypeRun(GetStyle());
					}
					Context.Format().ParamGoTo('|', ',');
					l = Context.Format().IsEqualForward('|');
					Context.Format().IgnoreSpace();
				}
			}
		}

		if constexpr (Get)
			return style;
	}

	template<typename CharFormat, bool Get, bool Exec>
	Detail::AnsiBasicTextStyle AnsiParseur<CharFormat, Get, Exec>::GetStyle() {
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

		Detail::AnsiBasicTextStyle val = Context.Format().GetWordFromList(styleCode);
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