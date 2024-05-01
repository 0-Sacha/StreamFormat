#pragma once

#include "CompilerInfo.h"

#include <cstdint>

#ifdef PROJECTCORE_DEBUG
#define PROJECTCORE_ASSERT_ENABLE
#define PROJECTCORE_ONLY_ON_DEBUG(x) x
#else /* PROJECTCORE_DEBUG */
#define PROJECTCORE_ONLY_ON_DEBUG(x)
#endif /* PROJECTCORE_DEBUG */

#ifdef PROJECTCORE_ASSERT_ENABLE
    #ifdef PROJECTCORE_COMPILER_MSVC
        #define PROJECTCORE_DEBUGBREAK() __debugbreak()
    #else
        #include <csignal>
        #define PROJECTCORE_DEBUGBREAK() std::raise(SIGINT)
    #endif
    #define PROJECTCORE_ASSERT(x)   if(!(x)) { std::cerr << "ASSERT FAILED! : {}" << #x << std::endl; PROJECTCORE_DEBUGBREAK(); }
#else
    #define PROJECTCORE_ASSERT(x)
    #define PROJECTCORE_DEBUGBREAK()
#endif

// NOT USED YET
#define PROJECTCORE_NODISCARD   [[nodiscard]]
#define PROJECTCORE_INLINE      inline

#define UNKOWN_TYPE_MESSAGE
#define UNKOWN_TYPE_DEBUG
