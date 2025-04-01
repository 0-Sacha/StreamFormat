#pragma once

#include <queue>
#include "stream/fmt/context/formatter_executor/formatter_type.hxx"

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::queue<T>, FormatterExecutor> {
        static void format(const std::queue<T>&  /*t*/, FormatterExecutor&  /*executor*/) {
            throw std::runtime_error("fmt error: FunctionNotImpl");
        }
    };
}  // namespace stream::fmt
