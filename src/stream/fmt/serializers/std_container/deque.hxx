#pragma once

#include "stream/fmt/context/formatter_executor/formatter_type.h"
#include "stream/fmt/context/formatter_executor/std_enumerable.h"

#include <deque>

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::deque<T>, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const std::deque<T>& t, FormatterExecutor& executor) {
            return FormatterType<ForwardAsSTDEnumerable<std::deque<T>>, FormatterExecutor>::format(t, executor);
        }
    };
}  // namespace stream::fmt
