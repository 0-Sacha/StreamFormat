#pragma once

#include "BasicFormatterContext.h"

namespace ProjectCore::FMT
{
    //------------------------------------------//
    //----------------- Resets -----------------//
    //------------------------------------------//

    template <typename FormatterContext>
    struct FormatterType<Detail::TextProperties::ResetProperties, FormatterContext>
    {
        static void Format(const Detail::TextProperties::ResetProperties, FormatterContext& context)
        {
            context.GetTextProperties().AllPropertiesReset();
        }
    };

    template <typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextColor::ResetColor, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextColor::ResetColor, FormatterContext& context)
        {
            context.GetTextProperties().ApplyColorReset();
        }
    };

    template <typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::ResetStyle, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::ResetStyle, FormatterContext& context)
        {
            context.GetTextProperties().ApplyStyleReset();
        }
    };

    template <typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextFront::ResetFront, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextFront::ResetFront, FormatterContext& context)
        {
            context.GetTextProperties().ApplyFrontReset();
        }
    };

    //---------------------------------------//
    //----------------- Ask -----------------//
    //---------------------------------------//

    template <typename T, typename FormatterContext>
    requires Detail::TextPropertiesColorIsApply<T>
    struct FormatterType<T, FormatterContext>
    {
        static void Format(const T& t, FormatterContext& context)
        {
            context.GetTextProperties().AskApplyColor(t);
        }
    };

    template <typename T, typename FormatterContext>
    requires Detail::TextPropertiesStyleIsApply<T>
    struct FormatterType<T, FormatterContext>
    {
        static void Format(const T& t, FormatterContext& context)
        {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };

    template <typename T, typename FormatterContext>
    requires Detail::TextPropertiesFrontIsApply<T>
    struct FormatterType<T, FormatterContext>
    {
        static void Format(const T& t, FormatterContext& context)
        {
            context.GetTextProperties().AskApplyFront(t);
        }
    };
}
