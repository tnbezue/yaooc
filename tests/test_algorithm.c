#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <yaooc/algorithm.h>
#include <time.h>

#include "test_harness.h"


void test_find()
{
	TESTCASE("Find");
	int32_t ary[] = { 10, 20, 30 , 40 , 50 };
	int n=ARRAY_SIZE(ary);
	int32_t val=30;
	int32_t* iptr=yaooc_find(int32_ti,ary,ary+n,&val);
	TEST("30 found in '{ 10, 20, 30 , 40 , 50 }'",iptr != (ary+n) && *iptr == 30);
}

void test_copy()
{
	char msg[256];
	TESTCASE("Copy");
	int32_t ary1[] = { 10, 20, 30 , 40 , 50 };
	int n=ARRAY_SIZE(ary1);
	int32_t* ary2=new_array(int32,n);
	memset(ary2,0,n*sizeof(int32_t));
	int i;
	for(i=0;i<n;i++) {
		sprintf(msg,"Before copy ary2[%d]==0",i);
		TEST(msg,ary2[i]==0);
	}
	yaooc_copy(int32_ti,ary1,ary1+n,ary2);
	for(i=0;i<n;i++) {
		sprintf(msg,"After copy ary2[%d]==ary1[%d]",i,i);
		TEST(msg,ary2[i]==ary1[i]);
	}
}

void double_fun(void* ptr)
{
	*(int32_t*)ptr <<= 1;
}

void test_for_each()
{
	char msg[256];
	TESTCASE("For Each");
	int32_t ary1[] = { 10, 20, 30 , 40 , 50 };
	int n=ARRAY_SIZE(ary1);
	int32_t ary2[] = { 10, 20, 30 , 40 , 50 };
	int i;
	for(i=0;i<n;i++) {
		sprintf(msg,"Before for each ary1[%d]==%d",i,ary1[i]);
		TEST(msg,ary1[i]==ary2[i]);
	}
	yaooc_for_each(int32_ti,ary1,ary1+n,double_fun);
	for(i=0;i<n;i++) {
		sprintf(msg,"After for each ary1[%d]==%d",i,ary2[i]<<1);
		TEST(msg,ary1[i]==ary2[i]<<1);
	}
}

void test_count()
{
	TESTCASE("Count");
	int32_t ary1[] = { 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 };
	int n=ARRAY_SIZE(ary1);
	int32_t val=1;
	TEST("5 1's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count(int32_ti,ary1,ary1+n,&val)==5);
	val=2;
	TEST("4 2's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count(int32_ti,ary1,ary1+n,&val)==4);
	val=3;
	TEST("3 3's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count(int32_ti,ary1,ary1+n,&val)==3);
	val=4;
	TEST("2 4's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count(int32_ti,ary1,ary1+n,&val)==2);
	val=5;
	TEST("1 5 in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count(int32_ti,ary1,ary1+n,&val)==1);
}

int32_t count_if_val;
bool cmp_fun(const void* ptr)
{
	return *(int32_t*)ptr==count_if_val;
}

void test_count_if()
{
	TESTCASE("Count if");
	int32_t ary1[] = { 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 };
	int n=ARRAY_SIZE(ary1);
	count_if_val=1;
	TEST("5 1's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count_if(int32_ti,ary1,ary1+n,cmp_fun)==5);
	count_if_val=2;
	TEST("4 2's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count_if(int32_ti,ary1,ary1+n,cmp_fun)==4);
	count_if_val=3;
	TEST("3 3's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count_if(int32_ti,ary1,ary1+n,cmp_fun)==3);
	count_if_val=4;
	TEST("2 4's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count_if(int32_ti,ary1,ary1+n,cmp_fun)==2);
	count_if_val=5;
	TEST("1 5 in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count_if(int32_ti,ary1,ary1+n,cmp_fun)==1);
}

test_function tests[]=
{
	test_find,
	test_copy,
	test_for_each,
	test_count,
	test_count_if
};

STD_MAIN(tests)
