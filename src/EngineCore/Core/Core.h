#pragma once

#include "EngineCorepch.h"

// Dev Mode
#ifdef ENGINE_CORE_DEV
#define ENGINE_CORE_DEBUG
#define ENGINE_CORE_EC_ENABLE
#endif

// Debug tools
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

#ifdef ENGINE_CORE_EC_ENABLE
#define EC_TRACE(...)	ENGINE_CORE_TRACE(...)
#define EC_INFO(...)	ENGINE_CORE_INFO(...
#define EC_WARN(...)	ENGINE_CORE_WARN(...)
#define EC_ERROR(...)	ENGINE_CORE_ERROR(...)
#define EC_FATAL(...)	ENGINE_CORE_FATAL(...)

#define EC_OK(...)		ENGINE_CORE_OK(...)
#define EC_FAIL(...)	ENGINE_CORE_FAIL(...)

#define EC_BASIC(...)	ENGINE_CORE_BASIC(...)
#endif

#define ENGINE_CORE_NODISCARD [[nodiscard]]

// Tools
#ifdef ENGINE_CORE_DEBUG
#define ENGINE_CORE_ONLY_ON_DEBUG(x) x
#else
#define ENGINE_CORE_ONLY_ON_DEBUG(x)
#endif

#include "EngineComputeBase.h"
#include "TypeInfo.h"

