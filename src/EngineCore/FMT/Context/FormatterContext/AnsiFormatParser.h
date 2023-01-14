#pragma once

#include "FMT/Context/BasicContext/AnsiParser.h"

namespace EngineCore::FMT::Detail {
	template<typename FormatterContext, typename Format>
	struct AnsiFormatParser : public BasicAnsiParser<Format, AnsiFormatParser<FormatterContext, Format>> {
	
	public:
		using Base = BasicAnsiParser<Format, AnsiFormatParser<FormatterContext, Format>>;
		using ContextPackageSaving = Detail::AnsiTextData;

		using Base::ParseColor;
		using Base::ParseStyle;
		using Base::ParseFront;

	public:
		explicit AnsiFormatParser(FormatterContext& context)
			: Base{context.Format()}
			, ParentCurrentContext{nullptr}
			, CurrentContext{}
			, Context{context}
		{}

		template<typename ParentAnsiParser>
		explicit AnsiFormatParser(FormatterContext& context, ParentAnsiParser& parent)
			: Base{context.Format()}
			, ParentCurrentContext{&(parent.CurrentContext)}
			, CurrentContext{parent.CurrentContext}
			, Context{context}
		{}

	public:
		Detail::AnsiTextData* 	ParentCurrentContext;
		Detail::AnsiTextData 	CurrentContext;
		FormatterContext& 			Context;
	
	public:
		Detail::FormatIndex GetFormatIndexThrow() { return Context.GetFormatIndexThrow(); }

	public:
		template <typename T>
		void ColorModif(const T& modif) 	{ CurrentContext.Color.ModifyThrow(modif); }

		template <typename T>
		void StyleModif(const T& modif) 	{ CurrentContext.Style.ModifyThrow(modif); }

		template <typename T>
		void FrontModif(const T& modif) 	{ CurrentContext.Front.ModifyThrow(modif); }

		void ColorModifReset() 				{ CurrentContext.Color.ModifyThrow(Detail::AnsiColor{}); }
		void StyleModifReset() 				{ CurrentContext.Style.ModifyThrow(Detail::AnsiStyle{}); }
		void FrontModifReset() 				{ CurrentContext.Front.ModifyThrow(Detail::AnsiFront{}); }

		void AllModifReset() 				{ ColorModifReset(); StyleModifReset(); FrontModifReset(); }

	public:
		void AllReset() 					{ AllModifReset(); Context.RunType(Detail::ResetAnsiAllParameters{}); }
		void AllResetIfNeeded() 			{
			if (CurrentContext != Detail::AnsiTextData{})
				AllReset();
		}

	public:
		void Kill()
		{
			if (ParentCurrentContext != nullptr)
				*ParentCurrentContext = CurrentContext;
			else
				AllResetIfNeeded();
		}

	public:
		template <typename T>
		void ColorRun(const T& modif)		{ Context.RunType(modif); }

		void ColorRunOnIndex(const Detail::FormatIndex& index)
		{
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiColor>(		index, [this](const AnsiColor& data) 		{ this->ColorRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiTextColorFG>(	index, [this](const AnsiTextColorFG& data) 	{ this->ColorRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiTextColorBG>(	index, [this](const AnsiTextColorBG& data) 	{ this->ColorRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiNColorFg>(	index, [this](const AnsiNColorFg& data) 	{ this->ColorRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiNColorBg>(	index, [this](const AnsiNColorBg& data) 	{ this->ColorRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiColor24bFg>(	index, [this](const AnsiColor24bFg& data) 	{ this->ColorRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiColor24bBg>(	index, [this](const AnsiColor24bBg& data) 	{ this->ColorRun(data); } );
		}


		template <typename T>
		void StyleRun(const T& modif) 		{ Context.RunType(modif); }

		void StyleRunOnIndex(const Detail::FormatIndex& index)
		{
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiStyle>(				index, [this](const AnsiStyle& data) 				{ this->StyleRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiTFSIntensity>(		index, [this](const AnsiTFSIntensity& data) 		{ this->StyleRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiTFSItalic>(			index, [this](const AnsiTFSItalic& data) 			{ this->StyleRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiTFSUnderline>(		index, [this](const AnsiTFSUnderline& data) 		{ this->StyleRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiNColorUnderline>(		index, [this](const AnsiNColorUnderline& data) 		{ this->StyleRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiUnderlineColor24b>(	index, [this](const AnsiUnderlineColor24b& data) 	{ this->StyleRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiTFSBlink>(			index, [this](const AnsiTFSBlink& data) 			{ this->StyleRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiTFSInverted>(			index, [this](const AnsiTFSInverted& data) 			{ this->StyleRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiTFSIdeogram>(			index, [this](const AnsiTFSIdeogram& data) 			{ this->StyleRun(data); } );
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiTFSScript>(			index, [this](const AnsiTFSScript& data) 			{ this->StyleRun(data); } );
		}


		template <typename T>
		void FrontRun(const T& modif) 		{ Context.RunType(modif); }
		
		void FrontRunOnIndex(const Detail::FormatIndex& index)
		{
			Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<AnsiFront>(index, [this](const AnsiFront& data) { this->FrontRun(data); } );
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