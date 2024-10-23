#pragma once

#include <array>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, std::size_t SIZE, typename FormatterExecutor>
    struct FormatterType<std::array<T, SIZE>, FormatterExecutor>
    {
        static void Format(const std::array<T, SIZE>& t, FormatterExecutor& executor)
        {
            FormatterType<ForwardAsSTDEnumerable<std::array<T, SIZE>>, FormatterExecutor>::Format(t, executor);
        }
    };
}
