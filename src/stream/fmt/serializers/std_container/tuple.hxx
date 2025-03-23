#pragma once

#include <tuple>
#include <utility>
#include "stream/fmt/context/formatter_executor/formatter_type.h"

namespace stream::fmt::tuple_detail {
    template <std::uint32_t N, typename... Args>
    using NthTypeOf = typename std::tuple_element<N, std::tuple<Args...>>::Type;

    template <std::uint32_t N, typename... Args>
    constexpr NthTypeOf<N, Args...>& get(Args&&... args) {
        std::tuple<Args...> tuple(args...);
        return std::get<N>(tuple);
    }

    template <typename FormatterExecutor>
    [[nodiscard]] static inline std::expected<void, FMTResult> tuple_format_rec(FormatterExecutor& executor) {
        return {};
    }

    template <typename T, typename FormatterExecutor>
    [[nodiscard]] static inline std::expected<void, FMTResult> tuple_format_rec(FormatterExecutor& executor, const T& t) {
        return executor.write_type(t);
    }

    template <typename T, typename FormatterExecutor, typename... Args>
    [[nodiscard]] static inline std::expected<void, FMTResult> tuple_format_rec(FormatterExecutor& executor, const T& t, Args&&... args) {
        SF_TRY(executor.write_type(t));
        SF_TRY(executor.ostream.pushback(','));
        SF_TRY(executor.ostream.pushback(' '));
        return tuple_format_rec(context, args...);
    }
}  // namespace stream::fmt::tuple_detail

namespace stream::fmt {
    template <typename... T, typename FormatterExecutor>
    struct FormatterType<std::tuple<T...>, FormatterExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::tuple<T...>& t, FormatterExecutor& executor) {
            SF_TRY(executor.ostream.pushback('<'));
            std::expected<void, FMTResult> err = {};
            std::apply([&context, &err](auto&&... args) {
                auto&& res = tuple_detail::tuple_format_rec(context, args...);
                if (not res) {
                    err = res.error();
                }
            }, t);
            SF_TRY(executor.ostream.pushback('>'));
        }
    };

    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::pair<T1, T2>, FormatterExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::pair<T1, T2>& t, FormatterExecutor& executor) {
            SF_TRY(executor.ostream.pushback('<'));
            SF_TRY(executor.write_type(t.first));
            SF_TRY(executor.ostream.pushback(':'));
            SF_TRY(executor.write_type(t.second));
            SF_TRY(executor.ostream.pushback('>'));

            return {};
        }
    };
}  // namespace stream::fmt
