#pragma once

#include "FMT/Context/UnFormatContext/BasicUnFormatContext.h"

namespace EngineCore::FMT {


	template<typename UnFormatContext>
	struct UnFormatType<Detail::ResetAnsiAllParameters, UnFormatContext>
	{
		static void Read(const Detail::ResetAnsiAllParameters& t, UnFormatContext& context) {
			context.AddNoStride(3);
			context.BasicReadType('\033', '[', 'm');
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::ResetAnsiStyle, UnFormatContext>
	{
		static void Read(const Detail::ResetAnsiStyle& t, UnFormatContext& context) {
			// FIXME
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiTFSIntensity, UnFormatContext>
	{
		static void Read(const Detail::AnsiTFSIntensity& t, UnFormatContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiTFSItalic, UnFormatContext>
	{
		static void Read(const Detail::AnsiTFSItalic& t, UnFormatContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiTFSUnderline, UnFormatContext>
	{
		static void Read(const Detail::AnsiTFSUnderline& t, UnFormatContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::ResetAnsiUnderlineColor, UnFormatContext>
	{
		static void Read(const Detail::ResetAnsiUnderlineColor& t, UnFormatContext& context) {
			// FIXME
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiNColorUnderline, UnFormatContext>
	{
		static void Read(const Detail::AnsiNColorUnderline& t, UnFormatContext& context) {
			context.BasicReadType("\033[58;5;", t.GetColorRef(), 'm');
		}
	};

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiUnderlineColor24b, UnFormatContext>
	{
		static void Read(const Detail::AnsiUnderlineColor24b& t, UnFormatContext& context) {
			context.BasicReadType("\033[58;2;", t.R, ';', t.G, ';', t.B, 'm');
		}
	};



	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiTFSBlink, UnFormatContext>
	{
		static void Read(const Detail::AnsiTFSBlink& t, UnFormatContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};



	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiTFSInverted, UnFormatContext>
	{
		static void Read(const Detail::AnsiTFSInverted& t, UnFormatContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};



	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiTFSIdeogram, UnFormatContext>
	{
		static void Read(const Detail::AnsiTFSIdeogram& t, UnFormatContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};



	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiTFSScript, UnFormatContext>
	{
		static void Read(const Detail::AnsiTFSScript& t, UnFormatContext& context) {
			context.BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');
		}
	};


	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiBasicTextStyle, UnFormatContext>
	{
		static void Read(const Detail::AnsiBasicTextStyle& t, UnFormatContext& context) {
			switch (t) {
			case Detail::AnsiBasicTextStyle::Intensity_Bold:
			case Detail::AnsiBasicTextStyle::Intensity_Dim:
			case Detail::AnsiBasicTextStyle::Intensity_Normal:
				UnFormatType<Detail::AnsiTFSIntensity, UnFormatContext>::Read(static_cast<Detail::AnsiTFSIntensity>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Italic_Enable:
			case Detail::AnsiBasicTextStyle::Italic_Disable:
				UnFormatType<Detail::AnsiTFSItalic, UnFormatContext>::Read(static_cast<Detail::AnsiTFSItalic>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Underline_Underlined:
			case Detail::AnsiBasicTextStyle::Underline_DoubleUnerlined:
			case Detail::AnsiBasicTextStyle::Underline_Disable:
				UnFormatType<Detail::AnsiTFSUnderline, UnFormatContext>::Read(static_cast<Detail::AnsiTFSUnderline>(t), context);
				break;
			case Detail::AnsiBasicTextStyle::Underline_SelectColor:
				break;

			case Detail::AnsiBasicTextStyle::Blink_SlowBlink:
			case Detail::AnsiBasicTextStyle::Blink_FastBlink:
			case Detail::AnsiBasicTextStyle::Blink_Disable:
				UnFormatType<Detail::AnsiTFSBlink, UnFormatContext>::Read(static_cast<Detail::AnsiTFSBlink>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Inverted_Enable:
			case Detail::AnsiBasicTextStyle::Inverted_Disable:
				UnFormatType<Detail::AnsiTFSInverted, UnFormatContext>::Read(static_cast<Detail::AnsiTFSInverted>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Ideogram_Underlined:
			case Detail::AnsiBasicTextStyle::Ideogram_DoubleUnderlined:
			case Detail::AnsiBasicTextStyle::Ideogram_Overlined:
			case Detail::AnsiBasicTextStyle::Ideogram_DoubleOverlined:
			case Detail::AnsiBasicTextStyle::Ideogram_StressMarking:
			case Detail::AnsiBasicTextStyle::Ideogram_AllDisable:
				UnFormatType<Detail::AnsiTFSIdeogram, UnFormatContext>::Read(static_cast<Detail::AnsiTFSIdeogram>(t), context);
				break;

			case Detail::AnsiBasicTextStyle::Script_Superscript:
			case Detail::AnsiBasicTextStyle::Script_Subscript:
			case Detail::AnsiBasicTextStyle::Script_AllDisable:
				UnFormatType<Detail::AnsiTFSScript, UnFormatContext>::Read(static_cast<Detail::AnsiTFSScript>(t), context);
				break;
			}
		}
	};
}