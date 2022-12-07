#pragma once

#include "EngineCorepch.h"

#ifdef ENGINECORE_DEV
#define ENGINECORE_DEBUG
#endif

#ifdef ENGINECORE_DEBUG

#define ENGINECORE_ASSERT_ENABLE

// Logger
#define ENGINECORE_LOGGER_ENABLE

// Profiling
#define ENGINECORE_PROFILING_ENABLE

#define ENGINECORE_ONLY_ON_DEBUG(x) x

#else /* ENGINECORE_DEBUG */

#define ENGINECORE_ONLY_ON_DEBUG(x)

#endif /* ENGINECORE_DEBUG */


// NOT USED YET
#define ENGINECORE_NODISCARD	[[nodiscard]]
#define ENGINECORE_INLINE		inline


#ifdef ENGINECORE_ASSERT_ENABLE
	#define ENGINECORE_ASSERT(x)	if(!(x)) ENGINECORE_FATAL("ASSERT FAILED! : {}", #x)
#else
	#define ENGINECORE_ASSERT(x)
#endif

#ifndef __FUNCSIG__
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif

#ifndef __FUNCDNAME__
#define __FUNCDNAME__ __PRETTY_FUNCTION__
#endif