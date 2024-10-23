#pragma once

#include "FormatterTextPropertiesExecutor.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class FormatterANSITextPropertiesExecutor final : public IFormatterTextPropertiesExecutor<TChar>
    {
    public:
        FormatterANSITextPropertiesExecutor() = default;
        ~FormatterANSITextPropertiesExecutor() override = default;

        using IFormatterTextPropertiesExecutor<TChar>::Buffer;

    public:
        void AllPropertiesReset() override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).FastWriteStringLitteral("\033[0m");
        }

    public:
        void ResetColor() override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).FastWriteStringLitteral("\033[39;49m");
        }
        
        void ExecuteColor(const TextProperties::TextColor::BasicColorFG& t)
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void ExecuteColor(const TextProperties::TextColor::BasicColorBG& t)
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::BasicColor& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t.Fg), ";", static_cast<std::uint8_t>(t.Bg), "m");
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::Color24bFG& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[38;2;", t.R, ";", t.G, ";", t.B, "m");
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::Color24bBG& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[48;2;", t.R, ";", t.G, ";", t.B, "m");
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::Color24b& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[38;2;", t.Fg.R, ";", t.Fg.G, ";", t.Fg.B, "; 48; 2;", t.Bg.R, ";", t.Bg.G, ";", t.Bg.B, "m");
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::ColorCubeFG& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[38;5;", t.GetColorRef(), "m");
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::ColorCubeBG& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[48;5;", t.GetColorRef(), "m");
        }
        void ExecuteColor(const Detail::TextProperties::TextColor::ColorCube& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[48;5;", t.Fg.GetColorRef(), ";48;5;", t.Bg.GetColorRef(), "m");
        }
    public:
        void ResetFront() override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[", Detail::TextProperties::TextFront::FrontID::DefaultFrontID, "m");
        }
        void ExecuteFront(const Detail::TextProperties::TextFront::FrontID& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[", t.ID, "m");
        }
    public:
        void ResetStyle() override
        {
            // TODO
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).FastWriteStringLitteral("\033[0m");
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Intensity& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Italic& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Underline& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::Color&) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[59m");
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::ColorCube& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[58;5;", t.GetColorRef(), "m");
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::Color24b& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[58;2;", t.R, ";", t.G, ";", t.B, "m");
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Blink& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Inverted& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Ideogram& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Script& t) override
        {
            NoStrideFunction noStride(*Buffer);
            BufferWriteManip(*Buffer).BasicWriteType("\033[", static_cast<std::uint8_t>(t), "m");
        }
    };
}
