#pragma once

#include "stream/fmt/context/formatter_executor/formatter_type.hxx"
#include "stream/fmt/context/formatter_executor/std_enumerable.hxx"

#include <set>

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::set<T>, FormatterExecutor> {
        static void format(const std::set<T>& t, FormatterExecutor& executor) {
            return FormatterType<ForwardAsSTDEnumerable<std::set<T>>, FormatterExecutor>::format(t, executor);
        }
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::multiset<T>, FormatterExecutor> {
        static void format(const std::multiset<T>& t, FormatterExecutor& executor) {
            return FormatterType<ForwardAsSTDEnumerable<std::multiset<T>>, FormatterExecutor>::format(t, executor);
        }
    };
}  // namespace stream::fmt
