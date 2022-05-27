#pragma once

#include "../BasicContext/AnsiParseur.h"

namespace EngineCore::Instrumentation::FMT::Detail {
	template<typename FormatContext, typename CharFormat>
	struct AnsiFormatParser : BasicAnsiParseur<CharFormat> {
	
	public:
		using Base = BasicAnsiParseur<CharFormat>;
		using ContextPackageSaving = Detail::AnsiTextData;

	public:
		explicit AnsiFormatParser(FormatContext& context)
			: Base(context.Format())
			, Context(context)
		{}

	public:
		Detail::AnsiTextData 	CurrentContext;
		FormatContext& 			Context;
	
	public:
		template <typename T>
		void ColorRun(const T& modif)
		{
			CurrentContext.Color.ModifyThrow(modif);
			Context.RunType(modif);
		}

		void ColorRunOnIndex(const Detail::FormatIndex& index)
		{
			Context.template RunFuncFromTypeAtIndex<AnsiColor>(			index, [this](const AnsiColor& data) 		{ this->Context.ColorRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiTextColorFG>(	index, [this](const AnsiTextColorFG& data) 	{ this->Context.ColorRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiTextColorBG>(	index, [this](const AnsiTextColorBG& data) 	{ this->Context.ColorRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiNColorFg>(		index, [this](const AnsiNColorFg& data) 	{ this->Context.ColorRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiNColorBg>(		index, [this](const AnsiNColorBg& data) 	{ this->Context.ColorRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiColor24bFg>(	index, [this](const AnsiColor24bFg& data) 	{ this->Context.ColorRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiColor24bBg>(	index, [this](const AnsiColor24bBg& data) 	{ this->Context.ColorRun(data); } );
		}


		template <typename T>
		void StyleRun(const T& modif)
		{
			CurrentContext.Style.ModifyThrow(modif);
			Context.RunType(modif);
		}

		void StyleRunOnIndex(const Detail::FormatIndex& index)
		{
			Context.template RunFuncFromTypeAtIndex<AnsiStyle>(				index, [this](const AnsiStyle& data) 				{ this->Context.StyleRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiTFSIntensity>(		index, [this](const AnsiTFSIntensity& data) 		{ this->Context.StyleRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiTFSItalic>(			index, [this](const AnsiTFSItalic& data) 			{ this->Context.StyleRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiTFSUnderline>(		index, [this](const AnsiTFSUnderline& data) 		{ this->Context.StyleRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiNColorUnderline>(	index, [this](const AnsiNColorUnderline& data) 		{ this->Context.StyleRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiUnderlineColor24b>(	index, [this](const AnsiUnderlineColor24b& data) 	{ this->Context.StyleRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiTFSBlink>(			index, [this](const AnsiTFSBlink& data) 			{ this->Context.StyleRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiTFSInverted>(		index, [this](const AnsiTFSInverted& data) 			{ this->Context.StyleRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiTFSIdeogram>(		index, [this](const AnsiTFSIdeogram& data) 			{ this->Context.StyleRun(data); } );
			Context.template RunFuncFromTypeAtIndex<AnsiTFSScript>(			index, [this](const AnsiTFSScript& data) 			{ this->Context.StyleRun(data); } );
		}


		template <typename T>
		void FrontRun(const T& modif)
		{
			CurrentContext.Front.ModifyThrow(modif);
			Context.RunType(modif);
		}
		
		void FrontRunOnIndex(const Detail::FormatIndex& index)
		{
			Context.template RunFuncFromTypeAtIndex<AnsiFront>(index, [this](const AnsiFront& data) { this->Context.FrontRun(data); } );
		}

	public:
		Detail::AnsiTextData Save() 					{ return CurrentContext; }
		void Reload(const Detail::AnsiTextData& target) {
			ReloadColor(target.Color);
			ReloadStyle(target.Style);
			ReloadFront(target.Front);
		}

		void ReloadColor(const Detail::AnsiColor& target) {
			if (target.Fg.Type != CurrentContext.Color.Fg.Type) {
				switch (target.Fg.Type) {
				case Detail::AnsiColorDataType::Default:
					Context.RunType(Detail::AnsiTextColorFG::Default);
					break;
				case Detail::AnsiColorDataType::AnsiTextColor:
					Context.RunType(target.Fg.Data.Text);
					CurrentContext.Color.Fg.Data.Text = target.Fg.Data.Text;
					break;
				case Detail::AnsiColorDataType::AnsiNColor:
					Context.RunType(target.Fg.Data.NColor);
					CurrentContext.Color.Fg.Data.NColor = target.Fg.Data.NColor;
					break;
				case Detail::AnsiColorDataType::AnsiColor24b:
					Context.RunType(target.Fg.Data.Color24b);
					CurrentContext.Color.Fg.Data.Color24b = target.Fg.Data.Color24b;
					break;
				}
				CurrentContext.Color.Fg.Type = target.Fg.Type;
			}
			else {
				switch (target.Fg.Type) {
				case Detail::AnsiColorDataType::Default:
					break;
				case Detail::AnsiColorDataType::AnsiTextColor:
					if (CurrentContext.Color.Fg.Data.Text != target.Fg.Data.Text) 			Context.RunType(target.Fg.Data.Text);
					CurrentContext.Color.Fg.Data.Text = target.Fg.Data.Text;
					break;
				case Detail::AnsiColorDataType::AnsiNColor:
					if (CurrentContext.Color.Fg.Data.NColor != target.Fg.Data.NColor) 		Context.RunType(target.Fg.Data.NColor);
					CurrentContext.Color.Fg.Data.NColor = target.Fg.Data.NColor;
					break;
				case Detail::AnsiColorDataType::AnsiColor24b:
					if (CurrentContext.Color.Fg.Data.Color24b != target.Fg.Data.Color24b) 	Context.RunType(target.Fg.Data.Color24b);
					CurrentContext.Color.Fg.Data.Color24b = target.Fg.Data.Color24b;
					break;
				}
			}


			if (target.Bg.Type != CurrentContext.Color.Bg.Type) {
				switch (target.Bg.Type) {
				case Detail::AnsiColorDataType::Default:
					Context.RunType(Detail::AnsiTextColorBG::Default);
					break;
				case Detail::AnsiColorDataType::AnsiTextColor:
					Context.RunType(target.Bg.Data.Text);
					CurrentContext.Color.Bg.Data.Text = target.Bg.Data.Text;
					break;
				case Detail::AnsiColorDataType::AnsiNColor:
					Context.RunType(target.Bg.Data.NColor);
					CurrentContext.Color.Bg.Data.NColor = target.Bg.Data.NColor;
					break;
				case Detail::AnsiColorDataType::AnsiColor24b:
					Context.RunType(target.Bg.Data.Color24b);
					CurrentContext.Color.Bg.Data.Color24b = target.Bg.Data.Color24b;
					break;
				}
				CurrentContext.Color.Bg.Type = target.Bg.Type;
			}
			else {
				switch (target.Bg.Type) {
				case Detail::AnsiColorDataType::Default:
					break;
				case Detail::AnsiColorDataType::AnsiTextColor:
					if (CurrentContext.Color.Bg.Data.Text != target.Bg.Data.Text) 			Context.RunType(target.Bg.Data.Text);
					CurrentContext.Color.Bg.Data.Text = target.Bg.Data.Text;
					break;
				case Detail::AnsiColorDataType::AnsiNColor:
					if (CurrentContext.Color.Bg.Data.NColor != target.Bg.Data.NColor) 		Context.RunType(target.Bg.Data.NColor);
					CurrentContext.Color.Bg.Data.NColor = target.Bg.Data.NColor;
					break;
				case Detail::AnsiColorDataType::AnsiColor24b:
					if (CurrentContext.Color.Bg.Data.Color24b != target.Bg.Data.Color24b) 	Context.RunType(target.Bg.Data.Color24b);
					CurrentContext.Color.Bg.Data.Color24b = target.Bg.Data.Color24b;
					break;
				}
			}
		}


		void ReloadFront(const Detail::AnsiFront& target) {
			if (CurrentContext.Front != target)
			{
				Context.RunType(target);
				CurrentContext.Front = target;
			}
		}

		void ReloadStyle(const Detail::AnsiStyle& target) {
			if (CurrentContext.Style.Intensity != target.Intensity) { Context.RunType(target.Intensity); 	CurrentContext.Style.Intensity = target.Intensity; 	}
			if (CurrentContext.Style.Italic != target.Italic) 		{ Context.RunType(target.Italic); 		CurrentContext.Style.Italic = target.Italic; 		}
			if (CurrentContext.Style.Blink != target.Blink) 		{ Context.RunType(target.Blink); 		CurrentContext.Style.Blink = target.Blink; 			}
			if (CurrentContext.Style.Inverted != target.Inverted) 	{ Context.RunType(target.Inverted); 	CurrentContext.Style.Inverted = target.Inverted; 	}
			if (CurrentContext.Style.Ideogram != target.Ideogram) 	{ Context.RunType(target.Ideogram); 	CurrentContext.Style.Ideogram = target.Ideogram; 	}
			if (CurrentContext.Style.Script != target.Script) 		{ Context.RunType(target.Script); 		CurrentContext.Style.Script = target.Script; 		}

			if (CurrentContext.Style.Underline != target.Underline) { Context.RunType(target.Underline); 	CurrentContext.Style.Underline = target.Underline; }


			if (target.UnderlineColor.Type != CurrentContext.Style.UnderlineColor.Type) {
				switch (target.UnderlineColor.Type) {
				case Detail::AnsiUnderlineColorType::Default:
					Context.RunType(RESET_ANSI_UNDERLINE_COLOR);
					break;
				case Detail::AnsiUnderlineColorType::AnsiNColor:
					Context.RunType(target.UnderlineColor.Data.NColor);
					CurrentContext.Style.UnderlineColor.Data.NColor = target.UnderlineColor.Data.NColor;
					break;
				case Detail::AnsiUnderlineColorType::AnsiColor24b:
					Context.RunType(target.UnderlineColor.Data.Color24b);
					CurrentContext.Style.UnderlineColor.Data.Color24b = target.UnderlineColor.Data.Color24b;
					break;
				}
				CurrentContext.Style.UnderlineColor.Type = target.UnderlineColor.Type;
			}
			else {
				switch (target.UnderlineColor.Type) {
				case Detail::AnsiUnderlineColorType::Default:
					break;
				case Detail::AnsiUnderlineColorType::AnsiNColor:
					if (CurrentContext.Style.UnderlineColor.Data.NColor != target.UnderlineColor.Data.NColor) 		Context.RunType(target.UnderlineColor.Data.NColor);
					CurrentContext.Style.UnderlineColor.Data.NColor = target.UnderlineColor.Data.NColor;
					break;
				case Detail::AnsiUnderlineColorType::AnsiColor24b:
					if (CurrentContext.Style.UnderlineColor.Data.Color24b != target.UnderlineColor.Data.Color24b) 	Context.RunType(target.UnderlineColor.Data.Color24b);
					CurrentContext.Style.UnderlineColor.Data.Color24b = target.UnderlineColor.Data.Color24b;
					break;
				}
			}
		}
	};
}