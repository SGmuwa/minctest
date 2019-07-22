/* Simple example of using MINCTEST to test a couple obvious cases. */

#include "minctest.h"
#include <limits.h>

void test1() {
	for(size_t i = 0; i < 4092; i++)
		lok('a' == 'a');
}

void test2() {
	ltests += SIZE_MAX / 2;
	for (size_t i = SIZE_MAX - 10; i < SIZE_MAX; i++)
	{
		lequal(5, 5);
		lfequal(5.5, 5.5);
		lsequal("abc", "abc");
		lsequal("a", "b");
	}
}

int main(int argc, char *argv[])
{
    lrun("Basic equalitypass", test1);
    lrun("Indexing", test2);
    lresults();
	scanf_s("%*s");
    return lfails != 0;
}
