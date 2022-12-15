// Target Define
#ifdef TARGET_DEBUG
#define ENGINECORE_DEBUG
#endif

#ifdef TARGET_RELEASE
#define ENGINECORE_RELEASE
#endif

#ifdef TARGET_DIST
#define ENGINECORE_DIST
#endif


// Architecture Define
#ifdef ARCHITECTURE_X86
#define ENGINECORE_X86
#endif

#ifdef ARCHITECTURE_X64
#define ENGINECORE_X64
#endif


// Platform Define 
#ifdef PLATFORM_WINDOWS
#define ENGINECORE_PLATFORM_WINDOWS
#endif

#ifdef PLATFORM_LINUX
#define ENGINECORE_PLATFORM_LINUX
#endif


// Compiler Define
#ifdef COMPILER_VS
#define ENGINECORE_COMPILER_VS
#endif

#ifdef COMPILER_GMAKE
#define ENGINECORE_COMPILER_GMAKE
#endif


// Include
#include <cstring>
#include <string>

#include <utility>
#include <memory>
#include <limits>
#include <array>
#include <chrono>
#include <bitset>

#include <algorithm>
#include <functional>
#include <type_traits>
#include <concepts>

#include <cmath>

#include <fstream>
#include <iostream>


// Intrinsic
#ifdef ENGINECORE_PLATFORM_WINDOWS
#include <intrin.h>
#endif
