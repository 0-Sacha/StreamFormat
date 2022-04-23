#pragma once

#include "TestCore.h"

#include "CopyMoveCheck/CopyMoveCheck.h"

#ifdef ENGINECORE_TESTMACRO_ENABLE
#include "Test/Test.h"
#endif

#ifdef ENGINECORE_TESTSUITE_ENABLE
#include "TestSuite/TestSuiteImpl.h"
#include "TestSuite/TestSuite.h"
#endif
