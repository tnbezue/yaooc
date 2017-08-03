#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <yaooc/stack.h>
#include <yaooc/string.h>
#include <time.h>
#include "test_harness.h"

STACK_DEFINITION(int64)  /* Normally in header file */
STACK_IMPLEMENTATION(int64) /* Normally in c source file (.c) */

void test_int64()
{
	int64_stack_pointer si64=new(int64_stack);
	int64_t numbers[]={ 9,10, -2, 44, 55};
	size_t n=sizeof(numbers)/sizeof(numbers[0]);
	size_t i;
	for(i=0;i<n;i++)
		M(si64,push_v,numbers[i]);
	int64_stack_const_iterator ivi;
	for(ivi=M(si64,begin);ivi!=M(si64,end);ivi++)
		printf("%ld ",*ivi);
	puts("\n");
	delete(si64);
}

STACK_DEFINITION(yaooc_string)
STACK_IMPLEMENTATION(yaooc_string)

const char* words[] = { "This", "is","a","stack","test"};
void test_string_stack()
{
  yaooc_string_stack_pointer sp=new(yaooc_string_stack);
  int i,n=ARRAY_SIZE(words);
  for(i=0;i<n;i++) {
    yaooc_string_pointer s1=new_ctor(yaooc_string,yaooc_string_ctor_ccs,words[i]);
    M(sp,push,s1);
    delete(s1);
  }
  yaooc_string_stack_const_iterator spi;
  for(spi=M(sp,cbegin);spi!=M(sp,cend);spi++)
    printf("%s ",M(spi,c_str));
  puts("\n");
  delete(sp);
}

test_function tests[]=
{
	test_int64,
  test_string_stack
};

STD_MAIN(tests)
