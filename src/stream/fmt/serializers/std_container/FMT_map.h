#pragma once

#include <map>
#include "stream/fmt/context/formatter_executor/formatter_type.h"

#include "FMT_tuple.h"

namespace stream::fmt
{
    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::map<T1, T2>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::map<T1, T2>& t, FormatterExecutor& executor)
        {
            return FormatterType<ForwardAsSTDEnumerable<std::map<T1, T2>>, FormatterExecutor>::format(t, executor);
        }
    };

    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::multimap<T1, T2>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::multimap<T1, T2>& t, FormatterExecutor& executor)
        {
            return ormatterType<ForwardAsSTDEnumerable<std::multimap<T1, T2>>, FormatterExecutor>::format(t, executor);
        }
    };
}
