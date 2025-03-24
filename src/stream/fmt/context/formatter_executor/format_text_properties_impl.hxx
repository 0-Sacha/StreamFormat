#pragma once

#include "basic_formatter_executor.hxx"

namespace stream::fmt {
    //------------------------------------------//
    //----------------- Resets -----------------//
    //------------------------------------------//

    template <typename FormatterExecutor>
    struct FormatterType<detail::TextProperties::ResetProperties, FormatterExecutor> {
        static void format(const detail::TextProperties::ResetProperties, FormatterExecutor& executor) {
            return executor.text_manager.all_properties_reset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<detail::TextProperties::TextColor::reset_color, FormatterExecutor> {
        static void format(const detail::TextProperties::TextColor::reset_color, FormatterExecutor& executor) {
            return executor.text_manager.apply_color_reset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<detail::TextProperties::TextStyle::reset_style, FormatterExecutor> {
        static void format(const detail::TextProperties::TextStyle::reset_style, FormatterExecutor& executor) {
            return executor.text_manager.apply_style_reset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<detail::TextProperties::TextFront::ResetFront, FormatterExecutor> {
        static void format(const detail::TextProperties::TextFront::ResetFront, FormatterExecutor& executor) {
            return executor.text_manager.apply_front_reset();
        }
    };

    //---------------------------------------//
    //----------------- Ask -----------------//
    //---------------------------------------//

    template <typename T, typename FormatterExecutor>
        requires detail::text_properties_color_is_apply<T>
    struct FormatterType<T, FormatterExecutor> {
        static void format(const T& t, FormatterExecutor& executor) {
            return executor.text_manager.ask_apply_color(t);
        }
    };

    template <typename T, typename FormatterExecutor>
        requires detail::TextPropertiesStyleIsapply<T>
    struct FormatterType<T, FormatterExecutor> {
        static void format(const T& t, FormatterExecutor& executor) {
            return executor.text_manager.ask_apply_style(t);
        }
    };

    template <typename T, typename FormatterExecutor>
        requires detail::TextPropertiesFrontIsapply<T>
    struct FormatterType<T, FormatterExecutor> {
        static void format(const T& t, FormatterExecutor& executor) {
            return executor.text_manager.ask_apply_front(t);
        }
    };
}  // namespace stream::fmt
