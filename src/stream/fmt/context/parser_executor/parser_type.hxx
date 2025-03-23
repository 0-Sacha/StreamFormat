#pragma once

#include "stream/fmt/detail/prelude.hxx"

#define STREAMFORMAT_PARSER_DECLARED
namespace stream::fmt {
    template <typename T, typename ParserExecutor = context::BasicParserExecutor<char>>
    struct ParserType {
        static inline bool parse(T&, ParserExecutor&) {
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

}  // namespace stream::fmt

#define STREAMFORMAT_AUTO_PARSER(type, fmt, ...)                   \
    template <typename ParserExecutor>                             \
    struct stream::fmt::ParserType<Type, ParserExecutor> {         \
        static bool parse(Type& value, ParserExecutor& executor) { \
            return executor.run(fmt, __VA_ARGS__);                 \
        }                                                          \
    };
