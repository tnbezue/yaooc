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
#include <yaooc/index_array_container.h>
#include "test_harness.h"

typedef int_t* int_index_array_container_iterator;
typedef const int_t* int_index_array_container_const_iterator;

yaooc_class_table(int_index_array_container)
{
  yaooc_index_array_container_class_table_t;
  int_index_array_container_iterator (*find)(const_pointer,const_pointer);
  int_index_array_container_const_iterator (*insert)(const_pointer,const_iterator,const_pointer);
  int_index_array_container_const_iterator (*insert_range)(const_pointer,const_iterator,const_iterator,const_iterator);
  int_index_array_container_const_iterator (*insert_n)(const_pointer,const_iterator,size_t,const_pointer);
  int_index_array_container_iterator (*erase)(pointer,const_iterator);
  int_index_array_container_iterator (*erase_range)(pointer,const_iterator,const_iterator);
  size_t (*erase_value)(pointer,int_t);
  void (*resize)(pointer,size_t,const_pointer);
  void (*shrink_to_fit)(pointer);
  void (*clear)(pointer);
  iterator (*at)(const_pointer,size_t);
};

yaooc_class_instance(int_index_array_container)
{
  yaooc_index_array_container_class_instance_t;
};

yaooc_class(int_index_array_container);

void int_index_array_container_default_ctor(pointer d)
{
	call_constructor(d,yaooc_index_array_container_ctor_ti,int_ti);
}

size_t int_index_array_container_erase_value(pointer p,int_t value)
{
	return yaooc_index_array_container_erase_value(p,&value);
}

void print_indexes(int_index_array_container_const_pointer this)
{
  optr=output;
  *optr=0;
  size_t i;
  for(i=0;i<M(this,size);i++)
    optr+=sprintf(optr,"%u ",this->indexes_[i]);
}

void print_value(int_index_array_container_const_pointer this)
{
  optr=output;
  *optr=0;
  size_t i;
  int_index_array_container_const_iterator array=M(this,begin);
  for(i=0;i<M(this,size);i++)
    optr+=sprintf(optr,"%d ",array[i]);
}

void print_in_order(int_index_array_container_const_pointer this)
{
  optr=output;
  *optr=0;
  size_t i;
  int_index_array_container_const_iterator array=M(this,begin);
  for(i=0;i<M(this,size);i++)
    optr+=sprintf(optr,"%d ",array[this->indexes_[i]]);
}

bool index_ordered(int_index_array_container_const_pointer this)
{
  size_t i;
  int_index_array_container_const_iterator array=M(this,begin);
  for(i=1;i<M(this,size);i++)
    if(array[this->indexes_[i-1]] > array[this->indexes_[i]])
      return false;
  return true;
}

int_index_array_container_class_table_t int_index_array_container_class_table=
{
  .parent_class_table_ = (const class_table_t*) &yaooc_index_array_container_class_table,
  .type_name_ = (const char*) "int_index_array_container_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_index_array_container_swap,
  .increase_capacity = (bool(*)(pointer,size_t)) yaooc_index_array_container_increase_capacity,
  .size = (size_t (*) (const_pointer p)) yaooc_array_container_size,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_pod_array_size_needed,
  .capacity = (size_t (*) (const_pointer p)) yaooc_array_container_capacity,
  .empty = (bool (*) (const_pointer p)) yaooc_array_container_empty,
  .begin = (iterator (*) (const_pointer p)) yaooc_array_container_begin,
  .end = (iterator (*) (const_pointer p)) yaooc_array_container_end,
	.find = (int_index_array_container_iterator (*)(const_pointer,const_pointer))yaooc_index_array_container_find, /* find */
	.insert = (int_index_array_container_const_iterator (*)(const_pointer,const_iterator,const_pointer))yaooc_index_array_container_insert,  /* insert */
	.insert_range = (int_index_array_container_const_iterator (*)(const_pointer,const_iterator,const_iterator,const_iterator))yaooc_index_array_container_insert_range,  /* insert_range */
	.insert_n = (int_index_array_container_const_iterator (*)(const_pointer,const_iterator,size_t,const_pointer))yaooc_index_array_container_insertn, /* insert_n */
	.erase = (int_index_array_container_iterator (*)(pointer,const_iterator))yaooc_index_array_container_erase, /* erase */
	.erase_range = (int_index_array_container_iterator (*)(pointer,const_iterator,const_iterator))yaooc_index_array_container_erase_range, /* erase_range */
	.erase_value = (size_t (*)(pointer,int_t))int_index_array_container_erase_value, /* erase_value */
	.resize = (void (*)(pointer,size_t,const_pointer))yaooc_index_array_container_resize_value, /* resize */
	.shrink_to_fit = (void (*)(pointer))yaooc_index_array_container_shrink_to_fit, /* shrink_to_fit */
	.clear = (void (*)(pointer))yaooc_array_container_clear, /* clear */
  .at = (iterator (*)(const_pointer,size_t)) yaooc_array_container_at
};

DEFINE_TYPE_INFO(int_index_array_container,Y,N,N,N,N,N,N,Y,yaooc_index_array_container)

void test_sizes()
{
	printf("%zu\n",sizeof(int_index_array_container_t));
	TEST("SIZE index_array_container == 48",sizeof(int_index_array_container_t)== 48);
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
	int_t values[] = { 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
	int n=ARRAY_SIZE(values);
	int_index_array_container_pointer bc=new(int_index_array_container);
	int i;
  TESTCASE("Insert");
	int_index_array_container_const_iterator pos;
	for(i=0;i<5;i++) {
		pos=M(bc,end);
		M(bc,insert,pos,values+i);
	}
	TEST("Array is not NULL",bc->array_!=NULL);
	TEST("Size is 5",bc->size_==5);
	TEST("Capacity is 16",bc->capacity_==16);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 2 99'",strcmp(output,"14 8 6 2 99 ")==0);
  print_indexes(bc);
  TEST("Indexes are '3 2 1 0 4'",strcmp(output,"3 2 1 0 4 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '2 6 8 14 99'",strcmp(output,"2 6 8 14 99 ")==0);

	for(i=5;i<18;i++) {
		pos=M(bc,end);
		M(bc,insert,pos,values+i);
	}
	TEST("Size is 18",bc->size_==18);
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 31 8 17 24 18 18 21 88 99 -8'",strcmp(output,"14 8 6 2 99 17 21 56 31 8 17 24 18 18 21 88 99 -8 ")==0);
  print_indexes(bc);
  TEST("Indexes are '17 3 2 9 1 0 10 5 13 12 14 6 11 8 7 15 16 4'",strcmp(output,"17 3 2 9 1 0 10 5 13 12 14 6 11 8 7 15 16 4 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '-8 2 6 8 8 14 17 17 18 18 21 21 24 31 56 88 99 99'",strcmp(output,"-8 2 6 8 8 14 17 17 18 18 21 21 24 31 56 88 99 99 ")==0);

	for(i=18;i<n;i++) {
		pos=M(bc,at,8);
		M(bc,insert,pos,values+i);
	}
	TEST("Size is n",bc->size_==n);
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 35 57 32 31 8 17 24 18 18 21 88 99 -8'",strcmp(output,"14 8 6 2 99 17 21 56 35 57 32 31 8 17 24 18 18 21 88 99 -8 ")==0);
  print_indexes(bc);
  TEST("Indexes are '20 3 2 12 1 0 13 5 16 15 17 6 14 11 10 8 7 9 18 19 4'",strcmp(output,"20 3 2 12 1 0 13 5 16 15 17 6 14 11 10 8 7 9 18 19 4 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '-8 2 6 8 8 14 17 17 18 18 21 21 24 31 32 35 56 57 88 99 99'",strcmp(output,"-8 2 6 8 8 14 17 17 18 18 21 21 24 31 32 35 56 57 88 99 99 ")==0);


  TESTCASE("Insert Range");
  M(bc,clear);
  TEST("Size is 0 after empty",M(bc,size)==0);
  TEST("Empty",M(bc,empty));
  pos=M(bc,begin);
  M(bc,insert_range,pos,values,values+n);
  TEST("Size is n after insert",bc->size_==n);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 31 8 17 24 18 18 21 88 99 -8 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 56 31 8 17 24 18 18 21 88 99 -8 32 57 35 ")==0);
  print_indexes(bc);
  TEST("Indexes are '17 3 2 9 1 0 10 5 13 12 14 6 11 8 18 20 7 19 15 16 4'",strcmp(output,"17 3 2 9 1 0 10 5 13 12 14 6 11 8 18 20 7 19 15 16 4 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '-8 2 6 8 8 14 17 17 18 18 21 21 24 31 32 35 56 57 88 99 99'",strcmp(output,"-8 2 6 8 8 14 17 17 18 18 21 21 24 31 32 35 56 57 88 99 99 ")==0);

  TESTCASE("Insert N")
  M(bc,clear);
  TEST("Size is 0",M(bc,size)==0);
  TEST("Empty",M(bc,empty));
  pos=M(bc,begin);
  M(bc,insert_n,pos,20,values+10);
  TEST("Size is 20 after insert",bc->size_==20);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17'",strcmp(output,"17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 ")==0);
  print_indexes(bc);
  TEST("Indexes are '0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19'",strcmp(output,"0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 ")==0);  print_in_order(bc);
  TEST("Sorter order is '17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17'",strcmp(output,"17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 17 ")==0);

  delete(bc);
}

void test_erase()
{
	int_t values[] = { 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
	int n=ARRAY_SIZE(values);
	int_index_array_container_pointer bc=new(int_index_array_container);
	int_index_array_container_const_iterator pos=M(bc,begin);
	M(bc,insert_range,pos,values,values+n);
	TESTCASE("Erase");
	TEST("Size is 21",bc->size_==21);
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 31 8 17 24 18 18 21 88 99 -8 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 56 31 8 17 24 18 18 21 88 99 -8 32 57 35 ")==0);
  print_indexes(bc);
  TEST("Indexes are '17 3 2 9 1 0 10 5 13 12 14 6 11 8 18 20 7 19 15 16 4'",strcmp(output,"17 3 2 9 1 0 10 5 13 12 14 6 11 8 18 20 7 19 15 16 4 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '-8 2 6 8 8 14 17 17 18 18 21 21 24 31 32 35 56 57 88 99 99'",strcmp(output,"-8 2 6 8 8 14 17 17 18 18 21 21 24 31 32 35 56 57 88 99 99 ")==0);

  TESTCASE("Erase pos");
	pos=M(bc,at,10);
	M(bc,erase,pos);
	TEST("Erase item 10. Size is 20",M(bc,size)==20);
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 31 8 24 18 18 21 88 99 -8 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 56 31 8 24 18 18 21 88 99 -8 32 57 35 ")==0);
  print_indexes(bc);
  TEST("Indexes are '16 3 2 9 1 0 5 12 11 13 6 10 8 17 19 7 18 14 15 4'",strcmp(output,"16 3 2 9 1 0 5 12 11 13 6 10 8 17 19 7 18 14 15 4 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '-8 2 6 8 8 14 17 18 18 21 21 24 31 32 35 56 57 88 99 99'",strcmp(output,"-8 2 6 8 8 14 17 18 18 21 21 24 31 32 35 56 57 88 99 99 ")==0);

	pos=M(bc,at,7);
  TESTCASE("Erase range");
  M(bc,erase_range,pos,pos+5);
	TEST("Erase 5 items starting at position 7. Size is 15",M(bc,size)==15);
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 2 99 17 21 18 21 88 99 -8 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 18 21 88 99 -8 32 57 35 ")==0);
  print_indexes(bc);
  TEST("Indexes are '11 3 2 1 0 5 7 8 6 12 14 13 9 10 4'",strcmp(output,"11 3 2 1 0 5 7 8 6 12 14 13 9 10 4 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '-8 2 6 8 14 17 18 21 21 32 35 57 88 99 99'",strcmp(output,"-8 2 6 8 14 17 18 21 21 32 35 57 88 99 99 ")==0);

	TESTCASE("Erase Value");
	TEST("Erasing 2 99's from '14 8 6 2 99 17 21 18 21 88 99 -8 32 57 35'",M(bc,erase_value,99)==2);
	TEST("Size is 13",bc->size_==13);
  TEST("Index is ordered",index_ordered(bc));
	TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",index_ordered(bc));
  print_value(bc);
  TEST("Values are '14 8 6 2 17 21 18 21 88 -8 32 57 35'",strcmp(output,"14 8 6 2 17 21 18 21 88 -8 32 57 35 ")==0);
  print_indexes(bc);
  TEST("Indexes are '9 3 2 1 0 4 6 7 5 10 12 11 8'",strcmp(output,"9 3 2 1 0 4 6 7 5 10 12 11 8 ")==0);
  print_in_order(bc);
  TEST("Sorter order is '-8 2 6 8 14 17 18 21 21 32 35 57 88'",strcmp(output,"-8 2 6 8 14 17 18 21 21 32 35 57 88 ")==0);

	delete(bc);
}


void test_copy()
{
	int_t values[] = { 14, 8, 6, 2 ,99 };
	int_index_array_container_pointer c1=new(int_index_array_container);
	int n=ARRAY_SIZE(values);
  int_index_array_container_const_iterator end=M(c1,end);
  M(c1,insert_range,end,values,values+n);
  TESTCASE("Copy Ctor");
	int_index_array_container_pointer c2=new_copy(c1);
	TEST("Size of c1 = size of c2",c1->size_==c2->size_);
	TEST("Capacity of c1 = capacity of c2",c1->capacity_==c2->capacity_);
  TEST("c1 is index ordered",index_ordered(c1));
  TEST("c2 is index ordered",index_ordered(c2));
  char temp[64];
  print_value(c1);
  strcpy(temp,output);
  print_value(c2);
  TEST("Values in c1 == values in c2",strcmp(output,temp)==0);
  print_indexes(c1);
  strcpy(temp,output);
  print_indexes(c2);
  TEST("Indexes in c1 == indexes in c2",strcmp(output,temp)==0);
  print_in_order(c1);
  strcpy(temp,output);
  print_in_order(c2);
  TEST("Index order of c1 == index order of c2",strcmp(output,temp)==0);

	delete(c2);
	delete(c1);
}

void test_assign()
{
	int_t values[] = { 14, 8, 6, 2 ,99 };
	int_index_array_container_pointer c1=new(int_index_array_container);
	int n=ARRAY_SIZE(values);
  int_index_array_container_const_iterator end=M(c1,end);
  M(c1,insert_range,end,values,values+n);
  TESTCASE("Assign");

	int_index_array_container_pointer c2=new(int_index_array_container);
	assign(c2,c1);
	TEST("Size of c1 = size of c2",c1->size_==c2->size_);
	TEST("Capacity of c1 = capacity of c2",c1->capacity_==c2->capacity_);
  TEST("c1 is index ordered",index_ordered(c1));
  TEST("c2 is index ordered",index_ordered(c2));
  char temp[64];
  print_value(c1);
  strcpy(temp,output);
  print_value(c2);
  TEST("Values in c1 == values in c2",strcmp(output,temp)==0);
  print_indexes(c1);
  strcpy(temp,output);
  print_indexes(c2);
  TEST("Indexes in c1 == indexes in c2",strcmp(output,temp)==0);
  print_in_order(c1);
  strcpy(temp,output);
  print_in_order(c2);
  TEST("Index order of c1 == index order of c2",strcmp(output,temp)==0);
	delete(c2);
	delete(c1);

}

void test_resize_shrink()
{

	int_index_array_container_pointer rs=new(int_index_array_container);
	TESTCASE("Creation");
	TEST("Container array is NULL",rs->array_==NULL);
	TEST("Size is 0",M(rs,size)==0);
	TEST("Capacity is 0",M(rs,capacity)==0);
  TEST("Indexes is NULL",rs->indexes_==NULL);
	int_t value=24;

	M(rs,resize,5,&value);
	TESTCASE("Resize to 5 with value of 24");
	TEST("Size is 5",M(rs,size)==5);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 24 24 24 24'",strcmp(output,"24 24 24 24 24 ")==0);
  print_indexes(rs);
  TEST("Indexes are '0 1 2 3 4'",strcmp(output,"0 1 2 3 4 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '24 24 24 24 24'",strcmp(output,"24 24 24 24 24 ")==0);

	M(rs,resize,5,&value);
	TESTCASE("Resize to current size.  No changes");
	TEST("Size is 5",M(rs,size)==5);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 24 24 24 24'",strcmp(output,"24 24 24 24 24 ")==0);
  print_indexes(rs);
  TEST("Indexes are '0 1 2 3 4'",strcmp(output,"0 1 2 3 4 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '24 24 24 24 24'",strcmp(output,"24 24 24 24 24 ")==0);

  value = 15;
	M(rs,resize,10,&value);
	TESTCASE("Resize to 10 with value of 15");
	TEST("Size is 10",M(rs,size)==10);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 24 24 24 24 15 15 15 15 15'",strcmp(output,"24 24 24 24 24 15 15 15 15 15 ")==0);
  print_indexes(rs);
  TEST("Indexes are '5 6 7 8 9 0 1 2 3 4'",strcmp(output,"5 6 7 8 9 0 1 2 3 4 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '15 15 15 15 15 24 24 24 24 24'",strcmp(output,"15 15 15 15 15 24 24 24 24 24 ")==0);

  value=20;
	M(rs,resize,20,&value);
	TESTCASE("Resize to 20 with value of 20");
	TEST("Size is 20",M(rs,size)==20);
	TEST("Capacity is 32",M(rs,capacity)==32);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 24 24 24 24 15 15 15 15 15 20 20 20 20 20 20 20 20 20 20'",strcmp(output,"24 24 24 24 24 15 15 15 15 15 20 20 20 20 20 20 20 20 20 20 ")==0);
  print_indexes(rs);
  TEST("Indexes are '5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 0 1 2 3 4'",strcmp(output,"5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 0 1 2 3 4 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '15 15 15 15 15 20 20 20 20 20 20 20 20 20 20 24 24 24 24 24'",strcmp(output,"15 15 15 15 15 20 20 20 20 20 20 20 20 20 20 24 24 24 24 24 ")==0);

  M(rs,shrink_to_fit);
	TESTCASE("Shrink to fit");
	TEST("Size is 20",M(rs,size)==20);
	TEST("Capacity is 20",M(rs,capacity)==20);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 24 24 24 24 15 15 15 15 15 20 20 20 20 20 20 20 20 20 20'",strcmp(output,"24 24 24 24 24 15 15 15 15 15 20 20 20 20 20 20 20 20 20 20 ")==0);
  print_indexes(rs);
  TEST("Indexes are '5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 0 1 2 3 4'",strcmp(output,"5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 0 1 2 3 4 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '15 15 15 15 15 20 20 20 20 20 20 20 20 20 20 24 24 24 24 24'",strcmp(output,"15 15 15 15 15 20 20 20 20 20 20 20 20 20 20 24 24 24 24 24 ")==0);

	M(rs,resize,12,&value);
	TESTCASE("Resize to 12");
	TEST("Size is 12",M(rs,size)==12);
	TEST("Capacity is 20",M(rs,capacity)==20);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 24 24 24 24 15 15 15 15 15 20 20'",strcmp(output,"24 24 24 24 24 15 15 15 15 15 20 20 ")==0);
  print_indexes(rs);
  TEST("Indexes are '5 6 7 8 9 10 11 12 0 1 2 3 4'",strcmp(output,"5 6 7 8 9 10 11 0 1 2 3 4 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '15 15 15 15 15 20 20 24 24 24 24 24'",strcmp(output,"15 15 15 15 15 20 20 24 24 24 24 24 ")==0);

	M(rs,shrink_to_fit);
	TESTCASE("Shrink to fit");
	TEST("Size is 12",M(rs,size)==12);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 24 24 24 24 15 15 15 15 15 20 20'",strcmp(output,"24 24 24 24 24 15 15 15 15 15 20 20 ")==0);
  print_indexes(rs);
  TEST("Indexes are '5 6 7 8 9 10 11 12 0 1 2 3 4'",strcmp(output,"5 6 7 8 9 10 11 0 1 2 3 4 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '15 15 15 15 15 20 20 24 24 24 24 24'",strcmp(output,"15 15 15 15 15 20 20 24 24 24 24 24 ")==0);

	M(rs,resize,3,&value);
	TESTCASE("Resize to 3");
	TEST("Size is 3",M(rs,size)==3);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 24 24'",strcmp(output,"24 24 24 ")==0);
  print_indexes(rs);
  TEST("Indexes are '0 1 2'",strcmp(output,"0 1 2 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '24 24 24'",strcmp(output,"24 24 24 ")==0);

	M(rs,shrink_to_fit);
	TESTCASE("Shrink to fit");
	TEST("Size is 3",M(rs,size)==3);
	TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",index_ordered(rs));
  print_value(rs);
  TEST("Values are '24 24 24'",strcmp(output,"24 24 24 ")==0);
  print_indexes(rs);
  TEST("Indexes are '0 1 2'",strcmp(output,"0 1 2 ")==0);
  print_in_order(rs);
  TEST("Sorter order is '24 24 24'",strcmp(output,"24 24 24 ")==0);

	M(rs,resize,0,&value);
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
