#pragma once

#include "FMT/Detail/Detail.h"

namespace EngineCore::FMT::Detail {
	template<typename FormatterContext>
	struct TextPropertiesParser {

	public:
		explicit TextPropertiesParser(FormatterContext& context, const TextProperties::Properties* baseContextProperties = nullptr)
			: Context{context}
			, BaseContextProperties{baseContextProperties}
			, CurrentContexProperties{baseContextProperties == nullptr ? TextProperties::Properties{} : *baseContextProperties}
		{}

		~TextPropertiesParser()
		{
			if (BaseContextProperties != nullptr)
				Reload(*BaseContextProperties);
			else
				AllResetIfNeeded();
		}

		void SetBaseContextProperties(const TextProperties::Properties* baseContextProperties) { BaseContextProperties = baseContextProperties; }

	public:
		FormatIndex GetFormatIndexThrow()  { return Context.GetFormatIndexThrow(); }
		
	public:
		template <typename T>
		void ColorRun(const T& modif) { Context.RunType(modif); }

		template <typename T>
		void StyleRun(const T& modif) { Context.RunType(modif); }

		template <typename T>
		void FrontRun(const T& modif) { Context.RunType(modif); }

	public:
		void ColorRunOnIndex(const FormatIndex& index);
		void StyleRunOnIndex(const FormatIndex& index);
		void FrontRunOnIndex(const FormatIndex& index);

		void ParseColor();
		std::size_t GetColorCode();
		template <typename T>
		T GetColorCodeAuto();

		void ParseStyle();
		TextProperties::TextStyle::BasicStyle GetStyleCode();
		TextProperties::TextStyle::UnderlineColor::ColorCube SelectUnderlinedColorStyle();

		void ParseFront();
		TextProperties::TextFront::Front GetFrontCode();

	public:
		template <typename T>
		void ColorModif(const T& modif) 	{ CurrentContexProperties.Color.ModifyThrow(modif); }

		template <typename T>
		void StyleModif(const T& modif) 	{ CurrentContexProperties.Style.ModifyThrow(modif); }

		template <typename T>
		void FrontModif(const T& modif) 	{ CurrentContexProperties.Front.ModifyThrow(modif); }

		void ColorModifReset() 				{ CurrentContexProperties.Color.ModifyThrow(TextProperties::TextColor::Color{}); }
		void StyleModifReset() 				{ CurrentContexProperties.Style.ModifyThrow(TextProperties::TextStyle::Style{}); }
		void FrontModifReset() 				{ CurrentContexProperties.Front.ModifyThrow(TextProperties::TextFront::Front{}); }

		void AllModifReset() 				{ ColorModifReset(); StyleModifReset(); FrontModifReset(); }
		void AllReset() 					{ AllModifReset(); Context.RunType(TextProperties::Reset{}); }
		void AllResetIfNeeded() 			{
			if (CurrentContexProperties != TextProperties::Properties{})
				AllReset();
		}

	public:
		TextProperties::Properties Save() 							{ return CurrentContexProperties; }
		void Reload(const TextProperties::Properties& target);
		void ReloadColor(const TextProperties::TextColor::Color& target);
		void ReloadStyle(const TextProperties::TextStyle::Style& target);
		void ReloadFront(const TextProperties::TextFront::Front& target);

	public:
		FormatterContext& 					Context;
		const TextProperties::Properties* 	BaseContextProperties;
		TextProperties::Properties 			CurrentContexProperties;
	};
}


namespace EngineCore::FMT::Detail {
template<typename FormatterContext>
	void TextPropertiesParser<FormatterContext>::ColorRunOnIndex(const FormatIndex& index)
	{
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::Color>(		index, [this](const TextProperties::TextColor::Color& data) 		{ this->ColorRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::BasicColorFG>(	index, [this](const TextProperties::TextColor::BasicColorFG& data) 	{ this->ColorRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::BasicColorBG>(	index, [this](const TextProperties::TextColor::BasicColorBG& data) 	{ this->ColorRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::ColorCubeFG>(	index, [this](const Detail::TextProperties::TextColor::ColorCubeFG& data) 	{ this->ColorRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::ColorCubeBG>(	index, [this](const Detail::TextProperties::TextColor::ColorCubeBG& data) 	{ this->ColorRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::Color24bFG>(	index, [this](const Detail::TextProperties::TextColor::Color24bFG& data) 	{ this->ColorRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::Color24bBG>(	index, [this](const Detail::TextProperties::TextColor::Color24bBG& data) 	{ this->ColorRun(data); } );
	}

	template<typename FormatterContext>
	void TextPropertiesParser<FormatterContext>::StyleRunOnIndex(const FormatIndex& index)
	{
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Style>(							index, [this](const TextProperties::TextStyle::Style& data) 				{ this->StyleRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Intensity>(index, [this](const TextProperties::TextStyle::Intensity& data) 		{ this->StyleRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Italic>(	index, [this](const TextProperties::TextStyle::Italic& data) 			{ this->StyleRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Underline>(index, [this](const TextProperties::TextStyle::Underline& data) 		{ this->StyleRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Blink>(	index, [this](const TextProperties::TextStyle::Blink& data) 			{ this->StyleRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Inverted>(	index, [this](const TextProperties::TextStyle::Inverted& data) 			{ this->StyleRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Ideogram>(	index, [this](const TextProperties::TextStyle::Ideogram& data) 			{ this->StyleRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Script>(	index, [this](const TextProperties::TextStyle::Script& data) 			{ this->StyleRun(data); } );

		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::UnderlineColor::ColorCube>(		index, [this](const TextProperties::TextStyle::UnderlineColor::ColorCube& data) { this->StyleRun(data); } );
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::UnderlineColor::Color24b>(			index, [this](const TextProperties::TextStyle::UnderlineColor::Color24b& data) 	{ this->StyleRun(data); } );
	}

	template<typename FormatterContext>
	void TextPropertiesParser<FormatterContext>::FrontRunOnIndex(const FormatIndex& index)
	{
		Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextFront::Front>(index, [this](const TextProperties::TextFront::Front& data) { this->FrontRun(data); } );
	}

	template<typename FormatterContext>
	void TextPropertiesParser<FormatterContext>::ParseColor() {
		if (Context.Format().IsEqualToForward(':')) {
			Context.Format().IgnoreAllSpaces();
			if (Context.Format().IsEqualToForward('{'))
			{
				FormatIndex idx = GetFormatIndexThrow();
				ColorRunOnIndex(idx);
				Context.Format().IsEqualToForward('}');
			}
			else
			{
				TextProperties::TextColor::BasicColorFG colorFg = GetColorCodeAuto<TextProperties::TextColor::BasicColorFG>();

				Context.Format().ParamGoTo('-', ',');
				if (Context.Format().IsEqualToForward('-')) {
					Context.Format().IgnoreAllSpaces();
					TextProperties::TextColor::BasicColorBG colorBg = GetColorCodeAuto<TextProperties::TextColor::BasicColorBG>();
					ColorRun(TextProperties::TextColor::BasicColor{ colorFg, colorBg });
				}
				else
					ColorRun(colorFg);
			}
		}
		else
			ColorRun(TextProperties::TextColor::Reset{});
	}


	template<typename FormatterContext>
	std::size_t TextPropertiesParser<FormatterContext>::GetColorCode() {
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

	template<typename FormatterContext>
	template<typename T>
	T TextPropertiesParser<FormatterContext>::GetColorCodeAuto() {
		std::size_t step = static_cast<std::size_t>(Context.Format().IsEqualToForward('+') ? T::BaseBStep : T::BaseStep);
		std::size_t code = GetColorCode();
		if (code == Context.Format().GET_WORD_FROM_LIST_NOT_FOUND) 	return T::Default;
		return static_cast<T>(code + step);
	}

	template<typename FormatterContext>
	void TextPropertiesParser<FormatterContext>::ParseStyle() {
		if (Context.Format().IsEqualToForward(':')) {
			if (!Context.Format().IsEqualTo('}', ',')) {
				bool l = true;
				while (l) {
					Context.Format().IgnoreAllSpaces();
					if (Context.Format().IsEqualToForward('{'))
					{
						FormatIndex idx = GetFormatIndexThrow();
						StyleRunOnIndex(idx);
						Context.Format().IsEqualToForward('}');
					}
					else
					{
						TextProperties::TextStyle::BasicStyle style = GetStyleCode();
						if (style == TextProperties::TextStyle::BasicStyle::Underline_SelectColor)
						{
							TextProperties::TextStyle::UnderlineColor::ColorCube underlineColor = SelectUnderlinedColorStyle();
							StyleRun(underlineColor);
						}
						else	
							StyleRun(style);
					}
					Context.Format().ParamGoTo('|', ',');
					l = Context.Format().IsEqualToForward('|');
					Context.Format().IgnoreAllSpaces();
				}
			}
			else
				StyleRun(TextProperties::TextStyle::Reset{});
		}
		else
			StyleRun(TextProperties::TextStyle::Reset{});
	}

	template<typename FormatterContext>
	TextProperties::TextStyle::BasicStyle TextPropertiesParser<FormatterContext>::GetStyleCode() {
		using FormatType = typename FormatterContext::FormatBufferType;
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

		return Context.Format().GetWordFromList(styleCode);
	}

	template<typename FormatterContext>
	TextProperties::TextStyle::UnderlineColor::ColorCube TextPropertiesParser<FormatterContext>::SelectUnderlinedColorStyle() {
		Context.Format().ParamGoTo(':');
		Context.Format().IsEqualToForward(':');
		Context.Format().IgnoreAllSpaces();
		return GetColorCodeAuto<TextProperties::TextStyle::UnderlineColor::ColorCube>();
	}



	template<typename FormatterContext>
	void TextPropertiesParser<FormatterContext>::ParseFront() {
		if (Context.Format().IsEqualToForward(':')) {
			Context.Format().IgnoreAllSpaces();
			FrontRun(GetFrontCode());
		}
		else
			FrontRun(TextProperties::TextFront::Reset{});
	}

	template<typename FormatterContext>
	TextProperties::TextFront::Front TextPropertiesParser<FormatterContext>::GetFrontCode() {
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

		return TextProperties::TextFront::Front(static_cast<uint8_t>(Context.Format().GetWordFromList(frontCode)));
	}

	template<typename FormatterContext>
	void TextPropertiesParser<FormatterContext>::ReloadColor(const TextProperties::TextColor::Color& target)
	{
		if (target.Fg.Type != CurrentContexProperties.Color.Fg.Type) {
			switch (target.Fg.Type) {
			case TextProperties::TextColor::ColorType::Default:
				Context.RunType(TextProperties::TextColor::BasicColorFG::Default);
				break;
			case TextProperties::TextColor::ColorType::BasicColor:
				Context.RunType(target.Fg.Data.BasicColor);
				CurrentContexProperties.Color.Fg.Data.BasicColor = target.Fg.Data.BasicColor;
				break;
			case TextProperties::TextColor::ColorType::ColorCube:
				Context.RunType(target.Fg.Data.ColorCube);
				CurrentContexProperties.Color.Fg.Data.ColorCube = target.Fg.Data.ColorCube;
				break;
			case TextProperties::TextColor::ColorType::Color24b:
				Context.RunType(target.Fg.Data.Color24b);
				CurrentContexProperties.Color.Fg.Data.Color24b = target.Fg.Data.Color24b;
				break;
			}
			CurrentContexProperties.Color.Fg.Type = target.Fg.Type;
		}
		else {
			switch (target.Fg.Type) {
			case TextProperties::TextColor::ColorType::Default:
				break;
			case TextProperties::TextColor::ColorType::BasicColor:
				if (CurrentContexProperties.Color.Fg.Data.BasicColor != target.Fg.Data.BasicColor) 			Context.RunType(target.Fg.Data.BasicColor);
				CurrentContexProperties.Color.Fg.Data.BasicColor = target.Fg.Data.BasicColor;
				break;
			case TextProperties::TextColor::ColorType::ColorCube:
				if (CurrentContexProperties.Color.Fg.Data.ColorCube != target.Fg.Data.ColorCube) Context.RunType(target.Fg.Data.ColorCube);
				CurrentContexProperties.Color.Fg.Data.ColorCube = target.Fg.Data.ColorCube;
				break;
			case TextProperties::TextColor::ColorType::Color24b:
				if (CurrentContexProperties.Color.Fg.Data.Color24b != target.Fg.Data.Color24b) 	Context.RunType(target.Fg.Data.Color24b);
				CurrentContexProperties.Color.Fg.Data.Color24b = target.Fg.Data.Color24b;
				break;
			}
		}


		if (target.Bg.Type != CurrentContexProperties.Color.Bg.Type) {
			switch (target.Bg.Type) {
			case TextProperties::TextColor::ColorType::Default:
				Context.RunType(TextProperties::TextColor::BasicColorBG::Default);
				break;
			case TextProperties::TextColor::ColorType::BasicColor:
				Context.RunType(target.Bg.Data.BasicColor);
				CurrentContexProperties.Color.Bg.Data.BasicColor = target.Bg.Data.BasicColor;
				break;
			case TextProperties::TextColor::ColorType::ColorCube:
				Context.RunType(target.Bg.Data.ColorCube);
				CurrentContexProperties.Color.Bg.Data.ColorCube = target.Bg.Data.ColorCube;
				break;
			case TextProperties::TextColor::ColorType::Color24b:
				Context.RunType(target.Bg.Data.Color24b);
				CurrentContexProperties.Color.Bg.Data.Color24b = target.Bg.Data.Color24b;
				break;
			}
			CurrentContexProperties.Color.Bg.Type = target.Bg.Type;
		}
		else {
			switch (target.Bg.Type) {
			case TextProperties::TextColor::ColorType::Default:
				break;
			case TextProperties::TextColor::ColorType::BasicColor:
				if (CurrentContexProperties.Color.Bg.Data.BasicColor != target.Bg.Data.BasicColor) 			Context.RunType(target.Bg.Data.BasicColor);
				CurrentContexProperties.Color.Bg.Data.BasicColor = target.Bg.Data.BasicColor;
				break;
			case TextProperties::TextColor::ColorType::ColorCube:
				if (CurrentContexProperties.Color.Bg.Data.ColorCube != target.Bg.Data.ColorCube) 		Context.RunType(target.Bg.Data.ColorCube);
				CurrentContexProperties.Color.Bg.Data.ColorCube = target.Bg.Data.ColorCube;
				break;
			case TextProperties::TextColor::ColorType::Color24b:
				if (CurrentContexProperties.Color.Bg.Data.Color24b != target.Bg.Data.Color24b) 	Context.RunType(target.Bg.Data.Color24b);
				CurrentContexProperties.Color.Bg.Data.Color24b = target.Bg.Data.Color24b;
				break;
			}
		}
	}

	template<typename FormatterContext>
	void TextPropertiesParser<FormatterContext>::ReloadStyle(const TextProperties::TextStyle::Style& target)
	{
		if (CurrentContexProperties.Style.Intensity != target.Intensity) { Context.RunType(target.Intensity); 	CurrentContexProperties.Style.Intensity = target.Intensity; 	}
		if (CurrentContexProperties.Style.Italic != target.Italic) 		{ Context.RunType(target.Italic); 		CurrentContexProperties.Style.Italic = target.Italic; 		}
		if (CurrentContexProperties.Style.Blink != target.Blink) 		{ Context.RunType(target.Blink); 		CurrentContexProperties.Style.Blink = target.Blink; 			}
		if (CurrentContexProperties.Style.Inverted != target.Inverted) 	{ Context.RunType(target.Inverted); 	CurrentContexProperties.Style.Inverted = target.Inverted; 	}
		if (CurrentContexProperties.Style.Ideogram != target.Ideogram) 	{ Context.RunType(target.Ideogram); 	CurrentContexProperties.Style.Ideogram = target.Ideogram; 	}
		if (CurrentContexProperties.Style.Script != target.Script) 		{ Context.RunType(target.Script); 		CurrentContexProperties.Style.Script = target.Script; 		}

		if (CurrentContexProperties.Style.Underline != target.Underline) { Context.RunType(target.Underline); 	CurrentContexProperties.Style.Underline = target.Underline; }

		if (target.UnderlineColor.Type != CurrentContexProperties.Style.UnderlineColor.Type)
		{
			switch (target.UnderlineColor.Type) {
			case TextProperties::TextStyle::UnderlineColor::ColorType::Default:
				Context.RunType(TextProperties::TextStyle::UnderlineColor::Reset{});
				break;
			case TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube:
				Context.RunType(target.UnderlineColor.Data.ColorCube);
				CurrentContexProperties.Style.UnderlineColor.Data.ColorCube = target.UnderlineColor.Data.ColorCube;
				break;
			case TextProperties::TextStyle::UnderlineColor::ColorType::Color24b:
				Context.RunType(target.UnderlineColor.Data.Color24b);
				CurrentContexProperties.Style.UnderlineColor.Data.Color24b = target.UnderlineColor.Data.Color24b;
				break;
			}
			CurrentContexProperties.Style.UnderlineColor.Type = target.UnderlineColor.Type;
		}
		else
		{
			switch (target.UnderlineColor.Type) {
			case TextProperties::TextStyle::UnderlineColor::ColorType::Default:
				break;
			case TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube:
				if (CurrentContexProperties.Style.UnderlineColor.Data.ColorCube != target.UnderlineColor.Data.ColorCube) 		Context.RunType(target.UnderlineColor.Data.ColorCube);
				CurrentContexProperties.Style.UnderlineColor.Data.ColorCube = target.UnderlineColor.Data.ColorCube;
				break;
			case TextProperties::TextStyle::UnderlineColor::ColorType::Color24b:
				if (CurrentContexProperties.Style.UnderlineColor.Data.Color24b != target.UnderlineColor.Data.Color24b) 	Context.RunType(target.UnderlineColor.Data.Color24b);
				CurrentContexProperties.Style.UnderlineColor.Data.Color24b = target.UnderlineColor.Data.Color24b;
				break;
			}
		}
	}

	template<typename FormatterContext>
	void TextPropertiesParser<FormatterContext>::ReloadFront(const TextProperties::TextFront::Front& target)
	{
		if (CurrentContexProperties.Front == target)
			return;

		Context.RunType(target);
		CurrentContexProperties.Front = target;
	}

	template<typename FormatterContext>
	void TextPropertiesParser<FormatterContext>::Reload(const TextProperties::Properties& target)
	{
		ReloadColor(target.Color);
		ReloadStyle(target.Style);
		ReloadFront(target.Front);
	}
}
