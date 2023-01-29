#pragma once

#include "FMT/Context/FormatterContext/BasicFormatterContext.h"

namespace EngineCore::FMT {

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::Reset, FormatterContext>
	{
		static void Write(const Detail::TextProperties::Reset t, FormatterContext& context) {
			context.BasicWriteType('\033', '[', 'm');
			context.BufferOut().AddNoStride(3);

			context.GetTextPropertiesParser().AllModifReset();
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextStyle::Style, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextStyle::Style t, FormatterContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextStyle::Intensity, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextStyle::Intensity t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};



	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextStyle::Italic, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextStyle::Italic t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};



	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextStyle::Underline, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextStyle::Underline t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextStyle::UnderlineColor::Color, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextStyle::UnderlineColor::Color t, FormatterContext& context) {
			context.BufferOut().AddNoStride(5);
			context.BufferOut().WriteCharArray("\033[59m");
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextStyle::UnderlineColor::ColorCube, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextStyle::UnderlineColor::ColorCube t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[58;5;", t.GetColorRef(), 'm');
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextStyle::UnderlineColor::Color24b, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextStyle::UnderlineColor::Color24b t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType("\033[58;2;", t.R, ';', t.G, ';', t.B, 'm');
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};



	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextStyle::Blink, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextStyle::Blink t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};



	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextStyle::Inverted, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextStyle::Inverted t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};



	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextStyle::Ideogram, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextStyle::Ideogram t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};



	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextStyle::Script, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextStyle::Script t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};


	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextStyle::BasicStyle, FormatterContext>
	{
		static void Write(const Detail::TextProperties::TextStyle::BasicStyle t, FormatterContext& context) {
			switch(t) {
			case Detail::TextProperties::TextStyle::BasicStyle::Intensity_Bold:
			case Detail::TextProperties::TextStyle::BasicStyle::Intensity_Dim:
			case Detail::TextProperties::TextStyle::BasicStyle::Intensity_Normal:
				FormatterType<Detail::TextProperties::TextStyle::Intensity, FormatterContext>::Write(static_cast<Detail::TextProperties::TextStyle::Intensity>(t), context);
				break;

			case Detail::TextProperties::TextStyle::BasicStyle::Italic_Enable:
			case Detail::TextProperties::TextStyle::BasicStyle::Italic_Disable:
				FormatterType<Detail::TextProperties::TextStyle::Italic, FormatterContext>::Write(static_cast<Detail::TextProperties::TextStyle::Italic>(t), context);
				break;

			case Detail::TextProperties::TextStyle::BasicStyle::Underline_Underlined:
			case Detail::TextProperties::TextStyle::BasicStyle::Underline_DoubleUnerlined:
			case Detail::TextProperties::TextStyle::BasicStyle::Underline_Disable:
				FormatterType<Detail::TextProperties::TextStyle::Underline, FormatterContext>::Write(static_cast<Detail::TextProperties::TextStyle::Underline>(t), context);
				break;

			case Detail::TextProperties::TextStyle::BasicStyle::Blink_SlowBlink:
			case Detail::TextProperties::TextStyle::BasicStyle::Blink_FastBlink:
			case Detail::TextProperties::TextStyle::BasicStyle::Blink_Disable:
				FormatterType<Detail::TextProperties::TextStyle::Blink, FormatterContext>::Write(static_cast<Detail::TextProperties::TextStyle::Blink>(t), context);
				break;

			case Detail::TextProperties::TextStyle::BasicStyle::Inverted_Enable:
			case Detail::TextProperties::TextStyle::BasicStyle::Inverted_Disable:
				FormatterType<Detail::TextProperties::TextStyle::Inverted, FormatterContext>::Write(static_cast<Detail::TextProperties::TextStyle::Inverted>(t), context);
				break;

			case Detail::TextProperties::TextStyle::BasicStyle::Ideogram_Underlined:
			case Detail::TextProperties::TextStyle::BasicStyle::Ideogram_DoubleUnderlined:
			case Detail::TextProperties::TextStyle::BasicStyle::Ideogram_Overlined:
			case Detail::TextProperties::TextStyle::BasicStyle::Ideogram_DoubleOverlined:
			case Detail::TextProperties::TextStyle::BasicStyle::Ideogram_StressMarking:
			case Detail::TextProperties::TextStyle::BasicStyle::Ideogram_AllDisable:
				FormatterType<Detail::TextProperties::TextStyle::Ideogram, FormatterContext>::Write(static_cast<Detail::TextProperties::TextStyle::Ideogram>(t), context);
				break;

			case Detail::TextProperties::TextStyle::BasicStyle::Script_Superscript:
			case Detail::TextProperties::TextStyle::BasicStyle::Script_Subscript:
			case Detail::TextProperties::TextStyle::BasicStyle::Script_AllDisable:
				FormatterType<Detail::TextProperties::TextStyle::Script, FormatterContext>::Write(static_cast<Detail::TextProperties::TextStyle::Script>(t), context);
				break;
			default:
				break;
			}
		}
	};
}