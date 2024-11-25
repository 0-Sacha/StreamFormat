#pragma once

#include <list>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::list<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const std::list<T>& t, FormatterExecutor& executor)
            { return FormatterType<ForwardAsSTDEnumerable<std::list<T>>, FormatterExecutor>::Format(t, executor); }
    };
}
