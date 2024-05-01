#pragma once

#include "BasicParserContext.h"

namespace ProjectCore::FMT
{
    //------------------------------------------//
    //----------------- Resets -----------------//
    //------------------------------------------//

    template <typename ParserContext>
    struct ParserType<Detail::TextProperties::ResetProperties, ParserContext>
    {
        static void Parse(Detail::TextProperties::ResetProperties, ParserContext& context)
        {
            context.GetTextProperties().AllPropertiesReset();
        }
    };

    template <typename ParserContext>
    struct ParserType<Detail::TextProperties::TextColor::ResetColor, ParserContext>
    {
        static void Parse(Detail::TextProperties::TextColor::ResetColor, ParserContext& context)
        {
            context.GetTextProperties().ApplyColorReset();
        }
    };

    template <typename ParserContext>
    struct ParserType<Detail::TextProperties::TextStyle::ResetStyle, ParserContext>
    {
        static void Parse(Detail::TextProperties::TextStyle::ResetStyle, ParserContext& context)
        {
            context.GetTextProperties().ApplyStyleReset();
        }
    };

    template <typename ParserContext>
    struct ParserType<Detail::TextProperties::TextFront::ResetFront, ParserContext>
    {
        static void Parse(Detail::TextProperties::TextFront::ResetFront, ParserContext& context)
        {
            context.GetTextProperties().ApplyFrontReset();
        }
    };

    //---------------------------------------//
    //----------------- Ask -----------------//
    //---------------------------------------//

    template <typename T, typename ParserContext>
    requires Detail::TextPropertiesColorIsApply<T>
    struct ParserType<T, ParserContext>
    {
        static void Parse(T& t, ParserContext& context)
        {
            context.GetTextProperties().AskApplyColor(t);
        }
    };

    template <typename T, typename ParserContext>
    requires Detail::TextPropertiesStyleIsApply<T>
    struct ParserType<T, ParserContext>
    {
        static void Parse(T& t, ParserContext& context)
        {
            context.GetTextProperties().AskApplyStyle(t);
        }
    };

    template <typename T, typename ParserContext>
    requires Detail::TextPropertiesFrontIsApply<T>
    struct ParserType<T, ParserContext>
    {
        static void Parse(T& t, ParserContext& context)
        {
            context.GetTextProperties().AskApplyFront(t);
        }
    };
}
