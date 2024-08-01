#include "TextPropertiesManager.h"

namespace StreamFormat::FMT::Detail
{
    void TextPropertiesApplyManager::ReloadColorFG(const TextProperties::TextColor::ColorFG& target)
    {
        if (target.Type != m_CurrentContextProperties.Color.Fg.Type)
        {
            switch (target.Type)
            {
                case TextProperties::TextColor::ColorType::BasicColor:
                    ApplyColor(target.Data.BasicColor);
                    break;
                case TextProperties::TextColor::ColorType::ColorCube:
                    ApplyColor(target.Data.ColorCube);
                    break;
                case TextProperties::TextColor::ColorType::Color24b:
                    ApplyColor(target.Data.Color24b);
                    break;
            }
        }
        else
        {
            switch (target.Type)
            {
                case TextProperties::TextColor::ColorType::BasicColor:
                    if (m_CurrentContextProperties.Color.Fg.Data.BasicColor != target.Data.BasicColor) ApplyColor(target.Data.BasicColor);
                    break;
                case TextProperties::TextColor::ColorType::ColorCube:
                    if (m_CurrentContextProperties.Color.Fg.Data.ColorCube != target.Data.ColorCube) ApplyColor(target.Data.ColorCube);
                    break;
                case TextProperties::TextColor::ColorType::Color24b:
                    if (m_CurrentContextProperties.Color.Fg.Data.Color24b != target.Data.Color24b) ApplyColor(target.Data.Color24b);
                    break;
            }
        }
    }

    void TextPropertiesApplyManager::ReloadColorBG(const TextProperties::TextColor::ColorBG& target)
    {
        if (target.Type != m_CurrentContextProperties.Color.Bg.Type)
        {
            switch (target.Type)
            {
                case TextProperties::TextColor::ColorType::BasicColor:
                    ApplyColor(target.Data.BasicColor);
                    break;
                case TextProperties::TextColor::ColorType::ColorCube:
                    ApplyColor(target.Data.ColorCube);
                    break;
                case TextProperties::TextColor::ColorType::Color24b:
                    ApplyColor(target.Data.Color24b);
                    break;
            }
        }
        else
        {
            switch (target.Type)
            {
                case TextProperties::TextColor::ColorType::BasicColor:
                    if (m_CurrentContextProperties.Color.Bg.Data.BasicColor != target.Data.BasicColor) ApplyColor(target.Data.BasicColor);
                    break;
                case TextProperties::TextColor::ColorType::ColorCube:
                    if (m_CurrentContextProperties.Color.Bg.Data.ColorCube != target.Data.ColorCube) ApplyColor(target.Data.ColorCube);
                    break;
                case TextProperties::TextColor::ColorType::Color24b:
                    if (m_CurrentContextProperties.Color.Bg.Data.Color24b != target.Data.Color24b) ApplyColor(target.Data.Color24b);
                    break;
            }
        }
    }

    void TextPropertiesApplyManager::ReloadStyle(const TextProperties::TextStyle::Style& target)
    {
        if (target.Intensity != m_CurrentContextProperties.Style.Intensity)
        {
            ApplyStyle(target.Intensity);
            m_CurrentContextProperties.Style.Intensity = target.Intensity;
        }
        if (target.Italic != m_CurrentContextProperties.Style.Italic)
        {
            ApplyStyle(target.Italic);
            m_CurrentContextProperties.Style.Italic = target.Italic;
        }
        if (target.Blink != m_CurrentContextProperties.Style.Blink)
        {
            ApplyStyle(target.Blink);
            m_CurrentContextProperties.Style.Blink = target.Blink;
        }
        if (target.Inverted != m_CurrentContextProperties.Style.Inverted)
        {
            ApplyStyle(target.Inverted);
            m_CurrentContextProperties.Style.Inverted = target.Inverted;
        }
        if (target.Ideogram != m_CurrentContextProperties.Style.Ideogram)
        {
            ApplyStyle(target.Ideogram);
            m_CurrentContextProperties.Style.Ideogram = target.Ideogram;
        }
        if (target.Script != m_CurrentContextProperties.Style.Script)
        {
            ApplyStyle(target.Script);
            m_CurrentContextProperties.Style.Script = target.Script;
        }

        if (target.Underline != m_CurrentContextProperties.Style.Underline)
        {
            ApplyStyle(target.Underline);
            m_CurrentContextProperties.Style.Underline = target.Underline;
        }

        if (target.UnderlineColor.Type != m_CurrentContextProperties.Style.UnderlineColor.Type)
        {
            switch (target.UnderlineColor.Type)
            {
                case TextProperties::TextStyle::UnderlineColor::ColorType::Default:
                    ApplyStyle(TextProperties::TextStyle::UnderlineColor::ColorCube{TextProperties::TextStyle::UnderlineColor::ColorCube::Default});
                    break;
                case TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube:
                    ApplyStyle(target.UnderlineColor.Data.ColorCube);
                    m_CurrentContextProperties.Style.UnderlineColor.Data.ColorCube = target.UnderlineColor.Data.ColorCube;
                    break;
                case TextProperties::TextStyle::UnderlineColor::ColorType::Color24b:
                    ApplyStyle(target.UnderlineColor.Data.Color24b);
                    m_CurrentContextProperties.Style.UnderlineColor.Data.Color24b = target.UnderlineColor.Data.Color24b;
                    break;
            }
            m_CurrentContextProperties.Style.UnderlineColor.Type = target.UnderlineColor.Type;
        }
        else
        {
            switch (target.UnderlineColor.Type)
            {
                case TextProperties::TextStyle::UnderlineColor::ColorType::Default:
                    break;
                case TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube:
                    if (m_CurrentContextProperties.Style.UnderlineColor.Data.ColorCube != target.UnderlineColor.Data.ColorCube)
                    {
                        ApplyStyle(target.UnderlineColor.Data.ColorCube);
                        m_CurrentContextProperties.Style.UnderlineColor.Data.ColorCube = target.UnderlineColor.Data.ColorCube;
                    }
                    break;
                case TextProperties::TextStyle::UnderlineColor::ColorType::Color24b:
                    if (m_CurrentContextProperties.Style.UnderlineColor.Data.Color24b != target.UnderlineColor.Data.Color24b)
                    {
                        ApplyStyle(target.UnderlineColor.Data.Color24b);
                        m_CurrentContextProperties.Style.UnderlineColor.Data.Color24b = target.UnderlineColor.Data.Color24b;
                    }
                    break;
            }
        }
    }

    void TextPropertiesApplyManager::ReloadFront(const TextProperties::TextFront::Front& target)
    {
        if (m_CurrentContextProperties.Front == target) return;

        ApplyFront(target.CurrentID);
        m_CurrentContextProperties.Front = target;
    }
}
