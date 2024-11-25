#pragma once

#include <deque>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::deque<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const std::deque<T>& t, FormatterExecutor& executor)
            { return FormatterType<ForwardAsSTDEnumerable<std::deque<T>>, FormatterExecutor>::Format(t, executor); }
    };
}
