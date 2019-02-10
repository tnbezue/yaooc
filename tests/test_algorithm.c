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
#include <yaooc/algorithm.h>
#include <time.h>
#include "test_harness.h"

int cmp_val=0;
bool find_val(const void* v)
{
	return *(const int*)v==cmp_val;
}

bool find_lt_val(const void* v)
{
//	printf("X%dV%dV%dV\n",*(const int*)v,cmp_val,*(const int*)v<cmp_val);
	return *(const int*)v<cmp_val;
}

void test_find()
{
	TESTCASE("Find");
	int_t ary[] = { 10, 20, 30 , 40 , 50 };
	int n=ARRAY_SIZE(ary);
	int_t val=30;
	const int_t* iptr=yaooc_find(int,ary,ary+n,&val);
	TEST("30 found in '{ 10, 20, 30 , 40 , 50 }'",iptr != (ary+n) && *iptr == 30);
  TEST("iptr not equal to end",iptr != ary+n);
  val=25;
	iptr=yaooc_find(int,ary,ary+n,&val);
	TEST("25 not found in '{ 10, 20, 30 , 40 , 50 }'",iptr == (ary+n));

	cmp_val=0;
	iptr=yaooc_find_if(int,ary,ary+n,find_val);
	TEST("0 not found in '{ 10, 20, 30 , 40 , 50 }'",iptr == (ary+n));
	cmp_val=30;
	iptr=yaooc_find_if(int,ary,ary+n,find_val);
	TEST("30 not found in '{ 10, 20, 30 , 40 , 50 }'",iptr == (ary+2));
	cmp_val=100;
	iptr=yaooc_find_if_not(int,ary,ary+n,find_lt_val);
	TEST("Values '{ 10, 20, 30 , 40 , 50 }' are less than 100",iptr == (ary+n));
	cmp_val=35;
	iptr=yaooc_find_if_not(int,ary,ary+n,find_lt_val);
	TEST("First value not less than 35 is 40 '{ 10, 20, 30 , 40 , 50 }'",*iptr == 40);
}

void test_all_any_none()
{
	int_t ary[] = { 10, 20, 30 , 40 , 50 };
	int n=ARRAY_SIZE(ary);
	cmp_val=100;
	TEST("All values are less than 100",yaooc_all_of(int,ary,ary+n,find_lt_val));
	cmp_val=30;
	TEST("At least one 30",yaooc_any_of(int,ary,ary+n,find_val));
	cmp_val=0;
	TEST("None less than 0",yaooc_none_of(int,ary,ary+n,find_lt_val));
}

void test_copy()
{
	char msg[256];
	TESTCASE("Copy");
	int_t ary1[] = { 10, 20, 30 , 40 , 50 };
	int n=ARRAY_SIZE(ary1);
	int_t* ary2=new_array(int,n);
	memset(ary2,0,n*sizeof(int_t));
	int i;
	for(i=0;i<n;i++) {
		sprintf(msg,"Before copy ary2[%d]==0",i);
		TEST(msg,ary2[i]==0);
	}
	yaooc_copy(int,ary1,ary1+n,ary2);
	for(i=0;i<n;i++) {
		sprintf(msg,"After copy ary2[%d]==ary1[%d]",i,i);
		TEST(msg,ary2[i]==ary1[i]);
	}
  delete(ary2);
}
void test_fill()
{
#if 0
	char msg[256];
  TESTCASE("FILL");
	int n=5;
	int_t* ary2=new_array(int,n);
  int_t value=37;
	memset(ary2,0,n*sizeof(int_t));
  yaooc_fill(int,ary2,ary2+n,&value);
	int i;
	for(i=0;i<n;i++) {
		sprintf(msg,"ary2[%d]==37",i);
		TEST(msg,ary2[i]==37);
	}
  delete(ary2);
  yaooc_string_pointer str_ary = new_array(yaooc_string,5);
  yaooc_string_t str;
  newp(&str,yaooc_string);
  M(&str,set,"Testing");
  yaooc_fill(yaooc_string,str_ary,str_ary+5,&str);

  for(i=0;i<5;i++) {
    sprintf(msg,"str_ary[%d] is \"Testing\"",i);
    TEST(msg,strcmp(M(str_ary+i,c_str),"Testing")==0);
  }
  deletep(&str,yaooc_string);
  delete(str_ary);
#endif
}

void double_fun(void* ptr)
{
	*(int_t*)ptr <<= 1;
}

void test_for_each()
{
	char msg[256];
	TESTCASE("For Each");
	int_t ary1[] = { 10, 20, 30 , 40 , 50 };
	int n=ARRAY_SIZE(ary1);
	int_t ary2[] = { 10, 20, 30 , 40 , 50 };
	int i;
	for(i=0;i<n;i++) {
		sprintf(msg,"Before for each ary1[%d]==%d",i,ary1[i]);
		TEST(msg,ary1[i]==ary2[i]);
	}
	yaooc_for_each(int,ary1,ary1+n,double_fun);
	for(i=0;i<n;i++) {
		sprintf(msg,"After for each ary1[%d]==%d",i,ary2[i]<<1);
		TEST(msg,ary1[i]==ary2[i]<<1);
	}


}

void test_count()
{
	TESTCASE("Count");
	int_t ary1[] = { 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 };
	int n=ARRAY_SIZE(ary1);
	int_t val=1;
	TEST("5 1's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count(int,ary1,ary1+n,&val)==5);
	val=2;
	TEST("4 2's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count(int,ary1,ary1+n,&val)==4);
	val=3;
	TEST("3 3's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count(int,ary1,ary1+n,&val)==3);
	val=4;
	TEST("2 4's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count(int,ary1,ary1+n,&val)==2);
	val=5;
	TEST("1 5 in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count(int,ary1,ary1+n,&val)==1);
}

int_t count_if_val;
bool cmp_fun(const void* ptr)
{
	return *(int_t*)ptr==count_if_val;
}

void test_count_if()
{
	TESTCASE("Count if");
	int_t ary1[] = { 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 };
	int n=ARRAY_SIZE(ary1);
	count_if_val=1;
	TEST("5 1's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count_if(int,ary1,ary1+n,cmp_fun)==5);
	count_if_val=2;
	TEST("4 2's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count_if(int,ary1,ary1+n,cmp_fun)==4);
	count_if_val=3;
	TEST("3 3's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count_if(int,ary1,ary1+n,cmp_fun)==3);
	count_if_val=4;
	TEST("2 4's in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count_if(int,ary1,ary1+n,cmp_fun)==2);
	count_if_val=5;
	TEST("1 5 in '{ 1 , 1, 2 , 1 , 2,  3 , 1, 2, 3, 4, 1, 2, 3, 4, 5 }'",yaooc_count_if(int,ary1,ary1+n,cmp_fun)==1);
}

test_function tests[]=
{
	test_find,
	test_all_any_none,
	test_copy,
  test_fill,
	test_for_each,
	test_count,
	test_count_if
};

STD_MAIN(tests)
