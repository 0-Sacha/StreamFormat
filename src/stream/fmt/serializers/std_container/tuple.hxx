#pragma once

#include <tuple>
#include <utility>
#include "stream/fmt/context/formatter_executor/formatter_type.hxx"

namespace stream::fmt::tuple_detail {
    template <std::uint32_t N, typename... Args>
    using NthTypeOf = typename std::tuple_element<N, std::tuple<Args...>>::Type;

    template <std::uint32_t N, typename... Args>
    constexpr NthTypeOf<N, Args...>& get(Args&&... args) {
        std::tuple<Args...> tuple(std::forward<Args>(args)...);
        return std::get<N>(tuple);
    }

    template <typename FormatterExecutor>
    static inline void tuple_format_rec(FormatterExecutor& executor) {}

    template <typename T, typename FormatterExecutor>
    static inline void tuple_format_rec(FormatterExecutor& executor, const T& t) {
        return executor.write_type(t);
    }

    template <typename T, typename FormatterExecutor, typename... Args>
    static inline void tuple_format_rec(FormatterExecutor& executor, const T& t, Args&&... args) {
        executor.write_type(t);
        executor.ostream.pushback(',');
        executor.ostream.pushback(' ');
        return tuple_format_rec(executor, std::forward<Args>(args)...);
    }
}  // namespace stream::fmt::tuple_detail

namespace stream::fmt {
    template <typename... T, typename FormatterExecutor>
    struct FormatterType<std::tuple<T...>, FormatterExecutor> {
        static void format(const std::tuple<T...>& t, FormatterExecutor& executor) {
            executor.ostream.pushback('<');
            std::apply([&executor](auto&&... args) { auto&& res = tuple_detail::tuple_format_rec(executor, args...); }, t);
            executor.ostream.pushback('>');
        }
    };

    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::pair<T1, T2>, FormatterExecutor> {
        static void format(const std::pair<T1, T2>& t, FormatterExecutor& executor) {
            executor.ostream.pushback('<');
            executor.write_type(t.first);
            executor.ostream.pushback(':');
            executor.write_type(t.second);
            executor.ostream.pushback('>');
        }
    };
}  // namespace stream::fmt
