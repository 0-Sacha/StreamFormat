#pragma once

#include "../BasicFormatContext.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace EngineCore::Instrumentation::FMT {

	template<typename FormatContext>
	struct FormatType<Detail::ResetAnsiAllParameters, FormatContext>
	{
		static void Write(const Detail::ResetAnsiAllParameters t, FormatContext& context) {
			context.BasicWriteType('\033', '[', 'm');
			context.BufferOut().AddNoStride(3);

			context.GetAnsiManager().StyleModifReset();
			context.GetAnsiManager().StyleModifReset();
			context.GetAnsiManager().FrontModifReset();
		}
	};

	template<typename FormatContext>
	struct FormatType<Detail::ResetAnsiStyle, FormatContext>
	{
		static void Write(const Detail::ResetAnsiStyle t, FormatContext& context) {
			context.GetAnsiManager().StyleModif(t);
		}
	};

	template<typename FormatContext>
	struct FormatType<Detail::AnsiTFSIntensity, FormatContext>
	{
		static void Write(const Detail::AnsiTFSIntensity t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};



	template<typename FormatContext>
	struct FormatType<Detail::AnsiTFSItalic, FormatContext>
	{
		static void Write(const Detail::AnsiTFSItalic t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};



	template<typename FormatContext>
	struct FormatType<Detail::AnsiTFSUnderline, FormatContext>
	{
		static void Write(const Detail::AnsiTFSUnderline t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};

	template<typename FormatContext>
	struct FormatType<Detail::ResetAnsiUnderlineColor, FormatContext>
	{
		static void Write(const Detail::ResetAnsiUnderlineColor t, FormatContext& context) {
			context.BufferOut().AddNoStride(5);
			context.BufferOut().WriteCharArray("\033[59m");
			context.GetAnsiManager().StyleModif(t);
		}
	};

	template<typename FormatContext>
	struct FormatType<Detail::AnsiNColorUnderline, FormatContext>
	{
		static void Write(const Detail::AnsiNColorUnderline t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[58;5;", t.GetColorRef(), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};

	template<typename FormatContext>
	struct FormatType<Detail::AnsiUnderlineColor24b, FormatContext>
	{
		static void Write(const Detail::AnsiUnderlineColor24b t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[58;2;", t.R, ';', t.G, ';', t.B, 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};



	template<typename FormatContext>
	struct FormatType<Detail::AnsiTFSBlink, FormatContext>
	{
		static void Write(const Detail::AnsiTFSBlink t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};



	template<typename FormatContext>
	struct FormatType<Detail::AnsiTFSInverted, FormatContext>
	{
		static void Write(const Detail::AnsiTFSInverted t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};



	template<typename FormatContext>
	struct FormatType<Detail::AnsiTFSIdeogram, FormatContext>
	{
		static void Write(const Detail::AnsiTFSIdeogram t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};



	template<typename FormatContext>
	struct FormatType<Detail::AnsiTFSScript, FormatContext>
	{
		static void Write(const Detail::AnsiTFSScript t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetAnsiManager().StyleModif(t);
		}
	};


	template<typename FormatContext>
	struct FormatType<Detail::AnsiBasicTextStyle, FormatContext>
	{
		static void Write(const Detail::AnsiBasicTextStyle t, FormatContext& context) {
			switch(t) {
			case Detail::AnsiBasicTextStyle::Intensity_Bold:
			case Detail::AnsiBasicTextStyle::Intensity_Dim:
			case Detail::AnsiBasicTextStyle::Intensity_Normal:
				FormatType<Detail::AnsiTFSIntensity, FormatContext>::Write(static_cast<Detail::AnsiTFSIntensity>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Italic_Enable:
			case Detail::AnsiBasicTextStyle::Italic_Disable:
				FormatType<Detail::AnsiTFSItalic, FormatContext>::Write(static_cast<Detail::AnsiTFSItalic>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Underline_Underlined:
			case Detail::AnsiBasicTextStyle::Underline_DoubleUnerlined:
			case Detail::AnsiBasicTextStyle::Underline_Disable:
				FormatType<Detail::AnsiTFSUnderline, FormatContext>::Write(static_cast<Detail::AnsiTFSUnderline>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Blink_SlowBlink:
			case Detail::AnsiBasicTextStyle::Blink_FastBlink:
			case Detail::AnsiBasicTextStyle::Blink_Disable:
				FormatType<Detail::AnsiTFSBlink, FormatContext>::Write(static_cast<Detail::AnsiTFSBlink>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Inverted_Enable:
			case Detail::AnsiBasicTextStyle::Inverted_Disable:
				FormatType<Detail::AnsiTFSInverted, FormatContext>::Write(static_cast<Detail::AnsiTFSInverted>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Ideogram_Underlined:
			case Detail::AnsiBasicTextStyle::Ideogram_DoubleUnderlined:
			case Detail::AnsiBasicTextStyle::Ideogram_Overlined:
			case Detail::AnsiBasicTextStyle::Ideogram_DoubleOverlined:
			case Detail::AnsiBasicTextStyle::Ideogram_StressMarking:
			case Detail::AnsiBasicTextStyle::Ideogram_AllDisable:
				FormatType<Detail::AnsiTFSIdeogram, FormatContext>::Write(static_cast<Detail::AnsiTFSIdeogram>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Script_Superscript:
			case Detail::AnsiBasicTextStyle::Script_Subscript:
			case Detail::AnsiBasicTextStyle::Script_AllDisable:
				FormatType<Detail::AnsiTFSScript, FormatContext>::Write(static_cast<Detail::AnsiTFSScript>(t), context);
				break;
			default:
				break;
			}
		}
	};
}