#include <stdio.h>
#include <yaooc/object.h>
#include "test_harness.h"

yaooc_union_table(sample)
{
	yaooc_object_class_table_t;
	void (*print)(const_pointer);
};

yaooc_union_instance(sample)
{
	short short_;
	int   int_;
	long  long ll_;
	const char* ptr;
};

yaooc_union(sample)

void sample_swap(pointer p,pointer o)
{
	sample_pointer this=p;
	sample_pointer other=p;
	SWAP(long long,this->ll_,other->ll_);
}

void sample_default_ctor(pointer p)
{
	sample_pointer this=p;
	this->ll_=0;
}

void sample_print(const_pointer p)
{
	sample_const_pointer this=p;
	printf("%hd %d %ld\n",this->short_,this->int_,this->ll_); //,this->ptr);
}

sample_class_table_t sample_class_table = {
  .parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
  .type_name_ = (const char*) "sample_t",
  .swap = sample_swap,
	.print = sample_print
};

DEFINE_TYPE_INFO(sample,Y,N,N,N,N,N,N,Y,yaooc_object);

void test_basic()
{
	TEST("Size of union is 16",sizeof(sample_t)==16);
	sample_t samp;
//	M(&samp,print);
	newp(&samp,sample);
	M(&samp,print);
	samp.ll_ = 1234567890;
	M(&samp,print);
}

test_function tests[]=
{
 	test_basic,
};

STD_MAIN(tests)
