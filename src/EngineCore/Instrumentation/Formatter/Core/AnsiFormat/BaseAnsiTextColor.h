#pragma once

#include "EngineCore/Core.h"

namespace EngineCore::Instrumentation::FMT::Detail {

	// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

	enum class AnsiTextColorFG : std::uint8_t {
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

	enum class AnsiTextColorBG : std::uint8_t {
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

	struct AnsiTextColor {
		AnsiTextColor(AnsiTextColorFG _fg = AnsiTextColorFG::Default, AnsiTextColorBG _bg = AnsiTextColorBG::Default)
			: Fg(_fg), Bg(_bg) { }
		AnsiTextColorFG Fg;
		AnsiTextColorBG Bg;
	};



	struct AnsiNColorType {
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

	public:
		enum class AnsiColorNType : std::uint8_t {
			Normal,
			Bright,
			Cube666,
			Grayscale
		};

	public:
		std::uint8_t	Color;
		std::uint8_t GetColor() const { return Color; }

		std::uint8_t GetColorRef()				{ return Color; }
		const std::uint8_t GetColorRef() const	{ return Color; }
	
	public:
		AnsiNColorType(const std::uint8_t color = 0)
			: Color(color) {}

		AnsiColorNType GetAnsiNType() {
			if (Color >= MinNormalColor && Color <= MaxNormalColor)
				return AnsiColorNType::Normal;
			else if (Color >= MinBrightColor && Color <= MaxBrightColor)
				return AnsiColorNType::Bright;
			else if (Color >= Min666CubeColor && Color <= Max666CubeColor)
				return AnsiColorNType::Cube666;
			else if (Color >= MinGrayscale && Color <= MaxGrayscale)
				return AnsiColorNType::Grayscale;
			return AnsiColorNType::Normal;
		}

		static AnsiNColorType MakeNormalColor(std::uint8_t value) {
			if (value > MaxNormalColor) value -= MinBrightColor;
			if (value > MaxNormalColor) value = MaxNormalColor;
			return AnsiNColorType(value);
		}

		static AnsiNColorType MakeBrightColor(std::uint8_t value) {
			if (value < MinBrightColor) value += MinBrightColor;
			if (value > MaxBrightColor) value = MaxBrightColor;
			return AnsiNColorType(value);
		}

		static AnsiNColorType Make666CubeColor255(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return Make666CubeColor5(	static_cast<std::uint8_t>((static_cast<float>(r) / 255) * 5),
										static_cast<std::uint8_t>((static_cast<float>(g) / 255) * 5),
										static_cast<std::uint8_t>((static_cast<float>(b) / 255) * 5));
		}

		static AnsiNColorType Make666CubeColor5(std::uint8_t r, std::uint8_t g, std::uint8_t b) {
			if (r > 5) r = 5;
			if (g > 5) g = 5;
			if (b > 5) b = 5;
			return AnsiNColorType(Min666CubeColor + 36 * r + 6 * g + b);
		}

		static AnsiNColorType MakeGrayscaleColor255(const std::uint8_t value) {
			return MakeGrayscaleColor24(static_cast<std::uint8_t>(static_cast<float>(value) / 255) * 24);
		}

		static AnsiNColorType MakeGrayscaleColor24(std::uint8_t value) {
			if (value > 24) value = 24;
			return AnsiNColorType(MinGrayscale + value);
		}
	};

	struct AnsiNColorFg	: public AnsiNColorType {
	public:
		AnsiNColorFg(const std::uint8_t color = 0)	: AnsiNColorType(color) {}
		AnsiNColorFg(const AnsiNColorType color)	: AnsiNColorType(color.GetColor()) {}

	public:
		static AnsiNColorFg MakeNormalColor(const std::uint8_t value) {
			return static_cast<AnsiNColorFg>(AnsiNColorType::MakeNormalColor(value));
		}

		static AnsiNColorFg MakeBrightColor(const std::uint8_t value) {
			return static_cast<AnsiNColorFg>(AnsiNColorType::MakeBrightColor(value));
		}

		static AnsiNColorFg Make666CubeColor255(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return static_cast<AnsiNColorFg>(AnsiNColorType::Make666CubeColor255(r, g, b));
		}

		static AnsiNColorFg Make666CubeColor5(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return static_cast<AnsiNColorFg>(AnsiNColorType::Make666CubeColor5(r, g, b));
		}

		static AnsiNColorFg MakeGrayscaleColor255(const std::uint8_t value) {
			return static_cast<AnsiNColorFg>(AnsiNColorType::MakeGrayscaleColor255(value));
		}

		static AnsiNColorFg MakeGrayscaleColor24(const std::uint8_t value) {
			return static_cast<AnsiNColorFg>(AnsiNColorType::MakeGrayscaleColor24(value));
		}
	};
	
	struct AnsiNColorBg	: public AnsiNColorType {
		AnsiNColorBg(const std::uint8_t color = 0)	: AnsiNColorType(color) {}
		AnsiNColorBg(const AnsiNColorType color)	: AnsiNColorType(color.GetColor()) {}

	public:
		static AnsiNColorBg MakeNormalColor(const std::uint8_t value) {
			return static_cast<AnsiNColorBg>(AnsiNColorType::MakeNormalColor(value));
		}

		static AnsiNColorBg MakeBrightColor(const std::uint8_t value) {
			return static_cast<AnsiNColorBg>(AnsiNColorType::MakeBrightColor(value));
		}

		static AnsiNColorBg Make666CubeColor255(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return static_cast<AnsiNColorBg>(AnsiNColorType::Make666CubeColor255(r, g, b));
		}

		static AnsiNColorBg Make666CubeColor5(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) {
			return static_cast<AnsiNColorBg>(AnsiNColorType::Make666CubeColor5(r, g, b));
		}

		static AnsiNColorBg MakeGrayscaleColor255(const std::uint8_t value) {
			return static_cast<AnsiNColorBg>(AnsiNColorType::MakeGrayscaleColor255(value));
		}

		static AnsiNColorBg MakeGrayscaleColor24(const std::uint8_t value) {
			return static_cast<AnsiNColorBg>(AnsiNColorType::MakeGrayscaleColor24(value));
		}
	};

	struct AnsiNColor {
		AnsiNColor(const AnsiNColorFg&& fg = AnsiNColorFg(0), const AnsiNColorBg bg = AnsiNColorBg(0))
			: Fg(fg)
			, Bg(bg) {}
		
		AnsiNColorFg Fg;
		AnsiNColorBg Bg;
	};


	struct AnsiColor24bType {
		AnsiColor24bType(std::uint8_t r, std::uint8_t g, std::uint8_t b)
			: R(r), G(g), B(b) { }
		std::uint8_t R, G, B;
	};

	struct AnsiColor24bFg : public AnsiColor24bType {
		AnsiColor24bFg(std::uint8_t r = 255, std::uint8_t g = 255, std::uint8_t b = 255)
			: AnsiColor24bType(r, g, b) {};
	};

	struct AnsiColor24bBg : public AnsiColor24bType {
		AnsiColor24bBg(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0)
			: AnsiColor24bType(r, g, b) {};
	};


	struct AnsiColor24b {
		AnsiColor24b(const AnsiColor24bFg&& fg = AnsiColor24bFg(), const AnsiColor24bBg&& bg = AnsiColor24bBg())
			: Fg(fg), Bg(bg) { }
		AnsiColor24bFg Fg;
		AnsiColor24bBg Bg;
	};

	enum class AnsiTextColorDataType: std::uint8_t {
		Default,
		AnsiTextColor,
		AnsiNColor,
		AnsiColor24b
	};

	// Manage only the text color / the underline color will be manage by the AnsiTextFormatStyle
	struct AnsiColor
	{
		AnsiColor()
			: FgType(AnsiTextColorDataType::Default), BgType(AnsiTextColorDataType::Default) {}

		AnsiTextColorDataType	FgType;
		AnsiTextColorDataType	BgType;
		union {
			AnsiNColorFg Text;
			AnsiNColorFg NColor;
			AnsiColor24bFg Color24b;
		} Fg;

		union {
			AnsiNColorBg Text;
			AnsiNColorBg NColor;
			AnsiColor24bBg Color24b;
		} Bg;
	};

	struct AnsiTextColorChange
	{
		bool HasSetFg = false;
		bool HasSetBg = false;
	};

	const static inline AnsiTextColor RESET_ANSI_COLOR;
}