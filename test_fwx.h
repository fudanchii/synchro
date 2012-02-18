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

#include <string.h>

#define test_begin  do {\
    int test_counter = 1;\
    int test_failed  = 0;\
    int test_success = 0;

#define test_end  fprintf(stderr, "%d Tests, %d success, %d failed.\n",\
        test_counter - 1, test_success, test_failed);\
}while (0)

/*
 * Usage example
 *
 * #= assert_(unsigned int, 23 + 22, ==, 55);
 * #! 23 + 22 .== 55
 *
 * `assert_` macro requires, as parameter, variable or
 * function return type, comparison operator, and expected value.
 *
 * Above, we see a test which results 45 with unsigned int
 * type, and the return value to be expected is `55`
 * the test will fail
 *
 * #= assert_(long, 23 + 22, <, 55);
 * #! 23 + 22 .< 55
 *
 */
#define assert_(typ,expr,op,cmp) do { \
    typ test_rst = (typ)expr;\
    fprintf(stderr, "TEST%04d : ", test_counter++);\
    fprintf(stderr, "%s %s %s : ", #expr, #op, #cmp);\
    if (test_rst op (typ)cmp) {\
        test_success++;\
        fprintf(stderr, "...PASSED\n");\
    }\
    else {\
        test_failed++;\
        fprintf(stderr, "...FAILED\n");\
        fprintf(stderr, "           expect : %d\n           result : %d\n", cmp, test_rst);\
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
#define assert_true(expr)       assert_(int, expr, !=, 0)
#define assert_false(expr)      assert_(int, expr, ==, 0)

/*
 * `assert_mem` can be used to test string or memory content
 * for example:
 *
 * #= assert_mem(strdup("hoho\x00ho"), "hohoho", 6);
 *
 * we see the test will failed since the duplicated string get truncated
 * by null character
 *
 * #= assert_mem(strdup("hohoho"), "hohoho", 6);
 * #! strdup("al\"oha") .== "al\"oha"
 *
 */
#define assert_mem(expr,cmp,len) do { \
    char *test_memcnt = (char *) expr;\
    int test_m_iterator;\
    fprintf(stderr, "TEST%04d : ", test_counter++);\
    fprintf(stderr, "%s == %s : ", #expr, #cmp);\
    if (memcmp(test_memcnt,cmp,len) == 0) {\
        test_success++;\
        fprintf(stderr, "...PASSED\n");\
    }\
    else {\
        test_failed++;\
        fprintf(stderr, "...FAILED");\
        fprintf(stderr, "\n           expect : ");\
        for (test_m_iterator = 0; test_m_iterator < len; test_m_iterator++)\
            fprintf(stderr, "%02X ",(unsigned char) cmp[test_m_iterator]);\
        fprintf(stderr, "\n           result : ");\
        for (test_m_iterator = 0; test_m_iterator < len; test_m_iterator++)\
            fprintf(stderr, "%02X ", (unsigned char)test_memcnt[test_m_iterator]);\
        fprintf(stderr, "\n");\
    }\
} while (0);

#endif

