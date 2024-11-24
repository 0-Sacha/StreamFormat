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
        [[nodiscard]] static inline std::expected<void, FMTResult> Parse(Detail::TextProperties::ResetProperties, ParserExecutor& executor)
        {
            return executor.TextManager.AllPropertiesReset();
        }
    };

    template <typename ParserExecutor>
    struct ParserType<Detail::TextProperties::TextColor::ResetColor, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Parse(Detail::TextProperties::TextColor::ResetColor, ParserExecutor& executor)
        {
            return executor.TextManager.ApplyColorReset();
        }
    };

    template <typename ParserExecutor>
    struct ParserType<Detail::TextProperties::TextStyle::ResetStyle, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Parse(Detail::TextProperties::TextStyle::ResetStyle, ParserExecutor& executor)
        {
            return executor.TextManager.ApplyStyleReset();
        }
    };

    template <typename ParserExecutor>
    struct ParserType<Detail::TextProperties::TextFront::ResetFront, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Parse(Detail::TextProperties::TextFront::ResetFront, ParserExecutor& executor)
        {
            return executor.TextManager.ApplyFrontReset();
        }
    };

    //---------------------------------------//
    //----------------- Ask -----------------//
    //---------------------------------------//

    template <typename T, typename ParserExecutor>
    requires Detail::TextPropertiesColorIsApply<T>
    struct ParserType<T, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Parse(T& t, ParserExecutor& executor)
        {
            return executor.TextManager.AskApplyColor(t);
        }
    };

    template <typename T, typename ParserExecutor>
    requires Detail::TextPropertiesStyleIsApply<T>
    struct ParserType<T, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Parse(T& t, ParserExecutor& executor)
        {
            return executor.TextManager.AskApplyStyle(t);
        }
    };

    template <typename T, typename ParserExecutor>
    requires Detail::TextPropertiesFrontIsApply<T>
    struct ParserType<T, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Parse(T& t, ParserExecutor& executor)
        {
            return executor.TextManager.AskApplyFront(t);
        }
    };
}
