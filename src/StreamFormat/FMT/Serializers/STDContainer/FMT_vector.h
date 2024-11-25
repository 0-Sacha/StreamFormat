#pragma once

#include <vector>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::vector<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const std::vector<T>& t, FormatterExecutor& executor)
            { return FormatterType<ForwardAsSTDEnumerable<std::vector<T>>, FormatterExecutor>::Format(t, executor); }
    };
}
