#pragma once

#include "stream/fmt/context/formatter_executor/formatter_type.hxx"
#include "stream/fmt/context/formatter_executor/std_enumerable.hxx"

#include <forward_list>

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::forward_list<T>, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const std::forward_list<T>& t, FormatterExecutor& executor) {
            return FormatterType<ForwardAsSTDEnumerable<std::forward_list<T>>, FormatterExecutor>::format(t, executor);
        }
    };
}  // namespace stream::fmt
