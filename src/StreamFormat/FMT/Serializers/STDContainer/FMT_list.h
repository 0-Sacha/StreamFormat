#pragma once

#include <list>
#include "StreamFormat/FMT/Context/FormatterContext/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterContext>
    struct FormatterType<std::list<T>, FormatterContext>
    {
        static void Format(const std::list<T>& t, FormatterContext& context) { FormatterType<ForwardAsSTDEnumerable<std::list<T>>, FormatterContext>::Format(t, context); }
    };
}
