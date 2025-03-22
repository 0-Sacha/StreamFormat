#pragma once

#include "BasicParserExecutor.h"

namespace stream::fmt
{
    //------------------------------------------//
    //----------------- Resets -----------------//
    //------------------------------------------//

    template <typename ParserExecutor>
    struct ParserType<detail::TextProperties::ResetProperties, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(detail::TextProperties::ResetProperties, ParserExecutor& executor)
        {
            return executor.TextManager.all_properties_reset();
        }
    };

    template <typename ParserExecutor>
    struct ParserType<detail::TextProperties::TextColor::reset_color, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(detail::TextProperties::TextColor::reset_color, ParserExecutor& executor)
        {
            return executor.TextManager.ApplyColorReset();
        }
    };

    template <typename ParserExecutor>
    struct ParserType<detail::TextProperties::TextStyle::ResetStyle, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(detail::TextProperties::TextStyle::ResetStyle, ParserExecutor& executor)
        {
            return executor.TextManager.ApplyStyleReset();
        }
    };

    template <typename ParserExecutor>
    struct ParserType<detail::TextProperties::TextFront::reset_front, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(detail::TextProperties::TextFront::reset_front, ParserExecutor& executor)
        {
            return executor.TextManager.ApplyFrontReset();
        }
    };

    //---------------------------------------//
    //----------------- Ask -----------------//
    //---------------------------------------//

    template <typename T, typename ParserExecutor>
    requires detail::TextPropertiesColorIsApply<T>
    struct ParserType<T, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T& t, ParserExecutor& executor)
        {
            return executor.TextManager.AskApplyColor(t);
        }
    };

    template <typename T, typename ParserExecutor>
    requires detail::TextPropertiesStyleIsApply<T>
    struct ParserType<T, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T& t, ParserExecutor& executor)
        {
            return executor.TextManager.AskApplyStyle(t);
        }
    };

    template <typename T, typename ParserExecutor>
    requires detail::TextPropertiesFrontIsApply<T>
    struct ParserType<T, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T& t, ParserExecutor& executor)
        {
            return executor.TextManager.AskApplyFront(t);
        }
    };
}
