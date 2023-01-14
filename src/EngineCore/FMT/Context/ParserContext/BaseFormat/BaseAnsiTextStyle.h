#pragma once

#include "FMT/Context/ParserContext/BasicParserContext.h"

namespace EngineCore::FMT {


	template<typename ParserContext>
	struct ParserType<Detail::ResetAnsiAllParameters, ParserContext>
	{
		static void Read(const Detail::ResetAnsiAllParameters& t, ParserContext& context) {
			context.AddNoStride(3);
			context.BasicReadType('\033', '[', 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::ResetAnsiStyle, ParserContext>
	{
		static void Read(const Detail::ResetAnsiStyle& t, ParserContext& context) {
			// FIXME
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::AnsiTFSIntensity, ParserContext>
	{
		static void Read(const Detail::AnsiTFSIntensity& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::AnsiTFSItalic, ParserContext>
	{
		static void Read(const Detail::AnsiTFSItalic& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::AnsiTFSUnderline, ParserContext>
	{
		static void Read(const Detail::AnsiTFSUnderline& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::ResetAnsiUnderlineColor, ParserContext>
	{
		static void Read(const Detail::ResetAnsiUnderlineColor& t, ParserContext& context) {
			// FIXME
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::AnsiNColorUnderline, ParserContext>
	{
		static void Read(const Detail::AnsiNColorUnderline& t, ParserContext& context) {
			context.BasicReadType("\033[58;5;", t.GetColorRef(), 'm');
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::AnsiUnderlineColor24b, ParserContext>
	{
		static void Read(const Detail::AnsiUnderlineColor24b& t, ParserContext& context) {
			context.BasicReadType("\033[58;2;", t.R, ';', t.G, ';', t.B, 'm');
		}
	};



	template<typename ParserContext>
	struct ParserType<Detail::AnsiTFSBlink, ParserContext>
	{
		static void Read(const Detail::AnsiTFSBlink& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};



	template<typename ParserContext>
	struct ParserType<Detail::AnsiTFSInverted, ParserContext>
	{
		static void Read(const Detail::AnsiTFSInverted& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};



	template<typename ParserContext>
	struct ParserType<Detail::AnsiTFSIdeogram, ParserContext>
	{
		static void Read(const Detail::AnsiTFSIdeogram& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};



	template<typename ParserContext>
	struct ParserType<Detail::AnsiTFSScript, ParserContext>
	{
		static void Read(const Detail::AnsiTFSScript& t, ParserContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};


	template<typename ParserContext>
	struct ParserType<Detail::AnsiBasicTextStyle, ParserContext>
	{
		static void Read(const Detail::AnsiBasicTextStyle& t, ParserContext& context) {
			switch (t) {
			case Detail::AnsiBasicTextStyle::Intensity_Bold:
			case Detail::AnsiBasicTextStyle::Intensity_Dim:
			case Detail::AnsiBasicTextStyle::Intensity_Normal:
				ParserType<Detail::AnsiTFSIntensity, ParserContext>::Read(static_cast<Detail::AnsiTFSIntensity>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Italic_Enable:
			case Detail::AnsiBasicTextStyle::Italic_Disable:
				ParserType<Detail::AnsiTFSItalic, ParserContext>::Read(static_cast<Detail::AnsiTFSItalic>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Underline_Underlined:
			case Detail::AnsiBasicTextStyle::Underline_DoubleUnerlined:
			case Detail::AnsiBasicTextStyle::Underline_Disable:
				ParserType<Detail::AnsiTFSUnderline, ParserContext>::Read(static_cast<Detail::AnsiTFSUnderline>(t), context);
				break;
			case Detail::AnsiBasicTextStyle::Underline_SelectColor:
				break;

			case Detail::AnsiBasicTextStyle::Blink_SlowBlink:
			case Detail::AnsiBasicTextStyle::Blink_FastBlink:
			case Detail::AnsiBasicTextStyle::Blink_Disable:
				ParserType<Detail::AnsiTFSBlink, ParserContext>::Read(static_cast<Detail::AnsiTFSBlink>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Inverted_Enable:
			case Detail::AnsiBasicTextStyle::Inverted_Disable:
				ParserType<Detail::AnsiTFSInverted, ParserContext>::Read(static_cast<Detail::AnsiTFSInverted>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Ideogram_Underlined:
			case Detail::AnsiBasicTextStyle::Ideogram_DoubleUnderlined:
			case Detail::AnsiBasicTextStyle::Ideogram_Overlined:
			case Detail::AnsiBasicTextStyle::Ideogram_DoubleOverlined:
			case Detail::AnsiBasicTextStyle::Ideogram_StressMarking:
			case Detail::AnsiBasicTextStyle::Ideogram_AllDisable:
				ParserType<Detail::AnsiTFSIdeogram, ParserContext>::Read(static_cast<Detail::AnsiTFSIdeogram>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Script_Superscript:
			case Detail::AnsiBasicTextStyle::Script_Subscript:
			case Detail::AnsiBasicTextStyle::Script_AllDisable:
				ParserType<Detail::AnsiTFSScript, ParserContext>::Read(static_cast<Detail::AnsiTFSScript>(t), context);
				break;
			}
		}
	};
}