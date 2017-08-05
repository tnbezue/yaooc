#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/unique_array_container.h>
#include "test_harness.h"
#include "simple_object.inc"

typedef int32_t* int32_unique_container_iterator;
typedef const int32_t* int32_unique_container_const_iterator;

class_table(int32_unique_container)
{
  yaooc_unique_array_container_class_members_t;
  int32_unique_container_iterator (*find)(const_pointer,const_pointer);
  int32_unique_container_const_iterator (*cfind)(const_pointer,const_pointer);
  int32_unique_container_iterator (*begin)(pointer);
  int32_unique_container_iterator (*end)(pointer);
  int32_unique_container_const_iterator (*cbegin)(const_pointer);
  int32_unique_container_const_iterator (*cend)(const_pointer);
  int32_unique_container_const_iterator (*insert)(pointer,const_iterator,const_pointer);
  int32_unique_container_const_iterator (*insert_range)(pointer,const_iterator,const_iterator,const_iterator);
  int32_unique_container_const_iterator (*insert_n)(pointer,const_iterator,size_t,const_pointer);
  int32_unique_container_iterator (*erase)(pointer,const_iterator);
  int32_unique_container_iterator (*erase_range)(pointer,const_iterator,const_iterator);
  size_t (*erase_value)(pointer,const_pointer);
  void (*resize)(pointer,size_t,const_pointer);
  void (*shrink_to_fit)(pointer);
};

class_instance(int32_unique_container)
{
	yaooc_array_container_instance_members_t;
};

class(int32_unique_container);

void int32_unique_container_default_ctor(pointer d)
{
	call_constructor(d,yaooc_array_container_ctor,int32_ti);
}

int32_unique_container_class_members_t int32_unique_container_class_members=
{
  { YAOOC_UNIQUE_ARRAY_CONTAINER_CLASS_MEMBERS },
	(int32_unique_container_iterator (*)(const_pointer,const_pointer))yaooc_unique_array_container_find,
	(int32_unique_container_const_iterator (*)(const_pointer,const_pointer))yaooc_unique_array_container_find,
	(int32_unique_container_iterator (*)(pointer))yaooc_unique_array_container_begin,
	(int32_unique_container_iterator (*)(pointer))yaooc_unique_array_container_end,
	(int32_unique_container_const_iterator (*)(const_pointer))yaooc_unique_array_container_begin,
	(int32_unique_container_const_iterator (*)(const_pointer))yaooc_unique_array_container_end,
	(int32_unique_container_const_iterator (*)(pointer,const_iterator,const_pointer))yaooc_unique_array_container_insert,
	(int32_unique_container_const_iterator (*)(pointer,const_iterator,const_iterator,const_iterator))yaooc_unique_array_container_insert_range,
	(int32_unique_container_const_iterator (*)(pointer,const_iterator,size_t,const_pointer))yaooc_unique_array_container_insert_n,
	(int32_unique_container_iterator (*)(pointer,const_iterator))yaooc_unique_array_container_erase,
	(int32_unique_container_iterator (*)(pointer,const_iterator,const_iterator))yaooc_unique_array_container_erase_range,
	(size_t (*)(pointer,const_pointer))yaooc_unique_array_container_erase_value,
	(void (*)(pointer,size_t,const_pointer))yaooc_unique_array_container_resize,
	(void (*)(pointer))yaooc_unique_array_container_shrink_to_fit
};

DEFINE_TYPE_INFO(int32_unique_container,int32_unique_container_default_ctor,
    NULL,NULL,NULL,NULL,&int32_unique_container_class_members,yaooc_array_container)

void test_sizes()
{
	printf("%zu\n",sizeof(int32_unique_container_t));
	TEST("SIZE container == 40",sizeof(int32_unique_container_t)== 40);
}

void test_constructor()
{
	yaooc_array_container_pointer bc=new_ctor(yaooc_array_container,yaooc_array_container_ctor,int32_ti);
	TEST("Array is NULL",bc->array_==NULL);
	TEST("Typeinfo is int32_ti",bc->type_info_==int32_ti);
	TEST("Size is 0",bc->size_==0);
	TEST("Capacity is 0",bc->capacity_==0);
	delete(bc);

}

void test_unique()
{
	TESTCASE("Unique");
	int32_t values[] = { 1, 1, 2, 1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 4, 5 };
	int32_unique_container_pointer c1=new(int32_unique_container);
	int n=ARRAY_SIZE(values);
	int i;
	for(i=0;i<n;i++) {
		int32_unique_container_const_iterator cend=M(c1,cend);
		M(c1,insert,cend,values+i);
	}
	optr=output;
	int32_unique_container_const_iterator ic;
	for(ic=M(c1,begin);ic!=M(c1,cend);ic++)
		optr+=sprintf(optr,"%d ",*ic);
	TEST("Inserting '1 1 2 1 2 3 1 2 3 4 1 2 3 4 5' results in '1 2 3 4 5' ",strcmp(output,"1 2 3 4 5 ")==0);
}

void test_copy()
{
	int32_t values[] = { 14, 8, 6, 2 ,99 };
	int32_unique_container_pointer c1=new(int32_unique_container);
	int n=ARRAY_SIZE(values);
	int i;
	for(i=0;i<n;i++) {
		int32_unique_container_const_iterator cend=M(c1,end);
		M(c1,insert,cend,values+i);
	}
	int32_unique_container_pointer c2=new_copy(c1);
	int32_unique_container_const_iterator ic;
	char* ptr=output;
	for(ic=M(c2,begin);ic!=M(c2,cend);ic++)
		ptr+=sprintf(ptr,"%d ",*ic);
	puts(output);
	TEST("Copy: new array si '14 8 6 2 99 '",strcmp(output,"14 8 6 2 99 ")==0);
	delete(c2);
	delete(c1);
}

void test_assign()
{
	TESTCASE("Assign");
	int32_t values[] = { 14, 8, 6, 2 ,99 };
	int32_unique_container_pointer c1=new(int32_unique_container);
	int n=ARRAY_SIZE(values);
/*	int i;
	for(i=0;i<n;i++)*/
	int32_unique_container_const_iterator cend=M(c1,end);
	M(c1,insert_range,cend,values,values+n);
	int32_unique_container_pointer c2=new(int32_unique_container);
	assign(c2,c1);
	int32_unique_container_const_iterator ic;
	optr=output;
	for(ic=M(c2,begin);ic!=M(c2,cend);ic++)
		optr+=sprintf(optr,"%d ",*ic);
	puts(output);
	TEST("Assign: new array si '14 8 6 2 99 '",strcmp(output,"14 8 6 2 99 ")==0);
	delete(c2);
	delete(c1);

}

void test_insert()
{
	int32_t values[] = { 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
	int n=ARRAY_SIZE(values);
	int32_unique_container_pointer bc=new(int32_unique_container);
	int32_unique_container_const_iterator pos;
	pos=M(bc,cend);
	M(bc,insert_range,pos,values,values+n);

	int32_unique_container_const_iterator ii;
	TESTCASE("Insert '14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35'");
	TEST("Size is 16",M(bc,size)==16);
	char* ptr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",*ii);
	TEST("container values are '14,8,6,2,99,17,21,56,31,24,18,88,-8,32,57,35'",
			strcmp(output,"14 8 6 2 99 17 21 56 31 24 18 88 -8 32 57 35 ")==0);
	//puts(output);
	delete(bc);
}

void test_erase()
{
	int32_t values[] = { 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
	int n=ARRAY_SIZE(values);
	int32_unique_container_pointer bc=new(int32_unique_container);
	int32_unique_container_const_iterator pos=M(bc,cend);
	M(bc,insert_range,pos,values,values+n);
	TESTCASE("Erase");
	TEST("Size is 16",M(bc,size)==16);
	optr=output;
	for(pos=M(bc,cbegin);pos!=M(bc,cend);pos++)
		optr+=sprintf(optr,"%d ",*pos);
	TEST("Output is '14 8 6 2 99 17 21 56 31 24 18 88 -8 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 56 31 24 18 88 -8 32 57 35 ")==0);
	pos=M(bc,cbegin)+10;
	M(bc,erase,pos);
	TEST("Erase item 10. Size is 15",M(bc,size)==15);
	int32_unique_container_const_iterator ii;
	char* ptr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",*ii);
	TEST("Array is '14 8 6 2 99 17 21 56 31 24 88 -8 32 57 35'",
		strcmp("14 8 6 2 99 17 21 56 31 24 88 -8 32 57 35 ",output)==0);
	M(bc,erase_range,pos,pos+5);
	TEST("Erase 5 items starting at position 10. Size is 10",M(bc,size)==10);
	ptr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",*ii);
	TEST("Array is '14 8 6 2 99 17 21 56 31 24'",
		strcmp("14 8 6 2 99 17 21 56 31 24 ",output)==0);

	delete(bc);
}

typedef simple_object_t* simple_object_unique_container_iterator;
typedef const simple_object_t* simple_object_unique_container_const_iterator;

class_table(simple_object_unique_container)
{
  yaooc_unique_array_container_class_members_t;
  simple_object_unique_container_iterator (*find)(const_pointer,const_pointer);
  simple_object_unique_container_const_iterator (*cfind)(const_pointer,const_pointer);
  simple_object_unique_container_iterator (*begin)(pointer);
  simple_object_unique_container_iterator (*end)(pointer);
  simple_object_unique_container_const_iterator (*cbegin)(const_pointer);
  simple_object_unique_container_const_iterator (*cend)(const_pointer);
  simple_object_unique_container_iterator (*insert)(const_pointer,const_iterator,const_pointer);
  simple_object_unique_container_iterator (*insert_range)(const_pointer,const_iterator,const_iterator,const_iterator);
  simple_object_unique_container_iterator (*insert_n)(const_pointer,const_iterator,size_t,const_pointer);
  simple_object_unique_container_iterator (*erase)(pointer,const_iterator);
  simple_object_unique_container_iterator (*erase_range)(pointer,const_iterator,const_iterator);
  void (*resize)(pointer,size_t,const_pointer);
  void (*shrink_to_fit)(pointer);
};

class_instance(simple_object_unique_container)
{
	yaooc_unique_array_container_instance_members_t;
};

class(simple_object_unique_container);

void simple_object_unique_container_default_ctor(pointer d)
{
	call_constructor(d,yaooc_array_container_ctor,simple_object_ti);
}

simple_object_unique_container_class_members_t simple_object_unique_container_class_members=
{
  { YAOOC_UNIQUE_ARRAY_CONTAINER_CLASS_MEMBERS },
	(simple_object_unique_container_iterator (*)(const_pointer,const_pointer))yaooc_unique_array_container_find,
	(simple_object_unique_container_const_iterator (*)(const_pointer,const_pointer))yaooc_unique_array_container_find,
	(simple_object_unique_container_iterator (*)(pointer))yaooc_unique_array_container_begin,
	(simple_object_unique_container_iterator (*)(pointer))yaooc_unique_array_container_end,
	(simple_object_unique_container_const_iterator (*)(const_pointer))yaooc_unique_array_container_begin,
	(simple_object_unique_container_const_iterator (*)(const_pointer))yaooc_unique_array_container_end,
	(simple_object_unique_container_iterator (*)(const_pointer,const_iterator,const_pointer))yaooc_unique_array_container_insert,
	(simple_object_unique_container_iterator (*)(const_pointer,const_iterator,const_iterator,const_iterator))yaooc_unique_array_container_insert_range,
	(simple_object_unique_container_iterator (*)(const_pointer,const_iterator,size_t,const_pointer))yaooc_unique_array_container_insert_n,
	(simple_object_unique_container_iterator (*)(pointer,const_iterator))yaooc_unique_array_container_erase,
	(simple_object_unique_container_iterator (*)(pointer,const_iterator,const_iterator))yaooc_unique_array_container_erase_range,
	(void (*)(pointer,size_t,const_pointer))yaooc_unique_array_container_resize,
	(void (*)(pointer))yaooc_unique_array_container_shrink_to_fit,
};

DEFINE_TYPE_INFO(simple_object_unique_container,simple_object_unique_container_default_ctor,
    NULL,NULL,NULL,NULL,&simple_object_unique_container_class_members,yaooc_unique_array_container)

void test_resize_shrink()
{
	size_t new_size;
	simple_object_unique_container_pointer soc=new(simple_object_unique_container);
	TESTCASE("Creation");
	TEST("Container array is NULL",soc->array_==NULL);
	TEST("Size is 0",yaooc_array_container_size(soc)==0);
	TEST("Capacity is 0",yaooc_array_container_capacity(soc)==0);

	simple_object_t* so=new_ctor(simple_object,simple_object_ctor,12);
	optr=output;
	new_size=M(soc,size)+5;
	M(soc,resize,new_size,so);
	TESTCASE("Resize: Increase by 5 objects");
	TEST("Size is 1",M(soc,size)==1);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"SOCC:X:12 ")==0);

	optr=output;
	*optr=0;
	so->x=15;
	new_size=M(soc,size);
	M(soc,resize,new_size,so);
	TESTCASE("Resize: Set size to current size of container (no change in container)");
	TEST("Size is 1",M(soc,size)==1);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"")==0);

	optr=output;
	so->x=20;
	new_size=M(soc,size)+10;
	M(soc,resize,new_size,so);
	TESTCASE("Resize: Increase by 10 objects");
	TEST("Size is 2",M(soc,size)==2);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"SOCC:X:20 ")==0);

	optr=output;
	so->x=25;
	new_size=M(soc,size)+20;
	M(soc,resize,new_size,so);
	TESTCASE("Resize: Increase by 20 objects");
	TEST("Size is 3",M(soc,size)==3);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"SOCC:X:25 ")==0);

	optr=output;
	*optr=0;
	M(soc,shrink_to_fit);
	TESTCASE("Shrink to fit: Should be no changes in container");
	TEST("Size is 3",M(soc,size)==3);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"")==0);

	optr=output;
	M(soc,resize,10,so);
	new_size=M(soc,size)-1;
	M(soc,resize,new_size,so);
	TESTCASE("Resize: Decrease size by 1");
	TEST("Size is 2",M(soc,size)==2);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"SODT:25 ")==0);

	optr=output;
	M(soc,resize,0,so);
	TESTCASE("Resize: Set size to 0");
	TEST("Size is 0",M(soc,size)==0);
	TEST("Capacity is 15",M(soc,capacity)==16);
	puts(output);
	TEST("Output string",strcmp(output,"SODT:12 SODT:20 ")==0);

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
	test_unique,
	test_copy,
	test_assign,
	test_insert,
	test_erase,
	test_resize_shrink
};

STD_MAIN(tests)
