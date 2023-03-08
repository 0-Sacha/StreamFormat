#pragma once

#include "ProjectCore/FMT/Detail/Detail.h"

namespace ProjectCore::FMT::Detail
{
	class ITextPropertiesExecutor
    {
    public:
        virtual ~ITextPropertiesExecutor() = default;
        
    public:
        virtual void AllPropertiesReset() = 0;

    public:
        virtual void ResetColor() = 0;
        virtual void ExecuteColor(const TextProperties::TextColor::BasicColorFG& t) = 0;
        virtual void ExecuteColor(const TextProperties::TextColor::BasicColorBG& t) = 0;
        virtual void ExecuteColor(const TextProperties::TextColor::BasicColor& t) = 0;
        virtual void ExecuteColor(const TextProperties::TextColor::Color24bFG& t) = 0;
        virtual void ExecuteColor(const TextProperties::TextColor::Color24bBG& t) = 0;
        virtual void ExecuteColor(const TextProperties::TextColor::Color24b& t) = 0;
        virtual void ExecuteColor(const TextProperties::TextColor::ColorCubeFG& t) = 0;
        virtual void ExecuteColor(const TextProperties::TextColor::ColorCubeBG& t) = 0;
        virtual void ExecuteColor(const TextProperties::TextColor::ColorCube& t) = 0;

    public:
        virtual void ResetFront() = 0;
        virtual void ExecuteFront(const TextProperties::TextFront::FrontID& t) = 0;

    public:
        virtual void ResetStyle() = 0;
        virtual void ExecuteStyle(const TextProperties::TextStyle::Intensity& t) = 0;
        virtual void ExecuteStyle(const TextProperties::TextStyle::Italic& t) = 0;
        virtual void ExecuteStyle(const TextProperties::TextStyle::Underline& t) = 0;
        virtual void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::Color& t) = 0;
        virtual void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::ColorCube& t) = 0;
        virtual void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::Color24b& t) = 0;
        virtual void ExecuteStyle(const TextProperties::TextStyle::Blink& t) = 0;
        virtual void ExecuteStyle(const TextProperties::TextStyle::Inverted& t) = 0;
        virtual void ExecuteStyle(const TextProperties::TextStyle::Ideogram& t) = 0;
        virtual void ExecuteStyle(const TextProperties::TextStyle::Script& t) = 0;

        virtual void ExecuteStyle(const TextProperties::TextStyle::BasicStyle& t)
        {
            switch(t)
            {
                case TextProperties::TextStyle::BasicStyle::Intensity_Bold:
                case TextProperties::TextStyle::BasicStyle::Intensity_Dim:
                case TextProperties::TextStyle::BasicStyle::Intensity_Normal:
                    ExecuteStyle(static_cast<TextProperties::TextStyle::Intensity>(t));
                    break;

                case TextProperties::TextStyle::BasicStyle::Italic_Enable:
                case TextProperties::TextStyle::BasicStyle::Italic_Disable:
                    ExecuteStyle(static_cast<TextProperties::TextStyle::Italic>(t));
                    break;

                case TextProperties::TextStyle::BasicStyle::Underline_Underlined:
                case TextProperties::TextStyle::BasicStyle::Underline_DoubleUnerlined:
                case TextProperties::TextStyle::BasicStyle::Underline_Disable:
                    ExecuteStyle(static_cast<TextProperties::TextStyle::Underline>(t));
                    break;

                case TextProperties::TextStyle::BasicStyle::Blink_SlowBlink:
                case TextProperties::TextStyle::BasicStyle::Blink_FastBlink:
                case TextProperties::TextStyle::BasicStyle::Blink_Disable:
                    ExecuteStyle(static_cast<TextProperties::TextStyle::Blink>(t));
                    break;

                case TextProperties::TextStyle::BasicStyle::Inverted_Enable:
                case TextProperties::TextStyle::BasicStyle::Inverted_Disable:
                    ExecuteStyle(static_cast<TextProperties::TextStyle::Inverted>(t));
                    break;

                case TextProperties::TextStyle::BasicStyle::Ideogram_Underlined:
                case TextProperties::TextStyle::BasicStyle::Ideogram_DoubleUnderlined:
                case TextProperties::TextStyle::BasicStyle::Ideogram_Overlined:
                case TextProperties::TextStyle::BasicStyle::Ideogram_DoubleOverlined:
                case TextProperties::TextStyle::BasicStyle::Ideogram_StressMarking:
                case TextProperties::TextStyle::BasicStyle::Ideogram_AllDisable:
                    ExecuteStyle(static_cast<TextProperties::TextStyle::Ideogram>(t));
                    break;

                case TextProperties::TextStyle::BasicStyle::Script_Superscript:
                case TextProperties::TextStyle::BasicStyle::Script_Subscript:
                case TextProperties::TextStyle::BasicStyle::Script_AllDisable:
                    ExecuteStyle(static_cast<TextProperties::TextStyle::Script>(t));
                    break;

                default:
                    break;
            }
        }
    };
}
