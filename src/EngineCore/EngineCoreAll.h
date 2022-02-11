#pragma once

#include "Core/Core.h"

#include "Instrumentation/Formatter/Formatter.h"
#include "Instrumentation/LogSystem/LogSystem.h"
#include "Instrumentation/Formatter/Format/Container/AllContainer.h"
#include "Instrumentation/Profiling/Profiling.h"
#include "Instrumentation/Test/Test.h"

// #include "Maths/Maths.h"

#ifdef ENGINE_CORE_LOGGER_ENABLE
#define ENGINE_CORE_TRACE(...)	EngineCore::LogSystem::GetCoreInstance().LogTrace(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)	EngineCore::LogSystem::GetCoreInstance().LogInfo(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)	EngineCore::LogSystem::GetCoreInstance().LogWarn(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...)	EngineCore::LogSystem::GetCoreInstance().LogError(__VA_ARGS__)
#define ENGINE_CORE_FATAL(...)	EngineCore::LogSystem::GetCoreInstance().LogFatal(__VA_ARGS__)

#define ENGINE_CORE_OK(...)		EngineCore::LogSystem::GetCoreInstance().LogOk(__VA_ARGS__)
#define ENGINE_CORE_FAIL(...)	EngineCore::LogSystem::GetCoreInstance().LogFail(__VA_ARGS__)

#define ENGINE_CORE_BASIC(...)	EngineCore::LogSystem::GetCoreInstance().LogBasic(__VA_ARGS__)
#else
#define ENGINE_CORE_TRACE(...)
#define ENGINE_CORE_INFO(...)
#define ENGINE_CORE_WARN(...)
#define ENGINE_CORE_ERROR(...)
#define ENGINE_CORE_FATAL(...)

#define ENGINE_CORE_OK(...)
#define ENGINE_CORE_FAIL(...)

#define ENGINE_CORE_BASIC(...)
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
