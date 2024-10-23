#pragma once

#include <vector>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::vector<T>, FormatterExecutor>
    {
        static void Format(const std::vector<T>& t, FormatterExecutor& executor) { FormatterType<ForwardAsSTDEnumerable<std::vector<T>>, FormatterExecutor>::Format(t, executor); }
    };
}
