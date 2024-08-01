#pragma once

#ifndef STREAMFORMAT_DO_NOT_USE_DEFAULT_MACRO
#if defined(__clang__)
#define STREAMFORMAT_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
#define STREAMFORMAT_COMPILER_GCC
#elif defined(_MSC_VER)
#define STREAMFORMAT_COMPILER_MSVC
#endif

#ifdef STREAMFORMAT_COMPILER_MSVC
#ifdef _DEBUG
#define STREAMFORMAT_DEBUG
#endif
#endif

#if defined(STREAMFORMAT_COMPILER_CLANG) || defined(STREAMFORMAT_COMPILER_GCC)
#if !defined(NDEBUG)
#define STREAMFORMAT_DEBUG
#endif
#endif
#endif
