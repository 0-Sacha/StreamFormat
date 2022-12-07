#pragma once

#include "FMT/Context/UnFormatContext/BasicUnFormatContext.h"

namespace EngineCore::FMT {

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiTextColorFG, UnFormatContext>
	{
		static void Read(Detail::AnsiTextColorFG& t, UnFormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetFg = true;
			context.GetAnsiTextCurrentColor().FgType = Detail::AnsiColorDataType::AnsiTextColor;
			context.GetAnsiTextCurrentColor().Color.Fg = t;

			context.BasicReadType('\033', '[', (std::uint8_t&)(t), 'm');
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiTextColorBG, UnFormatContext>
	{
		static void Read(Detail::AnsiTextColorBG& t, UnFormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetBg = true;
			context.GetAnsiTextCurrentColor().BgType = Detail::AnsiColorDataType::AnsiTextColor;
			context.GetAnsiTextCurrentColor().Color.Bg = t;

			context.BasicReadType('\033', '[', (std::uint8_t&)(t), 'm');
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiTextColor, UnFormatContext>
	{
		static void Read(Detail::AnsiTextColor& t, UnFormatContext& context) {
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

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiColor24bFg, UnFormatContext>
	{
		static void Read(Detail::AnsiColor24bFg& t, UnFormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetFg = true;
			context.GetAnsiTextCurrentColor().FgType = Detail::AnsiColorDataType::AnsiColor24b;
			context.GetAnsiTextCurrentColor().Color24bits.Fg = t;

			context.BasicReadType("\033[38;2;", t.R, ';', t.G, ';', t.B, 'm');
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiColor24bBg, UnFormatContext>
	{
		static void Read(Detail::AnsiColor24bBg& t, UnFormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetBg = true;
			context.GetAnsiTextCurrentColor().BgType = Detail::AnsiColorDataType::AnsiColor24b;
			context.GetAnsiTextCurrentColor().Color24bits.Bg = t;

			context.BasicReadType("\033[48;2;", t.R, ';', t.G, ';', t.B, 'm');
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiColor24b, UnFormatContext>
	{
		static void Read(Detail::AnsiColor24b& t, UnFormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetFg = true;
			context.GetFormatData().AnsiTextColorChange.HasSetBg = true;
			context.GetAnsiTextCurrentColor().FgType = Detail::AnsiColorDataType::AnsiColor24b;
			context.GetAnsiTextCurrentColor().BgType = Detail::AnsiColorDataType::AnsiColor24b;
			context.GetAnsiTextCurrentColor().Color24bits = t;

			context.BasicReadType("\033[38;2;", t.Fg.R, ';', t.Fg.G, ';', t.Fg.B, "; 48; 2;", t.Bg.R, ';', t.Bg.G, ';', t.Bg.B, 'm');
		}
	};


	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiNColorFg, UnFormatContext>
	{
		static void Read(Detail::AnsiNColorFg& t, UnFormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetFg = true;
			context.GetAnsiTextCurrentColor().FgType = Detail::AnsiColorDataType::AnsiNColor;
			context.GetAnsiTextCurrentColor().ColorN.Fg = t;

			context.BasicReadType("\033[38;5;", t.GetColorRef(), 'm');
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiNColorBg, UnFormatContext>
	{
		static void Read(Detail::AnsiNColorBg& t, UnFormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().AnsiTextColorChange.HasSetBg = true;
			context.GetAnsiTextCurrentColor().BgType = Detail::AnsiColorDataType::AnsiNColor;
			context.GetAnsiTextCurrentColor().ColorN.Bg = t;

			context.BasicReadType("\033[48;5;", t.GetColorRef(), 'm');
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiNColor, UnFormatContext>
	{
		static void Read(const Detail::AnsiNColor& t, UnFormatContext& context) {
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