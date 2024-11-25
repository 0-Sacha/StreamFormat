#pragma once

#include <set>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::set<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const std::set<T>& t, FormatterExecutor& executor)
            { return FormatterType<ForwardAsSTDEnumerable<std::set<T>>, FormatterExecutor>::Format(t, executor); }
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::multiset<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const std::multiset<T>& t, FormatterExecutor& executor)
            { return FormatterType<ForwardAsSTDEnumerable<std::multiset<T>>, FormatterExecutor>::Format(t, executor); }
    };
}
