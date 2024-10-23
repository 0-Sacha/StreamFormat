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
        void AllPropertiesReset() override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', 0, 'm');*/
        }

    public:
        void ResetColor() override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', 39, ';', 49, 'm');*/
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::BasicColorFG&) override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::BasicColorBG&) override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::BasicColor&) override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t.Fg) , ';', static_cast<std::uint8_t>(t.Bg), 'm');*/
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::Color24bFG&) override
        {
            /*BufferReadManip(Buffer).BasicReadType("\033[38;2;", t.R, ';', t.G, ';', t.B, 'm');*/
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::Color24bBG&) override
        {
            /*BufferReadManip(Buffer).BasicReadType("\033[48;2;", t.R, ';', t.G, ';', t.B, 'm');*/
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::Color24b&) override
        {
            /*BufferReadManip(Buffer).BasicReadType("\033[38;2;", t.Fg.R, ';', t.Fg.G, ';', t.Fg.B, "; 48; 2;", t.Bg.R, ';', t.Bg.G, ';', t.Bg.B, 'm');*/
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::ColorCubeFG&) override
        {
            /*BufferReadManip(Buffer).BasicReadType("\033[38;5;", t.GetColorRef(), 'm');*/
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::ColorCubeBG&) override
        {
            /*BufferReadManip(Buffer).BasicReadType("\033[48;5;", t.GetColorRef(), 'm');*/
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::ColorCube&) override
        {
            /*BufferReadManip(Buffer).BasicReadType("\033[48;5;", t.Fg.GetColorRef(), ";48;5;", t.Bg.GetColorRef(), 'm');*/
        }

    public:
        void ResetFront() override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', Detail::TextProperties::TextFront::FrontID::DefaultFrontID, 'm');*/
        }
        void ExecuteFront(const Detail::TextProperties::TextFront::FrontID&) override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', t.ID, 'm');*/
        }

    public:
        void ResetStyle() override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', 0, 'm');*/
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Intensity&) override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Italic&) override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Underline&) override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::Color&) override
        {
            /*BufferReadManip(Buffer).BasicReadType("\033[59m");*/
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::ColorCube&) override
        {
            /*BufferReadManip(Buffer).BasicReadType("\033[58;5;", t.GetColorRef(), 'm');*/
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::Color24b&) override
        {
            /*BufferReadManip(Buffer).BasicReadType("\033[58;2;", t.R, ';', t.G, ';', t.B, 'm');*/
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Blink&) override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Inverted&) override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Ideogram&) override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Script&) override
        {
            /*BufferReadManip(Buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
    };
}
