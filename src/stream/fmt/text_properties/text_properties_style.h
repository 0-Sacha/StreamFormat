#pragma once

#include "base_text_properties.h"
#include "text_properties_color.h"

namespace stream::fmt::detail
{
    struct TextProperties::TextStyle
    {
        struct reset_style
        {
        };

        enum class Intensity : std::uint8_t;
        enum class Italic : std::uint8_t;
        enum class Blink : std::uint8_t;
        enum class Inverted : std::uint8_t;
        enum class Ideogram : std::uint8_t;
        enum class Script : std::uint8_t;
        enum class Underline : std::uint8_t;
        struct UnderlineColor;

        struct Style;
    };

    enum class TextProperties::TextStyle::Intensity : std::uint8_t
    {
        Bold   = 1,
        Dim    = 2,
        Normal = 22
    };

    enum class TextProperties::TextStyle::Italic : std::uint8_t
    {
        Enable  = 3,
        Disable = 23
    };

    enum class TextProperties::TextStyle::Underline : std::uint8_t
    {
        Underlined      = 4,
        DoubleUnerlined = 21,  // may only disable bold
        Disable         = 24,

        SelectUnderlinedColor = 254
    };

    enum class TextProperties::TextStyle::Blink : std::uint8_t
    {
        SlowBlink = 5,
        FastBlink = 6,
        Disable   = 25
    };

    enum class TextProperties::TextStyle::Inverted : std::uint8_t
    {
        Enable  = 7,
        Disable = 27
    };

    enum class TextProperties::TextStyle::Ideogram : std::uint8_t
    {
        Underlined       = 60,
        DoubleUnderlined = 61,
        Overlined        = 62,
        DoubleOverlined  = 63,
        StressMarking    = 64,
        AllDisable       = 65
    };

    enum class TextProperties::TextStyle::Script : std::uint8_t
    {
        Superscript = 74,
        Subscript   = 75,
        AllDisable  = 76
    };

    struct TextProperties::TextStyle::UnderlineColor
    {
        struct ColorCube;
        struct Color24b;
        enum class ColorType : std::uint8_t;
        union ColorData;
        struct Color;
    };

    // No need of virtual destructor since color24b is purely a renaming of BaseColor24b
    struct TextProperties::TextStyle::UnderlineColor::Color24b : public TextProperties::TextColor::BaseColor24b
    {
        constexpr Color24b(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0)
            : TextProperties::TextColor::BaseColor24b(r, g, b)
        {}
    };

    // No need of virtual destructor since color_cube is purely a renaming of BaseColorCube
    struct TextProperties::TextStyle::UnderlineColor::ColorCube : public TextProperties::TextColor::BaseColorCube
    {
        constexpr ColorCube()
            : TextProperties::TextColor::BaseColorCube()
        {}
        constexpr ColorCube(const std::uint8_t color)
            : TextProperties::TextColor::BaseColorCube(color)
        {}
        constexpr ColorCube(const TextProperties::TextColor::BaseColorCube& color)
            : TextProperties::TextColor::BaseColorCube(color)
        {}

    public:
        static ColorCube MakeNormalColor(const std::uint8_t value) { return static_cast<ColorCube>(TextProperties::TextColor::BaseColorCube::MakeNormalColor(value)); }

        static ColorCube MakeBrightColor(const std::uint8_t value) { return static_cast<ColorCube>(TextProperties::TextColor::BaseColorCube::MakeBrightColor(value)); }

        static ColorCube Make666CubeColor255(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b)
        {
            return static_cast<ColorCube>(TextProperties::TextColor::BaseColorCube::Make666CubeColor255(r, g, b));
        }

        static ColorCube Make666CubeColor5(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b)
        {
            return static_cast<ColorCube>(TextProperties::TextColor::BaseColorCube::Make666CubeColor5(r, g, b));
        }

        static ColorCube MakeGrayscaleColor255(const std::uint8_t value) { return static_cast<ColorCube>(TextProperties::TextColor::BaseColorCube::MakeGrayscaleColor255(value)); }

        static ColorCube MakeGrayscaleColor24(const std::uint8_t value) { return static_cast<ColorCube>(TextProperties::TextColor::BaseColorCube::MakeGrayscaleColor24(value)); }
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
            : color_cube()
        {}

        TextProperties::TextStyle::UnderlineColor::ColorCube color_cube;
        TextProperties::TextStyle::UnderlineColor::Color24b  color24b;
    };

    struct TextProperties::TextStyle::UnderlineColor::Color
    {
        TextProperties::TextStyle::UnderlineColor::ColorData data;
        TextProperties::TextStyle::UnderlineColor::ColorType type = TextProperties::TextStyle::UnderlineColor::ColorType::Default;
    };

    inline bool operator==(const TextProperties::TextStyle::UnderlineColor::Color& lhs, const TextProperties::TextStyle::UnderlineColor::Color& rhs)
    {
        if (lhs.type != rhs.type) return false;
        switch (lhs.type)
        {
            case TextProperties::TextStyle::UnderlineColor::ColorType::Default:
                return true;
            case TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube:
                return lhs.data.color_cube == rhs.data.color_cube;
            case TextProperties::TextStyle::UnderlineColor::ColorType::Color24b:
                return lhs.data.color24b == rhs.data.color24b;
        }
        return false;
    }

    bool operator==(const TextProperties::TextStyle::Style& lhs, const TextProperties::TextStyle::Style& rhs);

    struct TextProperties::TextStyle::Style
    {
    public:
        constexpr Style() {}

        TextProperties::TextStyle::Intensity intensity = TextProperties::TextStyle::Intensity::Normal;
        TextProperties::TextStyle::Italic    italic    = TextProperties::TextStyle::Italic::Disable;
        TextProperties::TextStyle::Blink     blink     = TextProperties::TextStyle::Blink::Disable;
        TextProperties::TextStyle::Inverted  inverted  = TextProperties::TextStyle::Inverted::Disable;
        TextProperties::TextStyle::Ideogram  ideogram  = TextProperties::TextStyle::Ideogram::AllDisable;
        TextProperties::TextStyle::Script    script    = TextProperties::TextStyle::Script::AllDisable;

        TextProperties::TextStyle::Underline             underline = TextProperties::TextStyle::Underline::Disable;
        TextProperties::TextStyle::UnderlineColor::Color underline_color;

    public:
        void modify_reset() { *this = Style{}; }

        void apply(const TextProperties::TextStyle::reset_style&) { modify_reset(); }
        void apply(const TextProperties::TextStyle::Style& given) { *this = given; }
        void apply(const TextProperties::TextStyle::Intensity& given) { intensity = given; }
        void apply(const TextProperties::TextStyle::Italic& given) { italic = given; }
        void apply(const TextProperties::TextStyle::Underline& given) { underline = given; }
        void apply(const TextProperties::TextStyle::Blink& given) { blink = given; }
        void apply(const TextProperties::TextStyle::Inverted& given) { inverted = given; }
        void apply(const TextProperties::TextStyle::Ideogram& given) { ideogram = given; }
        void apply(const TextProperties::TextStyle::Script& given) { script = given; }

        void apply(const TextProperties::TextStyle::UnderlineColor::Color& given) { underline_color = given; }
        void apply(const TextProperties::TextStyle::UnderlineColor::ColorCube& given)
        {
            underline_color.type           = TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube;
            underline_color.data.color_cube = given;
        }
        void apply(const TextProperties::TextStyle::UnderlineColor::Color24b& given)
        {
            underline_color.type          = TextProperties::TextStyle::UnderlineColor::ColorType::Color24b;
            underline_color.data.color24b = given;
        }

    public:
        bool need_modif(const TextProperties::TextStyle::reset_style&) { return true; }
        bool need_modif(const TextProperties::TextStyle::Style& given) { return *this != given; }
        bool need_modif(const TextProperties::TextStyle::Intensity& given) { return intensity != given; }
        bool need_modif(const TextProperties::TextStyle::Italic& given) { return italic != given; }
        bool need_modif(const TextProperties::TextStyle::Underline& given) { return underline != given; }
        bool need_modif(const TextProperties::TextStyle::Blink& given) { return blink != given; }
        bool need_modif(const TextProperties::TextStyle::Inverted& given) { return inverted != given; }
        bool need_modif(const TextProperties::TextStyle::Ideogram& given) { return ideogram != given; }
        bool need_modif(const TextProperties::TextStyle::Script& given) { return script != given; }

        bool need_modif(const TextProperties::TextStyle::UnderlineColor::Color& given) { return underline_color != given; }
        bool need_modif(const TextProperties::TextStyle::UnderlineColor::ColorCube& given)
        {
            return underline_color.type != TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube || underline_color.data.color_cube != given;
        }
        bool need_modif(const TextProperties::TextStyle::UnderlineColor::Color24b& given)
        {
            return underline_color.type != TextProperties::TextStyle::UnderlineColor::ColorType::Color24b || underline_color.data.color24b != given;
        }
    };

    inline bool operator==(const TextProperties::TextStyle::Style& lhs, const TextProperties::TextStyle::Style& rhs)
    {
        return lhs.intensity == rhs.intensity && lhs.italic == rhs.italic && lhs.blink == rhs.blink && lhs.inverted == rhs.inverted && lhs.ideogram == rhs.ideogram &&
               lhs.script == rhs.script && lhs.underline == rhs.underline && lhs.underline_color == rhs.underline_color;
    }

    template <typename T>
    concept text_properties_style_can_apply = requires(const T& value, TextProperties::TextStyle::Style& data)
    {
        data.apply(value);
    };

    template <typename T>
    struct TextPropertiesStyleIsapplyType
    {
        using BaseType              = get_base_type<T>;
        static constexpr bool value = std::is_same_v<BaseType, TextProperties::TextStyle::reset_style> || std::is_same_v<BaseType, TextProperties::TextStyle::Style> ||
                                      std::is_same_v<BaseType, TextProperties::TextStyle::Intensity> || std::is_same_v<BaseType, TextProperties::TextStyle::Italic> ||
                                      std::is_same_v<BaseType, TextProperties::TextStyle::Underline> || std::is_same_v<BaseType, TextProperties::TextStyle::Blink> ||
                                      std::is_same_v<BaseType, TextProperties::TextStyle::Inverted> || std::is_same_v<BaseType, TextProperties::TextStyle::Ideogram> ||
                                      std::is_same_v<BaseType, TextProperties::TextStyle::Script> || std::is_same_v<BaseType, TextProperties::TextStyle::UnderlineColor::Color> ||
                                      std::is_same_v<BaseType, TextProperties::TextStyle::UnderlineColor::ColorCube> ||
                                      std::is_same_v<BaseType, TextProperties::TextStyle::UnderlineColor::Color24b>;
    };

    template <typename T>
    concept TextPropertiesStyleIsapply = TextPropertiesStyleIsapplyType<T>::value;
}

namespace stream::fmt::detail::OLD
{
    enum class BasicStyle : std::uint8_t
    {
        Intensity_Bold   = static_cast<std::uint8_t>(TextProperties::TextStyle::Intensity::Bold),
        Intensity_Dim    = static_cast<std::uint8_t>(TextProperties::TextStyle::Intensity::Dim),
        Intensity_Normal = static_cast<std::uint8_t>(TextProperties::TextStyle::Intensity::Normal),

        Italic_Enable  = static_cast<std::uint8_t>(TextProperties::TextStyle::Italic::Enable),
        Italic_Disable = static_cast<std::uint8_t>(TextProperties::TextStyle::Italic::Disable),

        Underline_Underlined      = static_cast<std::uint8_t>(TextProperties::TextStyle::Underline::Underlined),
        Underline_DoubleUnerlined = static_cast<std::uint8_t>(TextProperties::TextStyle::Underline::DoubleUnerlined),  // may only disable bold
        Underline_Disable         = static_cast<std::uint8_t>(TextProperties::TextStyle::Underline::Disable),
        Underline_SelectColor     = 255,

        Blink_SlowBlink = static_cast<std::uint8_t>(TextProperties::TextStyle::Blink::SlowBlink),
        Blink_FastBlink = static_cast<std::uint8_t>(TextProperties::TextStyle::Blink::FastBlink),
        Blink_Disable   = static_cast<std::uint8_t>(TextProperties::TextStyle::Blink::Disable),

        Inverted_Enable  = static_cast<std::uint8_t>(TextProperties::TextStyle::Inverted::Enable),
        Inverted_Disable = static_cast<std::uint8_t>(TextProperties::TextStyle::Inverted::Disable),

        Ideogram_Underlined       = static_cast<std::uint8_t>(TextProperties::TextStyle::Ideogram::Underlined),
        Ideogram_DoubleUnderlined = static_cast<std::uint8_t>(TextProperties::TextStyle::Ideogram::DoubleUnderlined),
        Ideogram_Overlined        = static_cast<std::uint8_t>(TextProperties::TextStyle::Ideogram::Overlined),
        Ideogram_DoubleOverlined  = static_cast<std::uint8_t>(TextProperties::TextStyle::Ideogram::DoubleOverlined),
        Ideogram_StressMarking    = static_cast<std::uint8_t>(TextProperties::TextStyle::Ideogram::StressMarking),
        Ideogram_AllDisable       = static_cast<std::uint8_t>(TextProperties::TextStyle::Ideogram::AllDisable),

        Script_Superscript = static_cast<std::uint8_t>(TextProperties::TextStyle::Script::Superscript),
        Script_Subscript   = static_cast<std::uint8_t>(TextProperties::TextStyle::Script::Subscript),
        Script_AllDisable  = static_cast<std::uint8_t>(TextProperties::TextStyle::Script::AllDisable)
    };
}
