#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/unique_ordered_array_container.h>
#include "test_harness.h"
#include "simple_object.inc"

typedef int32_t* int32_unique_ordered_container_iterator;
typedef const int32_t* int32_unique_ordered_container_const_iterator;

class_table(int32_unique_ordered_container)
{
  yaooc_unique_ordered_array_container_class_members_t;
  int32_unique_ordered_container_iterator (*find)(const_pointer,const_pointer);
  int32_unique_ordered_container_const_iterator (*cfind)(const_pointer,const_pointer);
  int32_unique_ordered_container_iterator (*begin)(pointer);
  int32_unique_ordered_container_iterator (*end)(pointer);
  int32_unique_ordered_container_const_iterator (*cbegin)(const_pointer);
  int32_unique_ordered_container_const_iterator (*cend)(const_pointer);
  int32_unique_ordered_container_iterator (*insert)(pointer,const_iterator,const_pointer);
  int32_unique_ordered_container_iterator (*insert_range)(pointer,const_iterator,const_iterator,const_iterator);
  int32_unique_ordered_container_iterator (*insert_n)(pointer,const_iterator,yaooc_size_type,const_pointer);
  int32_unique_ordered_container_iterator (*erase)(pointer,const_iterator);
  int32_unique_ordered_container_iterator (*erase_range)(pointer,const_iterator,const_iterator);
  void (*resize)(pointer,yaooc_size_type,const_pointer);
  void (*shrink_to_fit)(pointer);
};

class_instance(int32_unique_ordered_container)
{
	yaooc_unique_ordered_array_container_instance_members_t;
};

class(int32_unique_ordered_container);

void int32_unique_ordered_container_default_ctor(pointer d)
{
	call_constructor(d,yaooc_array_container_ctor,int32_ti);
}

int32_unique_ordered_container_class_members_t int32_unique_ordered_container_class_members=
{
  { YAOOC_UNIQUE_ORDERED_ARRAY_CONTAINER_CLASS_MEMBERS },
	(int32_unique_ordered_container_iterator (*)(const_pointer,const_pointer))yaooc_unique_ordered_array_container_find,
	(int32_unique_ordered_container_const_iterator (*)(const_pointer,const_pointer))yaooc_unique_ordered_array_container_find,
	(int32_unique_ordered_container_iterator (*)(pointer))yaooc_unique_ordered_array_container_begin,
	(int32_unique_ordered_container_iterator (*)(pointer))yaooc_unique_ordered_array_container_end,
	(int32_unique_ordered_container_const_iterator (*)(const_pointer))yaooc_unique_ordered_array_container_begin,
	(int32_unique_ordered_container_const_iterator (*)(const_pointer))yaooc_unique_ordered_array_container_end,
	(int32_unique_ordered_container_iterator (*)(pointer,const_iterator,const_pointer))yaooc_unique_ordered_array_container_insert,
	(int32_unique_ordered_container_iterator (*)(pointer,const_iterator,const_iterator,const_iterator))yaooc_unique_ordered_array_container_insert_range,
  (int32_unique_ordered_container_iterator (*)(pointer,const_iterator,yaooc_size_type,const_pointer))yaooc_unique_ordered_array_container_insert_n,
	(int32_unique_ordered_container_iterator (*)(pointer,const_iterator))yaooc_unique_ordered_array_container_erase,
	(int32_unique_ordered_container_iterator (*)(pointer,const_iterator,const_iterator))yaooc_unique_ordered_array_container_erase_range,
  (void (*)(pointer,yaooc_size_type,const_pointer))yaooc_unique_ordered_array_container_resize,
	(void (*)(pointer))yaooc_unique_ordered_array_container_shrink_to_fit
};

DEFINE_TYPE_INFO(int32_unique_ordered_container,int32_unique_ordered_container_default_ctor,
      NULL,NULL,NULL,NULL,&int32_unique_ordered_container_class_members,yaooc_array_container)

void test_constructor()
{
	yaooc_array_container_pointer bc=new(int32_unique_ordered_container);
	TEST("Array is NULL",bc->array_==NULL);
	TEST("Typeinfo is int32_ti",bc->type_info_==int32_ti);
	TEST("Size is 0",bc->size_==0);
	TEST("Capacity is 0",bc->capacity_==0);
	delete(bc);

}

void test_copy()
{
	int32_t values[] = { 14, 8, 6, 2 ,99 };
	int32_unique_ordered_container_pointer c1=new(int32_unique_ordered_container);
	int n=ARRAY_SIZE(values);
	int i;
	for(i=0;i<n;i++) {
		int32_unique_ordered_container_const_iterator cend=M(c1,end);
		M(c1,insert,cend,values+i);
	}
	int32_unique_ordered_container_pointer c2=new_copy(c1);
	int32_unique_ordered_container_const_iterator ic;
	char* ptr=output;
	for(ic=M(c2,begin);ic!=M(c2,cend);ic++)
		ptr+=sprintf(ptr,"%d ",*ic);
//	puts(output);
	TEST("Copy: new array si '2 6 8 14 99 '",strcmp(output,"2 6 8 14 99 ")==0);
	delete(c2);
	delete(c1);
}

void test_assign()
{
	int32_t values[] = { 14, 8, 6, 2 ,99 };
	int32_unique_ordered_container_pointer c1=new(int32_unique_ordered_container);
	int n=ARRAY_SIZE(values);
	int32_unique_ordered_container_const_iterator cend=M(c1,end);
	M(c1,insert_range,cend,values,values+n);
	int32_unique_ordered_container_pointer c2=new(int32_unique_ordered_container);
	assign(c2,c1);
	int32_unique_ordered_container_const_iterator ic;
	char* ptr=output;
	for(ic=M(c1,begin);ic!=M(c1,cend);ic++)
		ptr+=sprintf(ptr,"%d ",*ic);
//	puts(output);
	ptr=output;
	for(ic=M(c2,begin);ic!=M(c2,cend);ic++)
		ptr+=sprintf(ptr,"%d ",*ic);
//	puts(output);
	TEST("Assign: new array si '2 6 8 14 99 '",strcmp(output,"2 6 8 14 99 ")==0);
	delete(c2);
	delete(c1);

}

void test_insert()
{
	int32_t values[] = { 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 , 8, 55 , -1 , 107 };
	int n=ARRAY_SIZE(values);
	int32_unique_ordered_container_pointer bc=new(int32_unique_ordered_container);
	int i;
	int32_unique_ordered_container_const_iterator pos;
	for(i=0;i<5;i++) {
		pos=M(bc,cend);
		M(bc,insert,pos,values+i);
	}
	TESTCASE("Insert '14, 8, 6, 2 ,99'");
	TEST("Array is not NULL",bc->array_!=NULL);
	TEST("Size is 5",bc->size_==5);
	TEST("Capacity is 16",bc->capacity_==16);
	char* ptr=output;
	int32_unique_ordered_container_const_iterator ii;
	for(ii=M(bc,cbegin);ii!=M(bc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",*ii);
	TEST("Output size is '2 6 8 14 99'",strcmp(output,"2 6 8 14 99 ")==0);

	TESTCASE("Insert '17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8'");
	for(i=5;i<18;i++) {
		pos=M(bc,cend);
		M(bc,insert,pos,values+i);
	}
	TEST("Size is 13",M(bc,size)==13);
	TEST("Capacity is 16",M(bc,capacity)==16);
	ptr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",*ii);
	TEST("Array contains '-8 2 6 8 14 17 18 21 24 31 56 88 99'",
			strcmp(output,"-8 2 6 8 14 17 18 21 24 31 56 88 99 ")==0);

	TESTCASE("Insert '32, 57, 35, 8, 55, -1 ,107'");
	for(i=18;i<n;i++) {
		pos=M(bc,cbegin)+8;
		M(bc,insert,pos,values+i);
	}
	TEST("Size is 19",M(bc,size)==19);
	TEST("Capacity is 32",M(bc,capacity)==32);
	ptr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",*ii);
	TEST("container values are '-8 -1 2 6 8 14 17 18 21 24 31 32 35 55 56 57 88 99 107'",
			strcmp(output,"-8 -1 2 6 8 14 17 18 21 24 31 32 35 55 56 57 88 99 107 ")==0);
	puts(output);
	delete(bc);
}

void test_erase()
{
	int32_t values[] = { 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
	int n=ARRAY_SIZE(values);
	int32_unique_ordered_container_pointer bc=new(int32_unique_ordered_container);
	int32_unique_ordered_container_const_iterator pos=M(bc,cend);
	M(bc,insert_range,pos,values,values+n);
	TESTCASE("Erase");
	TEST("Size is 16",M(bc,size)==16);
	int32_unique_ordered_container_const_iterator ii;
	pos=M(bc,cbegin)+10;
	M(bc,erase,pos);
	TEST("Erase item 10. Size is 15",M(bc,size)==15);
//	int32_unique_ordered_container_const_iterator ii;
	char* ptr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",*ii);
	TEST("Array is '-8 2 6 8 14 17 18 21 24 31 35 56 57 88 99'",
		strcmp("-8 2 6 8 14 17 18 21 24 31 35 56 57 88 99 ",output)==0);
	pos=M(bc,cbegin)+7;
	M(bc,erase_range,pos,pos+5);
	TESTCASE("Erase 5 items starting at position 7.");
	TEST("Size is 10",M(bc,size)==10);
	ptr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",*ii);
	TEST("Array is '-8 2 6 8 14 17 18 57 88 99'",
		strcmp("-8 2 6 8 14 17 18 57 88 99 ",output)==0);
	puts(output);
	delete(bc);
}


test_function tests[]=
{
	test_constructor,
	test_copy,
	test_assign,
	test_insert,
	test_erase
};

STD_MAIN(tests)
