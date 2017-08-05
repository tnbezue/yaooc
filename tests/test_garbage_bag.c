#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/garbage_bag.h>
#include "test_harness.h"
#include "demo_def.inc"

void test_push()
{
  TESTCASE("Push");
	yaooc_garbage_bag_t* pb=new(yaooc_garbage_bag);
	char*ptr = M(pb,push,new_array(char,128));
  demo_t* dt = M(pb,push,new_ctor(demo,demo_ctor,99));
  TEST("Size is 2",M(pb,size)==2);
  TEST("First item is ptr",pb->pointers_->array_[0]==ptr);
  TEST("Second item is dt",pb->pointers_->array_[1]==dt);
	delete(pb);
}

void test_push_list()
{
  TESTCASE("Push list");
	yaooc_garbage_bag_t* pb=new(yaooc_garbage_bag);
	char*ptr = new_array(char,128);
  demo_t* dt = new_ctor(demo,demo_ctor,99);
  M(pb,push_list,ptr,dt,NULL);
  TEST("Size is 2",M(pb,size)==2);
  TEST("First item is ptr",pb->pointers_->array_[0]==ptr);
  TEST("Second item is dt",pb->pointers_->array_[1]==dt);
	delete(pb);
}

void test_remove()
{
  TESTCASE("Remove");
	yaooc_garbage_bag_t* pb=new(yaooc_garbage_bag);
	char*ptr = new_array(char,128);
  demo_t* dt = new_ctor(demo,demo_ctor,99);
  M(pb,push_list,ptr,dt,NULL);
  TEST("Size is 2",M(pb,size)==2);
  TEST("First item is ptr",pb->pointers_->array_[0]==ptr);
  TEST("Second item is dt",pb->pointers_->array_[1]==dt);
  puts("Remove first item");
  M(pb,remove,ptr);
  TEST("Size is 1",M(pb,size)==1);
  TEST("First item is dt",pb->pointers_->array_[0]==dt);
  delete(ptr);
	delete(pb);

}

#define int_ti int32_ti
void test_macro()
{
  TESTCASE("Macros");
  GB_INIT; /* Normally at start of routine */
  /* Pointer to object stored at creation */
  char* astring=GB_SAVE(new_array(char,1024));
  astring[0]=0;
  /* Pointer to object stored after creation */
  char* ademo = new_ctor(demo,demo_ctor,99);
  GB_SAVE(ademo);
  /* Pointer to an object can be reused, does not affect item in PB */
  astring=GB_SAVE(yaooc_strdup("Another string"));
  /* Pointer to anything create with new... (not newp...) can be save in PB */
  int * int_array=GB_SAVE(new_array(int,20));
  int_array[0]=22;
  TEST("Bag size is 4",M(local_pb,size)==4);
  /* Object pointers can be set to NULL (or any value) and will not affect items in PB */
  astring=NULL;
  ademo=NULL;
  int_array=NULL;
  GB_EXIT; /* Just before exit.  All items in pointer bag are deleted */
  TEST("Bag size is 0",M(local_pb,size)==0);
}

test_function tests[]=
{
	test_push,
  test_push_list,
  test_push_list,
  test_remove,
  test_macro
};

STD_MAIN(tests)
