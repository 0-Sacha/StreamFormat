#pragma once

#include "StreamFormat/FLog.h"

#define STREAMFORMAT_TEST_TRACE(...) StreamFormat::Test::TestCore::GetLogger().Trace(__VA_ARGS__)
#define STREAMFORMAT_TEST_INFO(...)  StreamFormat::Test::TestCore::GetLogger().Info(__VA_ARGS__)
#define STREAMFORMAT_TEST_WARN(...)  StreamFormat::Test::TestCore::GetLogger().Warn(__VA_ARGS__)
#define STREAMFORMAT_TEST_ERROR(...) StreamFormat::Test::TestCore::GetLogger().Error(__VA_ARGS__)
#define STREAMFORMAT_TEST_FATAL(...) StreamFormat::Test::TestCore::GetLogger().Fatal(__VA_ARGS__)
#define STREAMFORMAT_TEST_OK(...)    StreamFormat::Test::TestCore::GetLogger().Ok(__VA_ARGS__)
#define STREAMFORMAT_TEST_FAIL(...)  StreamFormat::Test::TestCore::GetLogger().Fail(__VA_ARGS__)
#define STREAMFORMAT_TEST_BASIC(...) StreamFormat::Test::TestCore::GetLogger().Basic(__VA_ARGS__)

namespace StreamFormat::Test
{
    class TestCore
    {
    public:
        static FLog::BasicLogger& GetLogger()
        {
            static FLog::BasicLogger instance("StreamFormat-Test", "{name} {color} -> {data}");
            return instance;
        }
    };
}

// Assert log if false
#define STREAMFORMAT_TEST_ASSERT(x) \
    if (!(x)) STREAMFORMAT_TEST_FAIL("ASSERT FAIL : {0:C:red}", #x)

// Check if false
#define STREAMFORMAT_TEST_TEST(x)                         \
    if (x)                                               \
        STREAMFORMAT_TEST_OK("TEST OK : {:C:green}", #x); \
    else                                                 \
        STREAMFORMAT_TEST_FAIL("TEST FAIL : {:C:red}", #x)

// Check if equal with file printed
#define STREAMFORMAT_TEST_EQ(x, y)                         \
    if (x == y)                                           \
        STREAMFORMAT_TEST_OK("{C:green}{} == {}", #x, #y); \
    else                                                  \
        STREAMFORMAT_TEST_FAIL("{C:red}{} == {}", #x, #y)

// Check if not equal with file printed
#define STREAMFORMAT_TEST_NEQ(x, y)                        \
    if (x != y)                                           \
        STREAMFORMAT_TEST_OK("{C:green}{} != {}", #x, #y); \
    else                                                  \
        STREAMFORMAT_TEST_FAIL("{C:red}{} != {}", #x, #y)

#define STREAMFORMAT_TEST_FN(fn, resExpected)                                                   \
    {                                                                                           \
        auto res = fn;                                                                          \
        if (res == resExpected)                                                                 \
            STREAMFORMAT_TEST_OK("{C:green}{} return {}", #fn, res);                            \
        else                                                                                    \
            STREAMFORMAT_TEST_FAIL("{C:red}{} return {} instead of {}", #fn, res, resExpected); \
    }

#define STREAMFORMAT_TEST_FNFMT(fn, resExpected, ...)                                           \
    {                                                                                           \
        STREAMFORMAT_TEST_INFO(__VA_ARGS__);                                                    \
        auto res = fn;                                                                          \
        if (res == resExpected)                                                                 \
            STREAMFORMAT_TEST_OK("{C:green}{} return {}", #fn, res);                            \
        else                                                                                    \
            STREAMFORMAT_TEST_FAIL("{C:red}{} return {} instead of {}", #fn, res, resExpected); \
    }

#ifdef STREAMFORMAT_SFTM_ENABLE

#define SFTM_ASSERT(x)                   STREAMFORMAT_TEST_ASSERT(x)
#define SFTM_TEST(x)                     STREAMFORMAT_TEST_TEST(x)
#define SFTM_EQ(x, y)                    STREAMFORMAT_TEST_EQ(x, y)
#define SFTM_NEQ(x, y)                   STREAMFORMAT_TEST_NEQ(x, y)
#define SFTM_FN(fn, resExpected)         STREAMFORMAT_TEST_FN(fn, resExpected)
#define SFTM_FNFMT(fn, resExpected, ...) STREAMFORMAT_TEST_FNFMT(fn, resExpected, __VA_ARGS__)

#endif /* STREAMFORMAT_SFTM_ENABLE */

//******************************************************//
//******************************************************//
//******************************************************//

// Check if false at compile time
#define STREAMFORMAT_TEST_STATIC_ASSERT(x) static_assert(x, "ASSERT ERROR : " #x)
