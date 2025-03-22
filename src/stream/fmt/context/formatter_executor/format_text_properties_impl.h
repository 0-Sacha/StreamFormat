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
            return executor.TextManager.ApplyColorReset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<detail::TextProperties::TextStyle::ResetStyle, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const detail::TextProperties::TextStyle::ResetStyle, FormatterExecutor& executor)
        {
            return executor.TextManager.ApplyStyleReset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<detail::TextProperties::TextFront::reset_front, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const detail::TextProperties::TextFront::reset_front, FormatterExecutor& executor)
        {
            return executor.TextManager.ApplyFrontReset();
        }
    };

    //---------------------------------------//
    //----------------- Ask -----------------//
    //---------------------------------------//

    template <typename T, typename FormatterExecutor>
    requires detail::TextPropertiesColorIsApply<T>
    struct FormatterType<T, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const T& t, FormatterExecutor& executor)
        {
            return executor.TextManager.AskApplyColor(t);
        }
    };

    template <typename T, typename FormatterExecutor>
    requires detail::TextPropertiesStyleIsApply<T>
    struct FormatterType<T, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const T& t, FormatterExecutor& executor)
        {
            return executor.TextManager.AskApplyStyle(t);
        }
    };

    template <typename T, typename FormatterExecutor>
    requires detail::TextPropertiesFrontIsApply<T>
    struct FormatterType<T, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const T& t, FormatterExecutor& executor)
        {
            return executor.TextManager.AskApplyFront(t);
        }
    };
}
