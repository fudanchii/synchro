/*
 * synchro Test Suite Macro collection
 * synchro is collection of simple macro
 * I use to test my C/C++ unit.
 * The design itself is dead simple and
 * straight-forward, since I found another
 * Unit Test tool for C/C++ is either bloated or
 * simply not enough for my need.
 * If you read this source and has intention to use it,
 * go on, I hereby permit the use of this source code
 * under MIT/X11 license.
 *
 * Use it for good, not evil ;)
 *
 * Nurahmadie. 2011
 * */

#ifndef _TEST_FWX_H
#define _TEST_FWX_H

#ifndef _STRING_H
#include <string.h>
#endif


#define test_begin  do {\
    int __test_counter = 1;\
    int __test_failed  = 0;\
    int __test_success = 0

#define test_end  fprintf(stderr, "%d Tests, %d success, %d failed.\n",\
        __test_counter - 1, __test_success, __test_failed);\
}while (0)

/*
 * Usage example
 *
 * #! assert_(unsigned int, gcd(55, 0), ==, 55)
 *
 * `assert_` macro requires, as parameter, variable or
 * function return type, comparison operator, and expected value.
 *
 * Above, we see a test to `gcd` function with `unsigned int` return
 * type, and the return value to be expected is `55`
 *
 */
#define assert_(typ,expr,op,cmp) do { \
    typ __rst = (typ)expr;\
    fprintf(stderr, "TEST%04d : ", __test_counter++);\
    fprintf(stderr, "%s ", #expr);\
    if (__rst op (typ)cmp) {\
        __test_success++;\
        fprintf(stderr, "...PASSED\n");\
    }\
    else {\
        __test_failed++;\
        fprintf(stderr, "expected %d, get %d : ", cmp, __rst);\
        fprintf(stderr, "...FAILED\n");\
    }\
} while(0);

/*
 * Predefined macro below, for convenience
 */
#define assert_eq(expr, cmp)    assert_(int, expr, ==, cmp)
#define assert_ge(expr, cmp)    assert_(int, expr, >=, cmp)
#define assert_le(expr, cmp)    assert_(int, expr, <=, cmp)
#define assert_ne(expr, cmp)    assert_(int, expr, !=, cmp)
#define assert_gt(expr, cmp)    assert_(int, expr, > , cmp)
#define assert_lt(expr, cmp)    assert_(int, expr, < , cmp)

/*
 * `assert_mem` can be used to test string or memory content
 * for example:
 *
 * #! assert_mem(strdup("hoho\x00ho"), "hohoho", 6)
 *
 * we see the test will failed since the duplicated string get truncated
 * by null character
 */
#define assert_mem(expr,cmp,len) do { \
    char *__memcnt = (char *) expr;\
    int __m_iterator;\
    fprintf(stderr, "TEST%04d : ", __test_counter++);\
    fprintf(stderr, "%s ", #expr);\
    if (memcmp(__memcnt,cmp,len) == 0) {\
        __test_success++;\
        fprintf(stderr, "...PASSED\n");\
    }\
    else {\
        __test_failed++;\
        fprintf(stderr, "expected\n");\
        for (__m_iterator = 0; __m_iterator < len; __m_iterator++)\
            fprintf(stderr, "%02X ", cmp[__m_iterator]);\
        fprintf(stderr, "\nget\n");\
        for (__m_iterator = 0; __m_iterator < len; __m_iterator++)\
            fprintf(stderr, "%02X ", __memcnt[__m_iterator]);\
        fprintf(stderr, "\n : ...FAILED\n");\
    }\
} while (0);

#endif

