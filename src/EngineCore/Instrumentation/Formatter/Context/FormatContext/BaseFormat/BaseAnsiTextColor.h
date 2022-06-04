#pragma once

#include "../BasicFormatContext.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace EngineCore::FMT {

	template<typename FormatContext>
	struct FormatType<Detail::AnsiTextColorFG, FormatContext>
	{
		static void Write(const Detail::AnsiTextColorFG& t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatContext>
	struct FormatType<Detail::AnsiTextColorBG, FormatContext>
	{
		static void Write(const Detail::AnsiTextColorBG& t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatContext>
	struct FormatType<Detail::AnsiTextColor, FormatContext>
	{
		static void Write(const Detail::AnsiTextColor& t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t.Fg)
										 , ';', static_cast<std::uint8_t>(t.Bg), 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatContext>
	struct FormatType<Detail::AnsiColor24bFg, FormatContext>
	{
		static void Write(const Detail::AnsiColor24bFg& t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[38;2;", t.R, ';', t.G, ';', t.B, 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatContext>
	struct FormatType<Detail::AnsiColor24bBg, FormatContext>
	{
		static void Write(const Detail::AnsiColor24bBg& t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[48;2;", t.R, ';', t.G, ';', t.B, 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatContext>
	struct FormatType<Detail::AnsiColor24b, FormatContext>
	{
		static void Write(const Detail::AnsiColor24b& t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[38;2;", t.Fg.R, ';', t.Fg.G, ';', t.Fg.B, "; 48; 2;", t.Bg.R, ';', t.Bg.G, ';', t.Bg.B, 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};


	template<typename FormatContext>
	struct FormatType<Detail::AnsiNColorFg, FormatContext>
	{
		static void Write(const Detail::AnsiNColorFg& t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[38;5;", t.GetColorRef(), 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatContext>
	struct FormatType<Detail::AnsiNColorBg, FormatContext>
	{
		static void Write(const Detail::AnsiNColorBg& t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[48;5;", t.GetColorRef(), 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatContext>
	struct FormatType<Detail::AnsiNColor, FormatContext>
	{
		static void Write(const Detail::AnsiNColor& t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[48;5;", t.Fg.GetColorRef(), ";48;5;", t.Bg.GetColorRef(), 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

}