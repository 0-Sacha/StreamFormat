#pragma once

#include "../TestCore.h"

#define ENGINECORE_TEST_TRACE(...)	EngineCore::Test::TestCore::GetLogger().LogTrace(__VA_ARGS__)
#define ENGINECORE_TEST_INFO(...)	EngineCore::Test::TestCore::GetLogger().LogInfo(__VA_ARGS__)
#define ENGINECORE_TEST_WARN(...)	EngineCore::Test::TestCore::GetLogger().LogWarn(__VA_ARGS__)
#define ENGINECORE_TEST_ERROR(...)	EngineCore::Test::TestCore::GetLogger().LogError(__VA_ARGS__)
#define ENGINECORE_TEST_FATAL(...)	EngineCore::Test::TestCore::GetLogger().LogFatal(__VA_ARGS__)
#define ENGINECORE_TEST_OK(...)		EngineCore::Test::TestCore::GetLogger().LogOk(__VA_ARGS__)
#define ENGINECORE_TEST_FAIL(...)	EngineCore::Test::TestCore::GetLogger().LogFail(__VA_ARGS__)
#define ENGINECORE_TEST_BASIC(...)	EngineCore::Test::TestCore::GetLogger().LogBasic(__VA_ARGS__)

namespace EngineCore::Test {

	class TestCore
	{
	public:
		static LogSystem& GetLogger() { static LogSystem instance("EngineCore-Test", "{name} {color} -> {data}"); return instance; }
	};

}

// Assert log if false
#define ENGINECORE_TEST_ASSERT(x) if(!(x)) ENGINECORE_TEST_FAIL("ASSERT FAIL : {0:C:red}", #x)

// Check if false
#define ENGINECORE_TEST_TEST(x)	if(x)	ENGINECORE_TEST_OK("TEST OK : {:C:green}", #x);\
									else	ENGINECORE_TEST_FAIL("TEST FAIL : {:C:red}", #x)

// Check if equal with file printed
#define ENGINECORE_TEST_EQ(x, y) if(x == y)	ENGINECORE_TEST_OK("{C:green}{} == {}", #x, #y);\
								  else			ENGINECORE_TEST_FAIL("{C:red}{} == {}", #x, #y)

// Check if not equal with file printed
#define ENGINECORE_TEST_NEQ(x, y)	if(x != y)	ENGINECORE_TEST_OK("{C:green}{} != {}", #x, #y);\
									else		ENGINECORE_TEST_FAIL("{C:red}{} != {}", #x, #y)


#define ENGINECORE_TEST_FN(fn, resExpected)	{\
												auto res = fn;\
												if (res == resExpected)	ENGINECORE_TEST_OK("{C:green}{} return {}", #fn, res); \
												else					ENGINECORE_TEST_FAIL("{C:red}{} return {} instead of {}", #fn, res, resExpected); \
												}

#define ENGINECORE_TEST_FNFMT(fn, resExpected, ...)	{\
														ENGINECORE_TEST_INFO(__VA_ARGS__);\
														auto res = fn;\
														if (res == resExpected)	ENGINECORE_TEST_OK("{C:green}{} return {}", #fn, res); \
														else					ENGINECORE_TEST_FAIL("{C:red}{} return {} instead of {}", #fn, res, resExpected); \
														}


#ifdef ENGINECORE_ECTM_ENABLE

#define ECTM_ASSERT(x)						ENGINECORE_TEST_ASSERT(x)
#define ECTM_TEST(x)						ENGINECORE_TEST_TEST(x)
#define ECTM_EQ(x, y)						ENGINECORE_TEST_EQ(x, y)
#define ECTM_NEQ(x, y)						ENGINECORE_TEST_NEQ(x, y)
#define ECTM_FN(fn, resExpected)			ENGINECORE_TEST_FN(fn, resExpected)
#define ECTM_FNFMT(fn, resExpected, ...)	ENGINECORE_TEST_FNFMT(fn, resExpected, __VA_ARGS__)

#endif /* ENGINECORE_ECTM_ENABLE */

//******************************************************//
//******************************************************//
//******************************************************//

// Check if false at compile time
#define ENGINECORE_TEST_STATIC_ASSERT(x) static_assert(x, "ASSERT ERROR : " #x)
