#pragma once

#include <list>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::list<T>, FormatterExecutor>
    {
        static void Format(const std::list<T>& t, FormatterExecutor& executor) { FormatterType<ForwardAsSTDEnumerable<std::list<T>>, FormatterExecutor>::Format(t, executor); }
    };
}
