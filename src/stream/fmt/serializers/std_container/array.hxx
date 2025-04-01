#pragma once

#include "stream/fmt/context/formatter_executor/formatter_type.hxx"
#include "stream/fmt/context/formatter_executor/forwarders.hxx"

#include <array>

namespace stream::fmt {
    template <typename T, std::size_t SIZE, typename FormatterExecutor>
    struct FormatterType<std::array<T, SIZE>, FormatterExecutor> {
        static void format(const std::array<T, SIZE>& t, FormatterExecutor& executor) {
            detail::forwarders::format_span(std::span(t), executor);
        }
    };
}  // namespace stream::fmt
