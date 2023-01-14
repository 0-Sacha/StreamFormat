#pragma once

#include "FMT/Context/FormatterContext/BasicFormatterContext.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace EngineCore::FMT {

	template<typename FormatterContext>
	struct FormatterType<Detail::ResetAnsiAllParameters, FormatterContext>
	{
		static void Write(const Detail::ResetAnsiAllParameters t, FormatterContext& context) {
			context.BasicWriteType('\033', '[', 'm');
			context.BufferOut().AddNoStride(3);

			context.GetAnsiManager().AllModifReset();
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::ResetAnsiStyle, FormatterContext>
	{
		static void Write(const Detail::ResetAnsiStyle t, FormatterContext& context) {
			context.GetAnsiManager().StyleModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiTFSIntensity, FormatterContext>
	{
		static void Write(const Detail::AnsiTFSIntensity t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};



	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiTFSItalic, FormatterContext>
	{
		static void Write(const Detail::AnsiTFSItalic t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};



	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiTFSUnderline, FormatterContext>
	{
		static void Write(const Detail::AnsiTFSUnderline t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::ResetAnsiUnderlineColor, FormatterContext>
	{
		static void Write(const Detail::ResetAnsiUnderlineColor t, FormatterContext& context) {
			context.BufferOut().AddNoStride(5);
			context.BufferOut().WriteCharArray("\033[59m");
			context.GetAnsiManager().StyleModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiNColorUnderline, FormatterContext>
	{
		static void Write(const Detail::AnsiNColorUnderline t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[58;5;", t.GetColorRef(), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiUnderlineColor24b, FormatterContext>
	{
		static void Write(const Detail::AnsiUnderlineColor24b t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[58;2;", t.R, ';', t.G, ';', t.B, 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};



	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiTFSBlink, FormatterContext>
	{
		static void Write(const Detail::AnsiTFSBlink t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};



	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiTFSInverted, FormatterContext>
	{
		static void Write(const Detail::AnsiTFSInverted t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};



	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiTFSIdeogram, FormatterContext>
	{
		static void Write(const Detail::AnsiTFSIdeogram t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};



	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiTFSScript, FormatterContext>
	{
		static void Write(const Detail::AnsiTFSScript t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};


	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiBasicTextStyle, FormatterContext>
	{
		static void Write(const Detail::AnsiBasicTextStyle t, FormatterContext& context) {
			switch(t) {
			case Detail::AnsiBasicTextStyle::Intensity_Bold:
			case Detail::AnsiBasicTextStyle::Intensity_Dim:
			case Detail::AnsiBasicTextStyle::Intensity_Normal:
				FormatterType<Detail::AnsiTFSIntensity, FormatterContext>::Write(static_cast<Detail::AnsiTFSIntensity>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Italic_Enable:
			case Detail::AnsiBasicTextStyle::Italic_Disable:
				FormatterType<Detail::AnsiTFSItalic, FormatterContext>::Write(static_cast<Detail::AnsiTFSItalic>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Underline_Underlined:
			case Detail::AnsiBasicTextStyle::Underline_DoubleUnerlined:
			case Detail::AnsiBasicTextStyle::Underline_Disable:
				FormatterType<Detail::AnsiTFSUnderline, FormatterContext>::Write(static_cast<Detail::AnsiTFSUnderline>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Blink_SlowBlink:
			case Detail::AnsiBasicTextStyle::Blink_FastBlink:
			case Detail::AnsiBasicTextStyle::Blink_Disable:
				FormatterType<Detail::AnsiTFSBlink, FormatterContext>::Write(static_cast<Detail::AnsiTFSBlink>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Inverted_Enable:
			case Detail::AnsiBasicTextStyle::Inverted_Disable:
				FormatterType<Detail::AnsiTFSInverted, FormatterContext>::Write(static_cast<Detail::AnsiTFSInverted>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Ideogram_Underlined:
			case Detail::AnsiBasicTextStyle::Ideogram_DoubleUnderlined:
			case Detail::AnsiBasicTextStyle::Ideogram_Overlined:
			case Detail::AnsiBasicTextStyle::Ideogram_DoubleOverlined:
			case Detail::AnsiBasicTextStyle::Ideogram_StressMarking:
			case Detail::AnsiBasicTextStyle::Ideogram_AllDisable:
				FormatterType<Detail::AnsiTFSIdeogram, FormatterContext>::Write(static_cast<Detail::AnsiTFSIdeogram>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Script_Superscript:
			case Detail::AnsiBasicTextStyle::Script_Subscript:
			case Detail::AnsiBasicTextStyle::Script_AllDisable:
				FormatterType<Detail::AnsiTFSScript, FormatterContext>::Write(static_cast<Detail::AnsiTFSScript>(t), context);
				break;
			default:
				break;
			}
		}
	};
}