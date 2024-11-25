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
    [[nodiscard]] std::expected<void, FMTResult> Detail::TextPropertiesManager<TChar>::ApplyColorOnIndex(Context::BasicContext<TChar>& context, std::int32_t index)
    {
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::Color>(
            index, [this](const Detail::TextProperties::TextColor::Color& data) -> std::expected<void, FMTResult> { this->ReloadColor(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::BasicColorFG>(
            index, [this](const Detail::TextProperties::TextColor::BasicColorFG& data) -> std::expected<void, FMTResult> { this->AskApplyColor(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::BasicColorBG>(
            index, [this](const Detail::TextProperties::TextColor::BasicColorBG& data) -> std::expected<void, FMTResult> { this->AskApplyColor(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::ColorCubeFG>(
            index, [this](const Detail::TextProperties::TextColor::ColorCubeFG& data) -> std::expected<void, FMTResult> { this->AskApplyColor(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::ColorCubeBG>(
            index, [this](const Detail::TextProperties::TextColor::ColorCubeBG& data) -> std::expected<void, FMTResult> { this->AskApplyColor(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::Color24bFG>(
            index, [this](const Detail::TextProperties::TextColor::Color24bFG& data) -> std::expected<void, FMTResult> { this->AskApplyColor(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextColor::Color24bBG>(
            index, [this](const Detail::TextProperties::TextColor::Color24bBG& data) -> std::expected<void, FMTResult> { this->AskApplyColor(data); return {}; }));
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> Detail::TextPropertiesManager<TChar>::ApplyFrontOnIndex(Context::BasicContext<TChar>& context, std::int32_t index)
    {
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextFront::Front>(
            index, [this](const Detail::TextProperties::TextFront::Front& data) -> std::expected<void, FMTResult> { this->ReloadFront(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextFront::FrontID>(
            index, [this](const Detail::TextProperties::TextFront::FrontID& data) -> std::expected<void, FMTResult> { this->AskApplyFront(data); return {}; }));
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> Detail::TextPropertiesManager<TChar>::ApplyStyleOnIndex(Context::BasicContext<TChar>& context, std::int32_t index)
    {
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Style>(
            index, [this](const Detail::TextProperties::TextStyle::Style& data) -> std::expected<void, FMTResult> { return this->ReloadStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Intensity>(
            index, [this](const Detail::TextProperties::TextStyle::Intensity& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Italic>(
            index, [this](const Detail::TextProperties::TextStyle::Italic& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Underline>(
            index, [this](const Detail::TextProperties::TextStyle::Underline& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Blink>(
            index, [this](const Detail::TextProperties::TextStyle::Blink& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Inverted>(
            index, [this](const Detail::TextProperties::TextStyle::Inverted& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Ideogram>(
            index, [this](const Detail::TextProperties::TextStyle::Ideogram& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::Script>(
            index, [this](const Detail::TextProperties::TextStyle::Script& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));

        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::UnderlineColor::ColorCube>(
            index, [this](const Detail::TextProperties::TextStyle::UnderlineColor::ColorCube& data) -> std::expected<void, FMTResult> { this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<Detail::TextProperties::TextStyle::UnderlineColor::Color24b>(
            index, [this](const Detail::TextProperties::TextStyle::UnderlineColor::Color24b& data) -> std::expected<void, FMTResult> { this->AskApplyStyle(data); return {}; }));
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> Detail::TextPropertiesManager<TChar>::ParseColor(Context::BasicContext<TChar>& context)
    {
        if (BufferTestAccess(context.Format).IsEqualTo(':'))
        {
            SF_TRY(BufferManip(context.Format).Forward());
            BufferTestManip(context.Format).SkipAllSpaces();
            if (BufferTestAccess(context.Format).IsEqualTo('{'))
            {
                SF_TRY(BufferManip(context.Format).Forward());
                std::int32_t idx = SF_TRY(context.GetFormatIndex());
                SF_TRY(ApplyColorOnIndex(context, idx));
                SF_TRY(BufferTestManip(context.Format).IsEqualToForward('}'));
            }
            else
            {
                auto colorFg = GetColorCode<TextProperties::TextColor::BasicColorFG>(context.Format);
                FMTBufferParamsManip(context.Format).ParamGoTo('-', ',');
                if (BufferTestAccess(context.Format).IsEqualTo('-'))
                {
                    SF_TRY(BufferManip(context.Format).Forward());
                    BufferTestManip(context.Format).SkipAllSpaces();
                    auto colorBg = GetColorCode<TextProperties::TextColor::BasicColorBG>(context.Format);
                    if (colorBg.has_value() && colorFg.has_value())
                        { return AskApplyColor(Detail::TextProperties::TextColor::BasicColor{colorFg.value(), colorBg.value()}); }
                    else
                        { return ReloadDefaultColor(); }
                }
                else
                {
                    if (colorFg.has_value())
                        { return AskApplyColor(colorFg.value()); }
                    else
                        { return ReloadDefaultColor(); }
                }
            }
        }
        else
            { return ReloadDefaultColor(); }
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> Detail::TextPropertiesManager<TChar>::ParseStyle(Context::BasicContext<TChar>& context)
    {
        if (BufferTestAccess(context.Format).IsEqualTo(':'))
        {
            SF_TRY(BufferManip(context.Format).Forward());
            if (!BufferTestAccess(context.Format).IsEqualTo('}', ','))
            {
                bool l = true;
                while (l)
                {
                    BufferTestManip(context.Format).SkipAllSpaces();
                    if (BufferTestAccess(context.Format).IsEqualTo('{'))
                    {
                        SF_TRY(BufferManip(context.Format).Forward());
                        std::int32_t idx = SF_TRY(context.GetFormatIndex());
                        ApplyStyleOnIndex(context, idx);
                        BufferTestManip(context.Format).IsEqualToForward('}');
                    }
                    else
                    {
                        ParseStyleNamed(context.Format);
                    }
                    FMTBufferParamsManip(context.Format).ParamGoTo('|', ',');
                    l = SF_TRY(BufferTestManip(context.Format).IsEqualToForward('|'));
                    BufferTestManip(context.Format).SkipAllSpaces();
                }
            }
            else
                return ReloadDefaultStyle();
        }
        else
            return ReloadDefaultStyle();
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> Detail::TextPropertiesManager<TChar>::ParseStyleNamed(BufferInfoView<TChar>& format)
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

        std::uint8_t code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).GetWordFromDictPairs(styleIntensity));
        if (code != 255) return ApplyStyle(Detail::TextProperties::TextStyle::Intensity{code});
        code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).GetWordFromDictPairs(styleItalic));
        if (code != 255) return ApplyStyle(Detail::TextProperties::TextStyle::Italic{code});
        code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).GetWordFromDictPairs(styleBlink));
        if (code != 255) return ApplyStyle(Detail::TextProperties::TextStyle::Blink{code});
        code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).GetWordFromDictPairs(styleInverted));
        if (code != 255) return ApplyStyle(Detail::TextProperties::TextStyle::Inverted{code});
        code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).GetWordFromDictPairs(styleIdeogram));
        if (code != 255) return ApplyStyle(Detail::TextProperties::TextStyle::Ideogram{code});
        code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).GetWordFromDictPairs(styleScript));
        if (code != 255) return ApplyStyle(Detail::TextProperties::TextStyle::Script{code});

        code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).GetWordFromDictPairs(styleUnderline));
        if (code != 255)
        {
            if (code == (std::uint8_t)Detail::TextProperties::TextStyle::Underline::SelectUnderlinedColor)
            {
                Detail::TextProperties::TextStyle::UnderlineColor::ColorCube underlineColor = SF_TRY(SelectUnderlinedColorStyle(format));
                return ApplyStyle(underlineColor);
            }
            return ApplyStyle(Detail::TextProperties::TextStyle::Underline{code});
        }
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<TextProperties::TextStyle::UnderlineColor::ColorCube, FMTResult> TextPropertiesManager<TChar>::SelectUnderlinedColorStyle(BufferInfoView<TChar>& format)
    {
        // TODO
        // FIXME
        return std::unexpected(FMTResult::FunctionNotImpl);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> Detail::TextPropertiesManager<TChar>::ParseFront(Context::BasicContext<TChar>& context)
    {
        static constexpr std::string_view frontCode[] = {"default", "front0", "front1", "front2", "front3", "front4", "front5", "front6", "front7", "front8", "front9"};

        if (BufferTestAccess(context.Format).IsEqualTo(':'))
        {
            SF_TRY(BufferManip(context.Format).Forward());
            BufferTestManip(context.Format).SkipAllSpaces();

            Detail::TextProperties::TextFront::FrontID frontID = (std::uint8_t)SF_TRY(BufferUtilsManip(context.Format).GetWordFromList(frontCode));
            return ApplyFront(frontID);
        }
        else
            return ReloadDefaultFront();
        return {};
    }
}
