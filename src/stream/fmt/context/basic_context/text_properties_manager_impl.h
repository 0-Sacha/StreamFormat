#pragma once

#include "text_properties_manager.h"

#include "stream/fmt/buffer/buffer_manip.h"
#include "stream/fmt/buffer/buffer_out_manip.h"
#include "stream/fmt/buffer/buffer_test_manip.h"
#include "stream/fmt/buffer/fmt_buffer_out_manip.h"
#include "stream/fmt/buffer/utils/buffer_utils.h"

namespace stream::fmt::detail
{
    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> detail::TextPropertiesManager<TChar>::ApplyColorOnIndex(Context::BasicContext<TChar>& context, std::int32_t index)
    {
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextColor::Color>(
            index, [this](const detail::TextProperties::TextColor::Color& data) -> std::expected<void, FMTResult> { this->ReloadColor(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextColor::BasicColorFG>(
            index, [this](const detail::TextProperties::TextColor::BasicColorFG& data) -> std::expected<void, FMTResult> { this->AskApplyColor(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextColor::BasicColorBG>(
            index, [this](const detail::TextProperties::TextColor::BasicColorBG& data) -> std::expected<void, FMTResult> { this->AskApplyColor(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextColor::ColorCubeFG>(
            index, [this](const detail::TextProperties::TextColor::ColorCubeFG& data) -> std::expected<void, FMTResult> { this->AskApplyColor(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextColor::ColorCubeBG>(
            index, [this](const detail::TextProperties::TextColor::ColorCubeBG& data) -> std::expected<void, FMTResult> { this->AskApplyColor(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextColor::Color24bFG>(
            index, [this](const detail::TextProperties::TextColor::Color24bFG& data) -> std::expected<void, FMTResult> { this->AskApplyColor(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextColor::Color24bBG>(
            index, [this](const detail::TextProperties::TextColor::Color24bBG& data) -> std::expected<void, FMTResult> { this->AskApplyColor(data); return {}; }));
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> detail::TextPropertiesManager<TChar>::ApplyFrontOnIndex(Context::BasicContext<TChar>& context, std::int32_t index)
    {
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextFront::Front>(
            index, [this](const detail::TextProperties::TextFront::Front& data) -> std::expected<void, FMTResult> { this->ReloadFront(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextFront::FrontID>(
            index, [this](const detail::TextProperties::TextFront::FrontID& data) -> std::expected<void, FMTResult> { this->AskApplyFront(data); return {}; }));
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> detail::TextPropertiesManager<TChar>::ApplyStyleOnIndex(Context::BasicContext<TChar>& context, std::int32_t index)
    {
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextStyle::Style>(
            index, [this](const detail::TextProperties::TextStyle::Style& data) -> std::expected<void, FMTResult> { return this->ReloadStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextStyle::Intensity>(
            index, [this](const detail::TextProperties::TextStyle::Intensity& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextStyle::Italic>(
            index, [this](const detail::TextProperties::TextStyle::Italic& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextStyle::Underline>(
            index, [this](const detail::TextProperties::TextStyle::Underline& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextStyle::Blink>(
            index, [this](const detail::TextProperties::TextStyle::Blink& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextStyle::Inverted>(
            index, [this](const detail::TextProperties::TextStyle::Inverted& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextStyle::Ideogram>(
            index, [this](const detail::TextProperties::TextStyle::Ideogram& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextStyle::Script>(
            index, [this](const detail::TextProperties::TextStyle::Script& data) -> std::expected<void, FMTResult> { return this->AskApplyStyle(data); return {}; }));

        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextStyle::UnderlineColor::ColorCube>(
            index, [this](const detail::TextProperties::TextStyle::UnderlineColor::ColorCube& data) -> std::expected<void, FMTResult> { this->AskApplyStyle(data); return {}; }));
        SF_TRY(context.ArgsInterface.template RunFuncFromTypeAtIndex<detail::TextProperties::TextStyle::UnderlineColor::Color24b>(
            index, [this](const detail::TextProperties::TextStyle::UnderlineColor::Color24b& data) -> std::expected<void, FMTResult> { this->AskApplyStyle(data); return {}; }));
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> detail::TextPropertiesManager<TChar>::ParseColor(Context::BasicContext<TChar>& context)
    {
        if (BufferTestAccess(context.Format).IsEqualTo(':'))
        {
            SF_TRY(BufferManip(context.Format).Forward());
            BufferTestManip(context.Format).IgnoreEverySpaces();
            if (BufferTestAccess(context.Format).IsEqualTo('{'))
            {
                SF_TRY(BufferManip(context.Format).Forward());
                std::int32_t idx = SF_TRY(context.GetFormatIndex());
                SF_TRY(ApplyColorOnIndex(context, idx));
                SF_TRY(BufferTestManip(context.Format).SkipOneOf('}'));
            }
            else
            {
                auto colorFg = GetColorCode<TextProperties::TextColor::BasicColorFG>(context.Format);
                FMTBufferParamsManip(context.Format).ParamGoTo('-', ',');
                if (BufferTestAccess(context.Format).IsEqualTo('-'))
                {
                    SF_TRY(BufferManip(context.Format).Forward());
                    BufferTestManip(context.Format).IgnoreEverySpaces();
                    auto colorBg = GetColorCode<TextProperties::TextColor::BasicColorBG>(context.Format);
                    if (colorBg.has_value() && colorFg.has_value())
                        { return AskApplyColor(detail::TextProperties::TextColor::BasicColor{colorFg.value(), colorBg.value()}); }
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
    [[nodiscard]] std::expected<void, FMTResult> detail::TextPropertiesManager<TChar>::ParseStyle(Context::BasicContext<TChar>& context)
    {
        if (BufferTestAccess(context.Format).IsEqualTo(':'))
        {
            SF_TRY(BufferManip(context.Format).Forward());
            if (!BufferTestAccess(context.Format).IsEqualTo('}', ','))
            {
                bool loop = true;
                while (loop)
                {
                    BufferTestManip(context.Format).IgnoreEverySpaces();
                    if (BufferTestAccess(context.Format).IsEqualTo('{'))
                    {
                        SF_TRY(BufferManip(context.Format).Forward());
                        std::int32_t idx = SF_TRY(context.GetFormatIndex());
                        ApplyStyleOnIndex(context, idx);
                        BufferTestManip(context.Format).SkipOneOf('}');
                    }
                    else
                    {
                        ParseStyleNamed(context.Format);
                    }
                    FMTBufferParamsManip(context.Format).ParamGoTo('|', ',');
                    loop = SF_TRY(BufferTestManip(context.Format).IsEqualToForward('|'));
                    BufferTestManip(context.Format).IgnoreEverySpaces();
                }
            }
            else
                { return ReloadDefaultStyle(); }
        }
        else
            { return ReloadDefaultStyle(); }
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> detail::TextPropertiesManager<TChar>::ParseStyleNamed(BufferInfoView<TChar>& format)
    {
        detail::BufferUtilsManip utils(format);
        
        static constexpr std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Intensity> styleIntensity[] = {
            {"bold", detail::TextProperties::TextStyle::Intensity::Bold},
            {"dim", detail::TextProperties::TextStyle::Intensity::Dim},
            {"n-intensity", detail::TextProperties::TextStyle::Intensity::Normal}
        };

        static constexpr std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Italic> styleItalic[] = {
            {"italic", detail::TextProperties::TextStyle::Italic::Enable},
            {"n-italic", detail::TextProperties::TextStyle::Italic::Disable}
        };

        // TODO: magic values
        static constexpr typename std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Underline> styleUnderline[] = {
            {"underlined", detail::TextProperties::TextStyle::Underline::Underlined},
            {"d-underlined", detail::TextProperties::TextStyle::Underline::DoubleUnerlined},
            {"n-underlined", detail::TextProperties::TextStyle::Underline::Disable},
            {"c-underlined", detail::TextProperties::TextStyle::Underline::SelectUnderlinedColor}};

        static constexpr typename std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Blink> styleBlink[] = {{"slowblink", detail::TextProperties::TextStyle::Blink::SlowBlink},
                                                                                                                   {"fastblink", detail::TextProperties::TextStyle::Blink::FastBlink},
                                                                                                                   {"n-blink", detail::TextProperties::TextStyle::Blink::Disable}};

        static constexpr typename std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Inverted> styleInverted[] = {
            {"inverted", detail::TextProperties::TextStyle::Inverted::Enable},
            {"n-inverted", detail::TextProperties::TextStyle::Inverted::Disable},
        };

        static constexpr typename std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Ideogram> styleIdeogram[] = {
            {"i-underlined", detail::TextProperties::TextStyle::Ideogram::Underlined}, {"i-d-underlined", detail::TextProperties::TextStyle::Ideogram::DoubleUnderlined},
            {"i-overlined", detail::TextProperties::TextStyle::Ideogram::Overlined},   {"i-d-overlined", detail::TextProperties::TextStyle::Ideogram::DoubleOverlined},
            {"i-stress", detail::TextProperties::TextStyle::Ideogram::StressMarking},  {"n-i", detail::TextProperties::TextStyle::Ideogram::AllDisable},
        };

        static constexpr typename std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Script> styleScript[] = {
            {"superscript", detail::TextProperties::TextStyle::Script::Superscript},
            {"subscript", detail::TextProperties::TextStyle::Script::Subscript},
            {"n-script", detail::TextProperties::TextStyle::Script::AllDisable}};

        std::uint8_t code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).get_word_from_dict_pairs(styleIntensity));
        if (code != 255) return ApplyStyle(detail::TextProperties::TextStyle::Intensity{code});
        code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).get_word_from_dict_pairs(styleItalic));
        if (code != 255) return ApplyStyle(detail::TextProperties::TextStyle::Italic{code});
        code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).get_word_from_dict_pairs(styleBlink));
        if (code != 255) return ApplyStyle(detail::TextProperties::TextStyle::Blink{code});
        code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).get_word_from_dict_pairs(styleInverted));
        if (code != 255) return ApplyStyle(detail::TextProperties::TextStyle::Inverted{code});
        code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).get_word_from_dict_pairs(styleIdeogram));
        if (code != 255) return ApplyStyle(detail::TextProperties::TextStyle::Ideogram{code});
        code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).get_word_from_dict_pairs(styleScript));
        if (code != 255) return ApplyStyle(detail::TextProperties::TextStyle::Script{code});

        code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).get_word_from_dict_pairs(styleUnderline));
        if (code != 255)
        {
            if (code == (std::uint8_t)detail::TextProperties::TextStyle::Underline::SelectUnderlinedColor)
            {
                detail::TextProperties::TextStyle::UnderlineColor::ColorCube underlineColor = SF_TRY(SelectUnderlinedColorStyle(format));
                return ApplyStyle(underlineColor);
            }
            return ApplyStyle(detail::TextProperties::TextStyle::Underline{code});
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
    [[nodiscard]] std::expected<void, FMTResult> detail::TextPropertiesManager<TChar>::ParseFront(Context::BasicContext<TChar>& context)
    {
        static constexpr std::string_view frontCode[] = {"default", "front0", "front1", "front2", "front3", "front4", "front5", "front6", "front7", "front8", "front9"};

        if (BufferTestAccess(context.Format).IsEqualTo(':'))
        {
            SF_TRY(BufferManip(context.Format).Forward());
            BufferTestManip(context.Format).IgnoreEverySpaces();

            detail::TextProperties::TextFront::FrontID frontID = (std::uint8_t)SF_TRY(BufferUtilsManip(context.Format).get_word_from_list(frontCode));
            return ApplyFront(frontID);
        }
        else
            return ReloadDefaultFront();
        return {};
    }
}
