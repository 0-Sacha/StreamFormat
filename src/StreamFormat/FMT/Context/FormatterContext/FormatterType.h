#pragma once

#include "StreamFormat/FMT/Detail/Detail.h"

#define STREAMFORMAT_FORMATTER_DECLARED
namespace StreamFormat::FMT
{
    template <typename T, typename FormatterContext = Context::BasicFormatterContext<char, char>>
    struct FormatterType
    {
        static inline void Format(const T&, FormatterContext& context)
        {
#ifdef UNKOWN_TYPE_MESSAGE
            context.SubContextArrayFMT("({C:red}FMT unknow type: {})", typeid(T).name());
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
    template <typename FormatterContext>                                                                                   \
    struct StreamFormat::FMT::FormatterType<Type, FormatterContext>                                                         \
    {                                                                                                                      \
        static void Format(const Type& value, FormatterContext& context) { context.SubContextArrayFMT(fmt, __VA_ARGS__); } \
    };

#define STREAMFORMAT_AUTO_FORMATTER_T(Type, fmt, ...)                                                                 \
    template <typename FormatterContext>                                                                             \
    struct StreamFormat::FMT::FormatterType<Type, FormatterContext>                                                   \
    {                                                                                                                \
        static void Format(const Type&, FormatterContext& context) { context.SubContextArrayFMT(fmt, __VA_ARGS__); } \
    };
