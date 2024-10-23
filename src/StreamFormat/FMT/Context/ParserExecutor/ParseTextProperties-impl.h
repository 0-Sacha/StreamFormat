#pragma once

#include "BasicParserExecutor.h"

namespace StreamFormat::FMT
{
    //------------------------------------------//
    //----------------- Resets -----------------//
    //------------------------------------------//

    template <typename ParserExecutor>
    struct ParserType<Detail::TextProperties::ResetProperties, ParserExecutor>
    {
        static void Parse(Detail::TextProperties::ResetProperties, ParserExecutor& executor)
        {
            executor.TextManager.AllPropertiesReset();
        }
    };

    template <typename ParserExecutor>
    struct ParserType<Detail::TextProperties::TextColor::ResetColor, ParserExecutor>
    {
        static void Parse(Detail::TextProperties::TextColor::ResetColor, ParserExecutor& executor)
        {
            executor.TextManager.ApplyColorReset();
        }
    };

    template <typename ParserExecutor>
    struct ParserType<Detail::TextProperties::TextStyle::ResetStyle, ParserExecutor>
    {
        static void Parse(Detail::TextProperties::TextStyle::ResetStyle, ParserExecutor& executor)
        {
            executor.TextManager.ApplyStyleReset();
        }
    };

    template <typename ParserExecutor>
    struct ParserType<Detail::TextProperties::TextFront::ResetFront, ParserExecutor>
    {
        static void Parse(Detail::TextProperties::TextFront::ResetFront, ParserExecutor& executor)
        {
            executor.TextManager.ApplyFrontReset();
        }
    };

    //---------------------------------------//
    //----------------- Ask -----------------//
    //---------------------------------------//

    template <typename T, typename ParserExecutor>
    requires Detail::TextPropertiesColorIsApply<T>
    struct ParserType<T, ParserExecutor>
    {
        static void Parse(T& t, ParserExecutor& executor)
        {
            executor.TextManager.AskApplyColor(t);
        }
    };

    template <typename T, typename ParserExecutor>
    requires Detail::TextPropertiesStyleIsApply<T>
    struct ParserType<T, ParserExecutor>
    {
        static void Parse(T& t, ParserExecutor& executor)
        {
            executor.TextManager.AskApplyStyle(t);
        }
    };

    template <typename T, typename ParserExecutor>
    requires Detail::TextPropertiesFrontIsApply<T>
    struct ParserType<T, ParserExecutor>
    {
        static void Parse(T& t, ParserExecutor& executor)
        {
            executor.TextManager.AskApplyFront(t);
        }
    };
}
