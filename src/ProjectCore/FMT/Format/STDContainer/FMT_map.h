#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/FormatterType.h"
#include <map>

#include "FMT_tuple.h"

namespace ProjectCore::FMT
{
    template<typename T1, typename T2, typename FormatterContext>
    struct FormatterType<std::map<T1, T2>, FormatterContext>
    {
        static void Format(const std::map<T1, T2>& t, FormatterContext& context) {
            FormatterType<ForwardAsSTDEnumerable<std::map<T1, T2>>, FormatterContext>::Format(t, context);
        }
    };

    template<typename T1, typename T2, typename FormatterContext>
    struct FormatterType<std::multimap<T1, T2>, FormatterContext>
    {
        static void Format(const std::multimap<T1, T2>& t, FormatterContext& context) {
            FormatterType<ForwardAsSTDEnumerable<std::multimap<T1, T2>>, FormatterContext>::Format(t, context);
        }
    };
}
