#pragma once

#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

#include <unordered_map>
#include "FMT_tuple.h"

namespace StreamFormat::FMT
{
    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::unordered_map<T1, T2>, FormatterExecutor>
    {
        static void Format(const std::unordered_map<T1, T2>& t, FormatterExecutor& executor)
        {
            FormatterType<ForwardAsSTDEnumerable<std::unordered_map<T1, T2>>, FormatterExecutor>::Format(t, executor);
        }
    };

    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::unordered_multimap<T1, T2>, FormatterExecutor>
    {
        static void Format(const std::unordered_multimap<T1, T2>& t, FormatterExecutor& executor)
        {
            FormatterType<ForwardAsSTDEnumerable<std::unordered_multimap<T1, T2>>, FormatterExecutor>::Format(t, executor);
        }
    };
}
