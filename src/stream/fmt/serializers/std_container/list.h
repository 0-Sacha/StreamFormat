#pragma once

#include "stream/fmt/context/formatter_executor/formatter_type.h"
#include "stream/fmt/context/formatter_executor/std_enumerable.h"

#include <list>

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::list<T>, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const std::list<T>& t, FormatterExecutor& executor) {
            return FormatterType<ForwardAsSTDEnumerable<std::list<T>>, FormatterExecutor>::format(t, executor);
        }
    };
}  // namespace stream::fmt
