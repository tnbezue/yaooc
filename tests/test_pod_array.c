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
#include <yaooc/pod_array.h>
#include "test_harness.h"

YAOOC_POD_ARRAY(int,int_pod_array)

void test_insert()
{
  TESTCASE("Int array insert")
  int_pod_array_t* intsa=new(int_pod_array);
  M(intsa,insert_back,10);
  M(intsa,insert_back,20);
  M(intsa,insert_back,30);
  M(intsa,insert_back,40);
  M(intsa,insert_back,50);
  M(intsa,insert_back,60);
  M(intsa,insert_back,70);
  int_pod_array_const_iterator i;
  FOR_EACH(i,intsa) {
    printf("%d ",*i);
  }
  printf("\n");
  i=M(intsa,find,40);
  TEST("Find",*i==40);
  i=int_pod_array_find(intsa,37);
  TEST("Find failed",i==M(intsa,end));
  delete(intsa);
}

void test_erase()
{
  TESTCASE("Int array erase")
  int_pod_array_t* intsa=new(int_pod_array);
  M(intsa,insert_back,10);
  M(intsa,insert_back,20);
  M(intsa,insert_back,30);
  M(intsa,insert_back,40);
  M(intsa,insert_back,50);
  M(intsa,insert_back,60);
  M(intsa,insert_back,70);
//  int_pod_array_erase(intsa,3);
  int_pod_array_const_iterator i;
  FOR_EACH(i,intsa) {
    printf("%d ",*i);
  }
  printf("\n");
  i=M(intsa,begin);
  i+=5;
  M(intsa,erase,i);
  FOR_EACH(i,intsa) {
    printf("%d ",*i);
  }
  printf("\n");
  delete(intsa);
}

struct demo_s {
  unsigned long ul;
  int m;
};

typedef struct {
  struct demo_s;
  int x;
  double y;
} sample_t;

sample_t input[] =
{
  { { 33UL, 5 } , 6 , 23.7 },
  { { 7UL, 4442 }, 22, 99.5 },
  { { 33UL, 55 }, 66, 237.0 },
  { { 919UL, 504 }, 248, 704 },
};
DEFINE_TYPE_INFO(sample,N,N,N,N,N,N,N,N,NULL)

sample_t not_found = { { 33UL, 5} , 6, 23.72 };
YAOOC_POD_ARRAY(sample,sample_pod_array)

void test_struct_insert()
{
  sample_pod_array_t* ssa = new(sample_pod_array);
  int i,n=ARRAY_SIZE(input);
  for(i=0;i<n;i++)
    M(ssa,insert_back,input[i]);
  sample_pod_array_const_iterator isa;
  FOR_EACH(isa,ssa) {
    printf("%lu %d %d %lf\n",isa->ul,isa->m,isa->x,isa->y);
  }
  isa=M(ssa,find,input[3]);
  TEST("Find",isa!=M(ssa,end));
  isa=M(ssa,find,not_found);
  TEST("Find",isa==M(ssa,end));
  delete(ssa);
}

test_function tests[] =
{
  test_insert,
  test_erase,
  test_struct_insert
};

STD_MAIN(tests)
