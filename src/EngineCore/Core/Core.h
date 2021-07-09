#pragma once

#include "CPPTools/Core/Core.h"
#include "CPPTools/LogSystem/LogSystem.h"
#include "EngineCorepch.h"

#ifdef ENGINE_CORE_DEBUG

#define ENGINE_CORE_USE_CPPTOOLS_LOGGER
#define ENGINE_CORE_USE_ASSERT

#endif

#define ENGINE_CORE_USE_CPPTOOLS_LOGGER

#ifdef ENGINE_CORE_USE_CPPTOOLS_LOGGER
	#define ENGINE_CORE_TRACE(...)	CPPTools::LogSystem::GetCoreInstance().LogTrace(__VA_ARGS__)
	#define ENGINE_CORE_INFO(...)	CPPTools::LogSystem::GetCoreInstance().LogInfo(__VA_ARGS__)
	#define ENGINE_CORE_WARN(...)	CPPTools::LogSystem::GetCoreInstance().LogWarn(__VA_ARGS__)
	#define ENGINE_CORE_ERROR(...)	CPPTools::LogSystem::GetCoreInstance().LogError(__VA_ARGS__)
	#define ENGINE_CORE_FATAL(...)	CPPTools::LogSystem::GetCoreInstance().LogFatal(__VA_ARGS__)

	#define ENGINE_CORE_OK(...)		CPPTools::LogSystem::GetCoreInstance().LogOk(__VA_ARGS__)
	#define ENGINE_CORE_FAIL(...)	CPPTools::LogSystem::GetCoreInstance().LogFail(__VA_ARGS__)
#else
	#define ENGINE_CORE_TRACE(...)
	#define ENGINE_CORE_INFO(...)
	#define ENGINE_CORE_WARN(...)
	#define ENGINE_CORE_ERROR(...)
	#define ENGINE_CORE_FATAL(...)

	#define ENGINE_CORE_OK(...)
	#define ENGINE_CORE_FAIL(...)
#endif


#ifdef ENGINE_CORE_USE_ASSERT
	#define ENGINE_CORE_ASSERT(x)	if(!(x)) ENGINE_CORE_FATAL("ASSERT FAILED!! : {}", #x)
#else
	#define ENGINE_CORE_ASSERT(x)
#endif
