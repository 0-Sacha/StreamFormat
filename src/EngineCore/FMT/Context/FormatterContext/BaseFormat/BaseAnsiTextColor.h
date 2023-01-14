#pragma once

#include "FMT/Context/FormatterContext/BasicFormatterContext.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace EngineCore::FMT {

	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiTextColorFG, FormatterContext>
	{
		static void Write(const Detail::AnsiTextColorFG& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiTextColorBG, FormatterContext>
	{
		static void Write(const Detail::AnsiTextColorBG& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiTextColor, FormatterContext>
	{
		static void Write(const Detail::AnsiTextColor& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t.Fg)
										 , ';', static_cast<std::uint8_t>(t.Bg), 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiColor24bFg, FormatterContext>
	{
		static void Write(const Detail::AnsiColor24bFg& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[38;2;", t.R, ';', t.G, ';', t.B, 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiColor24bBg, FormatterContext>
	{
		static void Write(const Detail::AnsiColor24bBg& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[48;2;", t.R, ';', t.G, ';', t.B, 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiColor24b, FormatterContext>
	{
		static void Write(const Detail::AnsiColor24b& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[38;2;", t.Fg.R, ';', t.Fg.G, ';', t.Fg.B, "; 48; 2;", t.Bg.R, ';', t.Bg.G, ';', t.Bg.B, 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};


	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiNColorFg, FormatterContext>
	{
		static void Write(const Detail::AnsiNColorFg& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[38;5;", t.GetColorRef(), 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiNColorBg, FormatterContext>
	{
		static void Write(const Detail::AnsiNColorBg& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[48;5;", t.GetColorRef(), 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiNColor, FormatterContext>
	{
		static void Write(const Detail::AnsiNColor& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[48;5;", t.Fg.GetColorRef(), ";48;5;", t.Bg.GetColorRef(), 'm');
			context.GetAnsiManager().ColorModif(t);
		}
	};

}