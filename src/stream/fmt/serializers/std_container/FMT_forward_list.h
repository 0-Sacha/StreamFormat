#pragma once

#include <forward_list>
#include "stream/fmt/context/formatter_executor/formatter_type.h"

namespace stream::fmt
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::forward_list<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::forward_list<T>& t, FormatterExecutor& executor)
        {
            return FormatterType<ForwardAsSTDEnumerable<std::forward_list<T>>, FormatterExecutor>::format(t, executor);
        }
    };
}
