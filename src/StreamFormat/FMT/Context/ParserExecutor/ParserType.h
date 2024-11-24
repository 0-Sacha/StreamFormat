#pragma once

#include "StreamFormat/FMT/Detail/Prelude.h"

#define STREAMFORMAT_PARSER_DECLARED
namespace StreamFormat::FMT
{
    template <typename T, typename ParserExecutor = Context::BasicParserExecutor<char>>
    struct ParserType
    {
        static inline bool Parse(T&, ParserExecutor&)
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
    struct StreamFormat::FMT::ParserType<Type, ParserExecutor>                                                            \
    {                                                                                                                   \
        static bool Parse(Type& value, ParserExecutor& executor) { return executor.Run(fmt, __VA_ARGS__); } \
    };
