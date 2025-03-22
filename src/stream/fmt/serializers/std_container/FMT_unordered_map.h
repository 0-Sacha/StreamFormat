#pragma once

#include "stream/fmt/context/formatter_executor/formatter_type.h"

#include <unordered_map>
#include "FMT_tuple.h"

namespace stream::fmt
{
    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::unordered_map<T1, T2>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::unordered_map<T1, T2>& t, FormatterExecutor& executor)
        {
            return FormatterType<ForwardAsSTDEnumerable<std::unordered_map<T1, T2>>, FormatterExecutor>::format(t, executor);
        }
    };

    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::unordered_multimap<T1, T2>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::unordered_multimap<T1, T2>& t, FormatterExecutor& executor)
        {
            return FormatterType<ForwardAsSTDEnumerable<std::unordered_multimap<T1, T2>>, FormatterExecutor>::format(t, executor);
        }
    };
}
