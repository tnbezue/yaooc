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
#include <stddef.h>
#include <yaooc/pointer_bag.h>
#include "test_harness.h"
#include "demo_def.inc"

void test_add()
{
  TESTCASE("Add");
	yaooc_pointer_bag_t* pb=new(yaooc_pointer_bag);
	char*ptr = M(pb,add,new_array(char,128));
  demo_t* dt = M(pb,add,new_ctor(demo,demo_ctor,99));
  TEST("Size is 2",M(pb,size)==2);
  yaooc_pointer_bag_const_iterator pi=M(pb,begin);
  TEST("First item is ptr",pi->pointer_==ptr); pi++;
  TEST("Second item is ptr",pi->pointer_==dt); pi++;
  TEST("Third item is end",pi == M(pb,end));
	delete(pb);
}


void test_remove()
{
  TESTCASE("Remove");
	yaooc_pointer_bag_t* pb=new(yaooc_pointer_bag);
	char*ptr = new_array(char,128);
  demo_t* dt = new_ctor(demo,demo_ctor,99);
  M(pb,add,ptr);
  M(pb,add,dt);
  TEST("Size is 2",M(pb,size)==2);
  yaooc_pointer_bag_const_iterator pi=M(pb,begin);
  TEST("First item is ptr",pi->pointer_==ptr); pi++;
  TEST("Second item is ptr",pi->pointer_==dt); pi++;
  TEST("Third item is end",pi == M(pb,end));
  puts("Remove first item");
  M(pb,remove,ptr);
  pi=M(pb,begin);
  TEST("Size is 1",M(pb,size)==1);
  TEST("First item is ptr",pi->pointer_==dt); pi++;
  TEST("Second item is end",pi == M(pb,end));
  delete(ptr);
	delete(pb);
}

int __x__;
yaooc_struct(demo_pb)
{
  int x;
};

void demo_pb_default_ctor(pointer p)
{
  ((demo_pb_pointer)p)->x=__x__++;
  optr+=sprintf(optr,":DEMO_CTOR%d",((demo_pb_pointer)p)->x);
}

void demo_pb_dtor(pointer p)
{
  optr+=sprintf(optr,":DEMO_DTOR%d",((demo_pb_pointer)p)->x);
}

DEFINE_TYPE_INFO(demo_pb,Y,Y,N,N,N,N,N,N,NULL);

void test_static()
{
  __x__ = 0;
  yaooc_pointer_bag_t* pb=new(yaooc_pointer_bag);
  optr=output;
  optr+=sprintf(optr,"New d1");
  demo_t d1,d2,d3[10];
  M(pb,add_static,newp(&d1,demo_pb),demo_pb_ti,1);
  optr=output;
  optr+=sprintf(optr,"New d2");
  M(pb,add_static,newp(&d2,demo_pb),demo_pb_ti,1);
  optr=output;
  optr+=sprintf(optr,"New d3");
  M(pb,add_static,newp_array(&d3,demo_pb,10),demo_pb_ti,10);
  optr=output;
  optr+=sprintf(optr,"Another d1");
  M(pb,add_static,newp(&d1,demo_pb),demo_pb_ti,1);
  puts(output);
  optr=output;
  optr+=sprintf(optr,"New d1");
  delete(pb);
  puts(output);
}

/*
  Much easier to use macros
*/
void test_macro()
{
  TESTCASE("Macros");
  pb_init(); /* Normally at start of routine */
  /* Pointer to object stored at creation */
  char* astring=pb_new_array(char,1024);
  astring[0]=0;
  /* Pointer to object stored after creation */
  char* ademo = pb_new_ctor(demo,demo_ctor,99);
  (void)ademo;
  /* Pointer to an object can be reused, does not affect item in PB */
  astring=pb_save(yaooc_strdup("Another string"));
  demo_t d;

  /* Pointer to anything create with new et all can be save in PB */
  int * int_array=pb_new_array(int,20);
  int_array[0]=22;
  TEST("Bag size is 4",M(local_pb,size)==4);

  pb_delete();
  TEST("Bag size is 0",M(local_pb,size)==0);
  pb_exit(); /* Just before exit.  All items in pointer bag are deleted */
}

test_function tests[]=
{
	test_add,
  test_remove,
  test_static,
  test_macro,
};

STD_MAIN(tests)
