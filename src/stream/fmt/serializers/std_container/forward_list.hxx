#pragma once

#include "stream/fmt/context/formatter_executor/formatter_type.hxx"
#include "stream/fmt/context/formatter_executor/forwarders.hxx"

#include <forward_list>

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::forward_list<T>, FormatterExecutor> {
        static void format(const std::forward_list<T>& t, FormatterExecutor& executor) {
            detail::forwarders::format_span(std::span(t), executor);
        }
    };
}  // namespace stream::fmt
