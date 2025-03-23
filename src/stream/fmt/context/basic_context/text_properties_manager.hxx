#pragma once

#include "stream/fmt/detail/prelude.h"
#include "text_properties_executor.h"
#include "basic_args_interface.h"
#include "stream/fmt/buf/stream.h"
#include "stream/fmt/buf/test_manip.h"
#include "stream/fmt/buf/utils/buffer_utils.h"

namespace stream::fmt::detail {
    class TextPropertiesapplyManager {
    public:
        TextPropertiesapplyManager(ITextPropertiesExecutor& text_properties_executor) : text_properties_executor_{text_properties_executor}, current_context_properties_{} {}

        [[nodiscard]] std::expected<void, FMTResult> terminate() {
            return reload_default();
        }

    public:
        template <typename T>
            requires detail::text_properties_color_can_apply<T>
        [[nodiscard]] std::expected<void, FMTResult> apply_color(const T& modif) {
            current_context_properties_.color.apply(modif);
            return text_properties_executor_.execute_color(modif);
        }
        template <typename T>
            requires detail::text_properties_style_can_apply<T>
        [[nodiscard]] std::expected<void, FMTResult> apply_style(const T& modif) {
            current_context_properties_.style.apply(modif);
            return text_properties_executor_.execute_style(modif);
        }
        template <typename T>
            requires detail::text_properties_front_can_apply<T>
        [[nodiscard]] std::expected<void, FMTResult> apply_front(const T& modif) {
            current_context_properties_.front.apply(modif);
            return text_properties_executor_.execute_front(modif);
        }

        [[nodiscard]] std::expected<void, FMTResult> all_properties_reset() {
            SF_TRY(apply_color_reset());
            SF_TRY(apply_style_reset());
            return apply_front_reset();
        }
        [[nodiscard]] std::expected<void, FMTResult> apply_color_reset() {
            current_context_properties_.color.modify_reset();
            return text_properties_executor_.reset_color();
        }
        [[nodiscard]] std::expected<void, FMTResult> apply_style_reset() {
            current_context_properties_.style.modify_reset();
            return text_properties_executor_.reset_style();
        }
        [[nodiscard]] std::expected<void, FMTResult> apply_front_reset() {
            current_context_properties_.front.modify_reset();
            return text_properties_executor_.reset_front();
        }

    public:
        detail::TextProperties::Properties save() {
            return current_context_properties_;
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> reload_default() {
            SF_TRY(reload_default_color());
            SF_TRY(reload_default_style());
            return reload_default_front();
        }
        [[nodiscard]] std::expected<void, FMTResult> reload_default_color() {
            SF_TRY(reload_default_color_fg());
            return reload_default_color_bg();
        }
        [[nodiscard]] std::expected<void, FMTResult> reload_default_color_fg() {
            return reload_color_fg(detail::TextProperties::TextColor::ColorFG{});
        }
        [[nodiscard]] std::expected<void, FMTResult> reload_default_color_bg() {
            return reload_color_bg(detail::TextProperties::TextColor::ColorBG{});
        }
        [[nodiscard]] std::expected<void, FMTResult> reload_default_style() {
            return reload_style(detail::TextProperties::TextStyle::Style{});
        }
        [[nodiscard]] std::expected<void, FMTResult> reload_default_front() {
            return reload_front(detail::TextProperties::TextFront::Front{});
        }

        [[nodiscard]] std::expected<void, FMTResult> reload(const detail::TextProperties::Properties& target) {
            SF_TRY(reload_color(target.color));
            SF_TRY(reload_style(target.style));
            return reload_front(target.front);
        }
        [[nodiscard]] std::expected<void, FMTResult> reload_color(const detail::TextProperties::TextColor::Color& target) {
            SF_TRY(reload_color_fg(target.fg));
            return reload_color_bg(target.bg);
        }

        [[nodiscard]] std::expected<void, FMTResult> reload_color_fg(const detail::TextProperties::TextColor::ColorFG& target);
        [[nodiscard]] std::expected<void, FMTResult> reload_color_bg(const detail::TextProperties::TextColor::ColorBG& target);
        [[nodiscard]] std::expected<void, FMTResult> reload_style(const detail::TextProperties::TextStyle::Style& target);
        [[nodiscard]] std::expected<void, FMTResult> reload_front(const detail::TextProperties::TextFront::Front& target);

    public:
        ITextPropertiesExecutor& get_text_properties_executor() {
            return text_properties_executor_;
        }
        detail::TextProperties::Properties& get_current_context_properties() {
            return current_context_properties_;
        }

    protected:
        ITextPropertiesExecutor&           text_properties_executor_;
        detail::TextProperties::Properties current_context_properties_;

    public:
        template <typename T>
            requires detail::text_properties_color_can_apply<T>
        [[nodiscard]] inline std::expected<void, FMTResult> ask_apply_color(const T& modif) {
            if (current_context_properties_.color.need_modif(modif)) return apply_color(modif);
            return {};
        }
        template <typename T>
            requires detail::text_properties_style_can_apply<T>
        [[nodiscard]] inline std::expected<void, FMTResult> ask_apply_style(const T& modif) {
            if (current_context_properties_.style.need_modif(modif)) return apply_style(modif);
            return {};
        }
        template <typename T>
            requires detail::text_properties_front_can_apply<T>
        [[nodiscard]] inline std::expected<void, FMTResult> ask_apply_front(const T& modif) {
            if (current_context_properties_.front.need_modif(modif)) return apply_front(modif);
            return {};
        }

        [[nodiscard]] std::expected<void, FMTResult> ask_apply_color(const detail::TextProperties::TextColor::BasicColor& modif) {
            if (current_context_properties_.color.need_modif(modif.fg)) {
                if (current_context_properties_.color.need_modif(modif.bg)) return apply_color(modif);
                return apply_color(modif.fg);
            }
            if (current_context_properties_.color.need_modif(modif.fg)) return apply_color(modif.bg);

            return {};
        }

        [[nodiscard]] std::expected<void, FMTResult> ask_apply_color(const detail::TextProperties::TextColor::ColorCube& modif) {
            if (current_context_properties_.color.need_modif(modif.fg)) {
                if (current_context_properties_.color.need_modif(modif)) return apply_color(modif);
                return apply_color(modif.fg);
            }
            if (current_context_properties_.color.need_modif(modif.fg)) return apply_color(modif.bg);

            return {};
        }

        [[nodiscard]] std::expected<void, FMTResult> ask_apply_color(const detail::TextProperties::TextColor::Color24b& modif) {
            if (current_context_properties_.color.need_modif(modif.fg)) {
                if (current_context_properties_.color.need_modif(modif)) return apply_color(modif);
                return apply_color(modif.fg);
            }
            if (current_context_properties_.color.need_modif(modif.fg)) return apply_color(modif.bg);

            return {};
        }

        [[nodiscard]] std::expected<void, FMTResult> ask_apply_color(const detail::TextProperties::TextColor::ColorFG& modif) {
            return reload_color_fg(modif);
        }
        [[nodiscard]] std::expected<void, FMTResult> ask_apply_color(const detail::TextProperties::TextColor::ColorBG& modif) {
            return reload_color_bg(modif);
        }
        [[nodiscard]] std::expected<void, FMTResult> ask_apply_color(const detail::TextProperties::TextColor::Color& modif) {
            return reload_color(modif);
        }
    };

    template <typename TChar>
    class TextPropertiesManager : public TextPropertiesapplyManager {
    public:
        TextPropertiesManager(ITextPropertiesExecutor& text_properties_executor) : TextPropertiesapplyManager(text_properties_executor) {}

    public:
        [[nodiscard]] std::expected<void, FMTResult> apply_colorOnIndex(context::BasicContext<TChar>& context, std::int32_t index);
        [[nodiscard]] std::expected<void, FMTResult> apply_styleOnIndex(context::BasicContext<TChar>& context, std::int32_t index);
        [[nodiscard]] std::expected<void, FMTResult> apply_frontOnIndex(context::BasicContext<TChar>& context, std::int32_t index);

    public:
        [[nodiscard]] std::expected<void, FMTResult> parse_color(context::BasicContext<TChar>& context);
        [[nodiscard]] std::expected<void, FMTResult> parse_style(context::BasicContext<TChar>& context);
        [[nodiscard]] std::expected<void, FMTResult> parse_front(context::BasicContext<TChar>& context);

    private:
        template <typename T>
        [[nodiscard]] std::expected<T, FMTResult>                                                    get_color_code(buf::StreamView<TChar>& format);
        [[nodiscard]] std::expected<void, FMTResult>                                                 parse_style_named(buf::StreamView<TChar>& format);
        [[nodiscard]] std::expected<TextProperties::TextStyle::UnderlineColor::ColorCube, FMTResult> select_underlined_color_style(buf::StreamView<TChar>& format);
    };
}  // namespace stream::fmt::detail

namespace stream::fmt::detail {
    template <typename TChar>
    template <typename T>
    [[nodiscard]] std::expected<T, FMTResult> detail::TextPropertiesManager<TChar>::get_color_code(buf::StreamView<TChar>& format) {
        static constexpr std::string_view colorCode[] = {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white", "      ", "default"};

        bool         bright = SF_TRY(buf::TestManip(format).is_equal_to_forward('+'));
        std::uint8_t step   = static_cast<std::uint8_t>(bright ? T::BaseBStep : T::BaseStep);
        std::uint8_t code   = (std::uint8_t)SF_TRY(buf::UtilsManip(format).get_word_from_list(colorCode));
        ;
        return static_cast<T>(code + step);
    }
}  // namespace stream::fmt::detail

#include "text_properties_manager_impl.h"
