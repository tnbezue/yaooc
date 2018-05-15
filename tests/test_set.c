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
#include <time.h>
#include <yaooc/set.h>

#include "demo_def.inc"
#include "test_harness.h"

SET_DEFINITION(int,int_set)
SET_IMPLEMENTATION(int,int_set)

void test_basic()
{
	int_t numbers1[] = { 10, 20, 30, 11, 4 , 8 };
	int_t numbers2[] = { 4 , 11, 88, 45, 23, 20 };
  size_t n=ARRAY_SIZE(numbers1);
  int_set_pointer s32=new(int_set);
  M(s32,insert_range,numbers1,numbers1+n);
  int j;
  for(j=0;j<n;j++)
    M(s32,insert,numbers2+j);
  int_set_const_iterator i;
  for(i=M(s32,begin);i!=M(s32,end);i++) {
    printf("%d ",*i);
  }
  printf("\n");
  delete(s32);
}

SET_DEFINITION(demo,demo_set)
SET_IMPLEMENTATION(demo,demo_set)
extern int demo_counter;
void test_object()
{
  int i;
  demo_set_pointer dsp=new(demo_set);
  for(i=0;i<10;i++) {
    demo_pointer d=new(demo);
    M(dsp,insert,d);
    delete(d);
  }
  demo_counter=18;
  for(i=0;i<10;i++) {
    demo_pointer d=new(demo);
    M(dsp,insert,d);
    delete(d);
  }
  demo_set_const_iterator dit;
  for(dit=M(dsp,begin);dit!=M(dsp,end);dit++) {
    printf("%d %s\n",dit->x,dit->str);
  }
  delete(dsp);
}

test_function tests[]=
{
	test_basic,
  test_object,
};

STD_MAIN(tests)
