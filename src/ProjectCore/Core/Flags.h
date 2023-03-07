#pragma once

// Target Define
#ifdef TARGET_DEBUG
#define PROJECTCORE_DEBUG
#endif

#ifdef TARGET_RELEASE
#define PROJECTCORE_RELEASE
#endif

#ifdef TARGET_DIST
#define PROJECTCORE_DIST
#endif


// Architecture Define
#ifdef ARCHITECTURE_X86
#define PROJECTCORE_X86
#endif

#ifdef ARCHITECTURE_X64
#define PROJECTCORE_X64
#endif


// Platform Define 
#ifdef PLATFORM_WINDOWS
#define PROJECTCORE_PLATFORM_WINDOWS
#endif

#ifdef PLATFORM_LINUX
#define PROJECTCORE_PLATFORM_LINUX
#endif


// Compiler Define
#ifdef COMPILER_VS
#define PROJECTCORE_COMPILER_VS
#endif

#ifdef COMPILER_GMAKE
#define PROJECTCORE_COMPILER_GMAKE
#endif


// Compiler Macro Define
#ifndef __FUNCSIG__
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif

#ifndef __FUNCDNAME__
#define __FUNCDNAME__ __PRETTY_FUNCTION__
#endif
