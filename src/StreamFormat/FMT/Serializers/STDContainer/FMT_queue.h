#pragma once

#include <queue>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::queue<T>, FormatterExecutor>
    {
        static void Format(const std::queue<T>& t, FormatterExecutor& executor) {}
    };
}
