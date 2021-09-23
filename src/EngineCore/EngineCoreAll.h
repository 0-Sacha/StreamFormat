#pragma once

#include "Core/Core.h"

#include "Instrumentation/Formatter/Formatter.h"
#include "Instrumentation/LogSystem/LogSystem.h"
// #include "Instrumentation/Formatter/Format/Container/AllContainer.h"
// #include "Instrumentation/Profiling/Profiling.h"
// #include "Instrumentation/Test/Test.h"

// #include "Maths/Maths.h"


#ifdef ENGINE_CORE_LOGGER
#define ENGINE_CORE_TRACE(...)	CPPTools::LogSystem::GetCoreInstance().LogTrace(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)	CPPTools::LogSystem::GetCoreInstance().LogInfo(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)	CPPTools::LogSystem::GetCoreInstance().LogWarn(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...)	CPPTools::LogSystem::GetCoreInstance().LogError(__VA_ARGS__)
#define ENGINE_CORE_FATAL(...)	CPPTools::LogSystem::GetCoreInstance().LogFatal(__VA_ARGS__)

#define ENGINE_CORE_OK(...)		CPPTools::LogSystem::GetCoreInstance().LogOk(__VA_ARGS__)
#define ENGINE_CORE_FAIL(...)	CPPTools::LogSystem::GetCoreInstance().LogFail(__VA_ARGS__)

#define ENGINE_CORE_BASIC(...)	CPPTools::LogSystem::GetCoreInstance().LogBasic(__VA_ARGS__)
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
