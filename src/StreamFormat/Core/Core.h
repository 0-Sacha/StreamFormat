#pragma once

#include "CompilerInfo.h"

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

// NOT USED YET
#define STREAMFORMAT_NODISCARD [[nodiscard]]
#define STREAMFORMAT_INLINE    inline

#define UNKOWN_TYPE_MESSAGE
#define UNKOWN_TYPE_DEBUG
