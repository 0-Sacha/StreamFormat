#pragma once

#ifndef PROJECTCORE_DO_NOT_USE_DEFAULT_MACRO
    #if defined(__clang__)
        #define PROJECTCORE_COMPILER_CLANG
    #elif defined(__GNUC__) || defined(__GNUG__)
        #define PROJECTCORE_COMPILER_GCC
    #elif defined(_MSC_VER)
        #define PROJECTCORE_COMPILER_MSVC
    #endif

    #ifdef PROJECTCORE_COMPILER_MSVC
        #ifdef _DEBUG
            #define PROJECTCORE_DEBUG
        #endif
    #endif

    #if defined(PROJECTCORE_COMPILER_CLANG) || defined(PROJECTCORE_COMPILER_GCC)
        #if !defined(NDEBUG)
            #define PROJECTCORE_DEBUG
        #endif
    #endif
#endif
