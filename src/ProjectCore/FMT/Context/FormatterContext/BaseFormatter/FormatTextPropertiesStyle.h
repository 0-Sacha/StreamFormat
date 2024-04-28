#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/BasicFormatterContext.h"

namespace ProjectCore::FMT
{
    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::ResetProperties, FormatterContext>
    {
        static void Format(const Detail::TextProperties::ResetProperties, FormatterContext& context) {
            context.GetTextProperties().AllPropertiesReset();
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::ResetStyle, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::ResetStyle, FormatterContext& context) {
            context.GetTextProperties().ApplyStyleReset();
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::Style, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::Style t, FormatterContext& context) {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::Intensity, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::Intensity t, FormatterContext& context) {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::Italic, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::Italic t, FormatterContext& context) {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::Underline, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::Underline t, FormatterContext& context) {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::UnderlineColor::Color, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::UnderlineColor::Color t, FormatterContext& context) {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::UnderlineColor::ColorCube, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::UnderlineColor::ColorCube t, FormatterContext& context) {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::UnderlineColor::Color24b, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::UnderlineColor::Color24b t, FormatterContext& context) {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::Blink, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::Blink t, FormatterContext& context) {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::Inverted, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::Inverted t, FormatterContext& context) {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::Ideogram, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::Ideogram t, FormatterContext& context) {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextStyle::Script, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextStyle::Script t, FormatterContext& context) {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };
}
