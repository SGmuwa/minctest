/*
 *
 * MINCTEST - Minimal C Test Library - 0.4.1-SGmuwa
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


/* Version of minctest. */
#define MINCTEST_VERSION "0.4.1-SGmuwa"



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
        printf("error at %s:%d\n", __FILE__, __LINE__);\
    }} while (0)


/* Prototype to assert equal. */
#define minctest_equal_base(equality, expect, actual, format) do {\
    ++minctest_tests;\
    if (!(equality)) {\
        ++minctest_fails;\
        printf("expect: <"format">, actual: <"format"> at %s:%d\n", (expect), (actual), __FILE__, __LINE__);\
    }} while (0)


/* Assert two integers are equal. */
#define minctest_equal(expect, actual)\
    minctest_equal_base((expect) == (actual), (long long int)expect, (long long int)actual, "%lld")


/* Assert two long doubles are equal. */
/* r: How far apart can long doubles be before we consider them unequal. */
#define minctest_fequal(expect, actual, r)\
    minctest_equal_base(fabsl((long double)(expect)-(long double)(actual)) <= (long double)r\
     && fabsl((long double)(expect)-(long double)(actual)) == fabsl((long double)(expect)-(long double)(actual)), (long double)(expect), (long double)(actual), "%Lf")


/* Assert two strings are equal. */
#define minctest_sequal(expect, actual)\
    minctest_equal_base(strcmp(expect, actual) == 0, expect, actual, "%s")


/* Print memory block "mem" of "size" bytes as hex numbers. */
void minctest_printmemory(void * mem, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%04X%*c", *((char *)mem + i), i + 1 < size, ' ');
    }
}


/* Prototype to assert equal for memory blocks. */
/* Assert two bloks of memory. "n" - number of bytes. */
/* void printer(void * point, size_t count) - function of print memory. */
#define minctest_mequal_base(expect, actual, n, printer) do {\
    ++minctest_tests;\
    if(expect == NULL){\
        ++minctest_fails;\
        printf("%s:%d expect == NULL at %s:%d", __FILE__, __LINE__);\
    }\
    else if(actual == NULL){\
        ++minctest_fails;\
        printf("%s:%d actual == NULL at %s:%d", __FILE__, __LINE__);\
    }\
    else if (!(memcmp(expect, actual, n))) {\
        ++minctest_fails;\
        printf("expect: <");\
        printer(expect, n);\
        printf(">, actual: <");\
        printer(actual, n);\
        printf("> at %s:%d \n", __FILE__, __LINE__);\
    }} while (0)


/* Assert two bloks of memory. "n" - number of bytes.*/
#define minctest_mequal(expect, actual, n)\
    minctest_mequal_base(expect, actual, n, minctest_printmemory)


#endif /*__MINCTEST_H__*/
