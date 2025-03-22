#pragma once

#include "FormatterTextPropertiesExecutor.h"
#include "stream/fmt/detail/IndentHandlers.h"

namespace stream::fmt::detail
{
    template <typename TChar>
    class FormatterANSITextPropertiesExecutor final : public IFormatterTextPropertiesExecutor<TChar>
    {
    public:
        FormatterANSITextPropertiesExecutor() = default;
        ~FormatterANSITextPropertiesExecutor() override = default;

        using IFormatterTextPropertiesExecutor<TChar>::Buffer;

    public:
        [[nodiscard]] std::expected<void, FMTResult> all_properties_reset() override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).FastWriteStringLitteral("\033[0m");
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> reset_color() override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).FastWriteStringLitteral("\033[39;49m");
        }
        
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const TextProperties::TextColor::BasicColorFG& t)
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const TextProperties::TextColor::BasicColorBG& t)
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::BasicColor& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t.Fg), ";", static_cast<std::uint8_t>(t.Bg), "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::Color24bFG& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[38;2;", t.R, ";", t.G, ";", t.B, "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::Color24bBG& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[48;2;", t.R, ";", t.G, ";", t.B, "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::Color24b& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[38;2;", t.Fg.R, ";", t.Fg.G, ";", t.Fg.B, "; 48; 2;", t.Bg.R, ";", t.Bg.G, ";", t.Bg.B, "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::ColorCubeFG& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[38;5;", t.GetColorRef(), "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::ColorCubeBG& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[48;5;", t.GetColorRef(), "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::ColorCube& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[48;5;", t.Fg.GetColorRef(), ";48;5;", t.Bg.GetColorRef(), "m");
        }
    public:
        [[nodiscard]] std::expected<void, FMTResult> reset_front() override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[", detail::TextProperties::TextFront::FrontID::DefaultFrontID, "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteFront(const detail::TextProperties::TextFront::FrontID& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[", t.ID, "m");
        }
    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetStyle() override
        {
            // TODO
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).FastWriteStringLitteral("\033[0m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Intensity& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Italic& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Underline& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color&) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[59m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::UnderlineColor::ColorCube& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[58;5;", t.GetColorRef(), "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color24b& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[58;2;", t.R, ";", t.G, ";", t.B, "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Blink& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Inverted& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Ideogram& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Script& t) override
        {
            NoStrideFunction noStride(*Buffer);
            return BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
    };
}
