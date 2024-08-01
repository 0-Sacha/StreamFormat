#pragma once

#include <queue>
#include "ProjectCore/FMT/Context/FormatterContext/FormatterType.h"

namespace ProjectCore::FMT
{
    template <typename T, typename FormatterContext>
    struct FormatterType<std::queue<T>, FormatterContext>
    {
        static void Format(const std::queue<T>& t, FormatterContext& context) {}
    };
}
