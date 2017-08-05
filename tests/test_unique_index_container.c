#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/unique_index_array_container.h>
#include "test_harness.h"
#include "simple_object.inc"

typedef int32_t* int32_unique_index_container_iterator;
typedef const int32_t* int32_unique_index_container_const_iterator;


class_table(int32_unique_index_container)
{
  yaooc_unique_index_array_container_class_members_t;
  int32_unique_index_container_iterator (*find)(const_pointer,const_pointer);
  int32_unique_index_container_const_iterator (*cfind)(const_pointer,const_pointer);
  int32_unique_index_container_iterator (*insert)(pointer,const_iterator,const_pointer);
  int32_unique_index_container_iterator (*insert_range)(pointer,const_iterator,const_iterator,const_iterator);
  int32_unique_index_container_iterator (*insert_n)(pointer,const_iterator,yaooc_size_type,const_pointer);
  int32_unique_index_container_iterator (*erase)(pointer,const_iterator);
  int32_unique_index_container_iterator (*erase_range)(pointer,const_iterator,const_iterator);
  int32_unique_index_container_iterator (*begin)(pointer);
  int32_unique_index_container_iterator (*end)(pointer);
  int32_unique_index_container_const_iterator (*cbegin)(const_pointer);
  int32_unique_index_container_const_iterator (*cend)(const_pointer);
};

class_instance(int32_unique_index_container)
{
	yaooc_unique_index_array_container_instance_members_t;
};

class(int32_unique_index_container);

void int32_unique_index_container_default_ctor(pointer d)
{
	call_constructor(d,yaooc_unique_index_array_container_ctor,int32_ti);
}

int32_unique_index_container_class_members_t int32_unique_index_container_class_members=
{
  {
    YAOOC_UNIQUE_INDEX_ARRAY_CONTAINER_CLASS_MEMBERS
  },
	(int32_unique_index_container_iterator (*)(const_pointer,const_pointer))yaooc_unique_index_array_container_find,
	(int32_unique_index_container_const_iterator (*)(const_pointer,const_pointer))yaooc_unique_index_array_container_find,
	(int32_unique_index_container_iterator (*)(pointer,const_iterator,const_pointer))yaooc_unique_index_array_container_insert,
	(int32_unique_index_container_iterator (*)(pointer,const_iterator,const_iterator,const_iterator))yaooc_unique_index_array_container_insert_range,
	(int32_unique_index_container_iterator (*)(pointer,const_iterator,yaooc_size_type,const_pointer))yaooc_unique_index_array_container_insert_n,
	(int32_unique_index_container_iterator (*)(pointer,const_iterator))yaooc_unique_index_array_container_erase,
	(int32_unique_index_container_iterator (*)(pointer,const_iterator,const_iterator))yaooc_unique_index_array_container_erase_range,
	(int32_unique_index_container_iterator (*)(pointer))yaooc_array_container_begin,
	(int32_unique_index_container_iterator (*)(pointer))yaooc_array_container_end,
	(int32_unique_index_container_const_iterator (*)(const_pointer))yaooc_array_container_begin,
	(int32_unique_index_container_const_iterator (*)(const_pointer))yaooc_array_container_end
};

DEFINE_TYPE_INFO(int32_unique_index_container,int32_unique_index_container_default_ctor,
      NULL,NULL,NULL,NULL,&int32_unique_index_container_class_members,
      yaooc_unique_index_array_container)

const char* get_values(int32_unique_index_container_const_pointer this)
{
  optr=output;
  int32_unique_index_container_const_iterator i;
  for(i=M(this,cbegin);i!=M(this,cend);i++)
    optr+=sprintf(optr,"%d ",*i);
  return output;
}

const char* get_indexes(int32_unique_index_container_const_pointer this)
{
  optr=output;
	yaooc_size_type i;
	for(i=0;i<this->size_;i++)
		optr+=sprintf(optr,"%d ",this->index_[i]);
  return output;
}

const char* get_values_in_order(int32_unique_index_container_const_pointer this)
{
	optr=output;
  yaooc_size_type i;
	for(i=0;i<this->size_;i++)
		optr+=sprintf(optr,"%d ",((int32_t*)this->array_)[this->index_[i]]);
  return output;
}

void test_sizes()
{
	printf("%zu\n",sizeof(int32_unique_index_container_t));
	TEST("SIZE container == 56",sizeof(int32_unique_index_container_t)== 56);
}

void test_constructor()
{
	yaooc_unique_index_array_container_pointer bc=new_ctor(yaooc_unique_index_array_container,yaooc_unique_index_array_container_ctor,int32_ti);
	TEST("Array is NULL",bc->array_==NULL);
	TEST("Index is NULL",bc->index_==NULL);
	TEST("Typeinfo is int32_ti",bc->type_info_==int32_ti);
	TEST("Size is 0",bc->size_==0);
	TEST("Capacity is 0",bc->capacity_==0);
	delete(bc);

}

void test_copy()
{
  TESTCASE("Unique index container copy")
	int32_t values[] = { 14, 8, 6, 2 ,99 };
	int32_unique_index_container_pointer c1=new(int32_unique_index_container);
	int n=ARRAY_SIZE(values);
	int i;
	for(i=0;i<n;i++) {
		int32_unique_index_container_const_iterator cend=M(c1,end);
		M(c1,insert,cend,values+i);
	}
	get_values(c1);
  TEST("C1 size is 5",M(c1,size)==5);
	TEST("C1 values are '14 8 6 2 99'",strcmp(output,"14 8 6 2 99 ")==0);
  get_indexes(c1);
  TEST("C1 indexes are '3 2 1 0 4'",strcmp(output,"3 2 1 0 4 ")==0);
  get_values_in_order(c1);
  TEST("C1 values in order are '2 6 8 14 99'",strcmp(output,"2 6 8 14 99 ")==0);

	int32_unique_index_container_pointer c2=new_copy(c1);
  TEST("After Copy Ctor: c2 size is 5",M(c2,size)==5);
  get_values(c2);
	TEST("C2 values are '14 8 6 2 99'",strcmp(output,"14 8 6 2 99 ")==0);
  get_indexes(c2);
  TEST("C2 indexes are '3 2 1 0 4'",strcmp(output,"3 2 1 0 4 ")==0);
  get_values_in_order(c2);
  TEST("C2 values in order are '2 6 8 14 99'",strcmp(output,"2 6 8 14 99 ")==0);
	delete(c2);
	delete(c1);
}

void test_assign()
{
TESTCASE("Assign");
	int32_t values[] = { 14, 8, 6, 2 ,99 };
	int32_unique_index_container_pointer c1=new(int32_unique_index_container);
	int n=ARRAY_SIZE(values);
	int32_unique_index_container_const_iterator cend=M(c1,end);
	puts("Insert Values 14, 8, 6, 2 ,99");
	M(c1,insert_range,cend,values,values+n);
  TEST("C1 size is 5",M(c1,size)==5);
  get_values(c1);
	TEST("C1 values are '14 8 6 2 99'",strcmp(output,"14 8 6 2 99 ")==0);
  get_indexes(c1);
  TEST("C1 indexes are '3 2 1 0 4'",strcmp(output,"3 2 1 0 4 ")==0);
  get_values_in_order(c1);
  TEST("C1 values in order are '2 6 8 14 99'",strcmp(output,"2 6 8 14 99 ")==0);

	puts("Do assign");
	int32_unique_index_container_pointer c2=new(int32_unique_index_container);
	assign(c2,c1);
  TEST("C2 size is 5",M(c1,size)==5);
  get_values(c2);
	TEST("C2 values are '14 8 6 2 99'",strcmp(output,"14 8 6 2 99 ")==0);
  get_indexes(c2);
  TEST("C2 indexes are '3 2 1 0 4'",strcmp(output,"3 2 1 0 4 ")==0);
  get_values_in_order(c2);
  TEST("C1 values in order are '2 6 8 14 99'",strcmp(output,"2 6 8 14 99 ")==0);
	delete(c2);
	delete(c1);

}

void test_insert()
{
  TESTCASE("Unique index container insert");
	int32_t values[] = { 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
	int n=ARRAY_SIZE(values);
	int32_unique_index_container_pointer bc=new(int32_unique_index_container);
	int32_unique_index_container_const_iterator pos=M(bc,cend);
  int i;
  printf("Inset 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8\n");
  M(bc,insert_range,pos,values,values+18);
	TEST("Array is not NULL",bc->array_!=NULL);
	TEST("Size is 13",bc->size_==13);
	TEST("Capacity is 32",bc->capacity_==32);
  get_values(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 31 24 18 88 -8'",strcmp(output,"14 8 6 2 99 17 21 56 31 24 18 88 -8 ")==0);
  get_indexes(bc);
  TEST("Indexes are '12 3 2 1 0 5 10 6 9 8 7 11 4'",strcmp(output,"12 3 2 1 0 5 10 6 9 8 7 11 4 ")==0);
  get_values_in_order(bc);
  TEST("Values in order are '-8 2 6 8 14 17 18 21 24 31 56 88 99'",strcmp(output,"-8 2 6 8 14 17 18 21 24 31 56 88 99 ")==0);
	for(i=5;i<18;i++) {
		pos=M(bc,cend);
		M(bc,insert,pos,values+i);
	}
	TEST("Size is 13",bc->size_==13);
	TEST("Capacity is 32",bc->capacity_==32);
	for(i=18;i<n;i++) {
    printf("Insert %d at index 8\n",values[i]);
		pos=M(bc,cbegin)+8;
		M(bc,insert,pos,values+i);
	}
	TEST("Size is 16",bc->size_==16);
	TEST("Capacity is 32",bc->capacity_==32);
  get_values(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 35 57 32 31 24 18 88 -8'",strcmp(output,"14 8 6 2 99 17 21 56 35 57 32 31 24 18 88 -8 ")==0);
  get_indexes(bc);
  TEST("Indexes are '15 3 2 1 0 5 13 6 12 11 10 8 7 9 14 4'",strcmp(output,"15 3 2 1 0 5 13 6 12 11 10 8 7 9 14 4 ")==0);
  get_values_in_order(bc);
  TEST("Values in order are '-8 2 6 8 14 17 18 21 24 31 32 35 56 57 88 99'",strcmp(output,"-8 2 6 8 14 17 18 21 24 31 32 35 56 57 88 99 ")==0);

	delete(bc);
}

void test_erase()
{
	TESTCASE("Erase");
	int32_t values[] = { 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
	int n=ARRAY_SIZE(values);
	int32_unique_index_container_pointer bc=new(int32_unique_index_container);
	int32_unique_index_container_const_iterator pos=M(bc,cend);
  puts("Insert 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35");
	M(bc,insert_range,pos,values,values+n);
	TEST("Size is 16",bc->size_==16);
	TEST("Capacity is 32",bc->capacity_==32);
  get_values(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 31 24 18 88 -8 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 56 31 24 18 88 -8 32 57 35 ")==0);
  get_indexes(bc);
  TEST("Indexes are '12 3 2 1 0 5 10 6 9 8 13 15 7 14 11 4'",strcmp(output,"12 3 2 1 0 5 10 6 9 8 13 15 7 14 11 4 ")==0);
  get_values_in_order(bc);
  TEST("Values in order are '-8 2 6 8 14 17 18 21 24 31 32 35 56 57 88 99'",strcmp(output,"-8 2 6 8 14 17 18 21 24 31 32 35 56 57 88 99 ")==0);

  puts("Erase item at position 10");
	pos=M(bc,cbegin)+10;
	M(bc,erase,pos);
	TEST("Size is 15",bc->size_==15);
	TEST("Capacity is 32",bc->capacity_==32);
  get_values(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 31 24 88 -8 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 56 31 24 88 -8 32 57 35 ")==0);
  get_indexes(bc);
  TEST("Indexes are '11 3 2 1 0 5 6 9 8 12 14 7 13 10 4'",strcmp(output,"11 3 2 1 0 5 6 9 8 12 14 7 13 10 4 ")==0);
  get_values_in_order(bc);
  TEST("Values in order are '-8 2 6 8 14 17 21 24 31 32 35 56 57 88 99'",strcmp(output,"-8 2 6 8 14 17 21 24 31 32 35 56 57 88 99 ")==0);

	puts("Erase 5 items starting at position 7.");
  pos=M(bc,cbegin);
	M(bc,erase_range,pos+7,pos+12);
	TEST("Size is 10",bc->size_==10);
	TEST("Capacity is 32",bc->capacity_==32);
  get_values(bc);
  TEST("Values are '14 8 6 2 99 17 21 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 32 57 35 ")==0);
  get_indexes(bc);
  TEST("Indexes are '3 2 1 0 5 6 7 9 8 4'",strcmp(output,"3 2 1 0 5 6 7 9 8 4 ")==0);
  get_values_in_order(bc);
  TEST("Values in order are '2 6 8 14 17 21 32 35 57 99'",strcmp(output,"2 6 8 14 17 21 32 35 57 99 ")==0);

	delete(bc);
}

typedef simple_object_t* simple_unique_object_container_iterator;
typedef const simple_object_t* simple_unique_object_container_const_iterator;


class_table(simple_unique_object_container)
{
  yaooc_unique_index_array_container_class_members_t;
  simple_unique_object_container_iterator (*find)(const_pointer,const_pointer);
  simple_unique_object_container_const_iterator (*cfind)(const_pointer,const_pointer);
  simple_unique_object_container_iterator (*insert)(pointer,const_iterator,const_pointer);
  simple_unique_object_container_iterator (*insert_range)(pointer,const_iterator,const_iterator,const_iterator);
  simple_unique_object_container_iterator (*insert_n)(pointer,const_iterator,yaooc_size_type,const_pointer);
  simple_unique_object_container_iterator (*erase)(pointer,const_iterator);
  simple_unique_object_container_iterator (*erase_range)(pointer,const_iterator,const_iterator);
  simple_unique_object_container_iterator (*begin)(pointer);
  simple_unique_object_container_iterator (*end)(pointer);
  simple_unique_object_container_const_iterator (*cbegin)(const_pointer);
  simple_unique_object_container_const_iterator (*cend)(const_pointer);
};

class_instance(simple_unique_object_container)
{
	yaooc_unique_index_array_container_instance_members_t;
};

class(simple_unique_object_container);

void simple_unique_object_container_default_ctor(pointer d)
{
	call_constructor(d,yaooc_unique_index_array_container_ctor,simple_object_ti);
}

simple_unique_object_container_class_members_t simple_unique_object_container_class_members=
{
  {
    YAOOC_UNIQUE_INDEX_ARRAY_CONTAINER_CLASS_MEMBERS
  },
	(simple_unique_object_container_iterator (*)(const_pointer,const_pointer))yaooc_unique_index_array_container_find,
	(simple_unique_object_container_const_iterator (*)(const_pointer,const_pointer))yaooc_unique_index_array_container_find,
	(simple_unique_object_container_iterator (*)(pointer,const_iterator,const_pointer))yaooc_unique_index_array_container_insert,
	(simple_unique_object_container_iterator (*)(pointer,const_iterator,const_iterator,const_iterator))yaooc_unique_index_array_container_insert_range,
	(simple_unique_object_container_iterator (*)(pointer,const_iterator,yaooc_size_type,const_pointer))yaooc_unique_index_array_container_insert_n,
	(simple_unique_object_container_iterator (*)(pointer,const_iterator))yaooc_unique_index_array_container_erase,
	(simple_unique_object_container_iterator (*)(pointer,const_iterator,const_iterator))yaooc_unique_index_array_container_erase_range,
	(simple_unique_object_container_iterator (*)(pointer))yaooc_unique_index_array_container_begin,
	(simple_unique_object_container_iterator (*)(pointer))yaooc_unique_index_array_container_end,
	(simple_unique_object_container_const_iterator (*)(const_pointer))yaooc_unique_index_array_container_begin,
	(simple_unique_object_container_const_iterator (*)(const_pointer))yaooc_unique_index_array_container_end,
};

DEFINE_TYPE_INFO(simple_unique_object_container,simple_unique_object_container_default_ctor,
      NULL,NULL,NULL,NULL,&int32_unique_index_container_class_members,
      yaooc_unique_index_array_container)

/*
void test_resize_shrink()
{
	simple_unique_object_container_pointer soc=new(simple_unique_object_container_ti);
	TESTCASE("Creation");
	TEST("Container array is NULL",soc->array_==NULL);
	TEST("Size is 0",yaooc_array_container_size(soc)==0);
	TEST("Capacity is 0",yaooc_array_container_capacity(soc)==0);

	simple_object_t* so=new_ctor(simple_object_ti,simple_object_ctor,12);
	so_ptr=output;
	M(soc,resize,5,so);
	TESTCASE("Resize: Increase by 5 objects");
	TEST("Size is 5",M(soc,size)==5);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string is 'SOCC:X:12 SOCC:X:12 SOCC:X:12 SOCC:X:12 SOCC:X:12'",strcmp(output,"SOCC:X:12 SOCC:X:12 SOCC:X:12 SOCC:X:12 SOCC:X:12 ")==0);

	so_ptr=output;
	*so_ptr=0;
	so->x=15;
	M(soc,resize,5,so);
	TESTCASE("Resize: Set size to current size of container (no change in container)");
	TEST("Size is 5",M(soc,size)==5);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string is ''",strcmp(output,"")==0);

	so_ptr=output;
	so->x=20;
	M(soc,resize,10,so);
	TESTCASE("Resize: Increase by 5 objects");
	TEST("Size is 10",M(soc,size)==10);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"SOCC:X:20 SOCC:X:20 SOCC:X:20 SOCC:X:20 SOCC:X:20 ")==0);

	so_ptr=output;
	so->x=25;
	M(soc,resize,20,so);
	TESTCASE("Resize: Increase by 10 objects");
	TEST("Size is 20",M(soc,size)==20);
	TEST("Capacity is 32",M(soc,capacity)==32);
	TEST("Output string",strcmp(output,"SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 ")==0);

	so_ptr=output;
	*so_ptr=0;
	M(soc,shrink_to_fit);
	TESTCASE("Shrink to fit: Should be no changes in container");
	TEST("Size is 20",M(soc,size)==20);
	TEST("Capacity is 32",M(soc,capacity)==32);
	TEST("Output string",strcmp(output,"")==0);

	so_ptr=output;
	M(soc,resize,10,so);
	TESTCASE("Resize: Decrease size by 10");
	TEST("Size is 10",M(soc,size)==10);
	TEST("Capacity is 32",M(soc,capacity)==32);
	TEST("Output string",strcmp(output,"SODT:25 SODT:25 SODT:25 SODT:25 SODT:25 SODT:25 SODT:25 SODT:25 SODT:25 SODT:25 ")==0);

	so_ptr=output;
	*so_ptr=0;
	M(soc,shrink_to_fit);
	TESTCASE("Shrink to fit:  Only capacity changes");
	TEST("Size is 10",M(soc,size)==10);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"")==0);

	so_ptr=output;
	M(soc,resize,0,so);
	TESTCASE("Resize: Set size to 0");
	TEST("Size is 0",M(soc,size)==0);
	TEST("Capacity is 15",M(soc,capacity)==16);
	puts(output);
	TEST("Output string",strcmp(output,"SODT:12 SODT:12 SODT:12 SODT:12 SODT:12 SODT:20 SODT:20 SODT:20 SODT:20 SODT:20 ")==0);

	so_ptr=output;
	*so_ptr=0;
	M(soc,shrink_to_fit);
	TESTCASE("Shrink");
	TEST("Size is 0",M(soc,size)==0);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"")==0);

	so_ptr=NULL;
	delete(so);
	delete(soc);
}
*/
test_function tests[]=
{
	test_sizes,
	test_constructor,
	test_copy,
	test_assign,
	test_insert,
	test_erase,
/*	test_resize_shrink*/
};

STD_MAIN(tests)
