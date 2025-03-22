#pragma once

#include <list>
#include "stream/fmt/context/formatter_executor/formatter_type.h"

namespace stream::fmt
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::list<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::list<T>& t, FormatterExecutor& executor)
            { return FormatterType<ForwardAsSTDEnumerable<std::list<T>>, FormatterExecutor>::format(t, executor); }
    };
}
