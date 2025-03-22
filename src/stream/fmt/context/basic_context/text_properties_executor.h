#pragma once

#include "stream/fmt/detail/prelude.h"
#include "stream/fmt/text_properties/text_properties.h"

namespace stream::fmt::detail
{
    class ITextPropertiesExecutor
    {
    public:
        virtual ~ITextPropertiesExecutor() = default;

    public:
        virtual void link_to_executor(void* executor) = 0;

    public:
        [[nodiscard]] virtual std::expected<void, FMTResult> all_properties_reset() = 0;

    public:
        [[nodiscard]] virtual std::expected<void, FMTResult> reset_color()                                                   = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_color(const TextProperties::TextColor::BasicColorFG& t) = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_color(const TextProperties::TextColor::BasicColorBG& t) = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_color(const TextProperties::TextColor::BasicColor& t)   = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_color(const TextProperties::TextColor::Color24bFG& t)   = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_color(const TextProperties::TextColor::Color24bBG& t)   = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_color(const TextProperties::TextColor::Color24b& t)     = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_color(const TextProperties::TextColor::ColorCubeFG& t)  = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_color(const TextProperties::TextColor::ColorCubeBG& t)  = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_color(const TextProperties::TextColor::ColorCube& t)    = 0;

    public:
        [[nodiscard]] virtual std::expected<void, FMTResult> reset_front()                                              = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteFront(const TextProperties::TextFront::FrontID& t) = 0;

    public:
        [[nodiscard]] virtual std::expected<void, FMTResult> ResetStyle()                                                                = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_style(const TextProperties::TextStyle::Intensity& t)                 = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_style(const TextProperties::TextStyle::Italic& t)                    = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_style(const TextProperties::TextStyle::Underline& t)                 = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_style(const TextProperties::TextStyle::UnderlineColor::Color& t)     = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_style(const TextProperties::TextStyle::UnderlineColor::ColorCube& t) = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_style(const TextProperties::TextStyle::UnderlineColor::Color24b& t)  = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_style(const TextProperties::TextStyle::Blink& t)                     = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_style(const TextProperties::TextStyle::Inverted& t)                  = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_style(const TextProperties::TextStyle::Ideogram& t)                  = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> execute_style(const TextProperties::TextStyle::Script& t)                    = 0;
    };
}
