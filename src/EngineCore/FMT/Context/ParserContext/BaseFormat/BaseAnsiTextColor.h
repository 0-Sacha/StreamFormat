#pragma once

#include "FMT/Context/ParserContext/BasicParserContext.h"

namespace EngineCore::FMT {

	template<typename ParserContext>
	struct ParserType<Detail::AnsiTextColorFG, ParserContext>
	{
		static void Read(Detail::AnsiTextColorFG& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetFg = true;
			context.GetAnsiTextCurrentColor().FgType = Detail::AnsiColorDataType::AnsiTextColor;
			context.GetAnsiTextCurrentColor().Color.Fg = t;

			context.BasicReadType('\033', '[', (std::uint8_t&)(t), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::AnsiTextColorBG, ParserContext>
	{
		static void Read(Detail::AnsiTextColorBG& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetBg = true;
			context.GetAnsiTextCurrentColor().BgType = Detail::AnsiColorDataType::AnsiTextColor;
			context.GetAnsiTextCurrentColor().Color.Bg = t;

			context.BasicReadType('\033', '[', (std::uint8_t&)(t), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::AnsiTextColor, ParserContext>
	{
		static void Read(Detail::AnsiTextColor& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetFg = true;
			context.GetFormatData().AnsiTextColorChange.HasSetBg = true;
			context.GetAnsiTextCurrentColor().FgType = Detail::AnsiColorDataType::AnsiTextColor;
			context.GetAnsiTextCurrentColor().BgType = Detail::AnsiColorDataType::AnsiTextColor;
			context.GetAnsiTextCurrentColor().Color = t;

			context.BasicReadType('\033', '[', (std::uint8_t&)(t.Fg), ';'
											 , (std::uint8_t&)(t.Bg), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::AnsiColor24bFg, ParserContext>
	{
		static void Read(Detail::AnsiColor24bFg& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetFg = true;
			context.GetAnsiTextCurrentColor().FgType = Detail::AnsiColorDataType::AnsiColor24b;
			context.GetAnsiTextCurrentColor().Color24bits.Fg = t;

			context.BasicReadType("\033[38;2;", t.R, ';', t.G, ';', t.B, 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::AnsiColor24bBg, ParserContext>
	{
		static void Read(Detail::AnsiColor24bBg& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetBg = true;
			context.GetAnsiTextCurrentColor().BgType = Detail::AnsiColorDataType::AnsiColor24b;
			context.GetAnsiTextCurrentColor().Color24bits.Bg = t;

			context.BasicReadType("\033[48;2;", t.R, ';', t.G, ';', t.B, 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::AnsiColor24b, ParserContext>
	{
		static void Read(Detail::AnsiColor24b& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetFg = true;
			context.GetFormatData().AnsiTextColorChange.HasSetBg = true;
			context.GetAnsiTextCurrentColor().FgType = Detail::AnsiColorDataType::AnsiColor24b;
			context.GetAnsiTextCurrentColor().BgType = Detail::AnsiColorDataType::AnsiColor24b;
			context.GetAnsiTextCurrentColor().Color24bits = t;

			context.BasicReadType("\033[38;2;", t.Fg.R, ';', t.Fg.G, ';', t.Fg.B, "; 48; 2;", t.Bg.R, ';', t.Bg.G, ';', t.Bg.B, 'm');
		}
	};


	template<typename ParserContext>
	struct ParserType<Detail::AnsiNColorFg, ParserContext>
	{
		static void Read(Detail::AnsiNColorFg& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetFg = true;
			context.GetAnsiTextCurrentColor().FgType = Detail::AnsiColorDataType::AnsiNColor;
			context.GetAnsiTextCurrentColor().ColorN.Fg = t;

			context.BasicReadType("\033[38;5;", t.GetColorRef(), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::AnsiNColorBg, ParserContext>
	{
		static void Read(Detail::AnsiNColorBg& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetBg = true;
			context.GetAnsiTextCurrentColor().BgType = Detail::AnsiColorDataType::AnsiNColor;
			context.GetAnsiTextCurrentColor().ColorN.Bg = t;

			context.BasicReadType("\033[48;5;", t.GetColorRef(), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::AnsiNColor, ParserContext>
	{
		static void Read(const Detail::AnsiNColor& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetFg = true;
			context.GetFormatData().AnsiTextColorChange.HasSetBg = true;
			context.GetAnsiTextCurrentColor().FgType = Detail::AnsiColorDataType::AnsiNColor;
			context.GetAnsiTextCurrentColor().BgType = Detail::AnsiColorDataType::AnsiNColor;
			context.GetAnsiTextCurrentColor().ColorN = t;

			context.BasicReadType("\033[48;5;", t.Fg.GetColorRef(), ";48;5;", t.Bg.GetColorRef(), 'm');
		}
	};

}