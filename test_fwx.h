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

/*
 * Usage example
 *
 * assert_(unsigned int, gcd(55, 0), ==, 55)
 *
 * `assert_` macro requires as parameter variable or
 * function return type, comparation operator, and expected value.
 * Above, we see a test to `gcd` function with `unsigned int` return
 * type, and the return value to be expected is `55`
 *
 *
 * notice that before any assert_ call, user shall define variable named
 * __test_counter as `int` with initial value `1`
 *
 */
#define assert_(typ,expr,op,cmp) do { \
    typ __rst = (typ)expr;\
    printf("TEST%04d : ", __test_counter++);\
    printf("%s ", #expr);\
    if (__rst op (typ)cmp) {\
        printf("...PASSED\n");\
    }\
    else {\
        printf("expected %d, get %d : ", cmp, __rst);\
        printf("...FAILED\n");\
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
 * assert_mem(strdup("hoho\x00ho"), "hohoho", 6)
 *
 * we see the test will failed since the duplicated string get truncated
 * by null character
 */
#define assert_mem(expr,cmp,len) do { \
    char *__memcnt = (char *) expr;\
    int __m_iterator;\
    printf("TEST%04d : ", __test_counter++);\
    printf("%s ", #expr);\
    if (memcmp(__memcnt,cmp,len) == 0) {\
        printf("...PASSED\n");\
    }\
    else {\
        printf("expected\n");\
        for (__m_iterator = 0; __m_iterator < len; __m_iterator++)\
            printf("%02X ", cmp[__m_iterator]);\
        printf("\nget\n");\
        for (__m_iterator = 0; __m_iterator < len; __m_iterator++)\
            printf("%02X ", __memcnt[__m_iterator]);\
        printf("\n : ...FAILED\n");\
    }\
} while (0);

#endif

