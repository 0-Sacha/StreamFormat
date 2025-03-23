#pragma once

#include "stream/fmt/context/formatter_executor/formatter_type.hxx"
#include "stream/fmt/context/formatter_executor/std_enumerable.hxx"

#include <unordered_set>

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::unordered_set<T>, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const std::unordered_set<T>& t, FormatterExecutor& executor) {
            return FormatterType<ForwardAsSTDEnumerable<std::unordered_set<T>>, FormatterExecutor>::format(t, executor);
        }
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::unordered_multiset<T>, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const std::unordered_multiset<T>& t, FormatterExecutor& executor) {
            return FormatterType<ForwardAsSTDEnumerable<std::unordered_multiset<T>>, FormatterExecutor>::format(t, executor);
        }
    };
}  // namespace stream::fmt
