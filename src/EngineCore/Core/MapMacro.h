/*
 * Created by William Swanson in 2012.
 *
 * I, William Swanson, dedicate this work to the public domain.
 * I waive all rights to the work worldwide under copyright law,
 * including all related and neighboring rights,
 * to the extent allowed by law.
 *
 * You can copy, modify, distribute and perform the work,
 * even for commercial purposes, all without asking permission.
 */

#pragma once

#define ENGINECORE_INTERNAL_EVAL0(...)                     __VA_ARGS__
#define ENGINECORE_INTERNAL_EVAL1(...)                     ENGINECORE_INTERNAL_EVAL0(ENGINECORE_INTERNAL_EVAL0(ENGINECORE_INTERNAL_EVAL0(__VA_ARGS__)))
#define ENGINECORE_INTERNAL_EVAL2(...)                     ENGINECORE_INTERNAL_EVAL1(ENGINECORE_INTERNAL_EVAL1(ENGINECORE_INTERNAL_EVAL1(__VA_ARGS__)))
#define ENGINECORE_INTERNAL_EVAL3(...)                     ENGINECORE_INTERNAL_EVAL2(ENGINECORE_INTERNAL_EVAL2(ENGINECORE_INTERNAL_EVAL2(__VA_ARGS__)))
#define ENGINECORE_INTERNAL_EVAL4(...)                     ENGINECORE_INTERNAL_EVAL3(ENGINECORE_INTERNAL_EVAL3(ENGINECORE_INTERNAL_EVAL3(__VA_ARGS__)))
#define ENGINECORE_INTERNAL_EVAL(...)                      ENGINECORE_INTERNAL_EVAL4(ENGINECORE_INTERNAL_EVAL4(ENGINECORE_INTERNAL_EVAL4(__VA_ARGS__)))

#define ENGINECORE_INTERNAL_MAP_END(...)
#define ENGINECORE_INTERNAL_MAP_OUT
#define ENGINECORE_INTERNAL_MAP_COMMA                      ,

#define ENGINECORE_INTERNAL_MAP_GET_END2()                 0, ENGINECORE_INTERNAL_MAP_END
#define ENGINECORE_INTERNAL_MAP_GET_END1(...)              ENGINECORE_INTERNAL_MAP_GET_END2
#define ENGINECORE_INTERNAL_MAP_GET_END(...)               ENGINECORE_INTERNAL_MAP_GET_END1
#define ENGINECORE_INTERNAL_MAP_NEXT0(test, next, ...)     next ENGINECORE_INTERNAL_MAP_OUT
#define ENGINECORE_INTERNAL_MAP_NEXT1(test, next)          ENGINECORE_INTERNAL_MAP_NEXT0(test, next, 0)
#define ENGINECORE_INTERNAL_MAP_NEXT(test, next)           ENGINECORE_INTERNAL_MAP_NEXT1(ENGINECORE_INTERNAL_MAP_GET_END test, next)

#define ENGINECORE_INTERNAL_MAP0(f, x, peek, ...)          f(x) ENGINECORE_INTERNAL_MAP_NEXT(peek, ENGINECORE_INTERNAL_MAP1)(f, peek, __VA_ARGS__)
#define ENGINECORE_INTERNAL_MAP1(f, x, peek, ...)          f(x) ENGINECORE_INTERNAL_MAP_NEXT(peek, ENGINECORE_INTERNAL_MAP0)(f, peek, __VA_ARGS__)

#define ENGINECORE_INTERNAL_MAP_LIST_NEXT1(test, next)     ENGINECORE_INTERNAL_MAP_NEXT0(test, ENGINECORE_INTERNAL_MAP_COMMA next, 0)
#define ENGINECORE_INTERNAL_MAP_LIST_NEXT(test, next)      ENGINECORE_INTERNAL_MAP_LIST_NEXT1(ENGINECORE_INTERNAL_MAP_GET_END test, next)

#define ENGINECORE_INTERNAL_MAP_LIST0(f, x, peek, ...)     f(x) ENGINECORE_INTERNAL_MAP_LIST_NEXT(peek, ENGINECORE_INTERNAL_MAP_LIST1)(f, peek, __VA_ARGS__)
#define ENGINECORE_INTERNAL_MAP_LIST1(f, x, peek, ...)     f(x) ENGINECORE_INTERNAL_MAP_LIST_NEXT(peek, ENGINECORE_INTERNAL_MAP_LIST0)(f, peek, __VA_ARGS__)

/**
 * Applies the function macro `f` to each of the remaining parameters.
 */
#define ENGINECORE_MAPMACOR(f, ...)                        ENGINECORE_INTERNAL_EVAL(ENGINECORE_INTERNAL_MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters and
 * inserts commas between the results.
 */
#define ENGINECORE_MAPMACOR_LIST(f, ...)                   ENGINECORE_INTERNAL_EVAL(ENGINECORE_INTERNAL_MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))