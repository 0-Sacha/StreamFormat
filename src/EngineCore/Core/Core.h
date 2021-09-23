#pragma once

/*
* Mainly from GLM (This code is only for learning)
*
*/

#include "EngineCorepch.h"

#ifdef ENGINE_CORE_DEBUG

#define PROFILING_ENABLE
#define ENGINE_CORE_USE_ASSERT
#define ENGINE_CORE_LOGGER

#endif


#define ENGINE_CORE_NODISCARD [[nodiscard]]


#ifdef ENGINE_CORE_DEBUG
#define ENGINE_CORE_ONLY_ON_DEBUG(x) x
#else
#define ENGINE_CORE_ONLY_ON_DEBUG(x)
#endif

#ifdef ENGINE_CORE_USE_ASSERT
	#define ENGINE_CORE_ASSERT(x)	if(!(x)) ENGINE_CORE_FATAL("ASSERT FAILED! : {}", #x)
#else
	#define ENGINE_CORE_ASSERT(x)
#endif
