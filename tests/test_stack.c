/*
		Copyright (C) 2016-2018  by Terry N Bezue

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <yaooc/stack.h>
#include <yaooc/string.h>
#include <time.h>
#include "test_harness.h"

STACK_DEFINITION(long,long_stack);  /* Normally in header file */
STACK_IMPLEMENTATION(long,long_stack); /* Normally in c source file (.c) */

void test_long()
{
	long_stack_pointer si64=new(long_stack);
	long_t numbers[]={ 9,10, -2, 44, 55};
	size_t n=sizeof(numbers)/sizeof(numbers[0]);
	size_t i;
	for(i=0;i<n;i++)
		M(si64,push,numbers+i);
	long_stack_const_iterator ivi;
	for(ivi=M(si64,begin);ivi!=M(si64,end);ivi++)
		printf("%" PRIULONG " ",*ivi);
	puts("\n");
	delete(si64);
}

STACK_DEFINITION(yaooc_string,yaooc_string_stack);
STACK_IMPLEMENTATION(yaooc_string,yaooc_string_stack);

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
  for(spi=M(sp,begin);spi!=M(sp,end);spi++)
    printf("%s ",M(spi,c_str));
  puts("\n");
  delete(sp);
}

test_function tests[]=
{
	test_long,
  test_string_stack
};

STD_MAIN(tests)
