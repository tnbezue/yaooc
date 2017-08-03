#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <yaooc/queue.h>
#include <yaooc/string.h>
#include <time.h>
#include "test_harness.h"

QUEUE_DEFINITION(int64)  /* Normally in header file */
QUEUE_IMPLEMENTATION(int64) /* Normally in c source file (.c) */

void test_int64()
{
	int64_queue_pointer si64=new(int64_queue);
	int64_t numbers[]={ 9,10, -2, 44, 55};
	size_t n=sizeof(numbers)/sizeof(numbers[0]);
	size_t i;
	for(i=0;i<n;i++)
		M(si64,push,numbers+i);
	int64_queue_const_iterator ivi;
	for(ivi=M(si64,begin);ivi!=M(si64,end);ivi++)
		printf("%ld ",*ivi);
	puts("\n");
	delete(si64);
}

void test_string_queue()
{
}

test_function tests[]=
{
	test_int64,
  test_string_queue
};

STD_MAIN(tests)
