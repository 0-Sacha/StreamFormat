#pragma once

#include <unordered_set>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::unordered_set<T>, FormatterExecutor>
    {
        static void Format(const std::unordered_set<T>& t, FormatterExecutor& executor)
        {
            FormatterType<ForwardAsSTDEnumerable<std::unordered_set<T>>, FormatterExecutor>::Format(t, executor);
        }
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::unordered_multiset<T>, FormatterExecutor>
    {
        static void Format(const std::unordered_multiset<T>& t, FormatterExecutor& executor)
        {
            FormatterType<ForwardAsSTDEnumerable<std::unordered_multiset<T>>, FormatterExecutor>::Format(t, executor);
        }
    };
}
