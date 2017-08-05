#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/index_array_container.h>
#include "test_harness.h"
#include "simple_object.inc"

typedef int32_t* int32_index_container_iterator;
typedef const int32_t* int32_index_container_const_iterator;

class_table(int32_index_container)
{
  yaooc_index_array_container_class_members_t;
  int32_index_container_iterator (*find)(pointer,const_pointer);
  int32_index_container_const_iterator (*cfind)(const_pointer,const_pointer);
  int32_index_container_const_iterator (*insert)(pointer,const_iterator,const_pointer);
  int32_index_container_const_iterator (*insert_range)(pointer,const_iterator,const_iterator,const_iterator);
  int32_index_container_const_iterator (*insert_n)(pointer,const_iterator,yaooc_size_type,const_pointer);
  int32_index_container_iterator (*erase)(pointer,const_iterator);
  int32_index_container_iterator (*erase_range)(pointer,const_iterator,const_iterator);
  void (*resize)(pointer,yaooc_size_type,const_pointer);
  void (*shrink_to_fit)(pointer);
  int32_index_container_iterator (*begin)(pointer);
  int32_index_container_iterator (*end)(pointer);
  int32_index_container_const_iterator (*cbegin)(const_pointer);
  int32_index_container_const_iterator (*cend)(const_pointer);
};

class_instance(int32_index_container)
{
	yaooc_index_array_container_instance_members_t;
};

class(int32_index_container);

void int32_index_container_default_ctor(pointer d)
{
	call_constructor(d,yaooc_index_array_container_ctor,int32_ti);
}

int32_index_container_class_members_t int32_index_container_class_members=
{
  {
    YAOOC_INDEX_ARRAY_CONTAINER_CLASS_MEMBERS
  },
	(int32_index_container_iterator (*)(pointer,const_pointer))yaooc_index_array_container_find,
	(int32_index_container_const_iterator (*)(const_pointer,const_pointer))yaooc_index_array_container_find,
	(int32_index_container_const_iterator (*)(pointer,const_iterator,const_pointer))yaooc_index_array_container_insert,
	(int32_index_container_const_iterator (*)(pointer,const_iterator,const_iterator,const_iterator))yaooc_index_array_container_insert_range,
	(int32_index_container_const_iterator (*)(pointer,const_iterator,yaooc_size_type,const_pointer))yaooc_index_array_container_insert_n,
	(int32_index_container_iterator (*)(pointer,const_iterator))yaooc_index_array_container_erase,
	(int32_index_container_iterator (*)(pointer,const_iterator,const_iterator))yaooc_index_array_container_erase_range,
	(void (*)(pointer,yaooc_size_type,const_pointer))yaooc_index_array_container_resize,
	(void (*)(pointer))yaooc_index_array_container_shrink_to_fit,
	(int32_index_container_iterator (*)(pointer))yaooc_array_container_begin,
	(int32_index_container_iterator (*)(pointer))yaooc_array_container_end,
	(int32_index_container_const_iterator (*)(const_pointer))yaooc_array_container_begin,
	(int32_index_container_const_iterator (*)(const_pointer))yaooc_array_container_end
};

DEFINE_TYPE_INFO(int32_index_container,int32_index_container_default_ctor,
      NULL,NULL,NULL,NULL,&int32_index_container_class_members,yaooc_index_array_container)

void print_order(const_pointer p)
{
	yaooc_index_array_container_const_pointer this=p;
	optr=output;
	yaooc_size_type i;
  printf("Size is %d\n",this->size_);
	for(i=0;i<this->size_;i++)
		optr+=sprintf(optr,"%d ",this->index_[i]);
	optr+=sprintf(optr,"\n");
	for(i=0;i<this->size_;i++)
		optr+=sprintf(optr,"%d ",((int*)this->array_)[this->index_[i]]);

}

void test_sizes()
{
	printf("%zu\n",sizeof(int32_index_container_t));
	TEST("SIZE container == 48",sizeof(int32_index_container_t)== 48);
}

void test_constructor()
{
	yaooc_index_array_container_pointer bc=new_ctor(yaooc_index_array_container,yaooc_index_array_container_ctor,int32_ti);
	TEST("Array is NULL",bc->array_==NULL);
	TEST("Index is NULL",bc->index_==NULL);
	TEST("Typeinfo is int32_ti",bc->type_info_==int32_ti);
	TEST("Size is 0",bc->size_==0);
	TEST("Capacity is 0",bc->capacity_==0);
	delete(bc);

}

void test_copy()
{
	int32_t values[] = { 14, 8, 6, 2 ,99 };
  puts("Creating c1");
	int32_index_container_pointer c1=new(int32_index_container);
	int n=ARRAY_SIZE(values);
	int i;
  puts("Inserting");
	for(i=0;i<n;i++) {
		int32_index_container_const_iterator cend=M(c1,end);
		M(c1,insert,cend,values+i);
	}
	print_order(c1);
	printf("Order: %s\n",output);
  puts("Copy ctor c2");
	int32_index_container_pointer c2=new_copy(c1);
	print_order(c2);
	printf("Order: %s\n",output);
	int32_index_container_const_iterator ic;
	optr=output;
	for(ic=M(c2,begin);ic!=M(c2,cend);ic++)
		optr+=sprintf(optr,"%d ",*ic);
	puts(output);
	TEST("Copy: new array si '14 8 6 2 99 '",strcmp(output,"14 8 6 2 99 ")==0);
  puts("Deleting c2");
	delete(c2);
  puts("Deleting c1");
	delete(c1);
}

void test_assign()
{
	int32_t values[] = { 14, 8, 6, 2 ,99 };
	int32_index_container_pointer c1=new(int32_index_container);
	int n=ARRAY_SIZE(values);
	int32_index_container_const_iterator cend=M(c1,end);
	puts("Insert range");
	M(c1,insert_range,cend,values,values+n);
	puts("Range complete");
	int32_index_container_pointer c2=new(int32_index_container);
	puts("Do assign");
	assign(c2,c1);
	int32_index_container_const_iterator ic;
	char* ptr=output;
	for(ic=M(c2,begin);ic!=M(c2,cend);ic++)
		ptr+=sprintf(ptr,"%d ",*ic);
	puts(output);
	TEST("Assign: new array si '14 8 6 2 99 '",strcmp(output,"14 8 6 2 99 ")==0);
	delete(c2);
	delete(c1);

}

void test_insert()
{
	int32_t values[] = { 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
	int n=ARRAY_SIZE(values);
	int32_index_container_pointer bc=new(int32_index_container);
	int i;
	int32_index_container_const_iterator pos;
	for(i=0;i<5;i++) {
		pos=M(bc,cend);
		M(bc,insert,pos,values+i);
	}
	TEST("Array is not NULL",bc->array_!=NULL);
	TEST("Size is 5",bc->size_==5);
	TEST("Capacity is 16",bc->capacity_==16);

	for(i=5;i<18;i++) {
		pos=M(bc,cend);
		M(bc,insert,pos,values+i);
	}
	TEST("Size is 18",bc->size_==18);
	TEST("Capacity is 32",bc->capacity_==32);


	for(i=18;i<n;i++) {
		pos=M(bc,cbegin)+8;
		M(bc,insert,pos,values+i);
	}
	TEST("Size is n",bc->size_==n);
	TEST("Capacity is 32",bc->capacity_==32);

	int32_index_container_const_iterator ii;
	char* ptr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",*ii);
	TEST("container values are '99 2 6 8 14 17 21 56 35 57 32 31 8 17 24 18 18 21 88 99 -8 '",
			strcmp(output,"14 8 6 2 99 17 21 56 35 57 32 31 8 17 24 18 18 21 88 99 -8 ")==0);

  /*
  */
  int32_index_container_const_iterator ary=M(bc,cbegin);
  const yaooc_size_type* indexes=bc->index_;
  yaooc_size_type n_elem=M(bc,size);
  for(yaooc_size_type j=0;j<n_elem;j++)
    printf("%d ",ary[indexes[j]]);
  printf("\n");
	//puts(output);
	delete(bc);
}

void test_erase()
{
	int32_t values[] = { 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
	int n=ARRAY_SIZE(values);
	int32_index_container_pointer bc=new(int32_index_container);
	int32_index_container_const_iterator pos=M(bc,cend);
	M(bc,insert_range,pos,values,values+n);
	print_order(bc);
	printf("Order: %s\n",output);
	TESTCASE("Erase");
	TEST("Size is 21",M(bc,size)==21);
	pos=M(bc,cbegin)+10;
	M(bc,erase,pos);
	print_order(bc);
	printf("Order: %s\n",output);
	TEST("Erase item 10. Size is 20",M(bc,size)==20);
	int32_index_container_const_iterator ii;
	char* ptr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",*ii);
	TEST("Array is '14 8 6 2 99 17 21 56 31 8 24 18 18 21 88 99 -8 32 57 35'",
		strcmp("14 8 6 2 99 17 21 56 31 8 24 18 18 21 88 99 -8 32 57 35 ",output)==0);
	M(bc,erase_range,pos,pos+5);
	TEST("Erase 5 items starting at position 10. Size is 15",M(bc,size)==15);
	ptr=output;
	for(ii=M(bc,cbegin);ii!=M(bc,cend);ii++)
		ptr+=sprintf(ptr,"%d ",*ii);
	TEST("Array is '14 8 6 2 99 17 21 56 31 8 99 -8 32 57 35'",
		strcmp("14 8 6 2 99 17 21 56 31 8 99 -8 32 57 35 ",output)==0);
	print_order(bc);
	puts(output);
	delete(bc);
}

typedef simple_object_t* simple_object_container_iterator;
typedef const simple_object_t* simple_object_container_const_iterator;


class_table(simple_object_container)
{
  yaooc_index_array_container_class_members_t;
  simple_object_container_iterator (*find)(const_pointer,const_pointer);
  simple_object_container_const_iterator (*cfind)(const_pointer,const_pointer);
  simple_object_container_iterator (*insert)(pointer,const_iterator,const_pointer);
  simple_object_container_iterator (*insert_range)(pointer,const_iterator,const_iterator,const_iterator);
  simple_object_container_iterator (*insert_n)(pointer,const_iterator,yaooc_size_type,const_pointer);
  simple_object_container_iterator (*erase)(pointer,const_iterator);
  simple_object_container_iterator (*erase_range)(pointer,const_iterator,const_iterator);
  void (*resize)(pointer,yaooc_size_type,const_pointer);
  void (*shrink_to_fit)(pointer);
  simple_object_container_iterator (*begin)(pointer);
  simple_object_container_iterator (*end)(pointer);
  simple_object_container_const_iterator (*cbegin)(const_pointer);
  simple_object_container_const_iterator (*cend)(const_pointer);
};

class_instance(simple_object_container)
{
	yaooc_index_array_container_instance_members_t;
};

class(simple_object_container);

void simple_object_container_default_ctor(pointer d)
{
	call_constructor(d,yaooc_index_array_container_ctor,simple_object_ti);
}

simple_object_container_class_members_t simple_object_container_class_members=
{
  {
    YAOOC_INDEX_ARRAY_CONTAINER_CLASS_MEMBERS
  },
	(simple_object_container_iterator (*)(const_pointer,const_pointer))yaooc_array_container_find,
	(simple_object_container_const_iterator (*)(const_pointer,const_pointer))yaooc_array_container_find,
	(simple_object_container_iterator (*)(pointer,const_iterator,const_pointer))yaooc_array_container_insert,
	(simple_object_container_iterator (*)(pointer,const_iterator,const_iterator,const_iterator))yaooc_array_container_insert_range,
	(simple_object_container_iterator (*)(pointer,const_iterator,yaooc_size_type,const_pointer))yaooc_array_container_insert_n,
	(simple_object_container_iterator (*)(pointer,const_iterator))yaooc_array_container_erase,
	(simple_object_container_iterator (*)(pointer,const_iterator,const_iterator))yaooc_array_container_erase_range,
	(void (*)(pointer,yaooc_size_type,const_pointer))yaooc_array_container_resize,
	(void (*)(pointer))yaooc_array_container_shrink_to_fit,
	(simple_object_container_iterator (*)(pointer))yaooc_array_container_begin,
	(simple_object_container_iterator (*)(pointer))yaooc_array_container_end,
	(simple_object_container_const_iterator (*)(const_pointer))yaooc_array_container_begin,
	(simple_object_container_const_iterator (*)(const_pointer))yaooc_array_container_end,
};

DEFINE_TYPE_INFO(simple_object_container,simple_object_container_default_ctor,
      NULL,NULL,NULL,NULL,&simple_object_container_class_members,yaooc_index_array_container)

void test_resize_shrink()
{
	simple_object_container_pointer soc=new(simple_object_container);
	TESTCASE("Creation");
	TEST("Container array is NULL",soc->array_==NULL);
	TEST("Size is 0",yaooc_array_container_size(soc)==0);
	TEST("Capacity is 0",yaooc_array_container_capacity(soc)==0);

	simple_object_t* so=new_ctor(simple_object,simple_object_ctor,12);
	optr=output;
	M(soc,resize,5,so);
	TESTCASE("Resize: Increate by 5 objects");
	TEST("Size is 5",M(soc,size)==5);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"SOCC:X:12 SOCC:X:12 SOCC:X:12 SOCC:X:12 SOCC:X:12 ")==0);

	optr=output;
	*optr=0;
	so->x=15;
	M(soc,resize,5,so);
	TESTCASE("Resize: Set size to current size of container (no change in container)");
	TEST("Size is 5",M(soc,size)==5);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"")==0);

	optr=output;
	so->x=20;
	M(soc,resize,10,so);
	TESTCASE("Resize: Increase by 5 objects");
	TEST("Size is 10",M(soc,size)==10);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"SOCC:X:20 SOCC:X:20 SOCC:X:20 SOCC:X:20 SOCC:X:20 ")==0);

	optr=output;
	so->x=25;
	M(soc,resize,20,so);
	TESTCASE("Resize: Increase by 10 objects");
	TEST("Size is 20",M(soc,size)==20);
	TEST("Capacity is 32",M(soc,capacity)==32);
	TEST("Output string",strcmp(output,"SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 SOCC:X:25 ")==0);

	optr=output;
	*optr=0;
	M(soc,shrink_to_fit);
	TESTCASE("Shrink to fit: Should be no changes in container");
	TEST("Size is 20",M(soc,size)==20);
	TEST("Capacity is 32",M(soc,capacity)==32);
	TEST("Output string",strcmp(output,"")==0);

	optr=output;
	M(soc,resize,10,so);
	TESTCASE("Resize: Decrease size by 10");
	TEST("Size is 10",M(soc,size)==10);
	TEST("Capacity is 32",M(soc,capacity)==32);
	TEST("Output string",strcmp(output,"SODT:25 SODT:25 SODT:25 SODT:25 SODT:25 SODT:25 SODT:25 SODT:25 SODT:25 SODT:25 ")==0);

	optr=output;
	*optr=0;
	M(soc,shrink_to_fit);
	TESTCASE("Shrink to fit:  Only capacity changes");
	TEST("Size is 10",M(soc,size)==10);
	TEST("Capacity is 16",M(soc,capacity)==16);
	TEST("Output string",strcmp(output,"")==0);

	optr=output;
	M(soc,resize,0,so);
	TESTCASE("Resize: Set size to 0");
	TEST("Size is 0",M(soc,size)==0);
	TEST("Capacity is 15",M(soc,capacity)==16);
	puts(output);
	TEST("Output string",strcmp(output,"SODT:12 SODT:12 SODT:12 SODT:12 SODT:12 SODT:20 SODT:20 SODT:20 SODT:20 SODT:20 ")==0);

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
	test_copy,
	test_assign,
	test_insert,
	test_erase,
	test_resize_shrink
};

STD_MAIN(tests)
