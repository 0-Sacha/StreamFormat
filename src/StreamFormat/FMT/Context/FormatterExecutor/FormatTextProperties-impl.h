#pragma once

#include "BasicFormatterExecutor.h"

namespace StreamFormat::FMT
{
    //------------------------------------------//
    //----------------- Resets -----------------//
    //------------------------------------------//

    template <typename FormatterExecutor>
    struct FormatterType<Detail::TextProperties::ResetProperties, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> Format(const Detail::TextProperties::ResetProperties, FormatterExecutor& executor)
        {
            return executor.TextManager.AllPropertiesReset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<Detail::TextProperties::TextColor::ResetColor, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> Format(const Detail::TextProperties::TextColor::ResetColor, FormatterExecutor& executor)
        {
            return executor.TextManager.ApplyColorReset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<Detail::TextProperties::TextStyle::ResetStyle, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> Format(const Detail::TextProperties::TextStyle::ResetStyle, FormatterExecutor& executor)
        {
            return executor.TextManager.ApplyStyleReset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<Detail::TextProperties::TextFront::ResetFront, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> Format(const Detail::TextProperties::TextFront::ResetFront, FormatterExecutor& executor)
        {
            return executor.TextManager.ApplyFrontReset();
        }
    };

    //---------------------------------------//
    //----------------- Ask -----------------//
    //---------------------------------------//

    template <typename T, typename FormatterExecutor>
    requires Detail::TextPropertiesColorIsApply<T>
    struct FormatterType<T, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> Format(const T& t, FormatterExecutor& executor)
        {
            return executor.TextManager.AskApplyColor(t);
        }
    };

    template <typename T, typename FormatterExecutor>
    requires Detail::TextPropertiesStyleIsApply<T>
    struct FormatterType<T, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> Format(const T& t, FormatterExecutor& executor)
        {
            return executor.TextManager.AskApplyStyle(t);
        }
    };

    template <typename T, typename FormatterExecutor>
    requires Detail::TextPropertiesFrontIsApply<T>
    struct FormatterType<T, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> Format(const T& t, FormatterExecutor& executor)
        {
            return executor.TextManager.AskApplyFront(t);
        }
    };
}
