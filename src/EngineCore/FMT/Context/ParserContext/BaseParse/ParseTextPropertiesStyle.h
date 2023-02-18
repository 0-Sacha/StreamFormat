#pragma once

#include "EngineCore/FMT/Context/ParserContext/BasicParserContext.h"

namespace EngineCore::FMT {
	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::Reset, ParserContext>
	{
		static void Read(const Detail::TextProperties::Reset& t, ParserContext& context) {
			context.AddNoStride(3);
			context.BasicReadType('\033', '[', 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Reset, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextStyle::Reset& t, ParserContext& context) {
			// FIXME
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Intensity, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextStyle::Intensity& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Italic, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextStyle::Italic& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Underline, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextStyle::Underline& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::UnderlineColor::Color, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextStyle::UnderlineColor::Color& t, ParserContext& context) {
			// FIXME
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::UnderlineColor::ColorCube, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextStyle::UnderlineColor::ColorCube& t, ParserContext& context) {
			context.BasicReadType("\033[58;5;", t.GetColorRef(), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::UnderlineColor::Color24b, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextStyle::UnderlineColor::Color24b& t, ParserContext& context) {
			context.BasicReadType("\033[58;2;", t.R, ';', t.G, ';', t.B, 'm');
		}
	};



	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Blink, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextStyle::Blink& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};



	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Inverted, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextStyle::Inverted& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};



	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Ideogram, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextStyle::Ideogram& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};



	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Script, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextStyle::Script& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};


	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::BasicStyle, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextStyle::BasicStyle& t, ParserContext& context) {
			switch (t) {
			case Detail::TextProperties::TextStyle::BasicStyle::Intensity_Bold:
			case Detail::TextProperties::TextStyle::BasicStyle::Intensity_Dim:
			case Detail::TextProperties::TextStyle::BasicStyle::Intensity_Normal:
				ParserType<Detail::TextProperties::TextStyle::Intensity, ParserContext>::Read(static_cast<Detail::TextProperties::TextStyle::Intensity>(t), context);
				break;

			case Detail::TextProperties::TextStyle::BasicStyle::Italic_Enable:
			case Detail::TextProperties::TextStyle::BasicStyle::Italic_Disable:
				ParserType<Detail::TextProperties::TextStyle::Italic, ParserContext>::Read(static_cast<Detail::TextProperties::TextStyle::Italic>(t), context);
				break;

			case Detail::TextProperties::TextStyle::BasicStyle::Underline_Underlined:
			case Detail::TextProperties::TextStyle::BasicStyle::Underline_DoubleUnerlined:
			case Detail::TextProperties::TextStyle::BasicStyle::Underline_Disable:
				ParserType<Detail::TextProperties::TextStyle::Underline, ParserContext>::Read(static_cast<Detail::TextProperties::TextStyle::Underline>(t), context);
				break;
			case Detail::TextProperties::TextStyle::BasicStyle::Underline_SelectColor:
				break;

			case Detail::TextProperties::TextStyle::BasicStyle::Blink_SlowBlink:
			case Detail::TextProperties::TextStyle::BasicStyle::Blink_FastBlink:
			case Detail::TextProperties::TextStyle::BasicStyle::Blink_Disable:
				ParserType<Detail::TextProperties::TextStyle::Blink, ParserContext>::Read(static_cast<Detail::TextProperties::TextStyle::Blink>(t), context);
				break;

			case Detail::TextProperties::TextStyle::BasicStyle::Inverted_Enable:
			case Detail::TextProperties::TextStyle::BasicStyle::Inverted_Disable:
				ParserType<Detail::TextProperties::TextStyle::Inverted, ParserContext>::Read(static_cast<Detail::TextProperties::TextStyle::Inverted>(t), context);
				break;

			case Detail::TextProperties::TextStyle::BasicStyle::Ideogram_Underlined:
			case Detail::TextProperties::TextStyle::BasicStyle::Ideogram_DoubleUnderlined:
			case Detail::TextProperties::TextStyle::BasicStyle::Ideogram_Overlined:
			case Detail::TextProperties::TextStyle::BasicStyle::Ideogram_DoubleOverlined:
			case Detail::TextProperties::TextStyle::BasicStyle::Ideogram_StressMarking:
			case Detail::TextProperties::TextStyle::BasicStyle::Ideogram_AllDisable:
				ParserType<Detail::TextProperties::TextStyle::Ideogram, ParserContext>::Read(static_cast<Detail::TextProperties::TextStyle::Ideogram>(t), context);
				break;

			case Detail::TextProperties::TextStyle::BasicStyle::Script_Superscript:
			case Detail::TextProperties::TextStyle::BasicStyle::Script_Subscript:
			case Detail::TextProperties::TextStyle::BasicStyle::Script_AllDisable:
				ParserType<Detail::TextProperties::TextStyle::Script, ParserContext>::Read(static_cast<Detail::TextProperties::TextStyle::Script>(t), context);
				break;
			}
		}
	};
}