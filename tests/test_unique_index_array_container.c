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
#include <yaooc/unique_index_array_container.h>
#include "test_harness.h"

typedef int_t* int_unique_index_array_container_iterator;
typedef const int_t* int_unique_index_array_container_const_iterator;

yaooc_class_table(int_unique_index_array_container)
{
  yaooc_unique_index_array_container_class_table_t;
	int_unique_index_array_container_iterator (*find)(const_pointer,const_pointer);
	int_unique_index_array_container_const_iterator (*insert)(const_pointer,const_iterator,const_pointer);
	int_unique_index_array_container_const_iterator (*insert_range)(const_pointer,const_iterator,const_iterator,const_iterator);
	int_unique_index_array_container_const_iterator (*insert_n)(const_pointer,const_iterator,size_t,const_pointer);
	int_unique_index_array_container_iterator (*erase)(pointer,const_iterator);
	int_unique_index_array_container_iterator (*erase_range)(pointer,const_iterator,const_iterator);
	size_t (*erase_value)(pointer,int_t);
	void (*resize)(pointer,size_t);
	void (*resize_value)(pointer,size_t,const_pointer);
	void (*shrink_to_fit)(pointer);
	void (*clear)(pointer);
  int_unique_index_array_container_const_iterator(*at)(const_pointer,size_t);
};

yaooc_class_instance(int_unique_index_array_container)
{
  yaooc_index_array_container_class_instance_t;
};

yaooc_class(int_unique_index_array_container);

void int_unique_index_array_container_default_ctor(pointer d)
{
	call_constructor(d,yaooc_index_array_container_ctor_ti,int_ti);
}

size_t int_unique_index_array_container_erase_value(pointer p,int_t value)
{
	return yaooc_index_array_container_erase_value(p,&value);
}

void print_indexes(int_unique_index_array_container_const_pointer this)
{
  optr=output;
  *optr=0;
  size_t i;
  for(i=0;i<M(this,size);i++)
    optr+=sprintf(optr,"%u ",yaooc_uint24_to_uint32(this->indexes_+i));
}

void print_value(int_unique_index_array_container_const_pointer this)
{
  optr=output;
  *optr=0;
  size_t i;
  int_unique_index_array_container_const_iterator array=M(this,cbegin);
  for(i=0;i<M(this,size);i++)
    optr+=sprintf(optr,"%d ",array[i]);
}

void print_in_order(int_unique_index_array_container_const_pointer this)
{
  optr=output;
  *optr=0;
  size_t i;
  int_unique_index_array_container_const_iterator array=M(this,cbegin);
  for(i=0;i<M(this,size);i++)
    optr+=sprintf(optr,"%d ",array[yaooc_uint24_to_uint32(this->indexes_+i)]);
}

bool index_ordered(int_unique_index_array_container_const_pointer this)
{
  size_t i;
  int_unique_index_array_container_const_iterator array=M(this,cbegin);
  for(i=1;i<M(this,size);i++)
    if(array[yaooc_uint24_to_uint32(this->indexes_+i-1)] > array[yaooc_uint24_to_uint32(this->indexes_+i)])
      return false;
  return true;
}

int_unique_index_array_container_class_table_t int_unique_index_array_container_class_table=
{
  .parent_class_table_ = (const class_table_t*)&yaooc_unique_index_array_container_class_table, /* parent_class_table_ */
  .type_name_ = (const char*) "int_unique_index_array_container_t",
  .swap = yaooc_index_array_container_swap, /* swap  */
  .increase_capacity = (bool(*)(pointer,size_t)) yaooc_index_array_container_increase_capacity,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_index_array_container_size_needed,
  .size = (size_t (*) (const_pointer)) yaooc_index_array_container_size,
  .capacity =  yaooc_array_container_capacity, /* capacity */
  .empty = yaooc_array_container_empty, /* empty */
  .begin = (iterator (*) (pointer)) yaooc_array_container_begin, /* begin */
  .end = (iterator (*) (pointer)) yaooc_array_container_end, /*end  */
  .cbegin = (const_iterator (*) (const_pointer)) yaooc_array_container_begin, /* begin */
  .cend = (const_iterator (*) (const_pointer)) yaooc_array_container_end, /*end  */
	.find = (int_unique_index_array_container_iterator (*)(const_pointer,const_pointer))yaooc_index_array_container_find, /* find */
	.insert = (int_unique_index_array_container_const_iterator (*)(const_pointer,const_iterator,const_pointer))yaooc_unique_index_array_container_insert,  /* insert */
	.insert_range = (int_unique_index_array_container_const_iterator (*)(const_pointer,const_iterator,const_iterator,const_iterator))yaooc_unique_index_array_container_insert_range,  /* insert_range */
	.insert_n = (int_unique_index_array_container_const_iterator (*)(const_pointer,const_iterator,size_t,const_pointer))yaooc_unique_index_array_container_insertn, /* insert_n */
	.erase = (int_unique_index_array_container_iterator (*)(pointer,const_iterator))yaooc_index_array_container_erase, /* erase */
	.erase_range = (int_unique_index_array_container_iterator (*)(pointer,const_iterator,const_iterator))yaooc_index_array_container_erase_range, /* erase_range */
	.erase_value = (size_t (*)(pointer,int_t))int_unique_index_array_container_erase_value, /* erase_value */
	.resize = (void (*)(pointer,size_t))yaooc_unique_index_array_container_resize, /* resize */
	.resize_value = (void (*)(pointer,size_t,const_pointer))yaooc_unique_index_array_container_resize_value, /* resize */
	.shrink_to_fit = (void (*)(pointer))yaooc_index_array_container_shrink_to_fit, /* shrink_to_fit */
	.clear = (void (*)(pointer))yaooc_array_container_clear, /* clear */
  .at = (int_unique_index_array_container_const_iterator(*)(const_pointer,size_t)) yaooc_array_container_at
};

DEFINE_TYPE_INFO(int_unique_index_array_container,Y,N,N,N,N,N,N,Y,yaooc_index_array_container);

void test_sizes()
{
//	printf("%" PRIULONG "\n",sizeof(int_unique_index_array_container_t));
	TEST("SIZE index_array_container == 48",sizeof(int_unique_index_array_container_t)== 48);
}

void test_constructor()
{
	yaooc_index_array_container_pointer bc=new_ctor(yaooc_index_array_container,yaooc_index_array_container_ctor_ti,int_ti);
	TEST("Array is NULL",bc->array_==NULL);
	TEST("Typeinfo is int_ti",bc->type_info_==int_ti);
	TEST("Size is 0",bc->size_==0);
	TEST("Capacity is 0",bc->capacity_==0);
  TEST("Index array is NULL",bc->indexes_==NULL);
	delete(bc);
}

void test_insert()
{
	int_t values[] = { 14, 8, 6, 14 ,99, 17, 17, 17, 88, 21, 56, 31, 31, 8, 17, 24, 555, 24, 24, 18, 18, 21, 88, 102, 88, 99 , -8, 32, 57, 35 ,21 };
	int n=ARRAY_SIZE(values);
	int_unique_index_array_container_pointer bc=new(int_unique_index_array_container);
	int i;
  TESTCASE("Insert");
	int_unique_index_array_container_const_iterator pos;
	for(i=0;i<5;i++) {
		pos=M(bc,end);
		M(bc,insert,pos,values+i);
	}
	TEST("Array is not NULL",bc->array_!=NULL);
	TEST("Size is 5",bc->size_==4);
	TEST("Capacity is 16",bc->capacity_==16);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 99'",strcmp(output,"14 8 6 99 ")==0);
  print_indexes(bc);
  TEST("Indexes are '2 1 0 3'",strcmp(output,"2 1 0 3 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '6 8 14 99'",strcmp(output,"6 8 14 99 ")==0);

	for(i=5;i<18;i++) {
		pos=M(bc,end);
		M(bc,insert,pos,values+i);
	}
	TEST("Size is 18",bc->size_==11);
	TEST("Capacity is 32",bc->capacity_==16);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 99 17 88 21 56 31 24 555'",strcmp(output,"14 8 6 99 17 88 21 56 31 24 555 ")==0);
  print_indexes(bc);
  TEST("Indexes are '2 1 0 4 6 9 8 7 5 3 10'",strcmp(output,"2 1 0 4 6 9 8 7 5 3 10 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '6 8 14 17 21 24 31 56 88 99 555'",strcmp(output,"6 8 14 17 21 24 31 56 88 99 555 ")==0);

	for(i=18;i<n;i++) {
		pos=M(bc,at,8);
		M(bc,insert,pos,values+i);
	}
	TEST("Size is 17",bc->size_==17);
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 99 17 88 21 56 35 57 32 -8 102 18 31 24 555'",strcmp(output,"14 8 6 99 17 88 21 56 35 57 32 -8 102 18 31 24 555 ")==0);
  print_indexes(bc);
  TEST("Indexes are '11 2 1 0 4 13 6 15 14 10 8 7 9 5 3 12 16'",strcmp(output,"11 2 1 0 4 13 6 15 14 10 8 7 9 5 3 12 16 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '-8 6 8 14 17 18 21 24 31 32 35 56 57 88 99 102 555'",strcmp(output,"-8 6 8 14 17 18 21 24 31 32 35 56 57 88 99 102 555 ")==0);

	optr=output;
//	printf("X%sX\n",output);

  TESTCASE("Insert Range");
  M(bc,clear);
  pos=M(bc,begin);
  M(bc,insert_range,pos,values,values+n);
	TEST("Size is 17",bc->size_==17);
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 99 17 88 21 56 31 24 555 18 102 -8 32 57 35'",strcmp(output,"14 8 6 99 17 88 21 56 31 24 555 18 102 -8 32 57 35 ")==0);
  print_indexes(bc);
  puts(output);
  TEST("Indexes are '13 2 1 0 4 11 6 9 8 14 16 7 15 5 3 12 10'",strcmp(output,"13 2 1 0 4 11 6 9 8 14 16 7 15 5 3 12 10 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '-8 6 8 14 17 18 21 24 31 32 35 56 57 88 99 102 555'",strcmp(output,"-8 6 8 14 17 18 21 24 31 32 35 56 57 88 99 102 555 ")==0);

  TESTCASE("Insert N")

  M(bc,clear);
  pos=M(bc,begin);
  M(bc,insert_n,pos,20,values+10);
	TEST("Size is 1",bc->size_==1);
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '56'",strcmp(output,"56 ")==0);
  print_indexes(bc);
  puts(output);
  TEST("Indexes are '0'",strcmp(output,"0 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '56'",strcmp(output,"56 ")==0);

  delete(bc);
}

void test_erase()
{
	int_t values[] = { 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
	int n=ARRAY_SIZE(values);
	int_unique_index_array_container_pointer bc=new(int_unique_index_array_container);
	int_unique_index_array_container_const_iterator pos=M(bc,begin);
	M(bc,insert_range,pos,values,values+n);
	TESTCASE("Erase");
	TEST("Size is 16",bc->size_==16);
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 31 24 18 88 -8 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 56 31 24 18 88 -8 32 57 35 ")==0);
  print_indexes(bc);
  TEST("Indexes are '12 3 2 1 0 5 10 6 9 8 13 15 7 14 11 4'",strcmp(output,"12 3 2 1 0 5 10 6 9 8 13 15 7 14 11 4 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '-8 2 6 8 14 17 18 21 24 31 32 35 56 57 88 99'",strcmp(output,"-8 2 6 8 14 17 18 21 24 31 32 35 56 57 88 99 ")==0);

  TESTCASE("Erase pos");
	pos=M(bc,at,10);
	M(bc,erase,pos);
	TEST("Erase item 10. Size is 15",M(bc,size)==15);
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 31 24 88 -8 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 56 31 24 88 -8 32 57 35 ")==0);
  print_indexes(bc);
  TEST("Indexes are '11 3 2 1 0 5 6 9 8 12 14 7 13 10 4'",strcmp(output,"11 3 2 1 0 5 6 9 8 12 14 7 13 10 4 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '-8 2 6 8 14 17 21 24 31 32 35 56 57 88 99'",strcmp(output,"-8 2 6 8 14 17 21 24 31 32 35 56 57 88 99 ")==0);

	pos=M(bc,at,7);
  TESTCASE("Erase range");
  M(bc,erase_range,pos,pos+5);
	TEST("Erase 5 items starting at position 7. Size is 8",M(bc,size)==10);
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 2 99 17 21 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 32 57 35 ")==0);
  print_indexes(bc);
  TEST("Indexes are '3 2 1 0 5 6 7 9 8 4'",strcmp(output,"3 2 1 0 5 6 7 9 8 4 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '2 6 8 14 17 21 32 35 57 99'",strcmp(output,"2 6 8 14 17 21 32 35 57 99 ")==0);

	TESTCASE("Erase Value");
	TEST("Erasing 1 99's from '2 6 8 14 17 21 32 35 57 99'",M(bc,erase_value,99)==1);
	TEST("Size is 16",bc->size_==9);
  TEST("Index is ordered",index_ordered(bc));
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 2 17 21 32 57 35'",strcmp(output,"14 8 6 2 17 21 32 57 35 ")==0);
  print_indexes(bc);
  TEST("Indexes are '3 2 1 0 4 5 6 8 7'",strcmp(output,"3 2 1 0 4 5 6 8 7 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '2 6 8 14 17 21 32 35 57'",strcmp(output,"2 6 8 14 17 21 32 35 57 ")==0);

	delete(bc);
}


void test_copy()
{
	int_t values[] = { 14, 8, 6, 2 ,99 , 2 , 8, 21, 32, 21 ,21 , 14, -8 };
	int_unique_index_array_container_pointer c1=new(int_unique_index_array_container);
	int n=ARRAY_SIZE(values);
  int_unique_index_array_container_pointer pos=M(c1,begin);

  M(c1,insert_range,pos,values,values+n);
  TESTCASE("Copy");
	TEST("Size is 8",M(c1,size)==8);
	TEST("Capacity is 16",c1->capacity_==16);
  TEST("Index is ordered",index_ordered(c1));
  print_value(c1);
  puts(output);
  TEST("Values are '14 8 6 2 99 21 32 -8'",strcmp(output,"14 8 6 2 99 21 32 -8 ")==0);
  print_indexes(c1);
  puts(output);
  TEST("Indexes are '7 3 2 1 0 5 6 4'",strcmp(output,"7 3 2 1 0 5 6 4 ")==0);
  print_in_order(c1);
  puts(output);
  TEST("Sorter order is '-8 2 6 8 14 21 32 99'",strcmp(output,"-8 2 6 8 14 21 32 99 ")==0);

  int_unique_index_array_container_pointer c2=new_copy(c1);
	TEST("Size is 8",M(c2,size)==8);
	TEST("Capacity is 16",c2->capacity_==16);
  TEST("Index is ordered",index_ordered(c2));
  print_value(c2);
  puts(output);
  TEST("Values are '14 8 6 2 99 21 32 -8'",strcmp(output,"14 8 6 2 99 21 32 -8 ")==0);
  print_indexes(c2);
  puts(output);
  TEST("Indexes are '7 3 2 1 0 5 6 4'",strcmp(output,"7 3 2 1 0 5 6 4 ")==0);
  print_in_order(c2);
  puts(output);
  TEST("Sorter order is '-8 2 6 8 14 21 32 99'",strcmp(output,"-8 2 6 8 14 21 32 99 ")==0);

	delete(c2);
	delete(c1);
}
void test_assign()
{
	int_t values[] = { 14, 8, 6, 2 ,99 , 2 , 8, 21, 32, 21 ,21 , 14, -8 };
	int_unique_index_array_container_pointer c1=new(int_unique_index_array_container);
	int n=ARRAY_SIZE(values);
  int_unique_index_array_container_pointer pos=M(c1,begin);

  M(c1,insert_range,pos,values,values+n);
  TESTCASE("Assign");
	TEST("Size is 8",M(c1,size)==8);
	TEST("Capacity is 16",c1->capacity_==16);
  TEST("Index is ordered",index_ordered(c1));
  print_value(c1);
  puts(output);
  TEST("Values are '14 8 6 2 99 21 32 -8'",strcmp(output,"14 8 6 2 99 21 32 -8 ")==0);
  print_indexes(c1);
  puts(output);
  TEST("Indexes are '7 3 2 1 0 5 6 4'",strcmp(output,"7 3 2 1 0 5 6 4 ")==0);
  print_in_order(c1);
  puts(output);
  TEST("Sorter order is '-8 2 6 8 14 21 32 99'",strcmp(output,"-8 2 6 8 14 21 32 99 ")==0);

  int_unique_index_array_container_pointer c2=new(int_unique_index_array_container);
  assign(c2,c1);
	TEST("Size is 8",M(c2,size)==8);
	TEST("Capacity is 16",c2->capacity_==16);
  TEST("Index is ordered",index_ordered(c2));
  print_value(c2);
  puts(output);
  TEST("Values are '14 8 6 2 99 21 32 -8'",strcmp(output,"14 8 6 2 99 21 32 -8 ")==0);
  print_indexes(c2);
  puts(output);
  TEST("Indexes are '7 3 2 1 0 5 6 4'",strcmp(output,"7 3 2 1 0 5 6 4 ")==0);
  print_in_order(c2);
  puts(output);
  TEST("Sorter order is '-8 2 6 8 14 21 32 99'",strcmp(output,"-8 2 6 8 14 21 32 99 ")==0);

	delete(c2);
	delete(c1);

}

void test_resize_shrink()
{
	int_unique_index_array_container_pointer rs=new(int_unique_index_array_container);
	TESTCASE("Creation");
	TEST("Container array is NULL",rs->array_==NULL);
	TEST("Size is 0",M(rs,size)==0);
	TEST("Capacity is 0",M(rs,capacity)==0);
  TEST("Indexes is NULL",rs->indexes_==NULL);
	int_t value=24;

	M(rs,resize_value,5,&value);
	TESTCASE("Resize to 5 with value of 24");
	TEST("Size is 1",M(rs,size)==1);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24'",strcmp(output,"24 ")==0);
  print_indexes(rs);
  TEST("Indexes are '0'",strcmp(output,"0 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '24'",strcmp(output,"24 ")==0);

	M(rs,resize_value,5,&value);
	TESTCASE("Resize to current size.  No changes");
	TEST("Size is 1",M(rs,size)==1);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24'",strcmp(output,"24 ")==0);
  print_indexes(rs);
  TEST("Indexes are '0'",strcmp(output,"0 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '24'",strcmp(output,"24 ")==0);

  value = 15;
	M(rs,resize_value,10,&value);
	TESTCASE("Resize to 10 with value of 15");
	TEST("Size is 2",M(rs,size)==2);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 15'",strcmp(output,"24 15 ")==0);
  print_indexes(rs);
  TEST("Indexes are '1 0'",strcmp(output,"1 0 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '15 24'",strcmp(output,"15 24 ")==0);

  value=20;
	M(rs,resize_value,20,&value);
	TESTCASE("Resize to 20 with value of 20");
	TEST("Size is 3",M(rs,size)==3);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 15 20'",strcmp(output,"24 15 20 ")==0);
  print_indexes(rs);
  TEST("Indexes are '1 2 0'",strcmp(output,"1 2 0 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '15 20 24'",strcmp(output,"15 20 24 ")==0);

  M(rs,shrink_to_fit);
	TESTCASE("Shrink to fit");
	TEST("Size is 3",M(rs,size)==3);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 15 20'",strcmp(output,"24 15 20 ")==0);
  print_indexes(rs);
  TEST("Indexes are '1 2 0'",strcmp(output,"1 2 0 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '15 20 24'",strcmp(output,"15 20 24 ")==0);

	M(rs,resize_value,2,&value);
	TESTCASE("Resize to 2");
	TEST("Size is 3",M(rs,size)==2);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 15'",strcmp(output,"24 15 ")==0);
  print_indexes(rs);
  TEST("Indexes are '1 0'",strcmp(output,"1 0 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '15 24'",strcmp(output,"15 24 ")==0);

	M(rs,shrink_to_fit);
	TESTCASE("Shrink to fit");
	TEST("Size is 3",M(rs,size)==2);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 15'",strcmp(output,"24 15 ")==0);
  print_indexes(rs);
  TEST("Indexes are '1 0'",strcmp(output,"1 0 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '15 24'",strcmp(output,"15 24 ")==0);

	M(rs,resize_value,0,&value);
	TESTCASE("Resize to 0");
	TEST("Size is 0",M(rs,size)==0);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are ''",strcmp(output,"")==0);
  print_indexes(rs);
  TEST("Indexes are ''",strcmp(output,"")==0);
  print_in_order(rs);
  TEST("Sorter order is ''",strcmp(output,"")==0);

	M(rs,shrink_to_fit);
	TESTCASE("Shrink to fit");
	TEST("Size is 0",M(rs,size)==0);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are ''",strcmp(output,"")==0);
  print_indexes(rs);
  TEST("Indexes are ''",strcmp(output,"")==0);
  print_in_order(rs);
  TEST("Sorter order is ''",strcmp(output,"")==0);

	delete(rs);
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
