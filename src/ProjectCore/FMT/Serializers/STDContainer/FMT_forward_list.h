#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/FormatterType.h"
#include <forward_list>

namespace ProjectCore::FMT
{
    template <typename T, typename FormatterContext>
    struct FormatterType<std::forward_list<T>, FormatterContext>
    {
        static void Format(const std::forward_list<T>& t, FormatterContext& context) {
            FormatterType<ForwardAsSTDEnumerable<std::forward_list<T>>, FormatterContext>::Format(t, context);
        }
    };
}
