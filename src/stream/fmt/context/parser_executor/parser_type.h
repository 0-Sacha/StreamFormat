#pragma once

#include "stream/fmt/detail/prelude.h"

#define STREAMFORMAT_PARSER_DECLARED
namespace stream::fmt
{
    template <typename T, typename ParserExecutor = Context::BasicParserExecutor<char>>
    struct ParserType
    {
        static inline bool parse(T&, ParserExecutor&)
        {
#ifdef UNKOWN_TYPE_MESSAGE
            // FIXME
            STREAMFORMAT_DEBUGBREAK();
            // static_cast(false);
#endif
#ifdef UNKOWN_TYPE_FAIL
            static_cast(false);
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
            return false;
        }
    };

}

#define STREAMFORMAT_AUTO_PARSER(Type, fmt, ...)                                                                         \
    template <typename ParserExecutor>                                                                                   \
    struct stream::fmt::ParserType<Type, ParserExecutor>                                                            \
    {                                                                                                                   \
        static bool parse(Type& value, ParserExecutor& executor) { return executor.Run(fmt, __VA_ARGS__); } \
    };
