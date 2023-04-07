#pragma once

#include "ProjectCore/FMT/Context/ParserContext/BasicParserContext.h"

namespace ProjectCore::FMT {

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::ResetProperties, ParserContext>
	{
		static void Format(const Detail::TextProperties::ResetProperties, ParserContext& context) {
			context.GetTextPropertiesParser().AllPropertiesReset();
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::ResetStyle, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::ResetStyle, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModifReset();
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Style, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::Style t, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Intensity, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::Intensity t, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Italic, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::Italic t, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Underline, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::Underline t, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::UnderlineColor::Color, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::UnderlineColor::Color t, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::UnderlineColor::ColorCube, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::UnderlineColor::ColorCube t, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::UnderlineColor::Color24b, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::UnderlineColor::Color24b t, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Blink, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::Blink t, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Inverted, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::Inverted t, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Ideogram, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::Ideogram t, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::Script, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::Script t, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextStyle::BasicStyle, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextStyle::BasicStyle t, ParserContext& context) {
			context.GetTextPropertiesParser().StyleModif(t);
		}
	};
}
