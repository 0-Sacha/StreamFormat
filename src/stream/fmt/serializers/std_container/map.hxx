#pragma once

#include <map>
#include "stream/fmt/context/formatter_executor/formatter_type.hxx"
#include "stream/fmt/context/formatter_executor/forwarders.hxx"

#include "tuple.hxx"

namespace stream::fmt {
    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::map<T1, T2>, FormatterExecutor> {
        static void format(const std::map<T1, T2>& t, FormatterExecutor& executor) {
            detail::forwarders::format_span(std::span(t), executor);
        }
    };

    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::multimap<T1, T2>, FormatterExecutor> {
        static void format(const std::multimap<T1, T2>& t, FormatterExecutor& executor) {
            detail::forwarders::format_span(std::span(t), executor);
        }
    };
}  // namespace stream::fmt
