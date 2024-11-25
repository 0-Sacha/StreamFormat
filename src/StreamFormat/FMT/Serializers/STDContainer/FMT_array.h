#pragma once

#include <array>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, std::size_t SIZE, typename FormatterExecutor>
    struct FormatterType<std::array<T, SIZE>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const std::array<T, SIZE>& t, FormatterExecutor& executor)
        {
            return FormatterType<ForwardAsSTDEnumerable<std::array<T, SIZE>>, FormatterExecutor>::Format(t, executor);
        }
    };
}
