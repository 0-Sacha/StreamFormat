#pragma once

#include "EngineCore/Instrumentation/Formatter/Core/Detail/Detail.h"
#include "EngineCore/Instrumentation/Formatter/Core/Buffer/Buffer.h"
#include "EngineCore/Instrumentation/Formatter/Core/AnsiFormat/AnsiHandler.h"

namespace EngineCore::Instrumentation::FMT::Detail {
	template<typename FormatBuffer>
	struct BasicAnsiParseur {

	public:
		explicit BasicAnsiParseur(FormatBuffer& format)
			: Format(format)
		{}

	public:
		Detail::FormatIndex GetFormatIndexThrow();
		
	public:
		void ColorRunOnIndex(const Detail::FormatIndex& index) 	{ throw Detail::FormatShouldNotEndHere(); }
		template <typename T>
		void ColorRun(const T& modif) 							{ throw Detail::FormatShouldNotEndHere(); }

		void StyleRunOnIndex(const Detail::FormatIndex& index) 	{ throw Detail::FormatShouldNotEndHere(); }
		template <typename T>
		void StyleRun(const T& modif) 							{ throw Detail::FormatShouldNotEndHere(); }

		void FrontRunOnIndex(const Detail::FormatIndex& index) 	{ throw Detail::FormatShouldNotEndHere(); }
		template <typename T>
		void FrontRun(const T& modif) 							{ throw Detail::FormatShouldNotEndHere(); }

	public:
		void 						ParseColor();
		std::size_t 				GetColorCode();
		template <typename T>
		T 							GetColorCodeAuto();

		void 						ParseStyle();
		Detail::AnsiBasicTextStyle 	GetStyleCode();
		Detail::AnsiNColorUnderline SelectUnderlinedColorStyle();

		void 						ParseFront();
		Detail::AnsiFront 			GetFrontCode();

	public:
		FormatBuffer& Format;
	};
}


namespace EngineCore::Instrumentation::FMT::Detail {
	template<typename FormatBuffer>
	void BasicAnsiParseur<FormatBuffer>::ParseColor() {
		if (Format.IsEqualForward(':')) {
			Format.IgnoreSpace();
			if (Format.IsEqualForward('{'))
			{
				Detail::FormatIndex idx = GetFormatIndexThrow();
				ColorRunOnIndex(idx);
				Format.IsEqualForward('}');
			}
			else
			{
				Detail::AnsiTextColorFG colorFg = GetColorCodeAuto<Detail::AnsiTextColorFG>();

				Format.ParamGoTo('-', ',');
				if (Format.IsEqualForward('-')) {
					Format.IgnoreSpace();
					Detail::AnsiTextColorBG colorBg = GetColorCodeAuto<Detail::AnsiTextColorBG>();
					ColorRun(Detail::AnsiTextColor{ colorFg, colorBg });
				}
				else
					ColorRun(colorFg);
			}
		}
		else
			ColorRun(Detail::RESET_ANSI_COLOR);
	}


	template<typename FormatBuffer>
	std::size_t BasicAnsiParseur<FormatBuffer>::GetColorCode() {
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

		return Format.GetWordFromList(colorCode);
	}

	template<typename FormatBuffer>
	template<typename T>
	T BasicAnsiParseur<FormatBuffer>::GetColorCodeAuto() {
		std::size_t step = static_cast<std::size_t>(Format.IsEqualForward('+') ? T::BaseBStep : T::BaseStep);
		std::size_t code = GetColorCode();
		if (code == Format.GET_WORD_FROM_LIST_NOT_FOUND) 	return T::Default;
		return static_cast<T>(code + step);
	}

	template<typename FormatBuffer>
	void BasicAnsiParseur<FormatBuffer>::ParseStyle() {
		if (Format.IsEqualForward(':')) {
			if (!Format.IsEqualTo('}', ',')) {
				bool l = true;
				while (l) {
					Format.IgnoreSpace();
					if (Format.IsEqualForward('{'))
					{
						Detail::FormatIndex idx = GetFormatIndexThrow();
						StyleRunOnIndex(idx);
						Format.IsEqualForward('}');
					}
					else
					{
						Detail::AnsiBasicTextStyle style = GetStyleCode();
						if (style == Detail::AnsiBasicTextStyle::Underline_SelectColor)
						{
							Detail::AnsiNColorUnderline underlineColor = SelectUnderlinedColorStyle();
							StyleRun(underlineColor);
						}
						else	
							StyleRun(style);
					}
					Format.ParamGoTo('|', ',');
					l = Format.IsEqualForward('|');
					Format.IgnoreSpace();
				}
			}
			else
				StyleRun(Detail::RESET_ANSI_STYLE);
		}
		else
			StyleRun(Detail::RESET_ANSI_STYLE);
	}

	template <typename FormatBuffer>
	Detail::AnsiBasicTextStyle BasicAnsiParseur<FormatBuffer>::GetStyleCode() {
		static constexpr typename FormatBuffer::template TextTo<Detail::AnsiBasicTextStyle> styleCode[] = {
			{ "bold",			Detail::AnsiBasicTextStyle::Intensity_Bold				},
			{ "dim",			Detail::AnsiBasicTextStyle::Intensity_Dim				},
			{ "n-intensity",	Detail::AnsiBasicTextStyle::Intensity_Normal			},
			{ "italic",			Detail::AnsiBasicTextStyle::Italic_Enable				},
			{ "n-italic",		Detail::AnsiBasicTextStyle::Italic_Disable				},
			{ "underlined",		Detail::AnsiBasicTextStyle::Underline_Underlined		},
			{ "d-underlined",	Detail::AnsiBasicTextStyle::Underline_DoubleUnerlined	},
			{ "n-underlined",	Detail::AnsiBasicTextStyle::Underline_Disable			},
			{ "c-underlined",	Detail::AnsiBasicTextStyle::Underline_SelectColor		},
			{ "slowblink",		Detail::AnsiBasicTextStyle::Blink_SlowBlink				},
			{ "fastblink",		Detail::AnsiBasicTextStyle::Blink_FastBlink				},
			{ "n-blink",		Detail::AnsiBasicTextStyle::Blink_Disable				},
			{ "inverted",		Detail::AnsiBasicTextStyle::Inverted_Enable				},
			{ "n-inverted",		Detail::AnsiBasicTextStyle::Inverted_Disable			},
			{ "i-underlined",	Detail::AnsiBasicTextStyle::Ideogram_Underlined			},
			{ "i-d-underlined",	Detail::AnsiBasicTextStyle::Ideogram_DoubleUnderlined	},
			{ "i-overlined",	Detail::AnsiBasicTextStyle::Ideogram_Overlined			},
			{ "i-d-overlined",	Detail::AnsiBasicTextStyle::Ideogram_DoubleOverlined	},
			{ "i-stress",		Detail::AnsiBasicTextStyle::Ideogram_StressMarking		},
			{ "n-i",			Detail::AnsiBasicTextStyle::Ideogram_AllDisable			},
			{ "superscript",	Detail::AnsiBasicTextStyle::Script_Superscript			},
			{ "subscript",		Detail::AnsiBasicTextStyle::Script_Subscript			},
			{ "n-script",		Detail::AnsiBasicTextStyle::Script_AllDisable			}
		};

		return Format.GetWordFromList(styleCode);
	}

	template<typename FormatBuffer>
	Detail::AnsiNColorUnderline BasicAnsiParseur<FormatBuffer>::SelectUnderlinedColorStyle() {
		Format.ParamGoTo(':');
		Format.IsEqualForward(':');
		Format.IgnoreSpace();
		return GetColorCodeAuto<Detail::AnsiNColorUnderline>();
	}



	template<typename FormatBuffer>
	void BasicAnsiParseur<FormatBuffer>::ParseFront() {
		if (Format.IsEqualForward(':')) {
			Format.IgnoreSpace();
			WriteType(GetFrontCode());
		}
		else
			FrontRun(RESET_ANSI_FRONT);
	}

	template<typename FormatBuffer>
	Detail::AnsiFront BasicAnsiParseur<FormatBuffer>::GetFrontCode() {
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

		return Detail::AnsiFront(Format.GetWordFromList(frontCode));
	}
}