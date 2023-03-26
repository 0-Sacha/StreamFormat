#pragma once

#include <utility>
#include <cstdint>

#ifdef PROJECTCORE_DEV
#define PROJECTCORE_DEBUG
#endif

#ifdef PROJECTCORE_DEBUG
#define PROJECTCORE_ASSERT_ENABLE
#define PROJECTCORE_ONLY_ON_DEBUG(x) x
#else /* PROJECTCORE_DEBUG */
#define PROJECTCORE_ONLY_ON_DEBUG(x)
#endif /* PROJECTCORE_DEBUG */

// TODO : BETTER ASSERT
#ifdef PROJECTCORE_ASSERT_ENABLE
	#define PROJECTCORE_ASSERT(x)	if(!(x)) { std::cerr << "ASSERT FAILED! : {}" << #x << std::endl; }
#else
	#define PROJECTCORE_ASSERT(x)
#endif

// NOT USED YET
#define PROJECTCORE_NODISCARD	[[nodiscard]]
#define PROJECTCORE_INLINE		inline

