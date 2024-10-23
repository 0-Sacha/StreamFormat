#pragma once

#include <deque>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::deque<T>, FormatterExecutor>
    {
        static void Format(const std::deque<T>& t, FormatterExecutor& executor) { FormatterType<ForwardAsSTDEnumerable<std::deque<T>>, FormatterExecutor>::Format(t, executor); }
    };
}
