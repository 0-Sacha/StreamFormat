
#ifdef STREAMFORMAT_PLATFORM_LINUX
#include <sys/types.h>
#include <unistd.h>
#endif

#ifdef STREAMFORMAT_PLATFORM_WINDOWS
#include <Windows.h>
#include <process.h>
#endif

// NOLINTBEGIN(misc-use-internal-linkage)

namespace stream::profiler {
    int get_pid() {
#ifdef STREAMFORMAT_PLATFORM_LINUX
#define return getpid();
#endif

#ifdef STREAMFORMAT_PLATFORM_WINDOWS
        return _getpid();
#endif
        return 0;
    }
}  // namespace stream::profiler

// NOLINTEND(misc-use-internal-linkage)
