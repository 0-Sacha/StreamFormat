#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/BasicFormatterContext.h"

namespace ProjectCore::FMT {

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::ResetColor, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextColor::ResetColor t, FormatterContext& context) {
			context.GetTextPropertiesParser().ColorModifReset();
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextColor::BasicColorFG& t, FormatterContext& context) {
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::BasicColorBG, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextColor::BasicColorBG& t, FormatterContext& context) {
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::BasicColor, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextColor::BasicColor& t, FormatterContext& context) {
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::Color24bFG, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextColor::Color24bFG& t, FormatterContext& context) {
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::Color24bBG, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextColor::Color24bBG& t, FormatterContext& context) {
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::Color24b, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextColor::Color24b& t, FormatterContext& context) {
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};


	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::ColorCubeFG, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextColor::ColorCubeFG& t, FormatterContext& context) {
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::ColorCubeBG, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextColor::ColorCubeBG& t, FormatterContext& context) {
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextColor::ColorCube, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextColor::ColorCube& t, FormatterContext& context) {
			context.GetTextPropertiesParser().ColorModif(t);
		}
	};
}
