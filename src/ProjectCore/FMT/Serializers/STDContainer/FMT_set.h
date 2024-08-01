#pragma once

#include <set>
#include "ProjectCore/FMT/Context/FormatterContext/FormatterType.h"

namespace ProjectCore::FMT
{
    template <typename T, typename FormatterContext>
    struct FormatterType<std::set<T>, FormatterContext>
    {
        static void Format(const std::set<T>& t, FormatterContext& context) { FormatterType<ForwardAsSTDEnumerable<std::set<T>>, FormatterContext>::Format(t, context); }
    };

    template <typename T, typename FormatterContext>
    struct FormatterType<std::multiset<T>, FormatterContext>
    {
        static void Format(const std::multiset<T>& t, FormatterContext& context) { FormatterType<ForwardAsSTDEnumerable<std::multiset<T>>, FormatterContext>::Format(t, context); }
    };
}
