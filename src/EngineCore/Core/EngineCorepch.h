// Target Define
#ifdef BASE_TARGET_DEBUG
#define ENGINECORE_DEBUG
#endif

#ifdef BASE_TARGET_RELEASE
#define ENGINECORE_RELEASE
#endif

#ifdef BASE_TARGET_DIST
#define ENGINECORE_DIST
#endif


// Architecture Define
#ifdef BASE_ARCHITECTURE_X86
#define ENGINECORE_X86
#endif

#ifdef BASE_ARCHITECTURE_X86_64
#define ENGINECORE_X64
#endif


// Platform Define 
#ifdef BASE_PLATFORM_WINDOWS
#define ENGINECORE_PLATFORM_WINDOWS
#endif

#ifdef BASE_PLATFORM_LINUX
#define ENGINECORE_PLATFORM_LINUX
#endif


// Compiler Define
#ifdef BASE_COMPILER_MSVC
#define ENGINECORE_COMPILER_MSVC
#endif

#ifdef BASE_COMPILER_GCC
#define ENGINECORE_COMPILER_GCC
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
