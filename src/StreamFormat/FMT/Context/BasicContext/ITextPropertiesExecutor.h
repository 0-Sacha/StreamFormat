#pragma once

#include "StreamFormat/FMT/Detail/Prelude.h"
#include "StreamFormat/FMT/TextProperties/TextProperties.h"

namespace StreamFormat::FMT::Detail
{
    class ITextPropertiesExecutor
    {
    public:
        virtual ~ITextPropertiesExecutor() = default;

    public:
        virtual void LinkToExecutor(void* executor) = 0;

    public:
        [[nodiscard]] virtual std::expected<void, FMTResult> AllPropertiesReset() = 0;

    public:
        [[nodiscard]] virtual std::expected<void, FMTResult> ResetColor()                                                   = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteColor(const TextProperties::TextColor::BasicColorFG& t) = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteColor(const TextProperties::TextColor::BasicColorBG& t) = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteColor(const TextProperties::TextColor::BasicColor& t)   = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteColor(const TextProperties::TextColor::Color24bFG& t)   = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteColor(const TextProperties::TextColor::Color24bBG& t)   = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteColor(const TextProperties::TextColor::Color24b& t)     = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteColor(const TextProperties::TextColor::ColorCubeFG& t)  = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteColor(const TextProperties::TextColor::ColorCubeBG& t)  = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteColor(const TextProperties::TextColor::ColorCube& t)    = 0;

    public:
        [[nodiscard]] virtual std::expected<void, FMTResult> ResetFront()                                              = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteFront(const TextProperties::TextFront::FrontID& t) = 0;

    public:
        [[nodiscard]] virtual std::expected<void, FMTResult> ResetStyle()                                                                = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteStyle(const TextProperties::TextStyle::Intensity& t)                 = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteStyle(const TextProperties::TextStyle::Italic& t)                    = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteStyle(const TextProperties::TextStyle::Underline& t)                 = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::Color& t)     = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::ColorCube& t) = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::Color24b& t)  = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteStyle(const TextProperties::TextStyle::Blink& t)                     = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteStyle(const TextProperties::TextStyle::Inverted& t)                  = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteStyle(const TextProperties::TextStyle::Ideogram& t)                  = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecuteStyle(const TextProperties::TextStyle::Script& t)                    = 0;
    };
}
