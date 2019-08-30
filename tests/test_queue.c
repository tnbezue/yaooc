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
#include <yaooc/queue.h>
#include <yaooc/string.h>
#include <time.h>
#include "test_harness.h"

QUEUE_DEFINITION(long,long_queue);  /* Normally in header file */
QUEUE_IMPLEMENTATION(long,long_queue); /* Normally in c source file (.c) */

void test_long()
{
	long_queue_pointer slong=new(long_queue);
	long_t numbers[]={ 9,10, -2, 44, 55};
	size_t n=ARRAY_SIZE(numbers);
	size_t i;
	for(i=0;i<n;i++)
		M(slong,push,numbers+i);
	long_queue_const_iterator ivi;
	for(ivi=M(slong,begin);ivi!=M(slong,end);ivi++)
		printf("%" PRId64 " ",*ivi);
	puts("\n");
	delete(slong);
}

void test_string_queue()
{
}

test_function tests[]=
{
	test_long,
  test_string_queue
};

STD_MAIN(tests)
