#pragma once

#include "../BasicContext/AnsiParseur.h"

namespace EngineCore::Instrumentation::FMT::Detail {
	template<typename FormatContext>
	struct AnsiFormatParser : BasicAnsiParseur<FormatBuffer> {
	
	public:
		using Base = BasicAnsiParseur<FormatBuffer>;
		using ContextPackageSaving = Detail::AnsiData;

	public:
		explicit AnsiFormatParser(FormatContext& context)
			: Base(context.Format())
			, Context(context)
		{}

	public:
		Detail::AnsiTextData 	CurrentContext;
		FormatContext& 			Context;
	
	public:
		void ColorRunOnIndex() (const Detail::FormatIndex& index)
		{
			ColorRun(Context.GetTypeAtIndexAuto(index));
		}

		template <typename T>
		void ColorRun()(const T& modif)
		{
			CurrentContext.Color.ModifyThrow(modif);
			Context.RunType(modif);
		}

		void StyleRunOnIndex() (const Detail::FormatIndex& index)
		{
			StyleRun(Context.GetTypeAtIndexAuto(index));
		}

		template <typename T>
		void StyleRun()(const T& modif)
		{
			CurrentContext.Style.ModifyThrow(modif);
			Context.RunType(modif);
		}

		void FrontRunOnIndex() (const Detail::FormatIndex& index)
		{
			FrontRun(Context.GetTypeAtIndexAuto(index));
		}

		template <typename T>
		void FrontRun()(const T& modif)
		{
			CurrentContext.Front.ModifyThrow(modif);
			Context.RunType(modif);
		}

	public:
		Detail::AnsiTextData Save() 					{ return CurrentContext; }
		void Reload(const Detail::AnsiTextData& target) {
			ReloadColor(target.Color);
			ReloadStyle(target.Style);
			ReloadFront(target.Front);
		}

		void ReloadColor(const Detail::AnsiColor& target) {
			if (target.FgType != CurrentContext.Color.FgType) {
				switch (target.FgType) {
				case Detail::AnsiColorDataType::Default:
					RunType(Detail::AnsiTextColorFG::Default);
					break;
				case Detail::AnsiColorDataType::AnsiTextColor:
					RunType(target.Fg.Text);
					CurrentContext.Color.Fg.Text = target.Fg.Text;
					break;
				case Detail::AnsiColorDataType::AnsiNColor:
					RunType(target.Fg.ColorN);
					CurrentContext.Color.Fg.ColorN = target.Fg.ColorN;
					break;
				case Detail::AnsiColorDataType::AnsiColor24b:
					RunType(target.Fg.Color24b);
					CurrentContext.Color.Fg.Color24b = target.Fg.Color24b;
					break;
				}
				CurrentContext.Color.FgType = target.FgType;
			}
			else {
				switch (target.FgType) {
				case Detail::AnsiColorDataType::Default:
					break;
				case Detail::AnsiColorDataType::AnsiTextColor:
					if (CurrentContext.Color.Fg.Text != target.Fg.Text) 		RunType(target.Fg.Text);
					CurrentContext.Color.Fg.Text = target.Fg.Text;
					break;
				case Detail::AnsiColorDataType::AnsiNColor:
					if (CurrentContext.Color.Fg.NColor != target.Fg.NColor) 	RunType(target.Fg.ColorN);
					CurrentContext.Color.Fg.ColorN = target.Fg.ColorN;
					break;
				case Detail::AnsiColorDataType::AnsiColor24b:
					if (CurrentContext.Color.Fg.Color24b != target.Fg.Color24b) RunType(target.Fg.Color24b);
					CurrentContext.Color.Fg.Color24b = target.Fg.Color24b;
					break;
				}
			}


			if (target.BgType != CurrentContext.Color.BgType) {
				switch (target.BgType) {
				case Detail::AnsiColorDataType::Default:
					RunType(Detail::AnsiTextColorBG::Default);
					break;
				case Detail::AnsiColorDataType::AnsiTextColor:
					RunType(target.Bg.Text);
					CurrentContext.Color.Bg.Text = target.Bg.Text;
					break;
				case Detail::AnsiColorDataType::AnsiNColor:
					RunType(target.Bg.ColorN);
					CurrentContext.Color.Bg.ColorN = target.Bg.ColorN;
					break;
				case Detail::AnsiColorDataType::AnsiColor24b:
					RunType(target.Bg.Color24b);
					CurrentContext.Color.Bg.Color24b = target.Bg.Color24b;
					break;
				}
				CurrentContext.Color.BgType = target.BgType;
			}
			else {
				switch (target.BgType) {
				case Detail::AnsiColorDataType::Default:
					break;
				case Detail::AnsiColorDataType::AnsiTextColor:
					if (CurrentContext.Color.Bg.Text != target.Bg.Text) 		RunType(target.Bg.Text);
					CurrentContext.Color.Bg.Text = target.Bg.Text;
					break;
				case Detail::AnsiColorDataType::AnsiNColor:
					if (CurrentContext.Color.Bg.NColor != target.Bg.NColor) 	RunType(target.Bg.ColorN);
					CurrentContext.Color.Bg.ColorN = target.Bg.ColorN;
					break;
				case Detail::AnsiColorDataType::AnsiColor24b:
					if (CurrentContext.Color.Bg.Color24b != target.Bg.Color24b) RunType(target.Bg.Color24b);
					CurrentContext.Color.Bg.Color24b = target.Bg.Color24b;
					break;
				}
			}
		}


		void ReloadFront(const Detail::AnsiFront& target) {
			if (CurrentContext.Front != target)
			{
				RunType(target);
				CurrentContext.Front = target;
			}
		}

		void ReloadStyle(const Detail::AnsiStyle& target) {
			if (CurrentContext.Style.Intensity != target.Intensity) { RunType(targetStyle.Intensity); 	CurrentContext.Style.Intensity = target.Intensity; 	}
			if (CurrentContext.Style.Italic != target.Italic) 		{ RunType(targetStyle.Italic); 		CurrentContext.Style.Italic = target.Italic; 		}
			if (CurrentContext.Style.Blink != target.Blink) 		{ RunType(targetStyle.Blink); 		CurrentContext.Style.Blink = target.Blink; 			}
			if (CurrentContext.Style.Inverted != target.Inverted) 	{ RunType(targetStyle.Inverted); 	CurrentContext.Style.Inverted = target.Inverted; 	}
			if (CurrentContext.Style.Ideogram != target.Ideogram) 	{ RunType(targetStyle.Ideogram); 	CurrentContext.Style.Ideogram = target.Ideogram; 	}
			if (CurrentContext.Style.Script != target.Script) 		{ RunType(targetStyle.Script); 		CurrentContext.Style.Script = target.Script; 		}

			if (CurrentContext.Style.Underline != target.Underline) { RunType(targetStyle.Underline); CurrentContext.Style.Underline = target.Underline; }


			if (target.UnderlineColorType != CurrentContext.Style.UnderlineColorType) {
				switch (target.BgType) {
				case Detail::AnsiColorUnderlineType::Default:
					RunType(RESET_ANSI_UNDERLINE_COLOR);
					break;
				case Detail::AnsiColorUnderlineType::AnsiNColor:
					RunType(target.UnderlineColor.ColorN);
					CurrentContext.Style.UnderlineColor.ColorN = target.UnderlineColor.ColorN;
					break;
				case Detail::AnsiColorUnderlineType::AnsiColor24b:
					RunType(target.UnderlineColor.Color24b);
					CurrentContext.Style.UnderlineColor.Color24b = target.UnderlineColor.Color24b;
					break;
				}
				CurrentContext.Color.UnderlineColorType = target.UnderlineColorType;
			}
			else {
				switch (target.UnderlineColorType) {
				case Detail::AnsiColorUnderlineType::Default:
					break;
				case Detail::AnsiColorUnderlineType::AnsiNColor:
					if (CurrentContext.Style.UnderlineColor.NColor != target.UnderlineColor.NColor) 	RunType(target.UnderlineColor.ColorN);
					CurrentContext.Style.UnderlineColor.ColorN = target.UnderlineColor.ColorN;
					break;
				case Detail::AnsiColorUnderlineType::AnsiColor24b:
					if (CurrentContext.Style.UnderlineColor.Color24b != target.UnderlineColor.Color24b) RunType(target.UnderlineColor.Color24b);
					CurrentContext.Style.UnderlineColor.Color24b = target.UnderlineColor.Color24b;
					break;
				}
			}
		}
	};
}