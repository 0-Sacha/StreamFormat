#pragma once

#include "stream/fmt/context/formatter_executor/formatter_type.hxx"
#include "stream/fmt/context/formatter_executor/forwarders.hxx"

#include <unordered_map>
#include "tuple.hxx"

namespace stream::fmt {
    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::unordered_map<T1, T2>, FormatterExecutor> {
        static void format(const std::unordered_map<T1, T2>& t, FormatterExecutor& executor) {
            detail::forwarders::format_span(std::span(t), executor);
        }
    };

    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::unordered_multimap<T1, T2>, FormatterExecutor> {
        static void format(const std::unordered_multimap<T1, T2>& t, FormatterExecutor& executor) {
            detail::forwarders::format_span(std::span(t), executor);
        }
    };
}  // namespace stream::fmt
