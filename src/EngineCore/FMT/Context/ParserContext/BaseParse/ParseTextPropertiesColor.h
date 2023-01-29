#pragma once

#include "FMT/Context/ParserContext/BasicParserContext.h"

namespace EngineCore::FMT {

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextColor::BasicColorFG, ParserContext>
	{
		static void Read(Detail::TextProperties::TextColor::BasicColorFG& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().BasicColorChange.HasSetFg = true;
			context.GetTextProperties().Color.FgType = Detail::TextProperties::TextColor::ColorType::BasicColor;
			context.GetTextProperties().Color.Color.Fg = t;

			context.BasicReadType('\033', '[', (std::uint8_t&)(t), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextColor::BasicColorBG, ParserContext>
	{
		static void Read(Detail::TextProperties::TextColor::BasicColorBG& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().BasicColorChange.HasSetBg = true;
			context.GetTextProperties().Color.BgType = Detail::TextProperties::TextColor::ColorType::BasicColor;
			context.GetTextProperties().Color.Color.Bg = t;

			context.BasicReadType('\033', '[', (std::uint8_t&)(t), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextColor::BasicColor, ParserContext>
	{
		static void Read(Detail::TextProperties::TextColor::BasicColor& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().BasicColorChange.HasSetFg = true;
			context.GetFormatData().BasicColorChange.HasSetBg = true;
			context.GetTextProperties().Color.FgType = Detail::TextProperties::TextColor::ColorType::BasicColor;
			context.GetTextProperties().Color.BgType = Detail::TextProperties::TextColor::ColorType::BasicColor;
			context.GetTextProperties().Color.Color = t;

			context.BasicReadType('\033', '[', (std::uint8_t&)(t.Fg), ';'
											 , (std::uint8_t&)(t.Bg), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextColor::Color24bFG, ParserContext>
	{
		static void Read(Detail::TextProperties::TextColor::Color24bFG& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().BasicColorChange.HasSetFg = true;
			context.GetTextProperties().Color.FgType = Detail::TextProperties::TextColor::ColorType::Color24b;
			context.GetTextProperties().Color.Color24bits.Fg = t;

			context.BasicReadType("\033[38;2;", t.R, ';', t.G, ';', t.B, 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextColor::Color24bBG, ParserContext>
	{
		static void Read(Detail::TextProperties::TextColor::Color24bBG& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().BasicColorChange.HasSetBg = true;
			context.GetTextProperties().Color.BgType = Detail::TextProperties::TextColor::ColorType::Color24b;
			context.GetTextProperties().Color.Color24bits.Bg = t;

			context.BasicReadType("\033[48;2;", t.R, ';', t.G, ';', t.B, 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextColor::Color24b, ParserContext>
	{
		static void Read(Detail::TextProperties::TextColor::Color24b& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().BasicColorChange.HasSetFg = true;
			context.GetFormatData().BasicColorChange.HasSetBg = true;
			context.GetTextProperties().Color.FgType = Detail::TextProperties::TextColor::ColorType::Color24b;
			context.GetTextProperties().Color.BgType = Detail::TextProperties::TextColor::ColorType::Color24b;
			context.GetTextProperties().Color.Color24bits = t;

			context.BasicReadType("\033[38;2;", t.Fg.R, ';', t.Fg.G, ';', t.Fg.B, "; 48; 2;", t.Bg.R, ';', t.Bg.G, ';', t.Bg.B, 'm');
		}
	};


	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextColor::ColorCubeFG, ParserContext>
	{
		static void Read(Detail::TextProperties::TextColor::ColorCubeFG& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().BasicColorChange.HasSetFg = true;
			context.GetTextProperties().Color.FgType = Detail::TextProperties::TextColor::ColorType::ColorCube;
			context.GetTextProperties().Color.ColorCube.Fg = t;

			context.BasicReadType("\033[38;5;", t.GetColorRef(), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextColor::ColorCubeBG, ParserContext>
	{
		static void Read(Detail::TextProperties::TextColor::ColorCubeBG& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().BasicColorChange.HasSetBg = true;
			context.GetTextProperties().Color.BgType = Detail::TextProperties::TextColor::ColorType::ColorCube;
			context.GetTextProperties().Color.ColorCube.Bg = t;

			context.BasicReadType("\033[48;5;", t.GetColorRef(), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextColor::ColorCube, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextColor::ColorCube& t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.GetFormatData().BasicColorChange.HasSetFg = true;
			context.GetFormatData().BasicColorChange.HasSetBg = true;
			context.GetTextProperties().Color.FgType = Detail::TextProperties::TextColor::ColorType::ColorCube;
			context.GetTextProperties().Color.BgType = Detail::TextProperties::TextColor::ColorType::ColorCube;
			context.GetTextProperties().Color.ColorCube = t;

			context.BasicReadType("\033[48;5;", t.Fg.GetColorRef(), ";48;5;", t.Bg.GetColorRef(), 'm');
		}
	};

}