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
#define STREAMFORMAT_ASSERT(x)                               \
    if (!(x)) {                                              \
        std::cerr << "ASSERT FAILED! : " << #x << std::endl; \
        STREAMFORMAT_DEBUGBREAK();                           \
    }
#else
#define STREAMFORMAT_ASSERT(x)
#define STREAMFORMAT_DEBUGBREAK()
#endif

// https://github.com/SerenityOS/serenity/blob/50642f85ac547a3caee353affcb08872cac49456/AK/Try.h
#include <system_error>
#include <expected>
#include <optional>

namespace stream::detail {
    template <typename T>
    T forward_error(T t) {
        return std::forward<T>(t);
    }
}  // namespace stream::detail

#define SF_TRY(exp)                                                                    \
    ({                                                                                 \
        auto __expected = exp;                                                         \
        if (not __expected) [[unlikely]]                                               \
            return std::unexpected(stream::detail::forward_error(__expected.error())); \
        __expected.value();                                                            \
    });

#define SF_FORWARD(exp) SF_TRY(exp)
