#pragma once

#include <deque>
#include "stream/fmt/context/formatter_executor/formatter_type.h"

namespace stream::fmt
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::deque<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::deque<T>& t, FormatterExecutor& executor)
            { return FormatterType<ForwardAsSTDEnumerable<std::deque<T>>, FormatterExecutor>::format(t, executor); }
    };
}
