/*
 * synchro Test Suite Macro collection
 * synchro is collection of simple macro
 * I used to test my C/C++ unit.
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

#define assert_(typ,expr,op,cmp) do { \
    typ __rst = (typ)expr;\
    if (__rst op (typ)cmp) {\
        printf("...PASSED\n");\
    }\
    else {\
        printf("expected %d, get %d : ", cmp, __rst);\
        printf("...FAILED\n");\
    }\
} while(0);

#define assert_eq(expr, cmp)    assert_(int, expr, ==, cmp)
#define assert_gq(expr, cmp)    assert_(int, expr, >=, cmp)
#define assert_lq(expr, cmp)    assert_(int, expr, <=, cmp)
#define assert_nq(expr, cmp)    assert_(int, expr, !=, cmp)
#define assert_gt(expr, cmp)    assert_(int, expr, > , cmp)
#define assert_lt(expr, cmp)    assert_(int, expr, < , cmp)
    
#define assert_mem(expr,cmp,len) do { \
    char *__memcnt = expr;\
    int __m_iterator;\
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
