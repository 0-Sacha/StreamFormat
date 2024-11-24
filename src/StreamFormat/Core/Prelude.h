#pragma once

#include <cstdint>

#define STREAMFORMAT_DEBUG

#ifdef STREAMFORMAT_DEBUG
#define STREAMFORMAT_ASSERT_ENABLE
#define STREAMFORMAT_ONLY_ON_DEBUG(x) x
#else /* STREAMFORMAT_DEBUG */
#define STREAMFORMAT_ONLY_ON_DEBUG(x)
#endif /* STREAMFORMAT_DEBUG */

#ifdef STREAMFORMAT_ASSERT_ENABLE
#ifdef STREAMFORMAT_DEBUG_MSVC
#define STREAMFORMAT_DEBUGBREAK() __debugbreak()
#else
#include <csignal>
#define STREAMFORMAT_DEBUGBREAK() std::raise(SIGINT)
#endif
#include <iostream>
#define STREAMFORMAT_ASSERT(x)                                  \
    if (!(x))                                                  \
    {                                                          \
        std::cerr << "ASSERT FAILED! : " << #x << std::endl; \
        STREAMFORMAT_DEBUGBREAK();                              \
    }
#else
#define STREAMFORMAT_ASSERT(x)
#define STREAMFORMAT_DEBUGBREAK()
#endif

#include <system_error>
#include <expected>
// https://github.com/SerenityOS/serenity/blob/50642f85ac547a3caee353affcb08872cac49456/AK/Try.h
#define SF_TRY(exp) ({ \
        auto __expected = exp; \
        if (not __expected) [[unlikely]] \
            return __expected; \
        __expected.value(); \
    });

#define SF_TRY_TERR(exp, transform_error) ({ \
        auto __expected = exp; \
        if (not __expected) [[unlikely]] \
            return __expected.transform_error(transform_error); \
        __expected.value(); \
    });

#define SF_TRY_OR(exp, new_error) SF_TRY_TERR(exp, [](auto){return new_error;})