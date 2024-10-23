#pragma once

#include <set>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::set<T>, FormatterExecutor>
    {
        static void Format(const std::set<T>& t, FormatterExecutor& executor) { FormatterType<ForwardAsSTDEnumerable<std::set<T>>, FormatterExecutor>::Format(t, executor); }
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::multiset<T>, FormatterExecutor>
    {
        static void Format(const std::multiset<T>& t, FormatterExecutor& executor) { FormatterType<ForwardAsSTDEnumerable<std::multiset<T>>, FormatterExecutor>::Format(t, executor); }
    };
}
