#pragma once

#include <map>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

#include "FMT_tuple.h"

namespace StreamFormat::FMT
{
    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::map<T1, T2>, FormatterExecutor>
    {
        static void Format(const std::map<T1, T2>& t, FormatterExecutor& executor) { FormatterType<ForwardAsSTDEnumerable<std::map<T1, T2>>, FormatterExecutor>::Format(t, executor); }
    };

    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::multimap<T1, T2>, FormatterExecutor>
    {
        static void Format(const std::multimap<T1, T2>& t, FormatterExecutor& executor)
        {
            FormatterType<ForwardAsSTDEnumerable<std::multimap<T1, T2>>, FormatterExecutor>::Format(t, executor);
        }
    };
}
