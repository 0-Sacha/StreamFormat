#pragma once

#include "stream/fmt/detail/prelude.hxx"
#include "text_properties_executor.hxx"
#include "basic_args_interface.hxx"
#include "stream/fmt/buf/stream.hxx"
#include "stream/fmt/buf/test_manip.hxx"
#include "stream/fmt/buf/utils/buffer_utils.hxx"

namespace stream::fmt::detail {
    class TextPropertiesapplyManager {
    public:
        TextPropertiesapplyManager(ITextPropertiesExecutor& text_properties_executor) : text_properties_executor_{text_properties_executor}, current_context_properties_{} {}

        void terminate() {
            return reload_default();
        }

    public:
        template <typename T>
            requires detail::text_properties_color_can_apply<T>
        void apply_color(const T& modif) {
            current_context_properties_.color.apply(modif);
            return text_properties_executor_.execute_color(modif);
        }
        template <typename T>
            requires detail::text_properties_style_can_apply<T>
        void apply_style(const T& modif) {
            current_context_properties_.style.apply(modif);
            return text_properties_executor_.execute_style(modif);
        }
        template <typename T>
            requires detail::text_properties_front_can_apply<T>
        void apply_front(const T& modif) {
            current_context_properties_.front.apply(modif);
            return text_properties_executor_.execute_front(modif);
        }

        void all_properties_reset() {
            apply_color_reset();
            apply_style_reset();
            return apply_front_reset();
        }
        void apply_color_reset() {
            current_context_properties_.color.modify_reset();
            return text_properties_executor_.reset_color();
        }
        void apply_style_reset() {
            current_context_properties_.style.modify_reset();
            return text_properties_executor_.reset_style();
        }
        void apply_front_reset() {
            current_context_properties_.front.modify_reset();
            return text_properties_executor_.reset_front();
        }

    public:
        detail::TextProperties::Properties save() {
            return current_context_properties_;
        }

    public:
        void reload_default() {
            reload_default_color();
            reload_default_style();
            return reload_default_front();
        }
        void reload_default_color() {
            reload_default_color_fg();
            return reload_default_color_bg();
        }
        void reload_default_color_fg() {
            return reload_color_fg(detail::TextProperties::TextColor::ColorFG{});
        }
        void reload_default_color_bg() {
            return reload_color_bg(detail::TextProperties::TextColor::ColorBG{});
        }
        void reload_default_style() {
            return reload_style(detail::TextProperties::TextStyle::Style{});
        }
        void reload_default_front() {
            return reload_front(detail::TextProperties::TextFront::Front{});
        }

        void reload(const detail::TextProperties::Properties& target) {
            reload_color(target.color);
            reload_style(target.style);
            return reload_front(target.front);
        }
        void reload_color(const detail::TextProperties::TextColor::Color& target) {
            reload_color_fg(target.fg);
            return reload_color_bg(target.bg);
        }

        void reload_color_fg(const detail::TextProperties::TextColor::ColorFG& target);
        void reload_color_bg(const detail::TextProperties::TextColor::ColorBG& target);
        void reload_style(const detail::TextProperties::TextStyle::Style& target);
        void reload_front(const detail::TextProperties::TextFront::Front& target);

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
        void ask_apply_color(const T& modif) {
            if (current_context_properties_.color.need_modif(modif)) return apply_color(modif);
        }
        template <typename T>
            requires detail::text_properties_style_can_apply<T>
        void ask_apply_style(const T& modif) {
            if (current_context_properties_.style.need_modif(modif)) return apply_style(modif);
        }
        template <typename T>
            requires detail::text_properties_front_can_apply<T>
        void ask_apply_front(const T& modif) {
            if (current_context_properties_.front.need_modif(modif)) return apply_front(modif);
        }

        void ask_apply_color(const detail::TextProperties::TextColor::BasicColor& modif) {
            if (current_context_properties_.color.need_modif(modif.fg)) {
                if (current_context_properties_.color.need_modif(modif.bg)) return apply_color(modif);
                return apply_color(modif.fg);
            }
            if (current_context_properties_.color.need_modif(modif.fg)) return apply_color(modif.bg);
        }

        void ask_apply_color(const detail::TextProperties::TextColor::ColorCube& modif) {
            if (current_context_properties_.color.need_modif(modif.fg)) {
                if (current_context_properties_.color.need_modif(modif)) return apply_color(modif);
                return apply_color(modif.fg);
            }
            if (current_context_properties_.color.need_modif(modif.fg)) return apply_color(modif.bg);
        }

        void ask_apply_color(const detail::TextProperties::TextColor::Color24b& modif) {
            if (current_context_properties_.color.need_modif(modif.fg)) {
                if (current_context_properties_.color.need_modif(modif)) return apply_color(modif);
                return apply_color(modif.fg);
            }
            if (current_context_properties_.color.need_modif(modif.fg)) return apply_color(modif.bg);
        }

        void ask_apply_color(const detail::TextProperties::TextColor::ColorFG& modif) {
            return reload_color_fg(modif);
        }
        void ask_apply_color(const detail::TextProperties::TextColor::ColorBG& modif) {
            return reload_color_bg(modif);
        }
        void ask_apply_color(const detail::TextProperties::TextColor::Color& modif) {
            return reload_color(modif);
        }
    };

    template <typename TChar>
    class TextPropertiesManager : public TextPropertiesapplyManager {
    public:
        TextPropertiesManager(ITextPropertiesExecutor& text_properties_executor) : TextPropertiesapplyManager(text_properties_executor) {}

    public:
        void apply_color_on_index(context::BasicContext<TChar>& context, std::int32_t index);
        void apply_style_on_index(context::BasicContext<TChar>& context, std::int32_t index);
        void apply_front_on_index(context::BasicContext<TChar>& context, std::int32_t index);

    public:
        void parse_color(context::BasicContext<TChar>& context, buf::StreamView<TChar>& stream);
        void parse_style(context::BasicContext<TChar>& context, buf::StreamView<TChar>& stream);
        void parse_front(context::BasicContext<TChar>& context, buf::StreamView<TChar>& stream);

    private:
        std::optional<std::size_t>                           get_color_code(buf::StreamView<TChar>& format, std::size_t base, std::size_t brightbase);
        void                                                 parse_style_named(buf::StreamView<TChar>& format);
        TextProperties::TextStyle::UnderlineColor::ColorCube select_underlined_color_style(buf::StreamView<TChar>& format);
    };
}  // namespace stream::fmt::detail

namespace stream::fmt::detail {
    template <typename TChar>
    std::optional<std::size_t> detail::TextPropertiesManager<TChar>::get_color_code(buf::StreamView<TChar>& format, std::size_t base, std::size_t brightbase) {
        static constexpr std::string_view colorCode[] = {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white", "      ", "default"};

        bool                       bright     = buf::TestManip(format).is_equal_to_forward('+');
        std::size_t                step       = bright ? brightbase : base;
        std::optional<std::size_t> color_code = buf::UtilsManip(format).get_word_from_list(colorCode);
        if (color_code.has_value() == false) {
            return std::nullopt;
        }
        return color_code.value() + step;
    }
}  // namespace stream::fmt::detail

#include "text_properties_manager_impl.hxx"
