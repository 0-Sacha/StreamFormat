#pragma once

#include <forward_list>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::forward_list<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const std::forward_list<T>& t, FormatterExecutor& executor)
        {
            FormatterType<ForwardAsSTDEnumerable<std::forward_list<T>>, FormatterExecutor>::Format(t, executor);
        }
    };
}
