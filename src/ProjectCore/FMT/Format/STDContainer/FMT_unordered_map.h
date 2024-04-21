#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/FormatterType.h"

#include <unordered_map>
#include "FMT_tuple.h"

namespace ProjectCore::FMT
{
    template<typename T1, typename T2, typename FormatterContext>
    struct FormatterType<std::unordered_map<T1, T2>, FormatterContext>
    {
        static void Format(const std::unordered_map<T1, T2>& t, FormatterContext& context) {
            FormatterType<ForwardAsSTDEnumerable<std::unordered_map<T1, T2>>, FormatterContext>::Format(t, context);
        }
    };

    template<typename T1, typename T2, typename FormatterContext>
    struct FormatterType<std::unordered_multimap<T1, T2>, FormatterContext>
    {
        static void Format(const std::unordered_multimap<T1, T2>& t, FormatterContext& context) {
            FormatterType<ForwardAsSTDEnumerable<std::unordered_multimap<T1, T2>>, FormatterContext>::Format(t, context);
        }
    };
}
