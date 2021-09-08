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
#error EngineCore does not support Linux yet
#endif


// Compiler Define
#ifdef BASE_COMPILER_MSVC
#endif

#ifdef BASE_COMPILER_GCC
#endif


// Include
#include <cstring>

#include <utility>
#include <memory>
#include <limits>
#include <array>
#include <chrono>
#include <algorithm>
#include <functional>
#include <type_traits>


// Intrinsic
#include <intrin.h>