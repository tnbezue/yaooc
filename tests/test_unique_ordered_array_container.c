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
#include <yaooc/unique_ordered_array_container.h>
#include "test_harness.h"
#include "simple_object.inc"

typedef int_t* int_unique_ordered_array_container_iterator;
typedef const int_t* int_unique_ordered_array_container_const_iterator;

yaooc_class_table(int_unique_ordered_array_container)
{
  yaooc_unique_ordered_array_container_class_table_t;
  int_unique_ordered_array_container_iterator (*find)(const_pointer,const_pointer);
  int_unique_ordered_array_container_const_iterator (*insert)(const_pointer,const_iterator,const_pointer);
  int_unique_ordered_array_container_const_iterator (*insert_range)(const_pointer,const_iterator,const_iterator,const_iterator);
  int_unique_ordered_array_container_const_iterator (*insert_n)(const_pointer,const_iterator,size_t,const_pointer);
  int_unique_ordered_array_container_iterator (*erase)(pointer,const_iterator);
  int_unique_ordered_array_container_iterator (*erase_range)(pointer,const_iterator,const_iterator);
  size_t (*erase_value)(pointer,int_t);
  void (*resize)(pointer,size_t,const_pointer);
  void (*shrink_to_fit)(pointer);
  void (*clear)(pointer);
  iterator (*at)(const_pointer,size_t);
};

yaooc_class_instance(int_unique_ordered_array_container)
{
  yaooc_unique_ordered_array_container_class_instance_t;
};

yaooc_class(int_unique_ordered_array_container);

void int_unique_ordered_array_container_default_ctor(pointer d)
{
	call_constructor(d,yaooc_ordered_array_container_ctor_ti,int_ti);
}

size_t int_unique_ordered_array_container_erase_value(pointer p,int_t value)
{
	return yaooc_array_container_erase_value(p,&value);
}

int_unique_ordered_array_container_class_table_t int_unique_ordered_array_container_class_table=
{
  .parent_class_table_ = (const class_table_t*)&yaooc_ordered_array_container_class_table, /* parent_class_table_ */
  .type_name_ = (const char*) "int_unique_ordered_array_container_t",
  .swap = yaooc_array_container_swap, /* swap  */
  .increase_capacity = (bool (*) (pointer,size_t)) yaooc_array_container_increase_capacity,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_array_container_size_needed,
  .size = yaooc_array_container_size, /* size */
  .capacity = yaooc_array_container_capacity, /* capacity */
  .empty = yaooc_array_container_empty, /* empty */
  .begin = (iterator (*) (pointer)) yaooc_array_container_begin, /* begin */
  .end = (iterator (*) (pointer)) yaooc_array_container_end, /*end  */
  .cbegin = (const_iterator (*) (const_pointer)) yaooc_array_container_begin, /* begin */
  .cend = (const_iterator (*) (const_pointer)) yaooc_array_container_end, /*end  */
	.find = (int_unique_ordered_array_container_iterator (*)(const_pointer,const_pointer))yaooc_ordered_array_container_find, /* find */
	.insert = (int_unique_ordered_array_container_const_iterator (*)(const_pointer,const_iterator,const_pointer))yaooc_unique_ordered_array_container_insert,  /* insert */
	.insert_range = (int_unique_ordered_array_container_const_iterator (*)(const_pointer,const_iterator,const_iterator,const_iterator))yaooc_unique_ordered_array_container_insert_range,  /* insert_range */
	.insert_n = (int_unique_ordered_array_container_const_iterator (*)(const_pointer,const_iterator,size_t,const_pointer))yaooc_unique_ordered_array_container_insertn, /* insert_n */
	.erase = (int_unique_ordered_array_container_iterator (*)(pointer,const_iterator))yaooc_array_container_erase, /* erase */
	.erase_range = (int_unique_ordered_array_container_iterator (*)(pointer,const_iterator,const_iterator))yaooc_array_container_erase_range, /* erase_range */
	.erase_value = (size_t (*)(pointer,int_t))int_unique_ordered_array_container_erase_value, /* erase_value */
	.resize = (void (*)(pointer,size_t,const_pointer))yaooc_unique_ordered_array_container_resize_value, /* resize */
	.shrink_to_fit = (void (*)(pointer))yaooc_array_container_shrink_to_fit, /* shrink_to_fit */
	.clear = (void (*)(pointer))yaooc_array_container_clear, /* clear */
	.at = (iterator (*)(const_pointer,size_t))yaooc_array_container_at, /* at */
};

DEFINE_TYPE_INFO(int_unique_ordered_array_container,Y,N,N,N,N,N,N,Y,yaooc_array_container);

void test_sizes()
{
//	printf("% "PRIULONG "\n",sizeof(int_unique_ordered_array_container_t));
	TEST("SIZE container == 40",sizeof(int_unique_ordered_array_container_t)== 40);
}

void test_constructor()
{
	yaooc_array_container_pointer bc=new_ctor(yaooc_array_container,yaooc_array_container_ctor_ti,int_ti);
	TEST("Array is NULL",bc->array_==NULL);
	TEST("Typeinfo is int_ti",bc->type_info_==int_ti);
	TEST("Size is 0",bc->size_==0);
	TEST("Capacity is 0",bc->capacity_==0);
	delete(bc);

}

bool is_ordered(int_unique_ordered_array_container_const_pointer oa)
{
  int_unique_ordered_array_container_const_iterator ir;
  for(ir=M(oa,at,1);ir!=M(oa,cend);ir++)
    if(*(ir-1) > *ir)
      return false;
  return true;
}

void test_insert()
{
	int_t values[] = { 14, 2, 6, 2 ,99, 17, 21, 21, 31, 8, 17, 6, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
	int n=ARRAY_SIZE(values);
	int_unique_ordered_array_container_pointer bc=new(int_unique_ordered_array_container);
	int i;
  TESTCASE("Insert");
	int_unique_ordered_array_container_const_iterator pos;
	for(i=0;i<5;i++) {
		pos=M(bc,end);
		M(bc,insert,pos,values+i);
	}

	TEST("Array is not NULL",bc->array_!=NULL);
	TEST("Size is 4",bc->size_==4);
	TEST("Capacity is 16",bc->capacity_==16);
  TEST("Array is ordered",is_ordered(bc));
	for(i=5;i<18;i++) {
		pos=M(bc,end);
		M(bc,insert,pos,values+i);
	}
	TEST("Size is 11",bc->size_==11);
	TEST("Capacity is 16",bc->capacity_==16);


	for(i=18;i<n;i++) {
		pos=M(bc,at,8);
		M(bc,insert,pos,values+i);
	}
	TEST("Size is 15",bc->size_==15);
	TEST("Capacity is 16",bc->capacity_==16);

	int_unique_ordered_array_container_const_iterator ii;
	optr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,end);ii++)
		optr+=sprintf(optr,"%d ",*ii);
	TEST("container values are '-8 2 6 8 14 17 18 21 24 31 32 35 57 88 99'",
			strcmp(output,"-8 2 6 8 14 17 18 21 24 31 32 35 57 88 99 ")==0);
//	printf("X%sX\n",output);

  TESTCASE("Insert Range");
  M(bc,clear);
  TEST("Size is 0",M(bc,size)==0);
  TEST("Empty",M(bc,empty));
  pos=M(bc,cbegin);
  M(bc,insert_range,pos,values,values+n);
  TEST("Size is 15",bc->size_==15);
	optr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,end);ii++)
		optr+=sprintf(optr,"%d ",*ii);
	TEST("container values are '-8 2 6 8 14 17 18 21 24 31 32 35 57 88 99'",
			strcmp(output,"-8 2 6 8 14 17 18 21 24 31 32 35 57 88 99 ")==0);

  TESTCASE("Insert N")

  M(bc,clear);
  TEST("Size is 0",M(bc,size)==0);
  TEST("Empty",M(bc,empty));
  pos=M(bc,cbegin);
  M(bc,insert_n,pos,20,values+10);
	optr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,end);ii++)
		optr+=sprintf(optr,"%d ",*ii);
	TEST("container values are '17'",
			strcmp(output,"17 ")==0);

  delete(bc);
}

void test_erase()
{
	int_t values[] = { 14, 2, 6, 2 ,99, 17, 21, 21, 31, 8, 17, 6, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
	int n=ARRAY_SIZE(values);
	int_unique_ordered_array_container_pointer bc=new(int_unique_ordered_array_container);
	int_unique_ordered_array_container_const_iterator pos=M(bc,cbegin);
	M(bc,insert_range,pos,values,values+n);
	TESTCASE("Erase");
	TEST("Size is 15",M(bc,size)==15);
	int_unique_ordered_array_container_const_iterator ii;
	optr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,end);ii++)
		optr+=sprintf(optr,"%d ",*ii);
	TEST("Array is '-8 2 6 8 14 17 18 21 24 31 32 35 57 88 99'",
		strcmp("-8 2 6 8 14 17 18 21 24 31 32 35 57 88 99 ",output)==0);
  puts(output);
	pos=M(bc,at,10);
	M(bc,erase,pos);
	TEST("Erase item 10. Size is 14",M(bc,size)==14);
//	int_unique_ordered_array_container_const_iterator ii;

	optr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,cend);ii++)
		optr+=sprintf(optr,"%d ",*ii);
//  puts(output);
	TEST("Array is '-8 2 6 8 14 17 18 21 24 31 35 57 88 99'",
		strcmp("-8 2 6 8 14 17 18 21 24 31 35 57 88 99 ",output)==0);
  M(bc,erase_range,pos,pos+3);
	TEST("Erase 3 items starting at position 10. Size is 11",M(bc,size)==11);
	optr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,end);ii++)
		optr+=sprintf(optr,"%d ",*ii);
	TEST("Array is '-8 2 6 8 14 17 18 21 24 31 99'",
		strcmp("-8 2 6 8 14 17 18 21 24 31 99 ",output)==0);
  puts(output);
#if 0
	TESTCASE("Erase Value");
	TEST("Erasing 2 99's from '14 8 6 2 99 17 21 56 31 8 99 -8 32 57 35'",M(bc,erase_value,99)==2);
	optr=output;
	for(ii=M(bc,begin);ii!=M(bc,end);ii++)
		optr+=sprintf(optr,"%d ",*ii);
	TEST("Array is now '14 8 6 2 17 21 56 31 8 -8 32 57 35'",strcmp(output,"14 8 6 2 17 21 56 31 8 -8 32 57 35 ")==0);
	puts(output);
#endif
	delete(bc);
}

void test_copy()
{
	int_t values[] = { 14, 8, 6, 2 ,99 };
	int_unique_ordered_array_container_pointer c1=new(int_unique_ordered_array_container);
	int n=ARRAY_SIZE(values);
	int i;
	for(i=0;i<n;i++) {
		int_unique_ordered_array_container_const_iterator end=M(c1,end);
		M(c1,insert,end,values+i);
	}
	int_unique_ordered_array_container_pointer c2=new_copy(c1);
	int_unique_ordered_array_container_const_iterator ic;
	char* ptr=output;
	for(ic=M(c2,cbegin);ic!=M(c2,cend);ic++)
		ptr+=sprintf(ptr,"%d ",*ic);
//	puts(output);
	TEST("Copy: new array si '2 6 8 14 99 '",strcmp(output,"2 6 8 14 99 ")==0);
	delete(c2);
	delete(c1);
}

void test_assign()
{
	int_t values[] = { 14, 8, 6, 2 ,99 };
	int_unique_ordered_array_container_pointer c1=new(int_unique_ordered_array_container);
	int n=ARRAY_SIZE(values);
	int_unique_ordered_array_container_const_iterator end=M(c1,end);
	M(c1,insert_range,end,values,values+n);
	int_unique_ordered_array_container_pointer c2=new(int_unique_ordered_array_container);
	assign(c2,c1);
	int_unique_ordered_array_container_const_iterator ic;
	char* ptr=output;
	for(ic=M(c1,cbegin);ic!=M(c1,cend);ic++)
		ptr+=sprintf(ptr,"%d ",*ic);
//	puts(output);
	ptr=output;
	for(ic=M(c2,cbegin);ic!=M(c2,cend);ic++)
		ptr+=sprintf(ptr,"%d ",*ic);
//	puts(output);
	TEST("Assign: new array si '2 6 8 14 99 '",strcmp(output,"2 6 8 14 99 ")==0);
	delete(c2);
	delete(c1);

}

typedef simple_object_t* simple_object_ordered_container_iterator;
typedef const simple_object_t* simple_object_ordered_container_const_iterator;

yaooc_class_table(simple_object_ordered_container)
{
  yaooc_array_container_class_table_t;
  simple_object_ordered_container_iterator (*find)(const_pointer,const_pointer);
  simple_object_ordered_container_const_iterator (*insert)(const_pointer,const_iterator,const_pointer);
  simple_object_ordered_container_const_iterator (*insert_range)(const_pointer,const_iterator,const_iterator,const_iterator);
  simple_object_ordered_container_const_iterator (*insert_n)(const_pointer,const_iterator,size_t,const_pointer);
  simple_object_ordered_container_iterator (*erase)(pointer,const_iterator);
  simple_object_ordered_container_iterator (*erase_range)(pointer,const_iterator,const_iterator);
  size_t (*erase_value)(pointer,simple_object_t);
  void (*resize)(pointer,size_t,const_pointer);
  void (*shrink_to_fit)(pointer);
  void (*clear)(pointer);
  void (*at)(const_pointer,size_t);
};

yaooc_class_instance(simple_object_ordered_container)
{
	yaooc_array_container_class_instance_t;
};

yaooc_class(simple_object_ordered_container);

void simple_object_ordered_container_default_ctor(pointer d)
{
	call_constructor(d,yaooc_array_container_ctor_ti,simple_object_ti);
}

size_t simple_object_ordered_container_erase_value(pointer p,simple_object_t so)
{
	return yaooc_array_container_erase_value(p,&so);
}

simple_object_ordered_container_class_table_t simple_object_ordered_container_class_table=
{
  .parent_class_table_ = (const class_table_t*) &yaooc_array_container_class_table, /* parent_class_table_ */
  .type_name_ = (const char*) "simple_object_ordered_container_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_array_container_swap, /* swap */
  .increase_capacity = (bool (*) (pointer,size_t)) yaooc_array_container_increase_capacity,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_array_container_size_needed,
  .size = (size_t (*) (const_pointer p)) yaooc_array_container_size, /* size */
  .capacity = (size_t (*) (const_pointer p)) yaooc_array_container_capacity, /* capacity */
  .empty = (bool (*) (const_pointer p)) yaooc_array_container_empty, /* empty */
  .begin = (iterator (*) (pointer)) yaooc_array_container_begin, /* begin */
  .end = (iterator (*) (pointer)) yaooc_array_container_end, /*end  */
  .cbegin = (const_iterator (*) (const_pointer)) yaooc_array_container_begin, /* begin */
  .cend = (const_iterator (*) (const_pointer)) yaooc_array_container_end, /*end  */
	.find = (simple_object_ordered_container_iterator (*)(const_pointer,const_pointer))yaooc_ordered_array_container_find,
	.insert = (simple_object_ordered_container_const_iterator (*)(const_pointer,const_iterator,const_pointer))yaooc_unique_ordered_array_container_insert,
	.insert_range = (simple_object_ordered_container_const_iterator (*)(const_pointer,const_iterator,const_iterator,const_iterator))yaooc_unique_ordered_array_container_insert_range,
	.insert_n = (simple_object_ordered_container_const_iterator (*)(const_pointer,const_iterator,size_t,const_pointer))yaooc_unique_ordered_array_container_insertn,
	.erase = (simple_object_ordered_container_iterator (*)(pointer,const_iterator))yaooc_array_container_erase,
	.erase_range = (simple_object_ordered_container_iterator (*)(pointer,const_iterator,const_iterator))yaooc_array_container_erase_range,
	.erase_value = (size_t (*)(pointer,simple_object_t))simple_object_ordered_container_erase_value,
	.resize = (void (*)(pointer,size_t,const_pointer))yaooc_unique_ordered_array_container_resize_value,
	.shrink_to_fit = (void (*)(pointer))yaooc_array_container_shrink_to_fit,
	.clear = (void (*)(pointer))yaooc_array_container_clear,
	.at = (void (*)(const_pointer,size_t))yaooc_array_container_at
};

DEFINE_TYPE_INFO(simple_object_ordered_container,Y,N,N,N,N,N,N,Y,yaooc_array_container);

void test_resize_shrink()
{
	simple_object_ordered_container_pointer soc=new(simple_object_ordered_container);
	TESTCASE("Creation");
	TEST("Container array is NULL",soc->array_==NULL);
	TEST("Size is 0",yaooc_array_container_size(soc)==0);
	TEST("Capacity is 0",yaooc_array_container_capacity(soc)==0);

	simple_object_t* so=new_ctor(simple_object,simple_object_ctor,24);
	optr=output;
	M(soc,resize,5,so);
	TESTCASE("Resize: Increate by 5 objects");
	TEST("Size is 1",M(soc,size)==1);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"SOCC:X:24 ")==0);
	simple_object_ordered_container_const_iterator ii;
	char* ptr=output;
	for(ii=M(soc,cbegin);ii!=M(soc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",ii->x);
	TEST("Output string",strcmp(output,"24 ")==0);

	optr=output;
	*optr=0;
	so->x=15;
	M(soc,resize,1,so);
	TESTCASE("Resize: Set size to current size of container (no change in container)");
	TEST("Size is 1",M(soc,size)==1);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"")==0);

	optr=output;
	so->x=20;
	M(soc,resize,10,so);
	TESTCASE("Resize: Increase by 5 objects");
	TEST("Size is 2",M(soc,size)==2);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"SOCC:X:20 ")==0);
	ptr=output;
	for(ii=M(soc,cbegin);ii!=M(soc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",ii->x);
	TEST("Output string",strcmp(output,"20 24 ")==0);

	optr=output;
	so->x=25;
	M(soc,resize,20,so);
	TESTCASE("Resize: Increase by 10 objects");
	TEST("Size is 3",M(soc,size)==3);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"SOCC:X:25 ")==0);
	ptr=output;
	for(ii=M(soc,cbegin);ii!=M(soc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",ii->x);
	TEST("Output string",strcmp(output,"20 24 25 ")==0);

  optr=output;
	*optr=0;
	M(soc,shrink_to_fit);
	TESTCASE("Shrink to fit: Should be no changes in container");
	TEST("Size is 20",M(soc,size)==3);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"")==0);

	optr=output;
	M(soc,resize,2,so);
	TESTCASE("Resize to 2");
	TEST("Size is 2",M(soc,size)==2);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"SODT:25 ")==0);

	optr=output;
	*optr=0;
	M(soc,shrink_to_fit);
	TESTCASE("Shrink to fit:  nothing changed");
	TEST("Size is 3",M(soc,size)==2);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"")==0);

	optr=output;
	M(soc,resize,0,so);
	TESTCASE("Resize: Set size to 0");
	TEST("Size is 0",M(soc,size)==0);
	TEST("Capacity is 16",M(soc,capacity)==16);
	puts(output);
	TEST("Output string",strcmp(output,"SODT:20 SODT:24 ")==0);

	optr=output;
	*optr=0;
	M(soc,shrink_to_fit);
	TESTCASE("Shrink");
	TEST("Size is 0",M(soc,size)==0);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"")==0);

	optr=NULL;
	delete(so);
	delete(soc);
}

test_function tests[]=
{
	test_sizes,
	test_constructor,
  test_insert,
	test_erase,
	test_copy,
	test_assign,
	test_resize_shrink
};

STD_MAIN(tests)
