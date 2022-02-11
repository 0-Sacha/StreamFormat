#pragma once

#include "EngineCorepch.h"

#ifdef ENGINE_CORE_DEV
#define ENGINE_CORE_DEBUG
#define ENGINE_CORE_EC_ENABLE
#endif

#ifdef ENGINE_CORE_DEBUG

#define ENGINE_CORE_ASSERT_ENABLE
#define ENGINE_CORE_LOGGER

// Logger
#define ENGINE_CORE_LOGGER_ENABLE

// Profiling
#define ENGINE_CORE_PROFILING_ENABLE

// Test
#define ENGINE_CORE_ECTM_ENABLE
#define ENGINE_CORE_TESTMACRO_ENABLE
#define ENGINE_CORE_ECTS_ENABLE
#define ENGINE_CORE_TESTSUITE_ENABLE

#endif


#define ENGINE_CORE_NODISCARD [[nodiscard]]


#ifdef ENGINE_CORE_DEBUG
#define ENGINE_CORE_ONLY_ON_DEBUG(x) x
#else
#define ENGINE_CORE_ONLY_ON_DEBUG(x)
#endif

#ifdef ENGINE_CORE_ASSERT_ENABLE
	#define ENGINE_CORE_ASSERT(x)	if(!(x)) ENGINE_CORE_FATAL("ASSERT FAILED! : {}", #x)
#else
	#define ENGINE_CORE_ASSERT(x)
#endif


#include "EngineComputeBase.h"
#include "STDWrapper.h"

