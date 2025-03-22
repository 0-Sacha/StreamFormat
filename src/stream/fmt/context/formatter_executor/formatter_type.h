#pragma once

#include "stream/fmt/detail/prelude.h"

#define STREAMFORMAT_FORMATTER_DECLARED
namespace stream::fmt
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const T&, FormatterExecutor& executor)
        {
#ifdef UNKOWN_TYPE_MESSAGE
            executor.Run("({C:red}FMT unknow type: {})", typeid(T).name());
#endif
#ifdef UNKOWN_TYPE_FAIL
            static_assert(false);
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        return {};
        }
    };
}

#define STREAMFORMAT_AUTO_FORMATTER(Type, fmt, ...)                                                                                                             \
    template <typename FormatterExecutor>                                                                                                                       \
    struct stream::fmt::FormatterType<Type, FormatterExecutor>                                                                                            \
    {                                                                                                                                                           \
        [[nodiscard]] static std::expected<void, FMTResult> format(const Type& value, FormatterExecutor& executor) { return executor.Run(fmt, __VA_ARGS__); }   \
    };

#define STREAMFORMAT_AUTO_FORMATTER_T(Type, fmt, ...)                                                                                                   \
    template <typename FormatterExecutor>                                                                                                               \
    struct stream::fmt::FormatterType<Type, FormatterExecutor>                                                                                    \
    {                                                                                                                                                   \
        [[nodiscard]] static std::expected<void, FMTResult> format(const Type&, FormatterExecutor& executor) { return executor.Run(fmt, __VA_ARGS__); } \
    };
