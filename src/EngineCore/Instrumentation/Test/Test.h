#pragma once

#include "TestCore.h"

#include "CopyMoveCheck/CopyMoveCheck.h"

#ifdef ENGINE_CORE_TESTMACRO_ENABLE
#include "Test/Test.h"
#endif

#ifdef ENGINE_CORE_TESTSUITE_ENABLE
#include "TestSuite/TestSuiteImpl.h"
#include "TestSuite/TestSuite.h"
#endif
