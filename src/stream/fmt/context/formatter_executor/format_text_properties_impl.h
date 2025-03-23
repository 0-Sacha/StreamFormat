#pragma once

#include "basic_formatter_executor.h"

namespace stream::fmt
{
    //------------------------------------------//
    //----------------- Resets -----------------//
    //------------------------------------------//

    template <typename FormatterExecutor>
    struct FormatterType<detail::TextProperties::ResetProperties, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const detail::TextProperties::ResetProperties, FormatterExecutor& executor)
        {
            return executor.TextManager.all_properties_reset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<detail::TextProperties::TextColor::reset_color, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const detail::TextProperties::TextColor::reset_color, FormatterExecutor& executor)
        {
            return executor.TextManager.apply_color_reset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<detail::TextProperties::TextStyle::reset_style, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const detail::TextProperties::TextStyle::reset_style, FormatterExecutor& executor)
        {
            return executor.TextManager.apply_style_reset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<detail::TextProperties::TextFront::reset_front, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const detail::TextProperties::TextFront::reset_front, FormatterExecutor& executor)
        {
            return executor.TextManager.apply_front_reset();
        }
    };

    //---------------------------------------//
    //----------------- Ask -----------------//
    //---------------------------------------//

    template <typename T, typename FormatterExecutor>
    requires detail::TextPropertiesColorIsapply<T>
    struct FormatterType<T, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const T& t, FormatterExecutor& executor)
        {
            return executor.TextManager.ask_apply_color(t);
        }
    };

    template <typename T, typename FormatterExecutor>
    requires detail::TextPropertiesStyleIsapply<T>
    struct FormatterType<T, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const T& t, FormatterExecutor& executor)
        {
            return executor.TextManager.ask_apply_style(t);
        }
    };

    template <typename T, typename FormatterExecutor>
    requires detail::TextPropertiesFrontIsapply<T>
    struct FormatterType<T, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const T& t, FormatterExecutor& executor)
        {
            return executor.TextManager.ask_apply_front(t);
        }
    };
}
