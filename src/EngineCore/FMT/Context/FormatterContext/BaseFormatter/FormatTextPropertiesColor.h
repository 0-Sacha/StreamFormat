#pragma once

#include "FMT/Context/FormatterContext/BasicFormatterContext.h"

namespace EngineCore::FMT {

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::Reset, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextColor::Reset& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', 39, ';', 49, 'm');
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextColor::BasicColorFG& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::BasicColorBG, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextColor::BasicColorBG& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::BasicColor, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextColor::BasicColor& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t.Fg)
										 , ';', static_cast<std::uint8_t>(t.Bg), 'm');
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::Color24bFG, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextColor::Color24bFG& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[38;2;", t.R, ';', t.G, ';', t.B, 'm');
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::Color24bBG, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextColor::Color24bBG& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[48;2;", t.R, ';', t.G, ';', t.B, 'm');
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::Color24b, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextColor::Color24b& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[38;2;", t.Fg.R, ';', t.Fg.G, ';', t.Fg.B, "; 48; 2;", t.Bg.R, ';', t.Bg.G, ';', t.Bg.B, 'm');
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};


	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::ColorCubeFG, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextColor::ColorCubeFG& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[38;5;", t.GetColorRef(), 'm');
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::ColorCubeBG, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextColor::ColorCubeBG& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[48;5;", t.GetColorRef(), 'm');
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::ColorCube, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextColor::ColorCube& t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[48;5;", t.Fg.GetColorRef(), ";48;5;", t.Bg.GetColorRef(), 'm');
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

}