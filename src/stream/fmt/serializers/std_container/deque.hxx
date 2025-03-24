#pragma once

#include "stream/fmt/context/formatter_executor/formatter_type.hxx"
#include "stream/fmt/context/formatter_executor/std_enumerable.hxx"

#include <deque>

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::deque<T>, FormatterExecutor> {
        static void format(const std::deque<T>& t, FormatterExecutor& executor) {
            return FormatterType<ForwardAsSTDEnumerable<std::deque<T>>, FormatterExecutor>::format(t, executor);
        }
    };
}  // namespace stream::fmt
