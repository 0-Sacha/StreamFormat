#pragma once

#include "EngineCore/Core/Core.h"
#include "BaseAnsiColor.h"

namespace EngineCore::FMT::Detail {

	// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

	struct ResetAnsiAllParameters {};

	struct ResetAnsiStyle {};


	enum class AnsiTFSIntensity : std::uint8_t {
		Bold = 1,
		Dim = 2,
		Normal = 22
	};

	enum class AnsiTFSItalic : std::uint8_t {
		Enable = 3,
		Disable = 23
	};

	enum class AnsiTFSUnderline : std::uint8_t {
		Underlined		= 4,
		DoubleUnerlined	= 21, // may only disable bold
		Disable			= 24
	};
	
	enum class AnsiTFSBlink : std::uint8_t {
		SlowBlink	= 5,
		FastBlink	= 6,
		Disable		= 25
	};

	enum class AnsiTFSInverted : std::uint8_t {
		Enable	= 7,
		Disable = 27
	};

	enum class AnsiTFSIdeogram : std::uint8_t {
		Underlined = 60,
		DoubleUnderlined = 61,
		Overlined = 62,
		DoubleOverlined = 63,
		StressMarking = 64,
		AllDisable = 65
	};

	enum class AnsiTFSScript : std::uint8_t {
		Superscript	= 74,
		Subscript	= 75,
		AllDisable	= 76
	};

	enum class AnsiBasicTextStyle : std::uint8_t {
		Intensity_Bold				= static_cast<std::uint8_t>(AnsiTFSIntensity::Bold),
		Intensity_Dim				= static_cast<std::uint8_t>(AnsiTFSIntensity::Dim),
		Intensity_Normal			= static_cast<std::uint8_t>(AnsiTFSIntensity::Normal),

		Italic_Enable				= static_cast<std::uint8_t>(AnsiTFSItalic::Enable),
		Italic_Disable				= static_cast<std::uint8_t>(AnsiTFSItalic::Disable),

		Underline_Underlined		= static_cast<std::uint8_t>(AnsiTFSUnderline::Underlined),
		Underline_DoubleUnerlined	= static_cast<std::uint8_t>(AnsiTFSUnderline::DoubleUnerlined), // may only disable bold
		Underline_Disable			= static_cast<std::uint8_t>(AnsiTFSUnderline::Disable),
		Underline_SelectColor		= 255,

		Blink_SlowBlink				= static_cast<std::uint8_t>(AnsiTFSBlink::SlowBlink),
		Blink_FastBlink				= static_cast<std::uint8_t>(AnsiTFSBlink::FastBlink),
		Blink_Disable				= static_cast<std::uint8_t>(AnsiTFSBlink::Disable),

		Inverted_Enable				= static_cast<std::uint8_t>(AnsiTFSInverted::Enable),
		Inverted_Disable			= static_cast<std::uint8_t>(AnsiTFSInverted::Disable),

		Ideogram_Underlined			= static_cast<std::uint8_t>(AnsiTFSIdeogram::Underlined),
		Ideogram_DoubleUnderlined	= static_cast<std::uint8_t>(AnsiTFSIdeogram::DoubleUnderlined),
		Ideogram_Overlined			= static_cast<std::uint8_t>(AnsiTFSIdeogram::Overlined),
		Ideogram_DoubleOverlined	= static_cast<std::uint8_t>(AnsiTFSIdeogram::DoubleOverlined),
		Ideogram_StressMarking		= static_cast<std::uint8_t>(AnsiTFSIdeogram::StressMarking),
		Ideogram_AllDisable			= static_cast<std::uint8_t>(AnsiTFSIdeogram::AllDisable),

		Script_Superscript			= static_cast<std::uint8_t>(AnsiTFSScript::Superscript),
		Script_Subscript			= static_cast<std::uint8_t>(AnsiTFSScript::Subscript),
		Script_AllDisable			= static_cast<std::uint8_t>(AnsiTFSScript::AllDisable)
	};

	struct ResetAnsiUnderlineColor {};

	struct AnsiUnderlineColor24b : public AnsiColor24bType {
		AnsiUnderlineColor24b(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0)
			: AnsiColor24bType(r, g, b) {};
	};

	struct AnsiNColorUnderline : public AnsiNColorType {
		AnsiNColorUnderline()								: AnsiNColorType() 	{}
		AnsiNColorUnderline(const std::uint8_t color)		: AnsiNColorType(color) {}
		AnsiNColorUnderline(const AnsiNColorType& color)	: AnsiNColorType(color) {}

	public:
		static AnsiNColorUnderline MakeNormalColor(const std::uint8_t value) {
			return static_cast<AnsiNColorUnderline>(AnsiNColorType::MakeNormalColor(value));
		}

		static AnsiNColorUnderline MakeBrightColor(const std::uint8_t value) {
			return static_cast<AnsiNColorUnderline>(AnsiNColorType::MakeBrightColor(value));
		}

		static AnsiNColorUnderline Make666CubeColor255(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return static_cast<AnsiNColorUnderline>(AnsiNColorType::Make666CubeColor255(r, g, b));
		}

		static AnsiNColorUnderline Make666CubeColor5(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return static_cast<AnsiNColorUnderline>(AnsiNColorType::Make666CubeColor5(r, g, b));
		}

		static AnsiNColorFg MakeGrayscaleColor255(const std::uint8_t value) {
			return static_cast<AnsiNColorUnderline>(AnsiNColorType::MakeGrayscaleColor255(value));
		}

		static AnsiNColorUnderline MakeGrayscaleColor24(const std::uint8_t value) {
			return static_cast<AnsiNColorUnderline>(AnsiNColorType::MakeGrayscaleColor24(value));
		}
	};

	enum class AnsiUnderlineColorType : std::uint8_t {
		Default,
		AnsiNColor,
		AnsiColor24b
	};

	union AnsiUnderlineColorUnion {
		AnsiUnderlineColorUnion()
			: NColor()
		{}

		AnsiNColorUnderline		NColor;
		AnsiUnderlineColor24b	Color24b;
	};

	struct AnsiUnderlineColor {
		AnsiUnderlineColorUnion Data;
		AnsiUnderlineColorType	Type = AnsiUnderlineColorType::Default;
	};

	inline bool operator==(const AnsiUnderlineColor& lhs, const AnsiUnderlineColor& rhs)
	{
		if (lhs.Type != rhs.Type)
			return false;
		switch(lhs.Type)
		{
			case AnsiUnderlineColorType::Default:		return true;
			case AnsiUnderlineColorType::AnsiNColor: 	return lhs.Data.NColor == rhs.Data.NColor;
			case AnsiUnderlineColorType::AnsiColor24b: 	return lhs.Data.Color24b == rhs.Data.Color24b;
		}
	}

	struct AnsiStyle {
	public:
		AnsiStyle() {}

		AnsiTFSIntensity		Intensity			= AnsiTFSIntensity::Normal;
		AnsiTFSItalic			Italic				= AnsiTFSItalic::Disable;
		AnsiTFSUnderline		Underline			= AnsiTFSUnderline::Disable;
		AnsiUnderlineColor		UnderlineColor;
		
		AnsiTFSBlink			Blink				= AnsiTFSBlink::Disable;
		AnsiTFSInverted			Inverted			= AnsiTFSInverted::Disable;
		AnsiTFSIdeogram			Ideogram			= AnsiTFSIdeogram::AllDisable;
		AnsiTFSScript			Script				= AnsiTFSScript::AllDisable;

		template <typename T> void ModifyThrow(const T&) { throw Detail::FormatGivenTypeError{}; }

		void ModifyThrow(const AnsiStyle& given)				{ *this = given; }

		void ModifyThrow(const AnsiTFSIntensity& given) 		{ Intensity = given; 	}
		void ModifyThrow(const AnsiTFSItalic& given) 			{ Italic = given; 		}
		void ModifyThrow(const AnsiTFSUnderline& given)			{ Underline = given;	}
		void ModifyThrow(const ResetAnsiUnderlineColor& given)	{ UnderlineColor.Type = AnsiUnderlineColorType::AnsiNColor; 	UnderlineColor.Data.NColor = AnsiNColorUnderline();  }
		void ModifyThrow(const AnsiNColorUnderline& given) 		{ UnderlineColor.Type = AnsiUnderlineColorType::AnsiNColor; 	UnderlineColor.Data.NColor = given;		}
		void ModifyThrow(const AnsiUnderlineColor24b& given) 	{ UnderlineColor.Type = AnsiUnderlineColorType::AnsiColor24b; 	UnderlineColor.Data.Color24b = given;	}

		void ModifyThrow(const AnsiTFSBlink& given) 			{ Blink = given; 	}
		void ModifyThrow(const AnsiTFSInverted& given) 			{ Inverted = given; }
		void ModifyThrow(const AnsiTFSIdeogram& given) 			{ Ideogram = given; }
		void ModifyThrow(const AnsiTFSScript& given) 			{ Script = given; 	}

	};

	inline bool operator==(const AnsiStyle& lhs, const AnsiStyle& rhs)
	{
		return lhs.Intensity == rhs.Intensity
			&& lhs.Italic == rhs.Italic
			&& lhs.Underline == rhs.Underline
			&& lhs.UnderlineColor == rhs.UnderlineColor
			&& lhs.Blink == rhs.Blink
			&& lhs.Inverted == rhs.Inverted
			&& lhs.Ideogram == rhs.Ideogram
			&& lhs.Script == rhs.Script;
	}

	const static inline ResetAnsiAllParameters	RESET_ANSI_ALL_PARAMETERS;
	const static inline ResetAnsiStyle			RESET_ANSI_STYLE;
	const static inline ResetAnsiUnderlineColor RESET_ANSI_UNDERLINE_COLOR;
}
