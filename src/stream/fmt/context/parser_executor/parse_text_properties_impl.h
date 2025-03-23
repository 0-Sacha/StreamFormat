#pragma once

#include "basic_parser_executor.h"

namespace stream::fmt {
    //------------------------------------------//
    //----------------- Resets -----------------//
    //------------------------------------------//

    template <typename ParserExecutor>
    struct ParserType<detail::TextProperties::ResetProperties, ParserExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(detail::TextProperties::ResetProperties, ParserExecutor& executor) {
            return executor.text_manager.all_properties_reset();
        }
    };

    template <typename ParserExecutor>
    struct ParserType<detail::TextProperties::TextColor::reset_color, ParserExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(detail::TextProperties::TextColor::reset_color, ParserExecutor& executor) {
            return executor.text_manager.apply_color_reset();
        }
    };

    template <typename ParserExecutor>
    struct ParserType<detail::TextProperties::TextStyle::reset_style, ParserExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(detail::TextProperties::TextStyle::reset_style, ParserExecutor& executor) {
            return executor.text_manager.apply_style_reset();
        }
    };

    template <typename ParserExecutor>
    struct ParserType<detail::TextProperties::TextFront::reset_front, ParserExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(detail::TextProperties::TextFront::reset_front, ParserExecutor& executor) {
            return executor.text_manager.apply_front_reset();
        }
    };

    //---------------------------------------//
    //----------------- Ask -----------------//
    //---------------------------------------//

    template <typename T, typename ParserExecutor>
        requires detail::text_properties_color_is_apply<T>
    struct ParserType<T, ParserExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T& t, ParserExecutor& executor) {
            return executor.text_manager.ask_apply_color(t);
        }
    };

    template <typename T, typename ParserExecutor>
        requires detail::TextPropertiesStyleIsapply<T>
    struct ParserType<T, ParserExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T& t, ParserExecutor& executor) {
            return executor.text_manager.ask_apply_style(t);
        }
    };

    template <typename T, typename ParserExecutor>
        requires detail::TextPropertiesFrontIsapply<T>
    struct ParserType<T, ParserExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T& t, ParserExecutor& executor) {
            return executor.text_manager.ask_apply_front(t);
        }
    };
}  // namespace stream::fmt
