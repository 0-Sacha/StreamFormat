#pragma once

#include <utility>
#include <cstdint>

#ifdef PROJECTCORE_DEBUG
#define PROJECTCORE_ASSERT_ENABLE
#define PROJECTCORE_ONLY_ON_DEBUG(x) x
#else /* PROJECTCORE_DEBUG */
#define PROJECTCORE_ONLY_ON_DEBUG(x)
#endif /* PROJECTCORE_DEBUG */

#ifdef PROJECTCORE_ASSERT_ENABLE
	#ifdef PROJECTCORE_COMPILER_VS
		#define PROJECTCORE_ASSERT(x)	if(!(x)) { std::cerr << "ASSERT FAILED! : {}" << #x << std::endl; __debugbreak(); }
	#else
		#include <csignal>
		#define PROJECTCORE_ASSERT(x)	if(!(x)) { std::cerr << "ASSERT FAILED! : {}" << #x << std::endl; std::raise(SIGINT); }
	#endif
#else
	#define PROJECTCORE_ASSERT(x)
#endif

// NOT USED YET
#define PROJECTCORE_NODISCARD	[[nodiscard]]
#define PROJECTCORE_INLINE		inline

