#pragma once

#include "TextPropertiesManager.h"

namespace ProjectCore::FMT::Detail
{
    template <typename BasicContext>
    void TextPropertiesManager<BasicContext>::ApplyColorOnIndex(const FormatIndex& index)
    {
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::Color>(          index, [this](const TextProperties::TextColor::Color& data)                 { this->ReloadColor(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::BasicColorFG>(   index, [this](const TextProperties::TextColor::BasicColorFG& data)          { this->AskApplyColor(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::BasicColorBG>(   index, [this](const TextProperties::TextColor::BasicColorBG& data)          { this->AskApplyColor(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::ColorCubeFG>(    index, [this](const Detail::TextProperties::TextColor::ColorCubeFG& data)   { this->AskApplyColor(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::ColorCubeBG>(    index, [this](const Detail::TextProperties::TextColor::ColorCubeBG& data)   { this->AskApplyColor(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::Color24bFG>(     index, [this](const Detail::TextProperties::TextColor::Color24bFG& data)    { this->AskApplyColor(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextColor::Color24bBG>(     index, [this](const Detail::TextProperties::TextColor::Color24bBG& data)    { this->AskApplyColor(data); } );
    }

    template <typename BasicContext>
    void TextPropertiesManager<BasicContext>::ApplyFrontOnIndex(const FormatIndex& index)
    {
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextFront::Front>(      index, [this](const TextProperties::TextFront::Front& data)     { this->ReloadFront(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextFront::FrontID>(    index, [this](const TextProperties::TextFront::FrontID& data)   { this->AskApplyFront(data); } );
    }
    
    template <typename BasicContext>
    void TextPropertiesManager<BasicContext>::ApplyStyleOnIndex(const FormatIndex& index)
    {
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Style>(      index, [this](const TextProperties::TextStyle::Style& data)     { this->ReloadStyle(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Intensity>(  index, [this](const TextProperties::TextStyle::Intensity& data) { this->AskApplyStyle(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Italic>(     index, [this](const TextProperties::TextStyle::Italic& data)    { this->AskApplyStyle(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Underline>(  index, [this](const TextProperties::TextStyle::Underline& data) { this->AskApplyStyle(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Blink>(      index, [this](const TextProperties::TextStyle::Blink& data)     { this->AskApplyStyle(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Inverted>(   index, [this](const TextProperties::TextStyle::Inverted& data)  { this->AskApplyStyle(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Ideogram>(   index, [this](const TextProperties::TextStyle::Ideogram& data)  { this->AskApplyStyle(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::Script>(     index, [this](const TextProperties::TextStyle::Script& data)    { this->AskApplyStyle(data); } );

        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::UnderlineColor::ColorCube>(  index, [this](const TextProperties::TextStyle::UnderlineColor::ColorCube& data) { this->AskApplyStyle(data); } );
        m_Context.GetContextArgsInterface().template RunFuncFromTypeAtIndex<TextProperties::TextStyle::UnderlineColor::Color24b>(   index, [this](const TextProperties::TextStyle::UnderlineColor::Color24b& data)  { this->AskApplyStyle(data); } );
    }

    template <typename BasicContext>
    void TextPropertiesManager<BasicContext>::ParseColor()
    {
        if (m_Context.Format().IsEqualToForward(':')) {
            m_Context.Format().IgnoreAllSpaces();
            if (m_Context.Format().IsEqualToForward('{'))
            {
                FormatIndex idx = m_Context.GetFormatIndexThrow();
                ApplyColorOnIndex(idx);
                m_Context.Format().IsEqualToForward('}');
            }
            else
            {
                TextProperties::TextColor::BasicColorFG colorFg;
                bool colorFgFound = GetColorCode(colorFg);

                m_Context.Format().ParamGoTo('-', ',');
                if (m_Context.Format().IsEqualToForward('-')) {
                    m_Context.Format().IgnoreAllSpaces();
                    TextProperties::TextColor::BasicColorBG colorBg;
                    bool colorBgFound = GetColorCode(colorBg);
                    if (colorBgFound && colorFgFound)
                        AskApplyColor(TextProperties::TextColor::BasicColor{ colorFg, colorBg });
                    else
                        ReloadDefaultColor();
                }
                else
                {
                    if (colorFgFound)
                        AskApplyColor(colorFg);
                    else
                        ReloadDefaultColor();
                }
            }
        }
        else
            ReloadDefaultColor();
    }

    template <typename BasicContext>
    template<typename T>
    bool TextPropertiesManager<BasicContext>::GetColorCode(T& t)
    {
        static constexpr std::string_view colorCode[] = {
            "black",
            "red",
            "green",
            "yellow",
            "blue",
            "magenta",
            "cyan",
            "white",
            "      ",
            "default"
        };

        std::uint8_t step = static_cast<std::uint8_t>(m_Context.Format().IsEqualToForward('+') ? T::BaseBStep : T::BaseStep);
        std::uint8_t code = static_cast<std::uint8_t>(m_Context.Format().GetWordFromList(colorCode));
        if (code == m_Context.Format().GET_WORD_FROM_LIST_NOT_FOUND)     return false;
        t = static_cast<T>(code + step);
        return true;
    }

    template <typename BasicContext>
    void TextPropertiesManager<BasicContext>::ParseStyle()
    {
        if (m_Context.Format().IsEqualToForward(':')) {
            if (!m_Context.Format().IsEqualTo('}', ',')) {
                bool l = true;
                while (l) {
                    m_Context.Format().IgnoreAllSpaces();
                    if (m_Context.Format().IsEqualToForward('{'))
                    {
                        FormatIndex idx = m_Context.GetFormatIndexThrow();
                        ApplyStyleOnIndex(idx);
                        m_Context.Format().IsEqualToForward('}');
                    }
                    else
                    {
                        ParseStyleNamed();
                    }
                    m_Context.Format().ParamGoTo('|', ',');
                    l = m_Context.Format().IsEqualToForward('|');
                    m_Context.Format().IgnoreAllSpaces();
                }
            }
            else
                ReloadDefaultStyle();
        }
        else
            ReloadDefaultStyle();
    }

    template <typename BasicContext>
    void TextPropertiesManager<BasicContext>::ParseStyleNamed()
    {
        using FormatType = typename BasicContext::FormatBufferType;
        static constexpr typename FormatType::template DictPairs<TextProperties::TextStyle::Intensity> styleIntensity[] = {
            { "bold",           TextProperties::TextStyle::Intensity::Bold                  },
            { "dim",            TextProperties::TextStyle::Intensity::Dim                   },
            { "n-intensity",    TextProperties::TextStyle::Intensity::Normal                }
        };

        static constexpr typename FormatType::template DictPairs<TextProperties::TextStyle::Italic> styleItalic[] = {
            { "italic",         TextProperties::TextStyle::Italic::Enable                   },
            { "n-italic",       TextProperties::TextStyle::Italic::Disable                  }
        };

        // TODO: magic values
        static constexpr typename FormatType::template DictPairs<TextProperties::TextStyle::Underline> styleUnderline[] = {
            { "underlined",     TextProperties::TextStyle::Underline::Underlined            },
            { "d-underlined",   TextProperties::TextStyle::Underline::DoubleUnerlined       },
            { "n-underlined",   TextProperties::TextStyle::Underline::Disable               },
            { "c-underlined",   TextProperties::TextStyle::Underline::SelectUnderlinedColor }
        };

        static constexpr typename FormatType::template DictPairs<TextProperties::TextStyle::Blink> styleBlink[] = {
            { "slowblink",      TextProperties::TextStyle::Blink::SlowBlink                 },
            { "fastblink",      TextProperties::TextStyle::Blink::FastBlink                 },
            { "n-blink",        TextProperties::TextStyle::Blink::Disable                   }
        };

        static constexpr typename FormatType::template DictPairs<TextProperties::TextStyle::Inverted> styleInverted[] = {
            { "inverted",       TextProperties::TextStyle::Inverted::Enable                 },
            { "n-inverted",     TextProperties::TextStyle::Inverted::Disable                },
        };

        static constexpr typename FormatType::template DictPairs<TextProperties::TextStyle::Ideogram> styleIdeogram[] = {
            { "i-underlined",   TextProperties::TextStyle::Ideogram::Underlined             },
            { "i-d-underlined", TextProperties::TextStyle::Ideogram::DoubleUnderlined       },
            { "i-overlined",    TextProperties::TextStyle::Ideogram::Overlined              },
            { "i-d-overlined",  TextProperties::TextStyle::Ideogram::DoubleOverlined        },
            { "i-stress",       TextProperties::TextStyle::Ideogram::StressMarking          },
            { "n-i",            TextProperties::TextStyle::Ideogram::AllDisable             },
        };

        static constexpr typename FormatType::template DictPairs<TextProperties::TextStyle::Script> styleScript[] = {
            { "superscript",    TextProperties::TextStyle::Script::Superscript              },
            { "subscript",      TextProperties::TextStyle::Script::Subscript                },
            { "n-script",       TextProperties::TextStyle::Script::AllDisable               }
        };

        std::uint8_t code = (std::uint8_t)m_Context.Format().GetWordFromDictPairs(styleIntensity, (TextProperties::TextStyle::Intensity)255);
        if (code != 255) return ApplyStyle(TextProperties::TextStyle::Intensity{code});
        code = (std::uint8_t)m_Context.Format().GetWordFromDictPairs(styleItalic, (TextProperties::TextStyle::Italic)255);
        if (code != 255) return ApplyStyle(TextProperties::TextStyle::Italic{code});
        code = (std::uint8_t)m_Context.Format().GetWordFromDictPairs(styleBlink, (TextProperties::TextStyle::Blink)255);
        if (code != 255) return ApplyStyle(TextProperties::TextStyle::Blink{code});
        code = (std::uint8_t)m_Context.Format().GetWordFromDictPairs(styleInverted, (TextProperties::TextStyle::Inverted)255);
        if (code != 255) return ApplyStyle(TextProperties::TextStyle::Inverted{code});
        code = (std::uint8_t)m_Context.Format().GetWordFromDictPairs(styleIdeogram, (TextProperties::TextStyle::Ideogram)255);
        if (code != 255) return ApplyStyle(TextProperties::TextStyle::Ideogram{code});
        code = (std::uint8_t)m_Context.Format().GetWordFromDictPairs(styleScript, (TextProperties::TextStyle::Script)255);
        if (code != 255) return ApplyStyle(TextProperties::TextStyle::Script{code});

        code = (std::uint8_t)m_Context.Format().GetWordFromDictPairs(styleUnderline, (TextProperties::TextStyle::Underline)255);
        if (code != 255)
        {
            if (code == (std::uint8_t)TextProperties::TextStyle::Underline::SelectUnderlinedColor)
            {
                TextProperties::TextStyle::UnderlineColor::ColorCube underlineColor = SelectUnderlinedColorStyle();
                return ApplyStyle(underlineColor);
            }
            return ApplyStyle(TextProperties::TextStyle::Underline{code});
        }
    }

    template <typename BasicContext>
    TextProperties::TextStyle::UnderlineColor::ColorCube TextPropertiesManager<BasicContext>::SelectUnderlinedColorStyle()
    {
        m_Context.Format().ParamGoTo(':');
        m_Context.Format().IsEqualToForward(':');
        m_Context.Format().IgnoreAllSpaces();
        TextProperties::TextStyle::UnderlineColor::ColorCube color;
        if (GetColorCode(color)) return color;
        // TODO : handle Color24b
        if (m_BaseContextProperties != nullptr)
            return m_BaseContextProperties->Style.UnderlineColor.Data.ColorCube;
        return TextProperties::TextStyle::UnderlineColor::ColorCube{};
    }

    template <typename BasicContext>
    void TextPropertiesManager<BasicContext>::ParseFront()
    {
        static constexpr std::string_view frontCode[] = {
            "default",
            "front0",
            "front1",
            "front2",
            "front3",
            "front4",
            "front5",
            "front6",
            "front7",
            "front8",
            "front9"
        };
        
        if (m_Context.Format().IsEqualToForward(':'))
        {
            m_Context.Format().IgnoreAllSpaces();
            TextProperties::TextFront::FrontID frontID = (static_cast<uint8_t>(m_Context.Format().GetWordFromList(frontCode)));
            ApplyFront(frontID);
        }
        else
            ReloadDefaultFront();
    }
}
