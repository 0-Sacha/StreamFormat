
#ifdef PROJECTCORE_PLATFORM_LINUX
#include <sys/types.h>
#include <unistd.h>
#endif

#ifdef PROJECTCORE_PLATFORM_WINDOWS
#include <Windows.h>
#include <process.h>
#endif

namespace ProjectCore::ProfilerManager
{
    int GetPid()
    {
#ifdef PROJECTCORE_PLATFORM_LINUX
        return getpid();
#endif

#ifdef PROJECTCORE_PLATFORM_WINDOWS
        return _getpid();
#endif
        return 0;
    }
}