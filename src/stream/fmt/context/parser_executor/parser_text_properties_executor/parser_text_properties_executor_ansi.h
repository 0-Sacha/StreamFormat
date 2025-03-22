#pragma once

#include "ParserTextPropertiesExecutor.h"

namespace stream::fmt::detail
{
    template <typename TChar>
    class ParserANSITextPropertiesExecutor : public IParserTextPropertiesExecutor<TChar>
    {
    public:
        ParserANSITextPropertiesExecutor() = default;
        ~ParserANSITextPropertiesExecutor() override = default;
        
        using IParserTextPropertiesExecutor<TChar>::Buffer;

    public:
        [[nodiscard]] std::expected<void, FMTResult> all_properties_reset() override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', 0, 'm');*/
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> reset_color() override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', 39, ';', 49, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::BasicColorFG&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::BasicColorBG&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::BasicColor&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t.Fg) , ';', static_cast<std::uint8_t>(t.Bg), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::Color24bFG&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType("\033[38;2;", t.R, ';', t.G, ';', t.B, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::Color24bBG&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType("\033[48;2;", t.R, ';', t.G, ';', t.B, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::Color24b&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType("\033[38;2;", t.Fg.R, ';', t.Fg.G, ';', t.Fg.B, "; 48; 2;", t.Bg.R, ';', t.Bg.G, ';', t.Bg.B, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::ColorCubeFG&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType("\033[38;5;", t.GetColorRef(), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::ColorCubeBG&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType("\033[48;5;", t.GetColorRef(), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::ColorCube&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType("\033[48;5;", t.Fg.GetColorRef(), ";48;5;", t.Bg.GetColorRef(), 'm');*/
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> reset_front() override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', detail::TextProperties::TextFront::FrontID::DefaultFrontID, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteFront(const detail::TextProperties::TextFront::FrontID&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', t.ID, 'm');*/
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetStyle() override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', 0, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Intensity&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Italic&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Underline&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType("\033[59m");*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::UnderlineColor::ColorCube&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType("\033[58;5;", t.GetColorRef(), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color24b&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType("\033[58;2;", t.R, ';', t.G, ';', t.B, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Blink&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Inverted&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Ideogram&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Script&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
    };
}
