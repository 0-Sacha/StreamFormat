#include "text_properties_manager.h"

namespace stream::fmt::detail
{
    [[nodiscard]] std::expected<void, FMTResult> TextPropertiesApplyManager::ReloadColorFG(const TextProperties::TextColor::ColorFG& target)
    {
        if (target.Type != m_CurrentContextProperties.color.Fg.Type)
        {
            switch (target.Type)
            {
                case TextProperties::TextColor::ColorType::BasicColor:
                    return ApplyColor(target.Data.BasicColor);
                case TextProperties::TextColor::ColorType::ColorCube:
                    return ApplyColor(target.Data.ColorCube);
                case TextProperties::TextColor::ColorType::Color24b:
                    return ApplyColor(target.Data.Color24b);
            }
        }
        else
        {
            switch (target.Type)
            {
                case TextProperties::TextColor::ColorType::BasicColor:
                    if (m_CurrentContextProperties.color.Fg.Data.BasicColor != target.Data.BasicColor)
                        return ApplyColor(target.Data.BasicColor);
                    break;
                case TextProperties::TextColor::ColorType::ColorCube:
                    if (m_CurrentContextProperties.color.Fg.Data.ColorCube != target.Data.ColorCube)
                        return ApplyColor(target.Data.ColorCube);
                    break;
                case TextProperties::TextColor::ColorType::Color24b:
                    if (m_CurrentContextProperties.color.Fg.Data.Color24b != target.Data.Color24b)
                        return ApplyColor(target.Data.Color24b);
                    break;
            }
        }
        return {};
    }

    [[nodiscard]] std::expected<void, FMTResult> TextPropertiesApplyManager::ReloadColorBG(const TextProperties::TextColor::ColorBG& target)
    {
        if (target.Type != m_CurrentContextProperties.color.Bg.Type)
        {
            switch (target.Type)
            {
                case TextProperties::TextColor::ColorType::BasicColor:
                    return ApplyColor(target.Data.BasicColor);
                case TextProperties::TextColor::ColorType::ColorCube:
                    return ApplyColor(target.Data.ColorCube);
                case TextProperties::TextColor::ColorType::Color24b:
                    return ApplyColor(target.Data.Color24b);
            }
        }
        else
        {
            switch (target.Type)
            {
                case TextProperties::TextColor::ColorType::BasicColor:
                    if (m_CurrentContextProperties.color.Bg.Data.BasicColor != target.Data.BasicColor)
                        return ApplyColor(target.Data.BasicColor);
                    break;
                case TextProperties::TextColor::ColorType::ColorCube:
                    if (m_CurrentContextProperties.color.Bg.Data.ColorCube != target.Data.ColorCube)
                        return ApplyColor(target.Data.ColorCube);
                    break;
                case TextProperties::TextColor::ColorType::Color24b:
                    if (m_CurrentContextProperties.color.Bg.Data.Color24b != target.Data.Color24b)
                        return ApplyColor(target.Data.Color24b);
                    break;
            }
        }
        return {};
    }

    [[nodiscard]] std::expected<void, FMTResult> TextPropertiesApplyManager::ReloadStyle(const TextProperties::TextStyle::Style& target)
    {
        if (target.Intensity != m_CurrentContextProperties.style.Intensity)
        {
            SF_TRY(ApplyStyle(target.Intensity));
            m_CurrentContextProperties.style.Intensity = target.Intensity;
        }
        if (target.Italic != m_CurrentContextProperties.style.Italic)
        {
            SF_TRY(ApplyStyle(target.Italic));
            m_CurrentContextProperties.style.Italic = target.Italic;
        }
        if (target.Blink != m_CurrentContextProperties.style.Blink)
        {
            SF_TRY(ApplyStyle(target.Blink));
            m_CurrentContextProperties.style.Blink = target.Blink;
        }
        if (target.Inverted != m_CurrentContextProperties.style.Inverted)
        {
            SF_TRY(ApplyStyle(target.Inverted));
            m_CurrentContextProperties.style.Inverted = target.Inverted;
        }
        if (target.Ideogram != m_CurrentContextProperties.style.Ideogram)
        {
            SF_TRY(ApplyStyle(target.Ideogram));
            m_CurrentContextProperties.style.Ideogram = target.Ideogram;
        }
        if (target.Script != m_CurrentContextProperties.style.Script)
        {
            SF_TRY(ApplyStyle(target.Script));
            m_CurrentContextProperties.style.Script = target.Script;
        }

        if (target.Underline != m_CurrentContextProperties.style.Underline)
        {
            SF_TRY(ApplyStyle(target.Underline));
            m_CurrentContextProperties.style.Underline = target.Underline;
        }

        if (target.UnderlineColor.Type != m_CurrentContextProperties.style.UnderlineColor.Type)
        {
            switch (target.UnderlineColor.Type)
            {
                case TextProperties::TextStyle::UnderlineColor::ColorType::Default:
                    SF_TRY(ApplyStyle(TextProperties::TextStyle::UnderlineColor::ColorCube{TextProperties::TextStyle::UnderlineColor::ColorCube::Default}));
                    break;
                case TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube:
                    SF_TRY(ApplyStyle(target.UnderlineColor.Data.ColorCube));
                    m_CurrentContextProperties.style.UnderlineColor.Data.ColorCube = target.UnderlineColor.Data.ColorCube;
                    break;
                case TextProperties::TextStyle::UnderlineColor::ColorType::Color24b:
                    SF_TRY(ApplyStyle(target.UnderlineColor.Data.Color24b));
                    m_CurrentContextProperties.style.UnderlineColor.Data.Color24b = target.UnderlineColor.Data.Color24b;
                    break;
            }
            m_CurrentContextProperties.style.UnderlineColor.Type = target.UnderlineColor.Type;
        }
        else
        {
            switch (target.UnderlineColor.Type)
            {
                case TextProperties::TextStyle::UnderlineColor::ColorType::Default:
                    break;
                case TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube:
                    if (m_CurrentContextProperties.style.UnderlineColor.Data.ColorCube != target.UnderlineColor.Data.ColorCube)
                    {
                        SF_TRY(ApplyStyle(target.UnderlineColor.Data.ColorCube));
                        m_CurrentContextProperties.style.UnderlineColor.Data.ColorCube = target.UnderlineColor.Data.ColorCube;
                    }
                    break;
                case TextProperties::TextStyle::UnderlineColor::ColorType::Color24b:
                    if (m_CurrentContextProperties.style.UnderlineColor.Data.Color24b != target.UnderlineColor.Data.Color24b)
                    {
                        SF_TRY(ApplyStyle(target.UnderlineColor.Data.Color24b));
                        m_CurrentContextProperties.style.UnderlineColor.Data.Color24b = target.UnderlineColor.Data.Color24b;
                    }
                    break;
            }
        }
        return {};
    }

    [[nodiscard]] std::expected<void, FMTResult> TextPropertiesApplyManager::ReloadFront(const TextProperties::TextFront::Front& target)
    {
        if (m_CurrentContextProperties.front == target)
            return {};

        SF_TRY(ApplyFront(target.CurrentID));
        m_CurrentContextProperties.front = target;
        return {};
    }
}
