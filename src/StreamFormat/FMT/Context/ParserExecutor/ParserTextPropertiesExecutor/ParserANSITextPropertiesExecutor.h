#pragma once

#include "ParserTextPropertiesExecutor.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class ParserANSITextPropertiesExecutor : public IParserTextPropertiesExecutor<TChar>
    {
    public:
        ParserANSITextPropertiesExecutor() = default;
        ~ParserANSITextPropertiesExecutor() override = default;
        
        using IParserTextPropertiesExecutor<TChar>::Buffer;

    public:
        [[nodiscard]] std::expected<void, FMTResult> AllPropertiesReset() override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', 0, 'm');*/
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetColor() override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', 39, ';', 49, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::BasicColorFG&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::BasicColorBG&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::BasicColor&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t.Fg) , ';', static_cast<std::uint8_t>(t.Bg), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::Color24bFG&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType("\033[38;2;", t.R, ';', t.G, ';', t.B, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::Color24bBG&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType("\033[48;2;", t.R, ';', t.G, ';', t.B, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::Color24b&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType("\033[38;2;", t.Fg.R, ';', t.Fg.G, ';', t.Fg.B, "; 48; 2;", t.Bg.R, ';', t.Bg.G, ';', t.Bg.B, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::ColorCubeFG&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType("\033[38;5;", t.GetColorRef(), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::ColorCubeBG&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType("\033[48;5;", t.GetColorRef(), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::ColorCube&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType("\033[48;5;", t.Fg.GetColorRef(), ";48;5;", t.Bg.GetColorRef(), 'm');*/
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetFront() override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', Detail::TextProperties::TextFront::FrontID::DefaultFrontID, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteFront(const Detail::TextProperties::TextFront::FrontID&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', t.ID, 'm');*/
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetStyle() override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', 0, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Intensity&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Italic&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Underline&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::Color&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType("\033[59m");*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::ColorCube&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType("\033[58;5;", t.GetColorRef(), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::Color24b&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType("\033[58;2;", t.R, ';', t.G, ';', t.B, 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Blink&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Inverted&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Ideogram&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Script&) override
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
    };
}
