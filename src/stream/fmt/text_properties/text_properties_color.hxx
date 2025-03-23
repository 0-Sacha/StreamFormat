#pragma once

#include "base_text_properties.hxx"

namespace stream::fmt::detail {
    struct TextProperties::TextColor {
        struct reset_color {};

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

    enum class TextProperties::TextColor::BasicColorFG : std::uint8_t {
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

        BaseStep  = Black,
        BaseBStep = BrightBlack
    };

    enum class TextProperties::TextColor::BasicColorBG : std::uint8_t {
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

        BaseStep  = Black,
        BaseBStep = BrightBlack,
    };

    struct TextProperties::TextColor::BasicColor {
        constexpr BasicColor(TextProperties::TextColor::BasicColorFG fg = TextProperties::TextColor::BasicColorFG::Default,
                             TextProperties::TextColor::BasicColorBG bg = TextProperties::TextColor::BasicColorBG::Default)
            : fg(fg), bg(bg) {}
        TextProperties::TextColor::BasicColorFG fg;
        TextProperties::TextColor::BasicColorBG bg;
    };

    struct TextProperties::TextColor::BaseColorCube {
    public:
        static inline constexpr std::uint8_t Black   = 0;
        static inline constexpr std::uint8_t Red     = 1;
        static inline constexpr std::uint8_t Green   = 2;
        static inline constexpr std::uint8_t Yellow  = 3;
        static inline constexpr std::uint8_t Blue    = 4;
        static inline constexpr std::uint8_t Magenta = 5;
        static inline constexpr std::uint8_t Cyan    = 6;
        static inline constexpr std::uint8_t White   = 7;

        static inline constexpr std::uint8_t BrightBlack   = 8;
        static inline constexpr std::uint8_t BrightRed     = 9;
        static inline constexpr std::uint8_t BrightGreen   = 10;
        static inline constexpr std::uint8_t BrightYellow  = 11;
        static inline constexpr std::uint8_t BrightBlue    = 12;
        static inline constexpr std::uint8_t BrightMagenta = 13;
        static inline constexpr std::uint8_t BrightCyan    = 14;
        static inline constexpr std::uint8_t BrightWhite   = 15;

        static inline constexpr std::uint8_t MinNormalColor  = 0;
        static inline constexpr std::uint8_t MaxNormalColor  = 7;
        static inline constexpr std::uint8_t MinBrightColor  = 8;
        static inline constexpr std::uint8_t MaxBrightColor  = 15;
        static inline constexpr std::uint8_t Min666CubeColor = 16;  // 16 + 36 * r + 6 * g + b
        static inline constexpr std::uint8_t Max666CubeColor = 231;
        static inline constexpr std::uint8_t MinGrayscale    = 232;  // grayscale from black to white in 24 step
        static inline constexpr std::uint8_t MaxGrayscale    = 255;

        static inline constexpr std::uint8_t BaseStep  = MinNormalColor;
        static inline constexpr std::uint8_t BaseBStep = MinBrightColor;
        static inline constexpr std::uint8_t Default   = 0;

    public:
        enum class type : std::uint8_t {
            Normal,
            Bright,
            Cube666,
            Grayscale
        };

    public:
        std::uint8_t color;

    public:
        std::uint8_t get_color() const {
            return color;
        }
        std::uint8_t get_color_ref() {
            return color;
        }
        std::uint8_t get_color_ref() const {
            return color;
        }

    public:
        constexpr BaseColorCube(const std::uint8_t color) : color(color) {}

        constexpr BaseColorCube() : color(0) {}

        type GetType() {
            if (color >= MinNormalColor && color <= MaxNormalColor)
                return type::Normal;
            else if (color >= MinBrightColor && color <= MaxBrightColor)
                return type::Bright;
            else if (color >= Min666CubeColor && color <= Max666CubeColor)
                return type::Cube666;
            else if (color >= MinGrayscale && color <= MaxGrayscale)
                return type::Grayscale;
            return type::Normal;
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
            return Make666CubeColor5(static_cast<std::uint8_t>((static_cast<float>(r) / 255) * 5), static_cast<std::uint8_t>((static_cast<float>(g) / 255) * 5),
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

    // No need of virtual destructor since ColorCubeFG is purely a renaming of BaseColorCube
    struct TextProperties::TextColor::ColorCubeFG : public TextProperties::TextColor::BaseColorCube {
    public:
        constexpr explicit ColorCubeFG() : TextProperties::TextColor::BaseColorCube() {}
        constexpr explicit ColorCubeFG(const std::uint8_t color) : TextProperties::TextColor::BaseColorCube(color) {}
        constexpr ColorCubeFG(const TextProperties::TextColor::BaseColorCube& color) : TextProperties::TextColor::BaseColorCube(color) {}

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

    // No need of virtual destructor since ColorCubeBG is purely a renaming of BaseColorCube
    struct TextProperties::TextColor::ColorCubeBG : public TextProperties::TextColor::BaseColorCube {
        constexpr explicit ColorCubeBG() : TextProperties::TextColor::BaseColorCube() {}
        constexpr explicit ColorCubeBG(const std::uint8_t color) : TextProperties::TextColor::BaseColorCube(color) {}
        constexpr ColorCubeBG(const TextProperties::TextColor::BaseColorCube& color) : TextProperties::TextColor::BaseColorCube(color) {}

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

    inline bool operator==(const TextProperties::TextColor::BaseColorCube& lhs, const TextProperties::TextColor::BaseColorCube& rhs) {
        return lhs.color == rhs.color;
    }

    struct TextProperties::TextColor::ColorCube {
        constexpr ColorCube() : fg(), bg() {}

        constexpr ColorCube(const TextProperties::TextColor::ColorCubeFG& fg) : fg(fg), bg() {}

        constexpr ColorCube(const TextProperties::TextColor::ColorCubeFG& fg, const TextProperties::TextColor::ColorCubeBG& bg) : fg(fg), bg(bg) {}

        TextProperties::TextColor::ColorCubeFG fg;
        TextProperties::TextColor::ColorCubeBG bg;
    };

    struct TextProperties::TextColor::BaseColor24b {
        constexpr BaseColor24b(std::uint8_t r, std::uint8_t g, std::uint8_t b) : r(r), g(g), b(b) {}
        std::uint8_t r, g, b;
    };

    inline bool operator==(const TextProperties::TextColor::BaseColor24b& lhs, const TextProperties::TextColor::BaseColor24b& rhs) {
        return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
    }

    // No need of virtual destructor since Color24bFG is purely a renaming of BaseColor24b
    struct TextProperties::TextColor::Color24bFG : public TextProperties::TextColor::BaseColor24b {
        constexpr Color24bFG(std::uint8_t r = 255, std::uint8_t g = 255, std::uint8_t b = 255) : TextProperties::TextColor::BaseColor24b(r, g, b) {}
    };

    // No need of virtual destructor since Color24bBG is purely a renaming of BaseColor24b
    struct TextProperties::TextColor::Color24bBG : public TextProperties::TextColor::BaseColor24b {
        constexpr Color24bBG(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0) : TextProperties::TextColor::BaseColor24b(r, g, b) {}
    };

    struct TextProperties::TextColor::Color24b {
        constexpr Color24b(const TextProperties::TextColor::Color24bFG&& fg_ = TextProperties::TextColor::Color24bFG(),
                           const TextProperties::TextColor::Color24bBG&& bg_ = TextProperties::TextColor::Color24bBG())
            : fg(fg_), bg(bg_) {}

        TextProperties::TextColor::Color24bFG fg;
        TextProperties::TextColor::Color24bBG bg;
    };

    inline bool operator==(const TextProperties::TextColor::Color24b& lhs, const TextProperties::TextColor::Color24b& rhs) {
        return lhs.fg == rhs.fg && lhs.bg == rhs.bg;
    }

    enum class TextProperties::TextColor::ColorType : std::uint8_t {
        BasicColor,
        ColorCube,
        Color24b
    };

    union TextProperties::TextColor::ColorFGData {
        constexpr ColorFGData() : basic_color{TextProperties::TextColor::BasicColorFG::Default} {}

        TextProperties::TextColor::BasicColorFG basic_color;
        TextProperties::TextColor::ColorCubeFG  color_cube;
        TextProperties::TextColor::Color24bFG   color24b;
    };

    union TextProperties::TextColor::ColorBGData {
        constexpr ColorBGData() : basic_color{TextProperties::TextColor::BasicColorBG::Default} {}

        TextProperties::TextColor::BasicColorBG basic_color;
        TextProperties::TextColor::ColorCubeBG  color_cube;
        TextProperties::TextColor::Color24bBG   color24b;
    };

    struct TextProperties::TextColor::ColorFG {
        TextProperties::TextColor::ColorFGData data;
        TextProperties::TextColor::ColorType   type{TextProperties::TextColor::ColorType::BasicColor};
    };

    struct TextProperties::TextColor::ColorBG {
        TextProperties::TextColor::ColorBGData data;
        TextProperties::TextColor::ColorType   type{TextProperties::TextColor::ColorType::BasicColor};
    };

    inline bool operator==(const TextProperties::TextColor::ColorFG& lhs, const TextProperties::TextColor::ColorFG& rhs) {
        if (lhs.type != rhs.type) return false;
        switch (lhs.type) {
            case TextProperties::TextColor::ColorType::BasicColor:
                return lhs.data.basic_color == rhs.data.basic_color;
            case TextProperties::TextColor::ColorType::ColorCube:
                return lhs.data.color_cube == rhs.data.color_cube;
            case TextProperties::TextColor::ColorType::Color24b:
                return lhs.data.color24b == rhs.data.color24b;
        }
        return false;
    }

    inline bool operator==(const TextProperties::TextColor::ColorBG& lhs, const TextProperties::TextColor::ColorBG& rhs) {
        if (lhs.type != rhs.type) return false;
        switch (lhs.type) {
            case TextProperties::TextColor::ColorType::BasicColor:
                return lhs.data.basic_color == rhs.data.basic_color;
            case TextProperties::TextColor::ColorType::ColorCube:
                return lhs.data.color_cube == rhs.data.color_cube;
            case TextProperties::TextColor::ColorType::Color24b:
                return lhs.data.color24b == rhs.data.color24b;
        }
        return false;
    }

    bool operator==(const TextProperties::TextColor::Color& lhs, const TextProperties::TextColor::Color& rhs);

    // Manage only the text color / the underline color will be manage by the TextProperties::TextStyle::UnderlineColor
    struct TextProperties::TextColor::Color {
    public:
        constexpr Color() : fg(), bg() {}

    public:
        TextProperties::TextColor::ColorFG fg;
        TextProperties::TextColor::ColorBG bg;

    public:
        void modify_reset() {
            fg = TextProperties::TextColor::ColorFG{};
            bg = TextProperties::TextColor::ColorBG{};
        }

        void apply(const TextProperties::TextColor::Color& given) {
            *this = given;
        }

        void apply(const TextProperties::TextColor::reset_color&) {
            modify_reset();
        }
        void apply(const TextProperties::TextColor::BasicColorFG& given) {
            fg.type             = TextProperties::TextColor::ColorType::BasicColor;
            fg.data.basic_color = given;
        }
        void apply(const TextProperties::TextColor::BasicColorBG& given) {
            bg.type             = TextProperties::TextColor::ColorType::BasicColor;
            bg.data.basic_color = given;
        }
        void apply(const TextProperties::TextColor::BasicColor& given) {
            apply(given.fg);
            apply(given.bg);
        }
        void apply(const TextProperties::TextColor::ColorCubeFG& given) {
            fg.type            = TextProperties::TextColor::ColorType::ColorCube;
            fg.data.color_cube = given;
        }
        void apply(const TextProperties::TextColor::ColorCubeBG& given) {
            bg.type            = TextProperties::TextColor::ColorType::ColorCube;
            bg.data.color_cube = given;
        }
        void apply(const TextProperties::TextColor::ColorCube& given) {
            apply(given.fg);
            apply(given.bg);
        }
        void apply(const TextProperties::TextColor::Color24bFG& given) {
            fg.type          = TextProperties::TextColor::ColorType::Color24b;
            fg.data.color24b = given;
        }
        void apply(const TextProperties::TextColor::Color24bBG& given) {
            bg.type          = TextProperties::TextColor::ColorType::Color24b;
            bg.data.color24b = given;
        }
        void apply(const TextProperties::TextColor::Color24b& given) {
            apply(given.fg);
            apply(given.bg);
        }

    public:
        bool need_modif(const TextProperties::TextColor::reset_color&) {
            return true;
        }

        bool need_modif(const TextProperties::TextColor::Color& given) {
            return *this != given;
        }

        bool need_modif(const TextProperties::TextColor::BasicColorFG& given) {
            return fg.type != TextProperties::TextColor::ColorType::BasicColor || fg.data.basic_color != given;
        }
        bool need_modif(const TextProperties::TextColor::BasicColorBG& given) {
            return bg.type != TextProperties::TextColor::ColorType::BasicColor || bg.data.basic_color != given;
        }
        bool need_modif(const TextProperties::TextColor::BasicColor& given) {
            return need_modif(given.fg) || need_modif(given.bg);
        }
        bool need_modif(const TextProperties::TextColor::ColorCubeFG& given) {
            return fg.type != TextProperties::TextColor::ColorType::ColorCube || fg.data.color_cube != given;
        }
        bool need_modif(const TextProperties::TextColor::ColorCubeBG& given) {
            return bg.type != TextProperties::TextColor::ColorType::ColorCube || bg.data.color_cube != given;
        }
        bool need_modif(const TextProperties::TextColor::ColorCube& given) {
            return need_modif(given.fg) || need_modif(given.bg);
        }
        bool need_modif(const TextProperties::TextColor::Color24bFG& given) {
            return fg.type != TextProperties::TextColor::ColorType::Color24b || fg.data.color24b != given;
        }
        bool need_modif(const TextProperties::TextColor::Color24bBG& given) {
            return bg.type != TextProperties::TextColor::ColorType::Color24b || bg.data.color24b != given;
        }
        bool need_modif(const TextProperties::TextColor::Color24b& given) {
            return need_modif(given.fg) || need_modif(given.bg);
        }
    };

    inline bool operator==(const TextProperties::TextColor::Color& lhs, const TextProperties::TextColor::Color& rhs) {
        return lhs.fg == rhs.fg && lhs.bg == rhs.bg;
    }

    template <typename T>
    concept text_properties_color_can_apply = requires(const T& value, TextProperties::TextColor::Color& data) { data.apply(value); };

    template <typename T>
    struct TextPropertiesColorIsApplyType {
        using BaseType              = get_base_type<T>;
        static constexpr bool value = std::is_same_v<BaseType, TextProperties::TextColor::Color> || std::is_same_v<BaseType, TextProperties::TextColor::reset_color> ||
                                      std::is_same_v<BaseType, TextProperties::TextColor::BasicColorFG> || std::is_same_v<BaseType, TextProperties::TextColor::BasicColorBG> ||
                                      std::is_same_v<BaseType, TextProperties::TextColor::BasicColor> || std::is_same_v<BaseType, TextProperties::TextColor::ColorCubeFG> ||
                                      std::is_same_v<BaseType, TextProperties::TextColor::ColorCubeBG> || std::is_same_v<BaseType, TextProperties::TextColor::ColorCube> ||
                                      std::is_same_v<BaseType, TextProperties::TextColor::Color24bFG> || std::is_same_v<BaseType, TextProperties::TextColor::Color24bBG> ||
                                      std::is_same_v<BaseType, TextProperties::TextColor::Color24b>;
    };

    template <typename T>
    concept text_properties_color_is_apply = TextPropertiesColorIsApplyType<T>::value;
}  // namespace stream::fmt::detail
