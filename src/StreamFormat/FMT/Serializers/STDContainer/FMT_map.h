#pragma once

#include <map>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

#include "FMT_tuple.h"

namespace StreamFormat::FMT
{
    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::map<T1, T2>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const std::map<T1, T2>& t, FormatterExecutor& executor)
        {
            return FormatterType<ForwardAsSTDEnumerable<std::map<T1, T2>>, FormatterExecutor>::Format(t, executor);
        }
    };

    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::multimap<T1, T2>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const std::multimap<T1, T2>& t, FormatterExecutor& executor)
        {
            return ormatterType<ForwardAsSTDEnumerable<std::multimap<T1, T2>>, FormatterExecutor>::Format(t, executor);
        }
    };
}
