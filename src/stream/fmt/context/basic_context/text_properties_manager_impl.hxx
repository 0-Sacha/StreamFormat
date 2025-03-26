#pragma once

#include "text_properties_manager.hxx"

#include "stream/fmt/buf/manip.hxx"
#include "stream/fmt/buf/manip_io.hxx"
#include "stream/fmt/buf/test_manip.hxx"
#include "stream/fmt/buf/fmt_manip_io.hxx"
#include "stream/fmt/buf/utils/buffer_utils.hxx"

namespace stream::fmt::detail {
    template <typename TChar>
    void detail::TextPropertiesManager<TChar>::apply_color_on_index(context::BasicContext<TChar>& context, std::int32_t index) {
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextColor::Color>(
            index, [this](const detail::TextProperties::TextColor::Color& data) { this->reload_color(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextColor::BasicColorFG>(
            index, [this](const detail::TextProperties::TextColor::BasicColorFG& data) { this->ask_apply_color(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextColor::BasicColorBG>(
            index, [this](const detail::TextProperties::TextColor::BasicColorBG& data) { this->ask_apply_color(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextColor::ColorCubeFG>(
            index, [this](const detail::TextProperties::TextColor::ColorCubeFG& data) { this->ask_apply_color(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextColor::ColorCubeBG>(
            index, [this](const detail::TextProperties::TextColor::ColorCubeBG& data) { this->ask_apply_color(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextColor::Color24bFG>(
            index, [this](const detail::TextProperties::TextColor::Color24bFG& data) { this->ask_apply_color(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextColor::Color24bBG>(
            index, [this](const detail::TextProperties::TextColor::Color24bBG& data) { this->ask_apply_color(data); });
    }

    template <typename TChar>
    void detail::TextPropertiesManager<TChar>::apply_front_on_index(context::BasicContext<TChar>& context, std::int32_t index) {
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextFront::Front>(
            index, [this](const detail::TextProperties::TextFront::Front& data) { this->reload_front(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextFront::FrontID>(
            index, [this](const detail::TextProperties::TextFront::FrontID& data) { this->ask_apply_front(data); });
    }

    template <typename TChar>
    void detail::TextPropertiesManager<TChar>::apply_style_on_index(context::BasicContext<TChar>& context, std::int32_t index) {
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextStyle::Style>(
            index, [this](const detail::TextProperties::TextStyle::Style& data) { return this->reload_style(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextStyle::Intensity>(
            index, [this](const detail::TextProperties::TextStyle::Intensity& data) { return this->ask_apply_style(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextStyle::Italic>(
            index, [this](const detail::TextProperties::TextStyle::Italic& data) { return this->ask_apply_style(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextStyle::Underline>(
            index, [this](const detail::TextProperties::TextStyle::Underline& data) { return this->ask_apply_style(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextStyle::Blink>(
            index, [this](const detail::TextProperties::TextStyle::Blink& data) { return this->ask_apply_style(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextStyle::Inverted>(
            index, [this](const detail::TextProperties::TextStyle::Inverted& data) { return this->ask_apply_style(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextStyle::Ideogram>(
            index, [this](const detail::TextProperties::TextStyle::Ideogram& data) { return this->ask_apply_style(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextStyle::Script>(
            index, [this](const detail::TextProperties::TextStyle::Script& data) { return this->ask_apply_style(data); });

        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextStyle::UnderlineColor::ColorCube>(
            index, [this](const detail::TextProperties::TextStyle::UnderlineColor::ColorCube& data) { this->ask_apply_style(data); });
        context.args_interface.template run_func_from_type_at<detail::TextProperties::TextStyle::UnderlineColor::Color24b>(
            index, [this](const detail::TextProperties::TextStyle::UnderlineColor::Color24b& data) { this->ask_apply_style(data); });
    }

    template <typename TChar>
    void detail::TextPropertiesManager<TChar>::parse_color(context::BasicContext<TChar>& context) {
        if (buf::TestAccess(context.fmtstream).is_equal_to(':')) {
            buf::Manip(context.fmtstream).forward();
            buf::TestManip(context.fmtstream).ignore_every_spaces();
            if (buf::TestAccess(context.fmtstream).is_equal_to('{')) {
                buf::Manip(context.fmtstream).forward();
                std::optional<std::int32_t> idx = context.get_format_index();
                if (idx.has_value() == false) {
                }
                apply_color_on_index(context, idx.value());
                buf::TestManip(context.fmtstream).skip_one_of('}');
            } else {
                std::optional<std::size_t> color_fg = get_color_code(context.fmtstream, static_cast<std::size_t>(TextProperties::TextColor::BasicColorFG::BaseStep),
                                                                     static_cast<std::size_t>(TextProperties::TextColor::BasicColorFG::BaseBrightStep));
                buf::FMTParamsManip(context.fmtstream).param_go_to('-', ',');
                if (buf::TestAccess(context.fmtstream).is_equal_to('-')) {
                    buf::Manip(context.fmtstream).forward();
                    buf::TestManip(context.fmtstream).ignore_every_spaces();
                    std::optional<std::size_t> color_bg = get_color_code(context.fmtstream, static_cast<std::size_t>(TextProperties::TextColor::BasicColorBG::BaseStep),
                                                                         static_cast<std::size_t>(TextProperties::TextColor::BasicColorBG::BaseBrightStep));
                    if (color_bg.has_value() && color_fg.has_value()) {
                        return ask_apply_color(detail::TextProperties::TextColor::BasicColor{static_cast<TextProperties::TextColor::BasicColorFG>(color_fg.value()),
                                                                                             static_cast<TextProperties::TextColor::BasicColorBG>(color_bg.value())});
                    } else {
                        return reload_default_color();
                    }
                } else {
                    if (color_fg.has_value()) {
                        return ask_apply_color(static_cast<TextProperties::TextColor::BasicColorFG>(color_fg.value()));
                    } else {
                        return reload_default_color();
                    }
                }
            }
        } else {
            return reload_default_color();
        }
    }

    template <typename TChar>
    void detail::TextPropertiesManager<TChar>::parse_style(context::BasicContext<TChar>& context) {
        if (buf::TestAccess(context.fmtstream).is_equal_to(':')) {
            buf::Manip(context.fmtstream).forward();
            if (!buf::TestAccess(context.fmtstream).is_equal_to('}', ',')) {
                bool loop = true;
                while (loop) {
                    buf::TestManip(context.fmtstream).ignore_every_spaces();
                    if (buf::TestAccess(context.fmtstream).is_equal_to('{')) {
                        buf::Manip(context.fmtstream).forward();
                        std::optional<std::int32_t> idx = context.get_format_index();
                        apply_style_on_index(context, idx.value());
                        buf::TestManip(context.fmtstream).skip_one_of('}');
                    } else {
                        parse_style_named(context.fmtstream);
                    }
                    buf::FMTParamsManip(context.fmtstream).param_go_to('|', ',');
                    loop = buf::TestAccess(context.fmtstream).is_equal_to('|');
                    buf::Manip(context.fmtstream).forward();
                    buf::TestManip(context.fmtstream).ignore_every_spaces();
                }
            } else {
                return reload_default_style();
            }
        } else {
            return reload_default_style();
        }
    }

    template <typename TChar>
    void detail::TextPropertiesManager<TChar>::parse_style_named(buf::StreamView<TChar>& format) {
        buf::UtilsManip utils(format);

        static constexpr std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Intensity> styleIntensity[] = {
            {       "bold",   detail::TextProperties::TextStyle::Intensity::Bold},
            {        "dim",    detail::TextProperties::TextStyle::Intensity::Dim},
            {"n-intensity", detail::TextProperties::TextStyle::Intensity::Normal}
        };

        static constexpr std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Italic> styleItalic[] = {
            {  "italic",  detail::TextProperties::TextStyle::Italic::enable},
            {"n-italic", detail::TextProperties::TextStyle::Italic::Disable}
        };

        // TODO: magic values
        static constexpr typename std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Underline> styleUnderline[] = {
            {  "underlined",            detail::TextProperties::TextStyle::Underline::Underlined},
            {"d-underlined",       detail::TextProperties::TextStyle::Underline::DoubleUnerlined},
            {"n-underlined",               detail::TextProperties::TextStyle::Underline::Disable},
            {"c-underlined", detail::TextProperties::TextStyle::Underline::SelectUnderlinedColor}
        };

        static constexpr typename std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Blink> styleBlink[] = {
            {"slowblink", detail::TextProperties::TextStyle::Blink::SlowBlink},
            {"fastblink", detail::TextProperties::TextStyle::Blink::FastBlink},
            {  "n-blink",   detail::TextProperties::TextStyle::Blink::Disable}
        };

        static constexpr typename std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Inverted> styleInverted[] = {
            {  "inverted",  detail::TextProperties::TextStyle::Inverted::enable},
            {"n-inverted", detail::TextProperties::TextStyle::Inverted::Disable},
        };

        static constexpr typename std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Ideogram> styleIdeogram[] = {
            {  "i-underlined",       detail::TextProperties::TextStyle::Ideogram::Underlined},
            {"i-d-underlined", detail::TextProperties::TextStyle::Ideogram::DoubleUnderlined},
            {   "i-overlined",        detail::TextProperties::TextStyle::Ideogram::Overlined},
            { "i-d-overlined",  detail::TextProperties::TextStyle::Ideogram::DoubleOverlined},
            {      "i-stress",    detail::TextProperties::TextStyle::Ideogram::StressMarking},
            {           "n-i",       detail::TextProperties::TextStyle::Ideogram::AllDisable},
        };

        static constexpr typename std::pair<std::basic_string_view<TChar>, detail::TextProperties::TextStyle::Script> styleScript[] = {
            {"superscript", detail::TextProperties::TextStyle::Script::Superscript},
            {  "subscript",   detail::TextProperties::TextStyle::Script::Subscript},
            {   "n-script",  detail::TextProperties::TextStyle::Script::AllDisable}
        };

        std::uint8_t code = (std::uint8_t)buf::UtilsManip(format).get_word_from_dict_pairs(styleIntensity);
        if (code != 255) return apply_style(detail::TextProperties::TextStyle::Intensity{code});
        code = (std::uint8_t)buf::UtilsManip(format).get_word_from_dict_pairs(styleItalic);
        if (code != 255) return apply_style(detail::TextProperties::TextStyle::Italic{code});
        code = (std::uint8_t)buf::UtilsManip(format).get_word_from_dict_pairs(styleBlink);
        if (code != 255) return apply_style(detail::TextProperties::TextStyle::Blink{code});
        code = (std::uint8_t)buf::UtilsManip(format).get_word_from_dict_pairs(styleInverted);
        if (code != 255) return apply_style(detail::TextProperties::TextStyle::Inverted{code});
        code = (std::uint8_t)buf::UtilsManip(format).get_word_from_dict_pairs(styleIdeogram);
        if (code != 255) return apply_style(detail::TextProperties::TextStyle::Ideogram{code});
        code = (std::uint8_t)buf::UtilsManip(format).get_word_from_dict_pairs(styleScript);
        if (code != 255) return apply_style(detail::TextProperties::TextStyle::Script{code});

        code = (std::uint8_t)buf::UtilsManip(format).get_word_from_dict_pairs(styleUnderline);
        if (code != 255) {
            if (code == (std::uint8_t)detail::TextProperties::TextStyle::Underline::SelectUnderlinedColor) {
                detail::TextProperties::TextStyle::UnderlineColor::ColorCube underlineColor = select_underlined_color_style(format);
                return apply_style(underlineColor);
            }
            return apply_style(detail::TextProperties::TextStyle::Underline{code});
        }
    }

    template <typename TChar>
    TextProperties::TextStyle::UnderlineColor::ColorCube TextPropertiesManager<TChar>::select_underlined_color_style(buf::StreamView<TChar>& format) {
        // TODO
        // FIXME
        throw std::runtime_error("fmt error: FunctionNotImpl");
    }

    template <typename TChar>
    void detail::TextPropertiesManager<TChar>::parse_front(context::BasicContext<TChar>& context) {
        static constexpr std::string_view frontCode[] = {"default", "front0", "front1", "front2", "front3", "front4", "front5", "front6", "front7", "front8", "front9"};

        if (buf::TestAccess(context.fmtstream).is_equal_to(':')) {
            buf::Manip(context.fmtstream).forward();
            buf::TestManip(context.fmtstream).ignore_every_spaces();

            std::optional<std::size_t> front_id = buf::UtilsManip(context.fmtstream).get_word_from_list(frontCode);

            if (front_id.has_value()) {
                apply_front(static_cast<detail::TextProperties::TextFront::FrontID>(front_id.value()));
                return;
            }
        }
        reload_default_front();
    }
}  // namespace stream::fmt::detail
