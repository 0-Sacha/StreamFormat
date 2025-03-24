#pragma once

#include "stream/fmt/detail/prelude.hxx"
#include "stream/fmt/text_properties/text_properties.hxx"

namespace stream::fmt::detail {
    class ITextPropertiesExecutor {
    public:
        virtual ~ITextPropertiesExecutor() = default;

    public:
        virtual void link_to_executor(void* executor) = 0;

    public:
        virtual void all_properties_reset() = 0;

    public:
        virtual void reset_color()                                                   = 0;
        virtual void execute_color(const TextProperties::TextColor::BasicColorFG& t) = 0;
        virtual void execute_color(const TextProperties::TextColor::BasicColorBG& t) = 0;
        virtual void execute_color(const TextProperties::TextColor::BasicColor& t)   = 0;
        virtual void execute_color(const TextProperties::TextColor::Color24bFG& t)   = 0;
        virtual void execute_color(const TextProperties::TextColor::Color24bBG& t)   = 0;
        virtual void execute_color(const TextProperties::TextColor::Color24b& t)     = 0;
        virtual void execute_color(const TextProperties::TextColor::ColorCubeFG& t)  = 0;
        virtual void execute_color(const TextProperties::TextColor::ColorCubeBG& t)  = 0;
        virtual void execute_color(const TextProperties::TextColor::ColorCube& t)    = 0;

    public:
        virtual void reset_front()                                              = 0;
        virtual void execute_front(const TextProperties::TextFront::FrontID& t) = 0;

    public:
        virtual void reset_style()                                                                = 0;
        virtual void execute_style(const TextProperties::TextStyle::Intensity& t)                 = 0;
        virtual void execute_style(const TextProperties::TextStyle::Italic& t)                    = 0;
        virtual void execute_style(const TextProperties::TextStyle::Underline& t)                 = 0;
        virtual void execute_style(const TextProperties::TextStyle::UnderlineColor::Color& t)     = 0;
        virtual void execute_style(const TextProperties::TextStyle::UnderlineColor::ColorCube& t) = 0;
        virtual void execute_style(const TextProperties::TextStyle::UnderlineColor::Color24b& t)  = 0;
        virtual void execute_style(const TextProperties::TextStyle::Blink& t)                     = 0;
        virtual void execute_style(const TextProperties::TextStyle::Inverted& t)                  = 0;
        virtual void execute_style(const TextProperties::TextStyle::Ideogram& t)                  = 0;
        virtual void execute_style(const TextProperties::TextStyle::Script& t)                    = 0;
    };
}  // namespace stream::fmt::detail
