#pragma once

#include <queue>
#include "stream/fmt/context/formatter_executor/formatter_type.hxx"

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::queue<T>, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const std::queue<T>& t, FormatterExecutor& executor) {
            return std::unexpected(FMTResult::FunctionNotImpl);
        }
    };
}  // namespace stream::fmt
