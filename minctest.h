/*
 *
 * MINCTEST - Minimal C Test Library - 0.3.1-SGmuwa
 *
 * Copyright (c) 2014-2017 Lewis Van Winkle
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

/*
* Sidorenko Mikhail Pavlovich [SG]Muwa https://github.com/SGmuwa 22.07.2019.
*/



/*
 * MINCTEST - Minimal testing library for C
 *
 *
 * Example:
 *
 *      void test1(void) {
 *           minctest_ok('a' == 'a');
 *      }
 *
 *      void test2(void) {
 *           minctest_equal(5, 6);
 *           minctest_fequal(5.5, 5.6, 0.001);
 *      }
 *
 *      int main(void) {
 *           minctest_run("test1", test1);
 *           minctest_run("test2", test2);
 *           minctest_results();
 *           return minctest_fails != 0;
 *      }
 *
 *
 *
 * Hints:
 *      All functions/variables start with the letter 'l'.
 *
 */


#ifndef __MINCTEST_H__
#define __MINCTEST_H__

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>



/* Track the number of passes, fails. */
/* NB this is made for all tests to be in one file. */
static size_t minctest_tests = 0;
static size_t minctest_fails = 0;

/* Reset number of passes, fails. */
#define minctest_reset() minctest_tests = 0; minctest_fails = 0

/* Display the test results. */
#define minctest_results() do {\
    if (minctest_fails == 0) {\
        printf("ALL TESTS PASSED (%zu/%zu)\n", minctest_tests, minctest_tests);\
    } else {\
        printf("SOME TESTS FAILED (%zu/%zu)\n", minctest_tests-minctest_fails, minctest_tests);\
    }\
} while (0)


/* Run a test. Name can be any string to print out, test is the function name to call. */
#define minctest_run(name, test) do {\
    const size_t ts = minctest_tests;\
    const size_t fs = minctest_fails;\
    const clock_t start = clock();\
    printf("\t%s:\n", name);\
    test();\
    printf("\t -- pass: %-20zu fail: %-20zu time: %ldms\n",\
            (minctest_tests-ts)-(minctest_fails-fs), minctest_fails-fs,\
            (long)((clock() - start) * 1000 / CLOCKS_PER_SEC));\
} while (0)


/* Assert a true statement. */
#define minctest_ok(test) do {\
    ++minctest_tests;\
    if (!(test)) {\
        ++minctest_fails;\
        printf("%s:%d error \n", __FILE__, __LINE__);\
    }} while (0)


/* Prototype to assert equal. */
#define minctest_equal_base(equality, a, b, format) do {\
    ++minctest_tests;\
    if (!(equality)) {\
        ++minctest_fails;\
        printf("%s:%d (<"format"> != <"format">)\n", __FILE__, __LINE__, (a), (b));\
    }} while (0)


/* Assert two integers are equal. */
#define minctest_equal(a, b)\
    minctest_equal_base((a) == (b), (long long int)a, (long long int)b, "%lld")


/* Assert two long double are equal.
r: How far apart can floats be before we consider them unequal. */
#define minctest_fequal(a, b, r)\
    minctest_equal_base(fabsl((long double)(a)-(long double)(b)) <= (long double)r\
     && fabsl((long double)(a)-(long double)(b)) == fabsl((long double)(a)-(long double)(b)), (long double)(a), (long double)(b), "%Lf")


/* Assert two strings are equal. */
#define minctest_sequal(a, b)\
    minctest_equal_base(strcmp(a, b) == 0, a, b, "%s")


#endif /*__MINCTEST_H__*/
