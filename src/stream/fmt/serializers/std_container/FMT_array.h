#pragma once

#include <array>
#include "stream/fmt/context/formatter_executor/formatter_type.h"

namespace stream::fmt
{
    template <typename T, std::size_t SIZE, typename FormatterExecutor>
    struct FormatterType<std::array<T, SIZE>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::array<T, SIZE>& t, FormatterExecutor& executor)
        {
            return FormatterType<ForwardAsSTDEnumerable<std::array<T, SIZE>>, FormatterExecutor>::format(t, executor);
        }
    };
}
