#pragma once

#include "ParserTextPropertiesExecutor.h"

namespace ProjectCore::FMT::Detail
{
    template <typename ParserContext>
    class ParserANSITextPropertiesExecutor : public IParserTextPropertiesExecutor<ParserContext>
    {
    public:
        ~ParserANSITextPropertiesExecutor() override = default;

    public:
        using Base = IParserTextPropertiesExecutor<ParserContext>;
        using Base::SetBuffer;

    protected:
        using Base::m_Buffer;

    public:
        void AllPropertiesReset() override
        { /*m_Buffer->BasicWriteType('\033', '[', 0, 'm');*/
        }

    public:
        void ResetColor() override
        { /*m_Buffer->BasicWriteType('\033', '[', 39, ';', 49, 'm');*/
        }
        void ExecuteColor(const TextProperties::TextColor::BasicColorFG&) override
        { /*m_Buffer->BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteColor(const TextProperties::TextColor::BasicColorBG&) override
        { /*m_Buffer->BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteColor(const TextProperties::TextColor::BasicColor&) override
        { /*m_Buffer->BasicWriteType('\033', '[', static_cast<std::uint8_t>(t.Fg) , ';', static_cast<std::uint8_t>(t.Bg), 'm');*/
        }
        void ExecuteColor(const TextProperties::TextColor::Color24bFG&) override
        { /*m_Buffer->BasicWriteType("\033[38;2;", t.R, ';', t.G, ';', t.B, 'm');*/
        }
        void ExecuteColor(const TextProperties::TextColor::Color24bBG&) override
        { /*m_Buffer->BasicWriteType("\033[48;2;", t.R, ';', t.G, ';', t.B, 'm');*/
        }
        void ExecuteColor(const TextProperties::TextColor::Color24b&) override
        { /*m_Buffer->BasicWriteType("\033[38;2;", t.Fg.R, ';', t.Fg.G, ';', t.Fg.B, "; 48; 2;", t.Bg.R, ';', t.Bg.G, ';', t.Bg.B, 'm');*/
        }
        void ExecuteColor(const TextProperties::TextColor::ColorCubeFG&) override
        { /*m_Buffer->BasicWriteType("\033[38;5;", t.GetColorRef(), 'm');*/
        }
        void ExecuteColor(const TextProperties::TextColor::ColorCubeBG&) override
        { /*m_Buffer->BasicWriteType("\033[48;5;", t.GetColorRef(), 'm');*/
        }
        void ExecuteColor(const TextProperties::TextColor::ColorCube&) override
        { /*m_Buffer->BasicWriteType("\033[48;5;", t.Fg.GetColorRef(), ";48;5;", t.Bg.GetColorRef(), 'm');*/
        }

    public:
        void ResetFront() override
        { /*m_Buffer->BasicWriteType('\033', '[', TextProperties::TextFront::FrontID::DefaultFrontID, 'm');*/
        }
        void ExecuteFront(const TextProperties::TextFront::FrontID&) override
        { /*m_Buffer->BasicWriteType('\033', '[', t.ID, 'm');*/
        }

    public:
        void ResetStyle() override
        { /*m_Buffer->BasicWriteType('\033', '[', 0, 'm');*/
        }
        void ExecuteStyle(const TextProperties::TextStyle::Intensity&) override
        { /*m_Buffer->BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteStyle(const TextProperties::TextStyle::Italic&) override
        { /*m_Buffer->BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteStyle(const TextProperties::TextStyle::Underline&) override
        { /*m_Buffer->BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::Color&) override
        { /*m_Buffer->BasicWriteType("\033[59m");*/
        }
        void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::ColorCube&) override
        { /*m_Buffer->BasicWriteType("\033[58;5;", t.GetColorRef(), 'm');*/
        }
        void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::Color24b&) override
        { /*m_Buffer->BasicWriteType("\033[58;2;", t.R, ';', t.G, ';', t.B, 'm');*/
        }
        void ExecuteStyle(const TextProperties::TextStyle::Blink&) override
        { /*m_Buffer->BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteStyle(const TextProperties::TextStyle::Inverted&) override
        { /*m_Buffer->BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteStyle(const TextProperties::TextStyle::Ideogram&) override
        { /*m_Buffer->BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void ExecuteStyle(const TextProperties::TextStyle::Script&) override
        { /*m_Buffer->BasicWriteType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
    };
}
