#pragma once

#include "BaseTextProperties.h"
#include "TextPropertiesColor.h"

namespace EngineCore::FMT::Detail {

	struct TextProperties::TextStyle
	{
		struct Reset {};
		enum class Intensity : std::uint8_t;
		enum class Italic : std::uint8_t;
		enum class Blink : std::uint8_t;
		enum class Inverted : std::uint8_t;
		enum class Ideogram : std::uint8_t;
		enum class Script : std::uint8_t;
		enum class BasicStyle : std::uint8_t;
		enum class Underline : std::uint8_t;
		struct UnderlineColor;

		struct Style;
	};

	enum class TextProperties::TextStyle::Intensity : std::uint8_t
	{
		Bold = 1,
		Dim = 2,
		Normal = 22
	};

	enum class TextProperties::TextStyle::Italic : std::uint8_t
	{
		Enable = 3,
		Disable = 23
	};

	enum class TextProperties::TextStyle::Underline : std::uint8_t
	{
		Underlined		= 4,
		DoubleUnerlined	= 21, // may only disable bold
		Disable			= 24
	};
	
	enum class TextProperties::TextStyle::Blink : std::uint8_t
	{
		SlowBlink	= 5,
		FastBlink	= 6,
		Disable		= 25
	};

	enum class TextProperties::TextStyle::Inverted : std::uint8_t
	{
		Enable	= 7,
		Disable = 27
	};

	enum class TextProperties::TextStyle::Ideogram : std::uint8_t
	{
		Underlined = 60,
		DoubleUnderlined = 61,
		Overlined = 62,
		DoubleOverlined = 63,
		StressMarking = 64,
		AllDisable = 65
	};

	enum class TextProperties::TextStyle::Script : std::uint8_t
	{
		Superscript	= 74,
		Subscript	= 75,
		AllDisable	= 76
	};

	enum class TextProperties::TextStyle::BasicStyle : std::uint8_t
	{
		Intensity_Bold				= static_cast<std::uint8_t>(TextProperties::TextStyle::Intensity::Bold),
		Intensity_Dim				= static_cast<std::uint8_t>(TextProperties::TextStyle::Intensity::Dim),
		Intensity_Normal			= static_cast<std::uint8_t>(TextProperties::TextStyle::Intensity::Normal),

		Italic_Enable				= static_cast<std::uint8_t>(TextProperties::TextStyle::Italic::Enable),
		Italic_Disable				= static_cast<std::uint8_t>(TextProperties::TextStyle::Italic::Disable),

		Underline_Underlined		= static_cast<std::uint8_t>(TextProperties::TextStyle::Underline::Underlined),
		Underline_DoubleUnerlined	= static_cast<std::uint8_t>(TextProperties::TextStyle::Underline::DoubleUnerlined), // may only disable bold
		Underline_Disable			= static_cast<std::uint8_t>(TextProperties::TextStyle::Underline::Disable),
		Underline_SelectColor		= 255,

		Blink_SlowBlink				= static_cast<std::uint8_t>(TextProperties::TextStyle::Blink::SlowBlink),
		Blink_FastBlink				= static_cast<std::uint8_t>(TextProperties::TextStyle::Blink::FastBlink),
		Blink_Disable				= static_cast<std::uint8_t>(TextProperties::TextStyle::Blink::Disable),

		Inverted_Enable				= static_cast<std::uint8_t>(TextProperties::TextStyle::Inverted::Enable),
		Inverted_Disable			= static_cast<std::uint8_t>(TextProperties::TextStyle::Inverted::Disable),

		Ideogram_Underlined			= static_cast<std::uint8_t>(TextProperties::TextStyle::Ideogram::Underlined),
		Ideogram_DoubleUnderlined	= static_cast<std::uint8_t>(TextProperties::TextStyle::Ideogram::DoubleUnderlined),
		Ideogram_Overlined			= static_cast<std::uint8_t>(TextProperties::TextStyle::Ideogram::Overlined),
		Ideogram_DoubleOverlined	= static_cast<std::uint8_t>(TextProperties::TextStyle::Ideogram::DoubleOverlined),
		Ideogram_StressMarking		= static_cast<std::uint8_t>(TextProperties::TextStyle::Ideogram::StressMarking),
		Ideogram_AllDisable			= static_cast<std::uint8_t>(TextProperties::TextStyle::Ideogram::AllDisable),

		Script_Superscript			= static_cast<std::uint8_t>(TextProperties::TextStyle::Script::Superscript),
		Script_Subscript			= static_cast<std::uint8_t>(TextProperties::TextStyle::Script::Subscript),
		Script_AllDisable			= static_cast<std::uint8_t>(TextProperties::TextStyle::Script::AllDisable)
	};

	struct TextProperties::TextStyle::UnderlineColor
	{
		struct Reset {};

		struct ColorCube;
		struct Color24b;
		enum class ColorType : std::uint8_t;
		union ColorData;
		struct Color;
	};

	struct TextProperties::TextStyle::UnderlineColor::Color24b : public TextProperties::TextColor::BaseColor24b
	{
		constexpr Color24b(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0)
			: TextProperties::TextColor::BaseColor24b(r, g, b) {};
	};

	struct TextProperties::TextStyle::UnderlineColor::ColorCube : public TextProperties::TextColor::BaseColorCube
	{
		constexpr ColorCube()															: TextProperties::TextColor::BaseColorCube() 	{}
		constexpr ColorCube(const std::uint8_t color)									: TextProperties::TextColor::BaseColorCube(color) {}
		constexpr ColorCube(const TextProperties::TextColor::BaseColorCube& color)	: TextProperties::TextColor::BaseColorCube(color) {}

	public:
		static ColorCube MakeNormalColor(const std::uint8_t value) {
			return static_cast<ColorCube>(TextProperties::TextColor::BaseColorCube::MakeNormalColor(value));
		}

		static ColorCube MakeBrightColor(const std::uint8_t value) {
			return static_cast<ColorCube>(TextProperties::TextColor::BaseColorCube::MakeBrightColor(value));
		}

		static ColorCube Make666CubeColor255(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return static_cast<ColorCube>(TextProperties::TextColor::BaseColorCube::Make666CubeColor255(r, g, b));
		}

		static ColorCube Make666CubeColor5(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return static_cast<ColorCube>(TextProperties::TextColor::BaseColorCube::Make666CubeColor5(r, g, b));
		}

		static ColorCube MakeGrayscaleColor255(const std::uint8_t value) {
			return static_cast<ColorCube>(TextProperties::TextColor::BaseColorCube::MakeGrayscaleColor255(value));
		}

		static ColorCube MakeGrayscaleColor24(const std::uint8_t value) {
			return static_cast<ColorCube>(TextProperties::TextColor::BaseColorCube::MakeGrayscaleColor24(value));
		}
	};

	enum class TextProperties::TextStyle::UnderlineColor::ColorType : std::uint8_t
	{
		Default,
		ColorCube,
		Color24b
	};

	union TextProperties::TextStyle::UnderlineColor::ColorData
	{
		constexpr ColorData()
			: ColorCube()
		{}

		TextProperties::TextStyle::UnderlineColor::ColorCube 	ColorCube;
		TextProperties::TextStyle::UnderlineColor::Color24b 	Color24b;
	};

	struct TextProperties::TextStyle::UnderlineColor::Color
	{
		TextProperties::TextStyle::UnderlineColor::ColorData Data;
		TextProperties::TextStyle::UnderlineColor::ColorType Type = TextProperties::TextStyle::UnderlineColor::ColorType::Default;
	};

	inline bool operator==(const TextProperties::TextStyle::UnderlineColor::Color& lhs, const TextProperties::TextStyle::UnderlineColor::Color& rhs)
	{
		if (lhs.Type != rhs.Type)
			return false;
		switch(lhs.Type)
		{
			case TextProperties::TextStyle::UnderlineColor::ColorType::Default:		return true;
			case TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube: 	return lhs.Data.ColorCube == rhs.Data.ColorCube;
			case TextProperties::TextStyle::UnderlineColor::ColorType::Color24b: 	return lhs.Data.Color24b == rhs.Data.Color24b;
		}
		return false;
	}

	struct TextProperties::TextStyle::Style
	{
	public:
		constexpr Style() {}

		TextProperties::TextStyle::Intensity		Intensity			= TextProperties::TextStyle::Intensity::Normal;
		TextProperties::TextStyle::Italic			Italic				= TextProperties::TextStyle::Italic::Disable;
		TextProperties::TextStyle::Blink			Blink				= TextProperties::TextStyle::Blink::Disable;
		TextProperties::TextStyle::Inverted			Inverted			= TextProperties::TextStyle::Inverted::Disable;
		TextProperties::TextStyle::Ideogram			Ideogram			= TextProperties::TextStyle::Ideogram::AllDisable;
		TextProperties::TextStyle::Script			Script				= TextProperties::TextStyle::Script::AllDisable;

		TextProperties::TextStyle::Underline				Underline			= TextProperties::TextStyle::Underline::Disable;
		TextProperties::TextStyle::UnderlineColor::Color	UnderlineColor;

		template <typename T> void ModifyThrow(const T&) { throw Detail::FMTGivenTypeError{}; }

		void ModifyThrow(const Style& given)										{ *this = given; }

		void ModifyThrow(const TextProperties::TextStyle::Intensity& given) 		{ Intensity = given; 	}
		void ModifyThrow(const TextProperties::TextStyle::Italic& given) 			{ Italic = given; 		}
		void ModifyThrow(const TextProperties::TextStyle::Underline& given)			{ Underline = given;	}
		void ModifyThrow(const TextProperties::TextStyle::Blink& given) 			{ Blink = given; 	}
		void ModifyThrow(const TextProperties::TextStyle::Inverted& given) 			{ Inverted = given; }
		void ModifyThrow(const TextProperties::TextStyle::Ideogram& given) 			{ Ideogram = given; }
		void ModifyThrow(const TextProperties::TextStyle::Script& given) 			{ Script = given; 	}

		void ModifyThrow(const TextProperties::TextStyle::UnderlineColor::Color& given)		{ UnderlineColor = given; }
		void ModifyThrow(const TextProperties::TextStyle::UnderlineColor::ColorCube& given) { UnderlineColor.Type = TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube; 	UnderlineColor.Data.ColorCube = given; }
		void ModifyThrow(const TextProperties::TextStyle::UnderlineColor::Color24b& given) 	{ UnderlineColor.Type = TextProperties::TextStyle::UnderlineColor::ColorType::Color24b; 	UnderlineColor.Data.Color24b = given; }
	};

	inline bool operator==(const TextProperties::TextStyle::Style& lhs, const TextProperties::TextStyle::Style& rhs)
	{
		return lhs.Intensity == rhs.Intensity
			&& lhs.Italic == rhs.Italic
			&& lhs.Blink == rhs.Blink
			&& lhs.Inverted == rhs.Inverted
			&& lhs.Ideogram == rhs.Ideogram
			&& lhs.Script == rhs.Script
			&& lhs.Underline == rhs.Underline
			&& lhs.UnderlineColor == rhs.UnderlineColor;
	}
}
