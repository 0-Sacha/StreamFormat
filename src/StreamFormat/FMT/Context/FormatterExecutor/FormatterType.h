#pragma once

#include "StreamFormat/FMT/Detail/Detail.h"

#define STREAMFORMAT_FORMATTER_DECLARED
namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType
    {
        static inline void Format(const T&, FormatterExecutor& executor)
        {
#ifdef UNKOWN_TYPE_MESSAGE
            executor.Run("({C:red}FMT unknow type: {})", typeid(T).name());
#endif
#ifdef UNKOWN_TYPE_THROW
            throw Detail::FMTShouldNotEndHere{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            throw Detail::FMTShouldNotEndHere{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        }
    };
}

#define STREAMFORMAT_AUTO_FORMATTER(Type, fmt, ...)                                                                         \
    template <typename FormatterExecutor>                                                                                   \
    struct StreamFormat::FMT::FormatterType<Type, FormatterExecutor>                                                         \
    {                                                                                                                      \
        static void Format(const Type& value, FormatterExecutor& executor) { executor.Run(fmt, __VA_ARGS__); } \
    };

#define STREAMFORMAT_AUTO_FORMATTER_T(Type, fmt, ...)                                                                 \
    template <typename FormatterExecutor>                                                                             \
    struct StreamFormat::FMT::FormatterType<Type, FormatterExecutor>                                                   \
    {                                                                                                                \
        static void Format(const Type&, FormatterExecutor& executor) { executor.Run(fmt, __VA_ARGS__); } \
    };
