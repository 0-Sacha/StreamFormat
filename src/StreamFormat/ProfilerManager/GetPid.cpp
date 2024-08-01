
#ifdef STREAMFORMAT_PLATFORM_LINUX
#include <sys/types.h>
#include <unistd.h>
#endif

#ifdef STREAMFORMAT_PLATFORM_WINDOWS
#include <Windows.h>
#include <process.h>
#endif

namespace StreamFormat::ProfilerManager
{
    int GetPid()
    {
#ifdef STREAMFORMAT_PLATFORM_LINUX
        return getpid();
#endif

#ifdef STREAMFORMAT_PLATFORM_WINDOWS
        return _getpid();
#endif
        return 0;
    }
}