#pragma once

#include "Flags.h"

#include <utility>

#ifdef ENGINECORE_DEV
#define ENGINECORE_DEBUG
#endif

#ifdef ENGINECORE_DEBUG
#define ENGINECORE_ASSERT_ENABLE
#define ENGINECORE_ONLY_ON_DEBUG(x) x
#else /* ENGINECORE_DEBUG */
#define ENGINECORE_ONLY_ON_DEBUG(x)
#endif /* ENGINECORE_DEBUG */

#ifdef ENGINECORE_ASSERT_ENABLE
	#define ENGINECORE_ASSERT(x)	if(!(x)) ENGINECORE_FATAL("ASSERT FAILED! : {}", #x)
#else
	#define ENGINECORE_ASSERT(x)
#endif

// NOT USED YET
#define ENGINECORE_NODISCARD	[[nodiscard]]
#define ENGINECORE_INLINE		inline

