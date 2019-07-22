/* Simple example of using MINCTEST to test a couple obvious cases. */

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
