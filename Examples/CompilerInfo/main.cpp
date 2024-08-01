#include "StreamFormat/FLog.h"
#include "StreamFormat/FLog/DefaultLogger.h"

#define COMPILER "Not Detected !"
#if defined(STREAMFORMAT_COMPILER_CLANG)
    #undef COMPILER
    #define COMPILER "clang"
#elif defined(STREAMFORMAT_COMPILER_GCC)
    #undef COMPILER
    #define COMPILER "gcc"
#elif defined(STREAMFORMAT_COMPILER_MSVC)
    #undef COMPILER
    #define COMPILER "msvc"
#endif

#define MODE "RELEASE"
#ifdef STREAMFORMAT_DEBUG
    #undef MODE
    #define MODE "DEBUG"
#endif

int main()
{
    StreamFormat::FLog::DefaultLogger::Core().Info("COMPILER : {}", COMPILER);
    StreamFormat::FLog::DefaultLogger::Core().Info("MODE     : {}", MODE);
}
