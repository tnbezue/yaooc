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

void test_push()
{
  TESTCASE("Push");
	yaooc_pointer_bag_t* pb=new(yaooc_pointer_bag);
	char*ptr = M(pb,push,new_array(char,128));
  demo_t* dt = M(pb,push,new_ctor(demo,demo_ctor,99));
  TEST("Size is 2",M(pb,size)==2);
  pointer_bag_const_iterator pi=M(pb,begin);
  TEST("First item is ptr",*pi++==ptr);
  TEST("Second item is ptr",*pi++==dt);
  TEST("Third item is end",pi == M(pb,end));
	delete(pb);
}

void test_push_list()
{
  TESTCASE("Push list");
	yaooc_pointer_bag_t* pb=new(yaooc_pointer_bag);
	char*ptr = new_array(char,128);
  demo_t* dt = new_ctor(demo,demo_ctor,99);
  M(pb,push_list,ptr,dt,NULL);
  TEST("Size is 2",M(pb,size)==2);
  pointer_bag_const_iterator pi=M(pb,begin);
  TEST("First item is ptr",*pi++==ptr);
  TEST("Second item is ptr",*pi++==dt);
  TEST("Third item is end",pi == M(pb,end));

	delete(pb);
}

void test_remove()
{
  TESTCASE("Remove");
	yaooc_pointer_bag_t* pb=new(yaooc_pointer_bag);
	char*ptr = new_array(char,128);
  demo_t* dt = new_ctor(demo,demo_ctor,99);
  M(pb,push_list,ptr,dt,NULL);
  TEST("Size is 2",M(pb,size)==2);
  pointer_bag_const_iterator pi=M(pb,begin);
  TEST("First item is ptr",*pi++==ptr);
  TEST("Second item is ptr",*pi++==dt);
  TEST("Third item is end",pi == M(pb,end));
  puts("Remove first item");
  M(pb,remove,ptr);
  pi=M(pb,begin);
  TEST("Size is 1",M(pb,size)==1);
  TEST("First item is ptr",*pi++==dt);
  TEST("Second item is end",pi == M(pb,end));
  delete(ptr);
	delete(pb);

}

void test_macro()
{
  TESTCASE("Macros");
  PB_INIT; /* Normally at start of routine */
  /* Pointer to object stored at creation */
  char* astring=PB_SAVE(new_array(char,1024));
  astring[0]=0;
  /* Pointer to object stored after creation */
  char* ademo = new_ctor(demo,demo_ctor,99);
  PB_SAVE(ademo);
  /* Pointer to an object can be reused, does not affect item in PB */
  astring=PB_SAVE(yaooc_strdup("Another string"));
  /* Pointer to anything create with new... (not newp...) can be save in PB */
  int * int_array=PB_SAVE(new_array(int,20));
  int_array[0]=22;
  TEST("Bag size is 4",M(local_pb,size)==4);
  /* Object pointers can be set to NULL (or any value) and will not affect items in PB */
  astring=NULL;
  ademo=NULL;
  int_array=NULL;
  PB_DELETE;
  TEST("Bag size is 0",M(local_pb,size)==0);
  PB_EXIT; /* Just before exit.  All items in pointer bag are deleted */
}

test_function tests[]=
{
	test_push,
  test_push_list,
  test_remove,
  test_macro
};

STD_MAIN(tests)
