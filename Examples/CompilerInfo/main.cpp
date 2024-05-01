#include "ProjectCore/FLog.h"
#include "ProjectCore/FLog/DefaultLogger.h"

#define COMPILER "Not Detected !"
#if defined(PROJECTCORE_COMPILER_CLANG)
    #undef COMPILER
    #define COMPILER "clang"
#elif defined(PROJECTCORE_COMPILER_GCC)
    #undef COMPILER
    #define COMPILER "gcc"
#elif defined(PROJECTCORE_COMPILER_MSVC)
    #undef COMPILER
    #define COMPILER "msvc"
#endif

#define MODE "RELEASE"
#ifdef PROJECTCORE_DEBUG
    #undef MODE
    #define MODE "DEBUG"
#endif

int main()
{
    ProjectCore::FLog::DefaultLogger::Core().Info("COMPILER : {}", COMPILER);
    ProjectCore::FLog::DefaultLogger::Core().Info("MODE     : {}", MODE);
}
