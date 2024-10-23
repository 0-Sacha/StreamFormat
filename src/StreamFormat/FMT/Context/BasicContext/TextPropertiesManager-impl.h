#pragma once

#include "TextPropertiesManager.h"

#include "StreamFormat/FMT/Buffer/BufferManip.h"
#include "StreamFormat/FMT/Buffer/BufferOutManip.h"
#include "StreamFormat/FMT/Buffer/BufferTestManip.h"
#include "StreamFormat/FMT/Buffer/FMTBufferOutManip.h"
#include "StreamFormat/FMT/Buffer/Utils/BufferUtils.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    void Detail::TextPropertiesManager<TChar>::ApplyColorOnIndex(Context::BasicContext<TChar>& context, std::int32_t index)
    {
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::Color>(
            index, [this](const Detail::TextProperties::TextColor::Color& data) { this->ReloadColor(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::BasicColorFG>(
            index, [this](const Detail::TextProperties::TextColor::BasicColorFG& data) { this->AskApplyColor(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::BasicColorBG>(
            index, [this](const Detail::TextProperties::TextColor::BasicColorBG& data) { this->AskApplyColor(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::ColorCubeFG>(
            index, [this](const Detail::TextProperties::TextColor::ColorCubeFG& data) { this->AskApplyColor(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::ColorCubeBG>(
            index, [this](const Detail::TextProperties::TextColor::ColorCubeBG& data) { this->AskApplyColor(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::Color24bFG>(
            index, [this](const Detail::TextProperties::TextColor::Color24bFG& data) { this->AskApplyColor(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::Color24bBG>(
            index, [this](const Detail::TextProperties::TextColor::Color24bBG& data) { this->AskApplyColor(data); });
    }

    template <typename TChar>
    void Detail::TextPropertiesManager<TChar>::ApplyFrontOnIndex(Context::BasicContext<TChar>& context, std::int32_t index)
    {
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextFront::Front>(
            index, [this](const Detail::TextProperties::TextFront::Front& data) { this->ReloadFront(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextFront::FrontID>(
            index, [this](const Detail::TextProperties::TextFront::FrontID& data) { this->AskApplyFront(data); });
    }

    template <typename TChar>
    void Detail::TextPropertiesManager<TChar>::ApplyStyleOnIndex(Context::BasicContext<TChar>& context, std::int32_t index)
    {
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Style>(
            index, [this](const Detail::TextProperties::TextStyle::Style& data) { this->ReloadStyle(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Intensity>(
            index, [this](const Detail::TextProperties::TextStyle::Intensity& data) { this->AskApplyStyle(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Italic>(
            index, [this](const Detail::TextProperties::TextStyle::Italic& data) { this->AskApplyStyle(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Underline>(
            index, [this](const Detail::TextProperties::TextStyle::Underline& data) { this->AskApplyStyle(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Blink>(
            index, [this](const Detail::TextProperties::TextStyle::Blink& data) { this->AskApplyStyle(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Inverted>(
            index, [this](const Detail::TextProperties::TextStyle::Inverted& data) { this->AskApplyStyle(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Ideogram>(
            index, [this](const Detail::TextProperties::TextStyle::Ideogram& data) { this->AskApplyStyle(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Script>(
            index, [this](const Detail::TextProperties::TextStyle::Script& data) { this->AskApplyStyle(data); });

        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::UnderlineColor::ColorCube>(
            index, [this](const Detail::TextProperties::TextStyle::UnderlineColor::ColorCube& data) { this->AskApplyStyle(data); });
        context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::UnderlineColor::Color24b>(
            index, [this](const Detail::TextProperties::TextStyle::UnderlineColor::Color24b& data) { this->AskApplyStyle(data); });
    }

    template <typename TChar>
    void Detail::TextPropertiesManager<TChar>::ParseColor(Context::BasicContext<TChar>& context)
    {
        if (BufferTestManip(context.Format).IsEqualToForward(':'))
        {
            BufferTestManip(context.Format).SkipAllSpaces();
            if (BufferTestManip(context.Format).IsEqualToForward('{'))
            {
                std::int32_t idx = 0;
                context.GetFormatIndex(idx).ThrowIfFailed();
                ApplyColorOnIndex(context, idx);
                BufferTestManip(context.Format).IsEqualToForward('}');
            }
            else
            {
                Detail::TextProperties::TextColor::BasicColorFG colorFg;
                bool colorFgFound = GetColorCode(context.Format, colorFg);

                FMTBufferParamsManip(context.Format).ParamGoTo('-', ',');
                if (BufferTestManip(context.Format).IsEqualToForward('-'))
                {
                    BufferTestManip(context.Format).SkipAllSpaces();
                    Detail::TextProperties::TextColor::BasicColorBG colorBg;
                    bool colorBgFound = GetColorCode(context.Format, colorBg);
                    if (colorBgFound && colorFgFound)
                        AskApplyColor(Detail::TextProperties::TextColor::BasicColor{colorFg, colorBg});
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

    template <typename TChar>
    void Detail::TextPropertiesManager<TChar>::ParseStyle(Context::BasicContext<TChar>& context)
    {
        if (BufferTestManip(context.Format).IsEqualToForward(':'))
        {
            if (!BufferTestAccess(context.Format).IsEqualTo('}', ','))
            {
                bool l = true;
                while (l)
                {
                    BufferTestManip(context.Format).SkipAllSpaces();
                    if (BufferTestManip(context.Format).IsEqualToForward('{'))
                    {
                        std::int32_t idx = 0;
                        context.GetFormatIndex(idx).ThrowIfFailed();
                        ApplyStyleOnIndex(context, idx);
                        BufferTestManip(context.Format).IsEqualToForward('}');
                    }
                    else
                    {
                        ParseStyleNamed(context.Format);
                    }
                    FMTBufferParamsManip(context.Format).ParamGoTo('|', ',');
                    l = BufferTestManip(context.Format).IsEqualToForward('|');
                    BufferTestManip(context.Format).SkipAllSpaces();
                }
            }
            else
                ReloadDefaultStyle();
        }
        else
            ReloadDefaultStyle();
    }

    template <typename TChar>
    void Detail::TextPropertiesManager<TChar>::ParseStyleNamed(BufferInfoView<TChar>& format)
    {
        Detail::BufferUtilsManip utils(format);
        
        static constexpr std::pair<std::basic_string_view<TChar>, Detail::TextProperties::TextStyle::Intensity> styleIntensity[] = {
            {"bold", Detail::TextProperties::TextStyle::Intensity::Bold},
            {"dim", Detail::TextProperties::TextStyle::Intensity::Dim},
            {"n-intensity", Detail::TextProperties::TextStyle::Intensity::Normal}
        };

        static constexpr std::pair<std::basic_string_view<TChar>, Detail::TextProperties::TextStyle::Italic> styleItalic[] = {
            {"italic", Detail::TextProperties::TextStyle::Italic::Enable},
            {"n-italic", Detail::TextProperties::TextStyle::Italic::Disable}
        };

        // TODO: magic values
        static constexpr typename std::pair<std::basic_string_view<TChar>, Detail::TextProperties::TextStyle::Underline> styleUnderline[] = {
            {"underlined", Detail::TextProperties::TextStyle::Underline::Underlined},
            {"d-underlined", Detail::TextProperties::TextStyle::Underline::DoubleUnerlined},
            {"n-underlined", Detail::TextProperties::TextStyle::Underline::Disable},
            {"c-underlined", Detail::TextProperties::TextStyle::Underline::SelectUnderlinedColor}};

        static constexpr typename std::pair<std::basic_string_view<TChar>, Detail::TextProperties::TextStyle::Blink> styleBlink[] = {{"slowblink", Detail::TextProperties::TextStyle::Blink::SlowBlink},
                                                                                                                   {"fastblink", Detail::TextProperties::TextStyle::Blink::FastBlink},
                                                                                                                   {"n-blink", Detail::TextProperties::TextStyle::Blink::Disable}};

        static constexpr typename std::pair<std::basic_string_view<TChar>, Detail::TextProperties::TextStyle::Inverted> styleInverted[] = {
            {"inverted", Detail::TextProperties::TextStyle::Inverted::Enable},
            {"n-inverted", Detail::TextProperties::TextStyle::Inverted::Disable},
        };

        static constexpr typename std::pair<std::basic_string_view<TChar>, Detail::TextProperties::TextStyle::Ideogram> styleIdeogram[] = {
            {"i-underlined", Detail::TextProperties::TextStyle::Ideogram::Underlined}, {"i-d-underlined", Detail::TextProperties::TextStyle::Ideogram::DoubleUnderlined},
            {"i-overlined", Detail::TextProperties::TextStyle::Ideogram::Overlined},   {"i-d-overlined", Detail::TextProperties::TextStyle::Ideogram::DoubleOverlined},
            {"i-stress", Detail::TextProperties::TextStyle::Ideogram::StressMarking},  {"n-i", Detail::TextProperties::TextStyle::Ideogram::AllDisable},
        };

        static constexpr typename std::pair<std::basic_string_view<TChar>, Detail::TextProperties::TextStyle::Script> styleScript[] = {
            {"superscript", Detail::TextProperties::TextStyle::Script::Superscript},
            {"subscript", Detail::TextProperties::TextStyle::Script::Subscript},
            {"n-script", Detail::TextProperties::TextStyle::Script::AllDisable}};

        std::uint8_t code = (std::uint8_t)BufferUtilsManip(format).GetWordFromDictPairs(styleIntensity, (Detail::TextProperties::TextStyle::Intensity)255);
        if (code != 255) return ApplyStyle(Detail::TextProperties::TextStyle::Intensity{code});
        code = (std::uint8_t)BufferUtilsManip(format).GetWordFromDictPairs(styleItalic, (Detail::TextProperties::TextStyle::Italic)255);
        if (code != 255) return ApplyStyle(Detail::TextProperties::TextStyle::Italic{code});
        code = (std::uint8_t)BufferUtilsManip(format).GetWordFromDictPairs(styleBlink, (Detail::TextProperties::TextStyle::Blink)255);
        if (code != 255) return ApplyStyle(Detail::TextProperties::TextStyle::Blink{code});
        code = (std::uint8_t)BufferUtilsManip(format).GetWordFromDictPairs(styleInverted, (Detail::TextProperties::TextStyle::Inverted)255);
        if (code != 255) return ApplyStyle(Detail::TextProperties::TextStyle::Inverted{code});
        code = (std::uint8_t)BufferUtilsManip(format).GetWordFromDictPairs(styleIdeogram, (Detail::TextProperties::TextStyle::Ideogram)255);
        if (code != 255) return ApplyStyle(Detail::TextProperties::TextStyle::Ideogram{code});
        code = (std::uint8_t)BufferUtilsManip(format).GetWordFromDictPairs(styleScript, (Detail::TextProperties::TextStyle::Script)255);
        if (code != 255) return ApplyStyle(Detail::TextProperties::TextStyle::Script{code});

        code = (std::uint8_t)BufferUtilsManip(format).GetWordFromDictPairs(styleUnderline, (Detail::TextProperties::TextStyle::Underline)255);
        if (code != 255)
        {
            if (code == (std::uint8_t)Detail::TextProperties::TextStyle::Underline::SelectUnderlinedColor)
            {
                Detail::TextProperties::TextStyle::UnderlineColor::ColorCube underlineColor = SelectUnderlinedColorStyle(format);
                return ApplyStyle(underlineColor);
            }
            return ApplyStyle(Detail::TextProperties::TextStyle::Underline{code});
        }
    }

    template <typename TChar>
    TextProperties::TextStyle::UnderlineColor::ColorCube TextPropertiesManager<TChar>::SelectUnderlinedColorStyle(BufferInfoView<TChar>& format)
    {
        FMTBufferParamsManip(format).ParamGoTo(':');
        BufferTestManip(format).IsEqualToForward(':');
        BufferTestManip(format).SkipAllSpaces();
        Detail::TextProperties::TextStyle::UnderlineColor::ColorCube color;
        if (GetColorCode(format, color)) return color;
        // TODO : handle Color24b
        return Detail::TextProperties::TextStyle::UnderlineColor::ColorCube{};
    }

    template <typename TChar>
    void Detail::TextPropertiesManager<TChar>::ParseFront(Context::BasicContext<TChar>& context)
    {
        static constexpr std::string_view frontCode[] = {"default", "front0", "front1", "front2", "front3", "front4", "front5", "front6", "front7", "front8", "front9"};

        if (BufferTestManip(context.Format).IsEqualToForward(':'))
        {
            BufferTestManip(context.Format).SkipAllSpaces();
            Detail::TextProperties::TextFront::FrontID frontID = (static_cast<uint8_t>(BufferUtilsManip(context.Format).GetWordFromList(frontCode)));
            ApplyFront(frontID);
        }
        else
            ReloadDefaultFront();
    }
}
