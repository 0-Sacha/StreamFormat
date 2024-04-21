#pragma once

#include "ProjectCore/LoggerManager/LoggerManager.h"

#define PROJECTCORE_TEST_TRACE(...)     ProjectCore::Test::TestCore::GetLogger().Trace(__VA_ARGS__)
#define PROJECTCORE_TEST_INFO(...)      ProjectCore::Test::TestCore::GetLogger().Info(__VA_ARGS__)
#define PROJECTCORE_TEST_WARN(...)      ProjectCore::Test::TestCore::GetLogger().Warn(__VA_ARGS__)
#define PROJECTCORE_TEST_ERROR(...)     ProjectCore::Test::TestCore::GetLogger().Error(__VA_ARGS__)
#define PROJECTCORE_TEST_FATAL(...)     ProjectCore::Test::TestCore::GetLogger().Fatal(__VA_ARGS__)
#define PROJECTCORE_TEST_OK(...)        ProjectCore::Test::TestCore::GetLogger().Ok(__VA_ARGS__)
#define PROJECTCORE_TEST_FAIL(...)      ProjectCore::Test::TestCore::GetLogger().Fail(__VA_ARGS__)
#define PROJECTCORE_TEST_BASIC(...)     ProjectCore::Test::TestCore::GetLogger().Basic(__VA_ARGS__)

namespace ProjectCore::Test
{
    class TestCore
    {
    public:
        static LoggerManager::BasicLogger& GetLogger() { static LoggerManager::BasicLogger instance("ProjectCore-Test", "{name} {color} -> {data}"); return instance; }
    };
}

// Assert log if false
#define PROJECTCORE_TEST_ASSERT(x) if(!(x)) PROJECTCORE_TEST_FAIL("ASSERT FAIL : {0:C:red}", #x)

// Check if false
#define PROJECTCORE_TEST_TEST(x)    if(x)   PROJECTCORE_TEST_OK("TEST OK : {:C:green}", #x);\
                                    else    PROJECTCORE_TEST_FAIL("TEST FAIL : {:C:red}", #x)

// Check if equal with file printed
#define PROJECTCORE_TEST_EQ(x, y) if(x == y)    PROJECTCORE_TEST_OK("{C:green}{} == {}", #x, #y);\
                                  else          PROJECTCORE_TEST_FAIL("{C:red}{} == {}", #x, #y)

// Check if not equal with file printed
#define PROJECTCORE_TEST_NEQ(x, y)  if(x != y)  PROJECTCORE_TEST_OK("{C:green}{} != {}", #x, #y);\
                                    else        PROJECTCORE_TEST_FAIL("{C:red}{} != {}", #x, #y)


#define PROJECTCORE_TEST_FN(fn, resExpected)    {\
                                                    auto res = fn;\
                                                    if (res == resExpected)    PROJECTCORE_TEST_OK("{C:green}{} return {}", #fn, res); \
                                                    else                    PROJECTCORE_TEST_FAIL("{C:red}{} return {} instead of {}", #fn, res, resExpected); \
                                                }

#define PROJECTCORE_TEST_FNFMT(fn, resExpected, ...)    {\
                                                            PROJECTCORE_TEST_INFO(__VA_ARGS__);\
                                                            auto res = fn;\
                                                            if (res == resExpected)    PROJECTCORE_TEST_OK("{C:green}{} return {}", #fn, res); \
                                                            else                    PROJECTCORE_TEST_FAIL("{C:red}{} return {} instead of {}", #fn, res, resExpected); \
                                                        }


#ifdef PROJECTCORE_ECTM_ENABLE

#define ECTM_ASSERT(x)                      PROJECTCORE_TEST_ASSERT(x)
#define ECTM_TEST(x)                        PROJECTCORE_TEST_TEST(x)
#define ECTM_EQ(x, y)                       PROJECTCORE_TEST_EQ(x, y)
#define ECTM_NEQ(x, y)                      PROJECTCORE_TEST_NEQ(x, y)
#define ECTM_FN(fn, resExpected)            PROJECTCORE_TEST_FN(fn, resExpected)
#define ECTM_FNFMT(fn, resExpected, ...)    PROJECTCORE_TEST_FNFMT(fn, resExpected, __VA_ARGS__)

#endif /* PROJECTCORE_ECTM_ENABLE */

//******************************************************//
//******************************************************//
//******************************************************//

// Check if false at compile time
#define PROJECTCORE_TEST_STATIC_ASSERT(x) static_assert(x, "ASSERT ERROR : " #x)
