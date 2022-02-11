#pragma once

#include "../TestCore.h"

#define ENGINE_CORE_TEST_TRACE(...)	EngineCore::TestCore::TestCore::GetLogger().LogTrace(__VA_ARGS__)
#define ENGINE_CORE_TEST_INFO(...)	EngineCore::TestCore::TestCore::GetLogger().LogInfo(__VA_ARGS__)
#define ENGINE_CORE_TEST_WARN(...)	EngineCore::TestCore::TestCore::GetLogger().LogWarn(__VA_ARGS__)
#define ENGINE_CORE_TEST_ERROR(...)	EngineCore::TestCore::TestCore::GetLogger().LogError(__VA_ARGS__)
#define ENGINE_CORE_TEST_FATAL(...)	EngineCore::TestCore::TestCore::GetLogger().LogFatal(__VA_ARGS__)
#define ENGINE_CORE_TEST_OK(...)	EngineCore::TestCore::TestCore::GetLogger().LogOk(__VA_ARGS__)
#define ENGINE_CORE_TEST_FAIL(...)	EngineCore::TestCore::TestCore::GetLogger().LogFail(__VA_ARGS__)
#define ENGINE_CORE_TEST_BASIC(...)	EngineCore::TestCore::TestCore::GetLogger().LogBasic(__VA_ARGS__)

namespace EngineCore::TestCore {
	class TestCore
	{
	public:
		static LogSystem& GetLogger() { static LogSystem instance("EngineCore-Test", "{name} {color} -> {data}"); return instance; }
	};
}

// Assert log if false
#define ENGINE_CORE_TEST_ASSERT(x) if(!(x)) ENGINE_CORE_TEST_FAIL("ASSERT FAIL : {0:C:red}", #x)

// Check if false
#define ENGINE_CORE_TEST_TEST(x)	if(x)	ENGINE_CORE_TEST_OK("TEST OK : {:C:green}", #x);\
									else	ENGINE_CORE_TEST_FAIL("TEST FAIL : {:C:red}", #x)

// Check if equal with file printed
#define ENGINE_CORE_TEST_EQ(x, y) if(x == y)	ENGINE_CORE_TEST_OK("{C:green}{} == {}", #x, #y);\
								  else			ENGINE_CORE_TEST_FAIL("{C:red}{} == {}", #x, #y)

// Check if not equal with file printed
#define ENGINE_CORE_TEST_NEQ(x, y)	if(x != y)	ENGINE_CORE_TEST_OK("{C:green}{} != {}", #x, #y);\
									else		ENGINE_CORE_TEST_FAIL("{C:red}{} != {}", #x, #y)


#define ENGINE_CORE_TEST_FN(fn, resExpected)	{\
												auto res = fn;\
												if (res == resExpected)	ENGINE_CORE_TEST_OK("{C:green}{} return {}", #fn, res); \
												else					ENGINE_CORE_TEST_FAIL("{C:red}{} return {} instead of {}", #fn, res, resExpected); \
												}

#define ENGINE_CORE_TEST_FNFMT(fn, resExpected, ...)	{\
														ENGINE_CORE_TEST_INFO(__VA_ARGS__);\
														auto res = fn;\
														if (res == resExpected)	ENGINE_CORE_TEST_OK("{C:green}{} return {}", #fn, res); \
														else					ENGINE_CORE_TEST_FAIL("{C:red}{} return {} instead of {}", #fn, res, resExpected); \
														}


#ifdef ENGINE_CORE_ECTM_ENABLE
#define ECTM_ASSERT(x)	ENGINE_CORE_TEST_ASSERT(x)
#define ECTM_TEST(x)	ENGINE_CORE_TEST_TEST(x)
#define ECTM_EQ(x, y)	ENGINE_CORE_TEST_EQ(x, y)
#define ECTM_NEQ(x, y)	ENGINE_CORE_TEST_NEQ(x, y)
#define ECTM_FN(fn, resExpected) ENGINE_CORE_TEST_FN(fn, resExpected)
#define ECTM_FNFMT(fn, resExpected, ...) ENGINE_CORE_TEST_FNFMT(fn, resExpected, __VA_ARGS__)
#endif


//******************************************************//
//******************************************************//
//******************************************************//


// Check if false at compile time
#define ENGINE_CORE_TEST_STATIC_ASSERT(x) static_assert(x, "ASSERT ERROR : " #x)
