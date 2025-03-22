#pragma once

#include <vector>
#include "stream/fmt/context/formatter_executor/formatter_type.h"

namespace stream::fmt
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::vector<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::vector<T>& t, FormatterExecutor& executor)
            { return FormatterType<ForwardAsSTDEnumerable<std::vector<T>>, FormatterExecutor>::format(t, executor); }
    };
}
