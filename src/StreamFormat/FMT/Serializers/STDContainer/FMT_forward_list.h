#pragma once

#include <forward_list>
#include "StreamFormat/FMT/Context/FormatterContext/FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterContext>
    struct FormatterType<std::forward_list<T>, FormatterContext>
    {
        static void Format(const std::forward_list<T>& t, FormatterContext& context)
        {
            FormatterType<ForwardAsSTDEnumerable<std::forward_list<T>>, FormatterContext>::Format(t, context);
        }
    };
}
