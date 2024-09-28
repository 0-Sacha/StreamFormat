#pragma once

#include <vector>
#include "StreamFormat/FMT/Context/FormatterContext/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterContext>
    struct FormatterType<std::vector<T>, FormatterContext>
    {
        static void Format(const std::vector<T>& t, FormatterContext& context) { FormatterType<ForwardAsSTDEnumerable<std::vector<T>>, FormatterContext>::Format(t, context); }
    };
}