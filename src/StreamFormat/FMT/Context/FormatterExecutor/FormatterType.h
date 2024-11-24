#pragma once

#include "StreamFormat/FMT/Detail/Prelude.h"

#define STREAMFORMAT_FORMATTER_DECLARED
namespace StreamFormat::FMT
{
    enum class FMTResult
    {
        BufferManip,
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType
    {
        [[nodiscard]] static std::expected<void, FMTResult> Format(const T&, FormatterExecutor& executor)
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
        }
    };
}

#define STREAMFORMAT_AUTO_FORMATTER(Type, fmt, ...)                                                                                                             \
    template <typename FormatterExecutor>                                                                                                                       \
    struct StreamFormat::FMT::FormatterType<Type, FormatterExecutor>                                                                                            \
    {                                                                                                                                                           \
        [[nodiscard]] static std::expected<void, FMTResult> Format(const Type& value, FormatterExecutor& executor) { executor.Run(fmt, __VA_ARGS__); } \
    };

#define STREAMFORMAT_AUTO_FORMATTER_T(Type, fmt, ...)                                                                                                       \
    template <typename FormatterExecutor>                                                                                                                   \
    struct StreamFormat::FMT::FormatterType<Type, FormatterExecutor>                                                                                        \
    {                                                                                                                                                       \
        [[nodiscard]] static std::expected<void, FMTResult> Format(const Type&, FormatterExecutor& executor) { executor.Run(fmt, __VA_ARGS__); }   \
    };
