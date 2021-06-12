#pragma once

// Target Define
#ifdef BASE_TARGET_DEBUG
#define ENGINE_CORE_DEBUG
#endif

#ifdef BASE_TARGET_RELEASE
#define ENGINE_CORE_RELEASE
#endif

#ifdef BASE_TARGET_DIST
#define ENGINE_CORE_DIST
#endif


// Architecture Define
#ifdef BASE_ARCHITECTURE_X86
#define ENGINE_CORE_X86
#endif

#ifdef BASE_ARCHITECTURE_X86_64
#define ENGINE_CORE_X64
#endif


// Platform Define 
#ifdef BASE_PLATFORM_WINDOWS
#define ENGINE_CORE_PLATFORM_WINDOWS
#endif

#ifdef BASE_PLATFORM_LINUX
#error EngineCore doesn't support Linux yet
#endif


// Compiler Define
#ifdef BASE_COMPILER_MSVC
#endif

#ifdef BASE_COMPILER_GCC
#error EngineCore doesn't support GCC yet
#endif


// Include 
#include <utility>
#include <limits>
#include <array>
#include <bitset>
#include <thread>
#include <string>
#include <chrono>
#include <algorithm>
#include <functional>



// Intrinsic

#include <intrin.h>
#include <xmmintrin.h>


