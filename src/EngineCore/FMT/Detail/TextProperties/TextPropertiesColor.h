#pragma once

#include "BaseTextProperties.h"

namespace EngineCore::FMT::Detail
{
	struct TextProperties::TextColor
	{
		struct Reset {};
	
		enum class BasicColorFG : std::uint8_t;
		enum class BasicColorBG : std::uint8_t;
		struct BasicColor;

		struct BaseColorCube;
		struct ColorCubeFG;
		struct ColorCubeBG;
		struct ColorCube;

		struct BaseColor24b;
		struct Color24bFG;
		struct Color24bBG;
		struct Color24b;

		enum class ColorType : std::uint8_t;
		union ColorFGData;
		union ColorBGData;
		struct ColorData;

		struct ColorFG;
		struct ColorBG;
		struct Color;
	};

	enum class TextProperties::TextColor::BasicColorFG : std::uint8_t
	{
		Black = 30,
		Red,
		Green,
		Yellow,
		Blue,
		Magenta,
		Cyan,
		White,

		BrightBlack = 90,
		BrightRed,
		BrightGreen,
		BrightYellow,
		BrightBlue,
		BrightMagenta,
		BrightCyan,
		BrightWhite,

		Default = 39,

		BaseStep = Black,
		BaseBStep = BrightBlack
	};

	enum class TextProperties::TextColor::BasicColorBG : std::uint8_t
	{
		Black = 40,
		Red,
		Green,
		Yellow,
		Blue,
		Magenta,
		Cyan,
		White,

		BrightBlack = 100,
		BrightRed,
		BrightGreen,
		BrightYellow,
		BrightBlue,
		BrightMagenta,
		BrightCyan,
		BrightWhite,

		Default = 49,

		BaseStep = Black,
		BaseBStep = BrightBlack,
	};

	struct TextProperties::TextColor::BasicColor
	{
		constexpr BasicColor(TextProperties::TextColor::BasicColorFG fg = TextProperties::TextColor::BasicColorFG::Default, TextProperties::TextColor::BasicColorBG bg = TextProperties::TextColor::BasicColorBG::Default)
			: Fg(fg), Bg(bg) { }
		TextProperties::TextColor::BasicColorFG Fg;
		TextProperties::TextColor::BasicColorBG Bg;
	};

	struct TextProperties::TextColor::BaseColorCube
	{
	public:
		static inline constexpr std::uint8_t Black		= 0;
		static inline constexpr std::uint8_t Red		= 1;
		static inline constexpr std::uint8_t Green		= 2;
		static inline constexpr std::uint8_t Yellow		= 3;
		static inline constexpr std::uint8_t Blue		= 4;
		static inline constexpr std::uint8_t Magenta	= 5;
		static inline constexpr std::uint8_t Cyan		= 6;
		static inline constexpr std::uint8_t White		= 7;

		static inline constexpr std::uint8_t BrightBlack	= 8;
		static inline constexpr std::uint8_t BrightRed		= 9;
		static inline constexpr std::uint8_t BrightGreen	= 10;
		static inline constexpr std::uint8_t BrightYellow	= 11;
		static inline constexpr std::uint8_t BrightBlue		= 12;
		static inline constexpr std::uint8_t BrightMagenta	= 13;
		static inline constexpr std::uint8_t BrightCyan		= 14;
		static inline constexpr std::uint8_t BrightWhite	= 15;

		static inline constexpr std::uint8_t MinNormalColor		= 0;
		static inline constexpr std::uint8_t MaxNormalColor		= 7;
		static inline constexpr std::uint8_t MinBrightColor		= 8;
		static inline constexpr std::uint8_t MaxBrightColor		= 15;
		static inline constexpr std::uint8_t Min666CubeColor	= 16;	// 16 + 36 * r + 6 * g + b
		static inline constexpr std::uint8_t Max666CubeColor	= 231;
		static inline constexpr std::uint8_t MinGrayscale		= 232;	// grayscale from black to white in 24 step
		static inline constexpr std::uint8_t MaxGrayscale		= 255;

		static inline constexpr std::uint8_t BaseStep		= MinNormalColor;
		static inline constexpr std::uint8_t BaseBStep		= MinBrightColor;
		static inline constexpr std::uint8_t Default		= 0;

	public:
		enum class Type : std::uint8_t
		{
			Normal,
			Bright,
			Cube666,
			Grayscale
		};

	public:
		std::uint8_t Color;

	public:
		std::uint8_t GetColor() const { return Color; }

		std::uint8_t GetColorRef()				{ return Color; }
		const std::uint8_t GetColorRef() const	{ return Color; }
	
	public:
		constexpr BaseColorCube(const std::uint8_t color)
			: Color(color) {}

		constexpr BaseColorCube()
			: Color(0) {}

		Type GetType()
		{
			if (Color >= MinNormalColor && Color <= MaxNormalColor)
				return Type::Normal;
			else if (Color >= MinBrightColor && Color <= MaxBrightColor)
				return Type::Bright;
			else if (Color >= Min666CubeColor && Color <= Max666CubeColor)
				return Type::Cube666;
			else if (Color >= MinGrayscale && Color <= MaxGrayscale)
				return Type::Grayscale;
			return Type::Normal;
		}

		static BaseColorCube MakeNormalColor(std::uint8_t value) {
			if (value > MaxNormalColor) value -= MinBrightColor;
			if (value > MaxNormalColor) value = MaxNormalColor;
			return BaseColorCube(value);
		}

		static BaseColorCube MakeBrightColor(std::uint8_t value) {
			if (value < MinBrightColor) value += MinBrightColor;
			if (value > MaxBrightColor) value = MaxBrightColor;
			return BaseColorCube(value);
		}

		static BaseColorCube Make666CubeColor255(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return Make666CubeColor5(	static_cast<std::uint8_t>((static_cast<float>(r) / 255) * 5),
										static_cast<std::uint8_t>((static_cast<float>(g) / 255) * 5),
										static_cast<std::uint8_t>((static_cast<float>(b) / 255) * 5));
		}

		static BaseColorCube Make666CubeColor5(std::uint8_t r, std::uint8_t g, std::uint8_t b) {
			if (r > 5) r = 5;
			if (g > 5) g = 5;
			if (b > 5) b = 5;
			return BaseColorCube(Min666CubeColor + 36 * r + 6 * g + b);
		}

		static BaseColorCube MakeGrayscaleColor255(const std::uint8_t value) {
			return MakeGrayscaleColor24(static_cast<std::uint8_t>(static_cast<float>(value) / 255) * 24);
		}

		static BaseColorCube MakeGrayscaleColor24(std::uint8_t value) {
			if (value > 24) value = 24;
			return BaseColorCube(MinGrayscale + value);
		}
	};

	struct TextProperties::TextColor::ColorCubeFG : public TextProperties::TextColor::BaseColorCube
	{
	public:
		constexpr explicit ColorCubeFG()												: TextProperties::TextColor::BaseColorCube() 		{}
		constexpr explicit ColorCubeFG(const std::uint8_t color)						: TextProperties::TextColor::BaseColorCube(color) 	{}
		constexpr ColorCubeFG(const TextProperties::TextColor::BaseColorCube& color)	: TextProperties::TextColor::BaseColorCube(color) 	{}

	public:
		static ColorCubeFG MakeNormalColor(const std::uint8_t value) {
			return static_cast<ColorCubeFG>(TextProperties::TextColor::BaseColorCube::MakeNormalColor(value));
		}

		static ColorCubeFG MakeBrightColor(const std::uint8_t value) {
			return static_cast<ColorCubeFG>(TextProperties::TextColor::BaseColorCube::MakeBrightColor(value));
		}

		static ColorCubeFG Make666CubeColor255(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return static_cast<ColorCubeFG>(TextProperties::TextColor::BaseColorCube::Make666CubeColor255(r, g, b));
		}

		static ColorCubeFG Make666CubeColor5(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return static_cast<ColorCubeFG>(TextProperties::TextColor::BaseColorCube::Make666CubeColor5(r, g, b));
		}

		static ColorCubeFG MakeGrayscaleColor255(const std::uint8_t value) {
			return static_cast<ColorCubeFG>(TextProperties::TextColor::BaseColorCube::MakeGrayscaleColor255(value));
		}

		static ColorCubeFG MakeGrayscaleColor24(const std::uint8_t value) {
			return static_cast<ColorCubeFG>(TextProperties::TextColor::BaseColorCube::MakeGrayscaleColor24(value));
		}
	};
	
	struct TextProperties::TextColor::ColorCubeBG : public TextProperties::TextColor::BaseColorCube
	{
		constexpr explicit ColorCubeBG()														: TextProperties::TextColor::BaseColorCube() 		{}
		constexpr explicit ColorCubeBG(const std::uint8_t color)								: TextProperties::TextColor::BaseColorCube(color) 	{}
		constexpr ColorCubeBG(const TextProperties::TextColor::BaseColorCube& color)			: TextProperties::TextColor::BaseColorCube(color) 	{}

	public:
		static TextProperties::TextColor::ColorCubeBG MakeNormalColor(const std::uint8_t value) {
			return static_cast<TextProperties::TextColor::ColorCubeBG>(TextProperties::TextColor::BaseColorCube::MakeNormalColor(value));
		}

		static TextProperties::TextColor::ColorCubeBG MakeBrightColor(const std::uint8_t value) {
			return static_cast<TextProperties::TextColor::ColorCubeBG>(TextProperties::TextColor::BaseColorCube::MakeBrightColor(value));
		}

		static TextProperties::TextColor::ColorCubeBG Make666CubeColor255(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return static_cast<TextProperties::TextColor::ColorCubeBG>(TextProperties::TextColor::BaseColorCube::Make666CubeColor255(r, g, b));
		}

		static TextProperties::TextColor::ColorCubeBG Make666CubeColor5(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return static_cast<TextProperties::TextColor::ColorCubeBG>(TextProperties::TextColor::BaseColorCube::Make666CubeColor5(r, g, b));
		}

		static TextProperties::TextColor::ColorCubeBG MakeGrayscaleColor255(const std::uint8_t value) {
			return static_cast<TextProperties::TextColor::ColorCubeBG>(TextProperties::TextColor::BaseColorCube::MakeGrayscaleColor255(value));
		}

		static TextProperties::TextColor::ColorCubeBG MakeGrayscaleColor24(const std::uint8_t value) {
			return static_cast<TextProperties::TextColor::ColorCubeBG>(TextProperties::TextColor::BaseColorCube::MakeGrayscaleColor24(value));
		}
	};

	inline bool operator==(const TextProperties::TextColor::BaseColorCube& lhs, const TextProperties::TextColor::BaseColorCube& rhs)
	{
		return lhs.Color == rhs.Color;
	}

	struct TextProperties::TextColor::ColorCube
	{
		constexpr ColorCube()
			: Fg()
			, Bg()
		{}
		
		constexpr ColorCube(const TextProperties::TextColor::ColorCubeFG& fg)
			: Fg(fg)
			, Bg()
		{}

		constexpr ColorCube(const TextProperties::TextColor::ColorCubeFG& fg, const TextProperties::TextColor::ColorCubeBG& bg)
			: Fg(fg)
			, Bg(bg)
		{}

		TextProperties::TextColor::ColorCubeFG Fg;
		TextProperties::TextColor::ColorCubeBG Bg;
	};


	struct TextProperties::TextColor::BaseColor24b
	{
		constexpr BaseColor24b(std::uint8_t r, std::uint8_t g, std::uint8_t b)
			: R(r), G(g), B(b) { }
		std::uint8_t R, G, B;
	};

	inline bool operator==(const TextProperties::TextColor::BaseColor24b& lhs, const TextProperties::TextColor::BaseColor24b& rhs)
	{
		return lhs.R == rhs.R && lhs.G == rhs.G && lhs.B == rhs.B;
	}

	struct TextProperties::TextColor::Color24bFG : public TextProperties::TextColor::BaseColor24b
	{
		constexpr Color24bFG(std::uint8_t r = 255, std::uint8_t g = 255, std::uint8_t b = 255)
			: TextProperties::TextColor::BaseColor24b(r, g, b) {};
	};

	struct TextProperties::TextColor::Color24bBG : public TextProperties::TextColor::BaseColor24b
	{
		constexpr Color24bBG(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0)
			: TextProperties::TextColor::BaseColor24b(r, g, b) {};
	};


	struct TextProperties::TextColor::Color24b
	{
		constexpr Color24b(const TextProperties::TextColor::Color24bFG&& fg = TextProperties::TextColor::Color24bFG(), const TextProperties::TextColor::Color24bBG&& bg = TextProperties::TextColor::Color24bBG())
			: Fg(fg), Bg(bg) { }

		TextProperties::TextColor::Color24bFG Fg;
		TextProperties::TextColor::Color24bBG Bg;
	};

	inline bool operator==(const TextProperties::TextColor::Color24b& lhs, const TextProperties::TextColor::Color24b& rhs)
	{
		return lhs.Fg == rhs.Fg && lhs.Bg == rhs.Bg;
	}

	enum class TextProperties::TextColor::ColorType : std::uint8_t
	{
		Default,
		BasicColor,
		ColorCube,
		Color24b
	};

	union TextProperties::TextColor::ColorFGData
	{
		constexpr ColorFGData()
			: BasicColor{ TextProperties::TextColor::BasicColorFG::Default }
		{}

		TextProperties::TextColor::BasicColorFG  BasicColor;
		TextProperties::TextColor::ColorCubeFG 	ColorCube;
		TextProperties::TextColor::Color24bFG 	Color24b;
	};

	union TextProperties::TextColor::ColorBGData
	{
		constexpr ColorBGData()
			: BasicColor{ TextProperties::TextColor::BasicColorBG::Default }
		{}

		TextProperties::TextColor::BasicColorBG  BasicColor;
		TextProperties::TextColor::ColorCubeBG	 ColorCube;
		TextProperties::TextColor::Color24bBG 	 Color24b;
	};

	struct TextProperties::TextColor::ColorFG
	{
		TextProperties::TextColor::ColorFGData 	Data;
		TextProperties::TextColor::ColorType	Type { TextProperties::TextColor::ColorType::Default };
	};

	struct TextProperties::TextColor::ColorBG
	{
		TextProperties::TextColor::ColorBGData 	Data;
		TextProperties::TextColor::ColorType	Type { TextProperties::TextColor::ColorType::Default };
	};

	inline bool operator==(const TextProperties::TextColor::ColorFG& lhs, const TextProperties::TextColor::ColorFG& rhs)
	{
		if (lhs.Type != rhs.Type)
			return false;
		switch(lhs.Type)
		{
			case TextProperties::TextColor::ColorType::Default:		return true;
			case TextProperties::TextColor::ColorType::BasicColor: 	return lhs.Data.BasicColor == rhs.Data.BasicColor;
			case TextProperties::TextColor::ColorType::ColorCube: 	return lhs.Data.ColorCube == rhs.Data.ColorCube;
			case TextProperties::TextColor::ColorType::Color24b: 	return lhs.Data.Color24b == rhs.Data.Color24b;
		}
		return false;
	}

	inline bool operator==(const TextProperties::TextColor::ColorBG& lhs, const TextProperties::TextColor::ColorBG& rhs)
	{
		if (lhs.Type != rhs.Type)
			return false;
		switch(lhs.Type)
		{
			case TextProperties::TextColor::ColorType::Default:		return true;
			case TextProperties::TextColor::ColorType::BasicColor: 	return lhs.Data.BasicColor == rhs.Data.BasicColor;
			case TextProperties::TextColor::ColorType::ColorCube: 	return lhs.Data.ColorCube == rhs.Data.ColorCube;
			case TextProperties::TextColor::ColorType::Color24b: 	return lhs.Data.Color24b == rhs.Data.Color24b;
		}
		return false;
	}

	// Manage only the text color / the underline color will be manage by the TextProperties::TextStyle::UnderlineColor
	struct TextProperties::TextColor::Color
	{
	public:
		constexpr Color()
			: Fg()
			, Bg()
		{}

	public:
		TextProperties::TextColor::ColorFG Fg;
		TextProperties::TextColor::ColorBG Bg;

	public:
		template <typename T> void ModifyThrow(const T&) { throw FMTGivenTypeError(); }

		void ModifyThrow(const Color& given) { *this = given; }

		void ModifyThrow(const TextProperties::TextColor::Reset& given) {
			Fg = TextProperties::TextColor::ColorFG{};
			Bg = TextProperties::TextColor::ColorBG{};
		}

		void ModifyThrow(const TextProperties::TextColor::BasicColorFG& given) {
			Fg.Type = TextProperties::TextColor::ColorType::BasicColor;
			Fg.Data.BasicColor = given;
		}

		void ModifyThrow(const TextProperties::TextColor::BasicColorBG& given) {
			Bg.Type = TextProperties::TextColor::ColorType::BasicColor;
			Bg.Data.BasicColor = given;
		}

		void ModifyThrow(const TextProperties::TextColor::ColorCubeFG& given) {
			Fg.Type = TextProperties::TextColor::ColorType::ColorCube;
			Fg.Data.ColorCube = given;
		}

		void ModifyThrow(const TextProperties::TextColor::ColorCubeBG& given) {
			Bg.Type = TextProperties::TextColor::ColorType::ColorCube;
			Bg.Data.ColorCube = given;
		}

		void ModifyThrow(const TextProperties::TextColor::Color24bFG& given) {
			Fg.Type = TextProperties::TextColor::ColorType::Color24b;
			Fg.Data.Color24b = given;
		}

		void ModifyThrow(const TextProperties::TextColor::Color24bBG& given) {
			Bg.Type = TextProperties::TextColor::ColorType::Color24b;
			Bg.Data.Color24b = given;
		}
	};
	
	inline bool operator==(const TextProperties::TextColor::Color& lhs, const TextProperties::TextColor::Color& rhs)
	{
		return lhs.Fg == rhs.Fg && lhs.Bg == rhs.Bg;
	}
}
