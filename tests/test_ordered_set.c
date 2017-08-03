#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <yaooc/ordered_set.h>

#include "demo_def.inc"
#include "test_harness.h"

ORDERED_SET_DEFINITION(int32)
ORDERED_SET_IMPLEMENTATION(int32)

void test_basic()
{
	int32_t numbers1[] = { 10, 20, 30, 11, 4 , 8 };
	int32_t numbers2[] = { 4 , 11, 88, 45, 23, 20 };
  size_t n=ARRAY_SIZE(numbers1);
  int32_ordered_set_pointer s32=new(int32_ordered_set);
  M(s32,insert_range,numbers1,numbers1+n);
  int j;
  for(j=0;j<n;j++)
    M(s32,insert_v,numbers2[j]);
  int32_ordered_set_const_iterator i;
  for(i=M(s32,cbegin);i!=M(s32,cend);i++) {
    printf("%d ",*i);
  }
  printf("\n");
  delete(s32);
}

ORDERED_SET_DEFINITION(demo)
ORDERED_SET_IMPLEMENTATION(demo)
extern int demo_counter;
void test_object()
{
  int i;
  demo_ordered_set_pointer dsp=new(demo_ordered_set);
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
  demo_ordered_set_const_iterator dit;
  for(dit=M(dsp,cbegin);dit!=M(dsp,cend);dit++) {
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
