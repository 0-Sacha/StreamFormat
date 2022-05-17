#pragma once

#ifdef ENGINECORE_TEST_ALL_ENABLE

#define ENGINECORE_ECTM_ENABLE
#define ENGINECORE_TESTMACRO_ENABLE
#define ENGINECORE_ECTS_ENABLE
#define ENGINECORE_TESTSUITE_ENABLE

#endif /* ENGINECORE_TEST_ALL_ENABLE */

#include "TestCore.h"

#include "CopyMoveCheck/CopyMoveCheck.h"

#ifdef ENGINECORE_TESTMACRO_ENABLE
#include "Test/Test.h"
#endif

#ifdef ENGINECORE_TESTSUITE_ENABLE
#include "TestSuite/TestSuiteImpl.h"
#include "TestSuite/TestSuite.h"
#endif

#ifdef ENGINE_CORE_ASSERT_ENABLE
	#define ENGINE_CORE_ASSERT(x)	if(!(x)) ENGINE_CORE_FATAL("ASSERT FAILED! : {}", #x)
#else
	#define ENGINE_CORE_ASSERT(x)
#endif
