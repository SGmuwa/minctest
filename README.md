# Minctest


Minctest is a very minimal unit-testing "framework" written in ANSI C and
implemented in a single header file. It's handy when you want some real simple
unit tests for a small project.

Basically, it implements assertion and equal functions. It'll track and time
how many tests pass and fail. Failed tests will also display which line the
failing test code was on.

There is a [Node.js port here](https://github.com/codeplea/minctest-node) and a [Lua port here.](https://github.com/codeplea/minctest-lua)

## Features

- **ANSI C with no dependencies**.
- Single header file.
- Reports file and line number for failed assertions.
- Reports run time for each test.
- Tests continue even after an assertion fails.
- Has assertion for checking float equality.
- Released under the zlib license - free for nearly any use.

## Example

    #include "minctest.h"

    void test1() {
    	minctest_ok('a' == 'a');
    }

    void test2() {
        minctest_equal(5, 5);
        minctest_fequal(5.5, 5.5, 0.00001);
        minctest_sequal("abc", "abc");
    }

    int main(int argc, char *argv[])
    {
        minctest_run("test1", test1);
        minctest_run("test2", test2);
        minctest_results();
        return minctest_fails != 0;
    }


That produces the following output:

            test1:
             -- pass: 1                    fail: 0                    time: 12ms
            test2:
             -- pass: 3                    fail: 0                    time: 0ms
    ALL TESTS PASSED (4/4)



## Hints
     All functions/variables start with the "minctest_".

## Users

Minctest is used in almost all of my C projects, including:

* [Tulip Indicators - Financial Technical Analysis Indicators](https://tulipindicators.org)
* [TinyExpr - Math Expression Evaluation Library](https://codeplea.com/tinyexpr)
* [Genann - Neural Network Library](https://codeplea.com/genann)

You can check those out to see how Minctest is used in practice.

If you're using Minctest in your project, let me know. I could add a link back.
