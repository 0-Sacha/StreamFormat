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
        static void Format(const Detail::TextProperties::ResetProperties, FormatterExecutor& executor)
        {
            executor.TextManager.AllPropertiesReset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<Detail::TextProperties::TextColor::ResetColor, FormatterExecutor>
    {
        static void Format(const Detail::TextProperties::TextColor::ResetColor, FormatterExecutor& executor)
        {
            executor.TextManager.ApplyColorReset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<Detail::TextProperties::TextStyle::ResetStyle, FormatterExecutor>
    {
        static void Format(const Detail::TextProperties::TextStyle::ResetStyle, FormatterExecutor& executor)
        {
            executor.TextManager.ApplyStyleReset();
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<Detail::TextProperties::TextFront::ResetFront, FormatterExecutor>
    {
        static void Format(const Detail::TextProperties::TextFront::ResetFront, FormatterExecutor& executor)
        {
            executor.TextManager.ApplyFrontReset();
        }
    };

    //---------------------------------------//
    //----------------- Ask -----------------//
    //---------------------------------------//

    template <typename T, typename FormatterExecutor>
    requires Detail::TextPropertiesColorIsApply<T>
    struct FormatterType<T, FormatterExecutor>
    {
        static void Format(const T& t, FormatterExecutor& executor)
        {
            executor.TextManager.AskApplyColor(t);
        }
    };

    template <typename T, typename FormatterExecutor>
    requires Detail::TextPropertiesStyleIsApply<T>
    struct FormatterType<T, FormatterExecutor>
    {
        static void Format(const T& t, FormatterExecutor& executor)
        {
            executor.TextManager.AskApplyStyle(t);
        }
    };

    template <typename T, typename FormatterExecutor>
    requires Detail::TextPropertiesFrontIsApply<T>
    struct FormatterType<T, FormatterExecutor>
    {
        static void Format(const T& t, FormatterExecutor& executor)
        {
            executor.TextManager.AskApplyFront(t);
        }
    };
}
