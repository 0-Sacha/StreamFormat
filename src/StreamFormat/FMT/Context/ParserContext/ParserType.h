#pragma once

#include "StreamFormat/FMT/Detail/Detail.h"

#define STREAMFORMAT_PARSER_DECLARED
namespace StreamFormat::FMT
{
    template <typename T, typename ParserContext = Context::BasicParserContext<char, char>>
    struct ParserType
    {
        static inline bool Parse(T&, ParserContext&)
        {
#ifdef UNKOWN_TYPE_MESSAGE
            // FIXME
            throw Detail::FMTShouldNotEndHere{};
#endif
#ifdef UNKOWN_TYPE_THROW
            throw Detail::FMTShouldNotEndHere{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw Detail::FMTShouldNotEndHere{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
            return false;
        }
    };

}

#define STREAMFORMAT_AUTO_PARSER(Type, fmt, ...)                                                                         \
    template <typename ParserContext>                                                                                   \
    struct StreamFormat::FMT::ParserType<Type, ParserContext>                                                            \
    {                                                                                                                   \
        static bool Parse(Type& value, ParserContext& context) { return context.SubContextArrayFMT(fmt, __VA_ARGS__); } \
    };
