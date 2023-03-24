#pragma once

#include "TextPropertiesParser.h"

namespace ProjectCore::FMT::Detail
{
	template <typename BasicContext>
	void BasicTextPropertiesParser<BasicContext>::ColorExecuteOnIndex(const FormatIndex& index)
	{
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::Color>(			index, [this](const TextProperties::TextColor::Color& data) 				{ this->ReloadColor(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::BasicColorFG>(	index, [this](const TextProperties::TextColor::BasicColorFG& data) 			{ this->AskColorModif(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::BasicColorBG>(	index, [this](const TextProperties::TextColor::BasicColorBG& data) 			{ this->AskColorModif(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::ColorCubeFG>(	index, [this](const Detail::TextProperties::TextColor::ColorCubeFG& data) 	{ this->AskColorModif(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::ColorCubeBG>(	index, [this](const Detail::TextProperties::TextColor::ColorCubeBG& data) 	{ this->AskColorModif(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::Color24bFG>(		index, [this](const Detail::TextProperties::TextColor::Color24bFG& data) 	{ this->AskColorModif(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::Color24bBG>(		index, [this](const Detail::TextProperties::TextColor::Color24bBG& data) 	{ this->AskColorModif(data); } );
	}

	template <typename BasicContext>
	void BasicTextPropertiesParser<BasicContext>::FrontExecuteOnIndex(const FormatIndex& index)
	{
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextFront::Front>(		index, [this](const TextProperties::TextFront::Front& data) 	{ this->ReloadFront(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextFront::FrontID>(	index, [this](const TextProperties::TextFront::FrontID& data) 	{ this->AskFrontModif(data); } );
	}
	
	template <typename BasicContext>
	void BasicTextPropertiesParser<BasicContext>::StyleExecuteOnIndex(const FormatIndex& index)
	{
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Style>(		index, [this](const TextProperties::TextStyle::Style& data) 		{ this->ReloadStyle(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Intensity>(	index, [this](const TextProperties::TextStyle::Intensity& data) 	{ this->AskStyleModif(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Italic>(		index, [this](const TextProperties::TextStyle::Italic& data) 		{ this->AskStyleModif(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Underline>(	index, [this](const TextProperties::TextStyle::Underline& data) 	{ this->AskStyleModif(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Blink>(		index, [this](const TextProperties::TextStyle::Blink& data) 		{ this->AskStyleModif(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Inverted>(	index, [this](const TextProperties::TextStyle::Inverted& data) 		{ this->AskStyleModif(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Ideogram>(	index, [this](const TextProperties::TextStyle::Ideogram& data) 		{ this->AskStyleModif(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Script>(		index, [this](const TextProperties::TextStyle::Script& data) 		{ this->AskStyleModif(data); } );

		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::UnderlineColor::ColorCube>(	index, [this](const TextProperties::TextStyle::UnderlineColor::ColorCube& data) { this->AskStyleModif(data); } );
		m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::UnderlineColor::Color24b>(	index, [this](const TextProperties::TextStyle::UnderlineColor::Color24b& data) 	{ this->AskStyleModif(data); } );
	}


	template <typename BasicContext>
	void BasicTextPropertiesParser<BasicContext>::ParseColor()
	{
		if (m_Context.Format().IsEqualToForward(':')) {
			m_Context.Format().IgnoreAllSpaces();
			if (m_Context.Format().IsEqualToForward('{'))
			{
				FormatIndex idx = m_Context.GetFormatIndexThrow();
				ColorExecuteOnIndex(idx);
				m_Context.Format().IsEqualToForward('}');
			}
			else
			{
				TextProperties::TextColor::BasicColorFG colorFg;
				bool colorFgFound = GetColorCode(colorFg);

				m_Context.Format().ParamGoTo('-', ',');
				if (m_Context.Format().IsEqualToForward('-')) {
					m_Context.Format().IgnoreAllSpaces();
					TextProperties::TextColor::BasicColorBG colorBg;
					bool colorBgFound = GetColorCode(colorBg);
					if (colorBgFound && colorFgFound)
						AskColorModif(TextProperties::TextColor::BasicColor{ colorFg, colorBg });
					else
						ReloadDefaultColor();
				}
				else
				{
					if (colorFgFound)
						AskColorModif(colorFg);
					else
						ReloadDefaultColor();
				}
			}
		}
		else
			ReloadDefaultColor();
	}

	template <typename BasicContext>
	template<typename T>
	bool BasicTextPropertiesParser<BasicContext>::GetColorCode(T& t)
	{
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

		std::uint8_t step = static_cast<std::uint8_t>(m_Context.Format().IsEqualToForward('+') ? T::BaseBStep : T::BaseStep);
		std::uint8_t code = m_Context.Format().GetWordFromList(colorCode);
		if (code == m_Context.Format().GET_WORD_FROM_LIST_NOT_FOUND) 	return false;
		t = static_cast<T>(code + step);
		return true;
	}

	template <typename BasicContext>
	void BasicTextPropertiesParser<BasicContext>::ParseStyle()
	{
		if (m_Context.Format().IsEqualToForward(':')) {
			if (!m_Context.Format().IsEqualTo('}', ',')) {
				bool l = true;
				while (l) {
					m_Context.Format().IgnoreAllSpaces();
					if (m_Context.Format().IsEqualToForward('{'))
					{
						FormatIndex idx = m_Context.GetFormatIndexThrow();
						StyleExecuteOnIndex(idx);
						m_Context.Format().IsEqualToForward('}');
					}
					else
					{
						TextProperties::TextStyle::BasicStyle style = GetStyleCode();
						if (style == TextProperties::TextStyle::BasicStyle::Underline_SelectColor)
						{
							TextProperties::TextStyle::UnderlineColor::ColorCube underlineColor = SelectUnderlinedColorStyle();
							StyleModif(underlineColor);
						}
						else	
							StyleModif(style);
					}
					m_Context.Format().ParamGoTo('|', ',');
					l = m_Context.Format().IsEqualToForward('|');
					m_Context.Format().IgnoreAllSpaces();
				}
			}
			else
				ReloadDefaultStyle();
		}
		else
			ReloadDefaultStyle();
	}

	template <typename BasicContext>
	TextProperties::TextStyle::BasicStyle BasicTextPropertiesParser<BasicContext>::GetStyleCode()
	{
		using FormatType = typename BasicContext::FormatBufferType;
		static constexpr typename FormatType::template TextTo<TextProperties::TextStyle::BasicStyle> styleCode[] = {
			{ "bold",			TextProperties::TextStyle::BasicStyle::Intensity_Bold				},
			{ "dim",			TextProperties::TextStyle::BasicStyle::Intensity_Dim				},
			{ "n-intensity",	TextProperties::TextStyle::BasicStyle::Intensity_Normal				},
			{ "italic",			TextProperties::TextStyle::BasicStyle::Italic_Enable				},
			{ "n-italic",		TextProperties::TextStyle::BasicStyle::Italic_Disable				},
			{ "underlined",		TextProperties::TextStyle::BasicStyle::Underline_Underlined			},
			{ "d-underlined",	TextProperties::TextStyle::BasicStyle::Underline_DoubleUnerlined	},
			{ "n-underlined",	TextProperties::TextStyle::BasicStyle::Underline_Disable			},
			{ "c-underlined",	TextProperties::TextStyle::BasicStyle::Underline_SelectColor		},
			{ "slowblink",		TextProperties::TextStyle::BasicStyle::Blink_SlowBlink				},
			{ "fastblink",		TextProperties::TextStyle::BasicStyle::Blink_FastBlink				},
			{ "n-blink",		TextProperties::TextStyle::BasicStyle::Blink_Disable				},
			{ "inverted",		TextProperties::TextStyle::BasicStyle::Inverted_Enable				},
			{ "n-inverted",		TextProperties::TextStyle::BasicStyle::Inverted_Disable				},
			{ "i-underlined",	TextProperties::TextStyle::BasicStyle::Ideogram_Underlined			},
			{ "i-d-underlined",	TextProperties::TextStyle::BasicStyle::Ideogram_DoubleUnderlined	},
			{ "i-overlined",	TextProperties::TextStyle::BasicStyle::Ideogram_Overlined			},
			{ "i-d-overlined",	TextProperties::TextStyle::BasicStyle::Ideogram_DoubleOverlined		},
			{ "i-stress",		TextProperties::TextStyle::BasicStyle::Ideogram_StressMarking		},
			{ "n-i",			TextProperties::TextStyle::BasicStyle::Ideogram_AllDisable			},
			{ "superscript",	TextProperties::TextStyle::BasicStyle::Script_Superscript			},
			{ "subscript",		TextProperties::TextStyle::BasicStyle::Script_Subscript				},
			{ "n-script",		TextProperties::TextStyle::BasicStyle::Script_AllDisable			}
		};

		return m_Context.Format().GetWordFromList(styleCode);
	}

	template <typename BasicContext>
	TextProperties::TextStyle::UnderlineColor::ColorCube BasicTextPropertiesParser<BasicContext>::SelectUnderlinedColorStyle()
	{
		m_Context.Format().ParamGoTo(':');
		m_Context.Format().IsEqualToForward(':');
		m_Context.Format().IgnoreAllSpaces();
		TextProperties::TextStyle::UnderlineColor::ColorCube color;
		if (GetColorCode(color)) return color;
		// TODO : handle Color24b
		if (m_BaseContextProperties != nullptr)
			return m_BaseContextProperties->Style.UnderlineColor.Data.ColorCube;
		return TextProperties::TextStyle::UnderlineColor::ColorCube{};
	}



	template <typename BasicContext>
	void BasicTextPropertiesParser<BasicContext>::ParseFront()
	{
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
		
		if (m_Context.Format().IsEqualToForward(':'))
		{
			m_Context.Format().IgnoreAllSpaces();
			TextProperties::TextFront::FrontID frontID = (static_cast<uint8_t>(m_Context.Format().GetWordFromList(frontCode)));
			FrontModif(frontID);
		}
		else
			ReloadDefaultFront();
	}

	template <typename BasicContext>
	void BasicTextPropertiesParser<BasicContext>::ReloadColorFG(const TextProperties::TextColor::ColorFG& target)
	{
		if (target.Type != m_CurrentContextProperties.Color.Fg.Type)
		{
			switch (target.Type)
			{
			case TextProperties::TextColor::ColorType::BasicColor:
				ColorModif(target.Data.BasicColor);
				break;
			case TextProperties::TextColor::ColorType::ColorCube:
				ColorModif(target.Data.ColorCube);
				break;
			case TextProperties::TextColor::ColorType::Color24b:
				ColorModif(target.Data.Color24b);
				break;
			}
		}
		else
		{
			switch (target.Type)
			{
			case TextProperties::TextColor::ColorType::BasicColor:
				if (m_CurrentContextProperties.Color.Fg.Data.BasicColor != target.Data.BasicColor)
					ColorModif(target.Data.BasicColor);
				break;
			case TextProperties::TextColor::ColorType::ColorCube:
				if (m_CurrentContextProperties.Color.Fg.Data.ColorCube != target.Data.ColorCube)
					ColorModif(target.Data.ColorCube);
				break;
			case TextProperties::TextColor::ColorType::Color24b:
				if (m_CurrentContextProperties.Color.Fg.Data.Color24b != target.Data.Color24b)
					ColorModif(target.Data.Color24b);
				break;
			}
		}
	}

	template <typename BasicContext>
	void BasicTextPropertiesParser<BasicContext>::ReloadColorBG(const TextProperties::TextColor::ColorBG& target)
	{
		if (target.Type != m_CurrentContextProperties.Color.Bg.Type)
		{
			switch (target.Type)
			{
				case TextProperties::TextColor::ColorType::BasicColor:
					ColorModif(target.Data.BasicColor);
					break;
				case TextProperties::TextColor::ColorType::ColorCube:
					ColorModif(target.Data.ColorCube);
					break;
				case TextProperties::TextColor::ColorType::Color24b:
					ColorModif(target.Data.Color24b);
					break;
			}
		}
		else
		{
			switch (target.Type)
			{
				case TextProperties::TextColor::ColorType::BasicColor:
					if (m_CurrentContextProperties.Color.Bg.Data.BasicColor != target.Data.BasicColor)
						ColorModif(target.Data.BasicColor);
					break;
				case TextProperties::TextColor::ColorType::ColorCube:
					if (m_CurrentContextProperties.Color.Bg.Data.ColorCube != target.Data.ColorCube)
						ColorModif(target.Data.ColorCube);
					break;
				case TextProperties::TextColor::ColorType::Color24b:
					if (m_CurrentContextProperties.Color.Bg.Data.Color24b != target.Data.Color24b) 
						ColorModif(target.Data.Color24b);
					break;
			}
		}
	}

	template <typename BasicContext>
	void BasicTextPropertiesParser<BasicContext>::ReloadStyle(const TextProperties::TextStyle::Style& target)
	{
		if (target.Intensity != m_CurrentContextProperties.Style.Intensity) { StyleModif(target.Intensity); 	m_CurrentContextProperties.Style.Intensity = target.Intensity; 	}
		if (target.Italic != m_CurrentContextProperties.Style.Italic) 		{ StyleModif(target.Italic); 		m_CurrentContextProperties.Style.Italic = target.Italic; 		}
		if (target.Blink != m_CurrentContextProperties.Style.Blink) 		{ StyleModif(target.Blink); 		m_CurrentContextProperties.Style.Blink = target.Blink; 			}
		if (target.Inverted != m_CurrentContextProperties.Style.Inverted) 	{ StyleModif(target.Inverted); 	m_CurrentContextProperties.Style.Inverted = target.Inverted; 	}
		if (target.Ideogram != m_CurrentContextProperties.Style.Ideogram) 	{ StyleModif(target.Ideogram); 	m_CurrentContextProperties.Style.Ideogram = target.Ideogram; 	}
		if (target.Script != m_CurrentContextProperties.Style.Script) 		{ StyleModif(target.Script); 		m_CurrentContextProperties.Style.Script = target.Script; 		}

		if (target.Underline != m_CurrentContextProperties.Style.Underline) { StyleModif(target.Underline); 	m_CurrentContextProperties.Style.Underline = target.Underline; }

		if (target.UnderlineColor.Type != m_CurrentContextProperties.Style.UnderlineColor.Type)
		{
			switch (target.UnderlineColor.Type)
			{
				case TextProperties::TextStyle::UnderlineColor::ColorType::Default:
					StyleModif(TextProperties::TextStyle::UnderlineColor::ColorCube{ TextProperties::TextStyle::UnderlineColor::ColorCube::Default });
					break;
				case TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube:
					StyleModif(target.UnderlineColor.Data.ColorCube);
					m_CurrentContextProperties.Style.UnderlineColor.Data.ColorCube = target.UnderlineColor.Data.ColorCube;
					break;
				case TextProperties::TextStyle::UnderlineColor::ColorType::Color24b:
					StyleModif(target.UnderlineColor.Data.Color24b);
					m_CurrentContextProperties.Style.UnderlineColor.Data.Color24b = target.UnderlineColor.Data.Color24b;
					break;
			}
			m_CurrentContextProperties.Style.UnderlineColor.Type = target.UnderlineColor.Type;
		}
		else
		{
			switch (target.UnderlineColor.Type)
			{
				case TextProperties::TextStyle::UnderlineColor::ColorType::Default:
					break;
				case TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube:
					if (m_CurrentContextProperties.Style.UnderlineColor.Data.ColorCube != target.UnderlineColor.Data.ColorCube)
					{
						StyleModif(target.UnderlineColor.Data.ColorCube);
						m_CurrentContextProperties.Style.UnderlineColor.Data.ColorCube = target.UnderlineColor.Data.ColorCube;
					}
					break;
				case TextProperties::TextStyle::UnderlineColor::ColorType::Color24b:
					if (m_CurrentContextProperties.Style.UnderlineColor.Data.Color24b != target.UnderlineColor.Data.Color24b)
					{
						StyleModif(target.UnderlineColor.Data.Color24b);
						m_CurrentContextProperties.Style.UnderlineColor.Data.Color24b = target.UnderlineColor.Data.Color24b;
					}
					break;
			}
		}
	}

	template <typename BasicContext>
	void BasicTextPropertiesParser<BasicContext>::ReloadFront(const TextProperties::TextFront::Front& target)
	{
		if (m_CurrentContextProperties.Front == target)
			return;

		FrontModif(target.CurrentID);
		m_CurrentContextProperties.Front = target;
	}
}
