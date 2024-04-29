#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/FormatterType.h"
#include <vector>

namespace ProjectCore::FMT
{
    template <typename T, typename FormatterContext>
    struct FormatterType<std::vector<T>, FormatterContext>
    {
        static void Format(const std::vector<T>& t, FormatterContext& context) {
            FormatterType<ForwardAsSTDEnumerable<std::vector<T>>, FormatterContext>::Format(t, context);
        }
    };
}
