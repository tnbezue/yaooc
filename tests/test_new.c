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
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/new.h>
#include "test_harness.h"

void test_type_sizes()
{
#if __WORDSIZE == 64
  TEST("Size of min_type_info is 8",sizeof(min_type_info_t)==8);
  TEST("Size of pod_type_info is 32",sizeof(pod_type_info_t)==32);
  TEST("Size of type_info is 80",sizeof(type_info_t)==80);
#else
  TEST("Size of min_type_info is 4",sizeof(min_type_info_t)==4);
  TEST("Size of pod_type_info is 16",sizeof(pod_type_info_t)==16);
  TEST("Size of type_info is 40",sizeof(type_info_t)==40);
#endif
}

int base_x=0;
yaooc_struct(demo) {
	int x;
};

void demo_default_ctor(pointer p)
{
	demo_pointer this=p;
	this->x=base_x++;
	if(optr) optr+=sprintf(optr,"DC%d",this->x);
}

void demo_dtor(pointer p)
{
	if(optr) optr+=sprintf(optr,"DT%d",((demo_const_pointer)p)->x);
}

void demo_assign(pointer dst,const_pointer src)
{
	((demo_pointer)dst)->x=((demo_const_pointer)src)->x;
	if(optr) optr+=sprintf(optr,"AS%d",((demo_const_pointer)src)->x);
}

void demo_copy_ctor(pointer dst,const_pointer src)
{
  if(optr) optr+=sprintf(optr,"CC%d",((demo_const_pointer)src)->x);
  demo_default_ctor(dst);
  demo_assign(dst,src);
}

bool demo_less_than_compare(const_pointer v1,const_pointer v2)
{
	if(optr) optr+=sprintf(optr,"%d<%d",((demo_const_pointer)v1)->x,((demo_const_pointer)v2)->x);
	return ((demo_const_pointer)v1)->x < ((demo_const_pointer)v2)->x;
}

DEFINE_TYPE_INFO(demo,Y,Y,Y,Y,Y,N,N,N,NULL)

/*
  Demo constructor that takes a integer as an argument
*/
void demo_ctor_int(pointer p,va_list args)
{
	demo_pointer this=p;
	this->x=va_arg(args,int);
	if(optr) optr+=sprintf(optr,"CT%d",this->x);
}

void test_new_delete()
{
	optr=output;
	demo_pointer d1 = new(demo);
	TESTCASE("New/delete");
	TEST("Default ctor called",strcmp(output,"DC0")==0);
	optr=output;
	delete(d1);
	TEST("Dtor called",strcmp(output,"DT0")==0);
	optr=output;
	demo_pointer d1a=new_ctor(demo,demo_ctor_int,99);
	TEST("Non default ctor called",strcmp(output,"CT99")==0);
	optr=output;
	demo_pointer d2=new_copy(d1a);
	TEST("Copy ctor (calls default and assign)",strcmp(output,"CC99DC1AS99")==0);
	optr=output;
	delete(d1a);
	delete(d2);
	TEST("Dtor called",strcmp(output,"DT99DT99")==0);

	TESTCASE("Placement new");
	demo_t d3;

	base_x=25;
	optr=output;
	newp(&d3,demo);
	TEST("Default ctor called",strcmp(output,"DC25")==0);
	optr=output;
	deletep(&d3,demo);
	TEST("Dtor called",strcmp(output,"DT25")==0);
}

typedef const demo_t* demo_array_const_iterator;
void test_new_delete_array()
{
	base_x=0;
	optr=output;
	demo_pointer d1 = new_array(demo,5);
	TESTCASE("New/delete Array");
	TEST("Default ctor called",strcmp(output,"DC0DC1DC2DC3DC4")==0);
	optr=output;
	int i;
	char msg[64];
	for(i=0;i<5;i++) {
		sprintf(msg,"d1[%d]==%d",i,i);
		TEST(msg,d1[i].x == i);
	}
	delete(d1);

	optr=output;
	demo_pointer d1a=new_array_ctor(demo,5,demo_ctor_int,127);
	demo_array_const_iterator iter;
	for(iter=d1a;iter!=d1a+5;iter++)
		TEST("Value is 127",iter->x == 127);
	TEST("Ctor called for each",strcmp(output,"CT127CT127CT127CT127CT127") ==0);
	delete(d1a);

	demo_t d2[5];
	optr=output;
	base_x=0;
	newp_array(d2,demo,5);
	TESTCASE("New/delete Array");
	TEST("Default ctor called",strcmp(output,"DC0DC1DC2DC3DC4")==0);
	optr=output;
	for(i=0;i<5;i++) {
		sprintf(msg,"d2[%d]==%d",i,i);
		TEST(msg,d2[i].x == i);
	}
	optr=output;
	deletep_array(d2,demo,5);
	TEST("Dtor called for each",strcmp(output,"DT0DT1DT2DT3DT4") ==0);

	optr=output;
	newp_array_ctor(d2,demo,5,demo_ctor_int,256);
	for(iter=d2;iter!=d2+5;iter++)
		TEST("Value is 256",iter->x == 256);
	TEST("Ctor called for each",strcmp(output,"CT256CT256CT256CT256CT256") ==0);
	optr=output;
	deletep_array(d2,demo,5);
	TEST("Dtor called for each",strcmp(output,"DT256DT256DT256DT256DT256") ==0);
}

void test_pod()
{
}


void test_operators()
{

	demo_pointer di = new_ctor(demo,demo_ctor_int,33);
	demo_pointer dj = new_ctor(demo,demo_ctor_int,24);
	demo_pointer dk = new_ctor(demo,demo_ctor_int,33);
	demo_pointer dm = new_ctor(demo,demo_ctor_int,40);
	puts("Static compares");
	printf("%d %d\n",di->x,dj->x);
	TEST("EQ: false",op_eq_static(di,dj,demo)== 0);
	TEST("NE: true",op_ne_static(di,dj,demo)!=0);
	TEST("LT: false",op_lt_static(di,dj,demo)==0);
	TEST("LE: false",op_le_static(di,dj,demo)==0);
	TEST("GT: true",op_gt_static(di,dj,demo)!=0);
	TEST("GE: true",op_ge_static(di,dj,demo)!=0);

	puts("Dynamic compares");
	printf("%d %d\n",di->x,dk->x);
	TEST("EQ: true",op_eq_static(di,dk,demo)!=0);
	TEST("NE: false",op_ne_static(di,dk,demo)==0);
	TEST("LT: false",op_lt_static(di,dk,demo)==0);
	TEST("LE: true",op_le_static(di,dk,demo)!=0);
	TEST("GT: false",op_gt_static(di,dk,demo)==0);
	TEST("GE: true",op_ge_static(di,dk,demo)!=0);

	printf("%d %d\n",di->x,dm->x);
	TEST("EQ: false",op_eq_static(di,dm,demo)==0);
	TEST("NE: true",op_ne_static(di,dm,demo)!=0);
	TEST("LT: true",op_lt_static(di,dm,demo)!=0);
	TEST("LE: true",op_le_static(di,dm,demo)!=0);
	TEST("GT: false",op_gt_static(di,dm,demo)==0);
	TEST("GE: false",op_ge_static(di,dm,demo)==0);

	delete(di);
	delete(dj);
	delete(dk);
	delete(dm);
}

void test_copy()
{
	demo_pointer dx=new_ctor(demo,demo_ctor_int,23);
	demo_pointer dy=new_copy(dx);
  TEST("dx == dy",op_eq(dx,dy));
  TEST("dx->x == dy->x",dx->x==dy->x);
	delete(dx);
	delete(dy);
}

yaooc_struct(base) {
	int x;
};

void base_default_ctor(pointer p)
{
  ((base_t*)p)->x = 0;
  if(optr) optr+=sprintf(optr,"BDC0");
}

void base_dtor(pointer p)
{
  if(optr) optr+=sprintf(optr,"BDT%d",((base_t*)p)->x);
}

void base_assign(pointer dst,const_pointer src) {
  if(optr) optr+=sprintf(optr,"BAS%d-%d",((const base_t*)dst)->x,((const base_t*)src)->x);
  ((base_t*)dst)->x = ((const base_t*)src)->x;
}
void base_copy_ctor(pointer dst,const_pointer src)
{
  base_default_ctor(dst);
  if(optr) optr+=sprintf(optr,"BCC%d-%d",((const base_t*)dst)->x,((const base_t*)src)->x);
  base_assign(dst,src);
}

bool base_less_than_compare(const_pointer v1,const_pointer v2)
{
  if(optr) optr+=sprintf(optr,"BLTC%d-%d",((const base_t*)v1)->x,((const base_t*)v2)->x);
  return ((const base_t*)v1)->x < ((const base_t*)v2)->x;
}
DEFINE_TYPE_INFO(base,Y,Y,Y,Y,Y,N,N,N,NULL);

void base_ctor_int(pointer p,va_list args)
{
  int x=va_arg(args,int);
  if(optr) optr+=sprintf(optr,"BCTI%d",x);
  ((base_t*)p)->x=x;
}

yaooc_struct(derived) {
	base_t;
	int y;
};

void derived_default_ctor(pointer p)
{
  if(optr) optr+=sprintf(optr,"DDC0");
  base_default_ctor(p);
  ((derived_t*)p)->y = 0;
}

void derived_dtor(pointer p)
{
  if(optr) optr+=sprintf(optr,"DDT%d",((derived_t*)p)->y);
}
void derived_assign(pointer dst,const_pointer src)
{
  if(optr) optr+=sprintf(optr,"DAS%d:%d-%d:%d",((const derived_t*)dst)->x,((const derived_t*)dst)->y,
          ((const derived_t*)src)->x,((const derived_t*)src)->y);
  base_assign(dst,src);
  ((derived_t*)dst)->y=((const derived_t*)src)->y;
}

void derived_copy_ctor(pointer dst,const_pointer src)
{
  /*
    Parent DTOR automatically called so no need to call from here
  */
  if(optr) optr+=sprintf(optr,"DCC%d:%d-%d:%d",((const derived_t*)dst)->x,((const derived_t*)dst)->y,
          ((const derived_t*)src)->x,((const derived_t*)src)->y);
  derived_default_ctor(dst);
  derived_assign(dst,src);
}

DEFINE_TYPE_INFO(derived,Y,Y,Y,Y,N,N,N,N,base)

void derived_ctor_int_int(pointer p,va_list args)
{
  int x=va_arg(args,int);
  int y=va_arg(args,int);
  if(optr) optr+=sprintf(optr,"DCTII%d",y);
  call_constructor(p,base_ctor_int,x);
  ((derived_t*)p)->y=y;
}

yaooc_struct(derived2) {
	derived_t;
	int z;
};

void derived2_default_ctor(pointer p)
{
  if(optr) optr+=sprintf(optr,"D2DC0");
  derived_default_ctor(p);
  ((derived2_t*)p)->z = 0;
}

void derived2_dtor(pointer p)
{
  if(optr) optr+=sprintf(optr,"D2DT%d",((derived2_t*)p)->z);
}

void derived2_assign(pointer dst,const_pointer src)
{
  if(optr) optr+=sprintf(optr,"D2AS%d:%d:%d-%d%d%d",
        ((const derived2_t*)dst)->x,((const derived2_t*)dst)->y,((const derived2_t*)dst)->z,
        ((const derived2_t*)src)->x,((const derived2_t*)src)->y,((const derived2_t*)src)->z);
  derived_assign(dst,src);
  ((derived2_t*)dst)->z = ((const derived2_t*)src)->z;
}

void derived2_copy_ctor(pointer dst,const_pointer src)
{
  if(optr) optr+=sprintf(optr,"D2CC%d:%d:%d-%d%d%d",
        ((const derived2_t*)dst)->x,((const derived2_t*)dst)->y,((const derived2_t*)dst)->z,
        ((const derived2_t*)src)->x,((const derived2_t*)src)->y,((const derived2_t*)src)->z);
  derived2_default_ctor(dst);
  derived2_assign(dst,src);
}

DEFINE_TYPE_INFO(derived2,Y,Y,Y,Y,N,N,N,N,derived)

void derived2_ctor_int_int_int(pointer p,va_list args)
{
  int x=va_arg(args,int);
  int y=va_arg(args,int);
  int z=va_arg(args,int);
  if(optr) optr+=sprintf(optr,"D2CTIII%d",z);
  call_constructor(p,derived_ctor_int_int,x,y);
  ((derived2_t*)p)->z=z;
}

void test_derived_dtor()
{
  TESTCASE("Default ctor");
  optr=output;
  base_t *b=new(base);
  TEST("output is: BDC0",strcmp(output,"BDC0")==0);

  optr=output;
	derived_t* d=new(derived);
  TEST("output is: DDC0BDC0",strcmp(output,"DDC0BDC0")==0);

  optr=output;
	derived2_t* d2=new(derived2);
  TEST("output is: D2DC0DDC0BDC0",strcmp(output,"D2DC0DDC0BDC0")==0);

  TESTCASE("Destructor");
  optr=output;
	delete(b);
  TEST("output is: BDT0",strcmp(output,"BDT0")==0);

  optr=output;
  delete(d);
  TEST("output is: DDT0BDT0",strcmp(output,"DDT0BDT0")==0);

  optr=output;
  delete(d2);
  TEST("output is: D2DT0DDT0BDT0",strcmp(output,"D2DT0DDT0BDT0")==0);

  TESTCASE("CONSTRUCTOR")
  optr=output;
  b=new_ctor(base,base_ctor_int,10);
  TEST("output is: BCTI10",strcmp(output,"BCTI10")==0);

  optr=output;
  d=new_ctor(derived,derived_ctor_int_int,15,20);
  TEST("output is: DCTII20BCTI15",strcmp(output,"DCTII20BCTI15")==0);

  optr=output;
  d2=new_ctor(derived2,derived2_ctor_int_int_int,30,40,50);
  TEST("output is: D2CTIII50DCTII40BCTI30",strcmp(output,"D2CTIII50DCTII40BCTI30")==0);

  DELETE_LIST(b,d,d2);
}


void print_base_array(base_const_pointer b)
{
	size_t i,n=get_n_elem(b);
	optr=output;
	for(i=0;i<n;i++)
		optr+=sprintf(optr,"%d ",b[i].x);
}

typedef const base_t* base_const_iterator;
void test_renew()
{
	optr=output;
	base_t* b=new_array(base,10);
	TEST("New array of 10 elements: Ctor called 10",strcmp(output,"BDC0BDC0BDC0BDC0BDC0BDC0BDC0BDC0BDC0BDC0")==0);
	TEST("N elements is 10",get_n_elem(b)==10);
	print_base_array(b);
	TEST("Values are all zero",strcmp(output,"0 0 0 0 0 0 0 0 0 0 ")==0);

	base_t* b_old=b;
	b=renew_array(b,10);
	TEST("Renew of same size changes nothing",b_old == b);

	optr=output;
	b=renew_array(b,5);
	TEST("Renew to 5. Dtor called 5 times",strcmp(output,"BDT0BDT0BDT0BDT0BDT0")==0);
	TEST("N elements is 5",get_n_elem(b)==5);

	base_t* temp=new_ctor(base,base_ctor_int,12);
	optr=output;
	b=renew_array_copy(b,10,temp);
	TEST("5 objects added (copied) to end",strcmp(output,"BDC0BCC0-12BAS0-12BDC0BCC0-12BAS0-12BDC0BCC0-12BAS0-12BDC0BCC0-12BAS0-12BDC0BCC0-12BAS0-12")==0);
	TEST("Size is 10",get_n_elem(b)==10);
	print_base_array(b);
	TEST("Values 5 zeros and 5 12's",strcmp(output,"0 0 0 0 0 12 12 12 12 12 ")==0);

	optr=output;
	b=renew_array_ctor(b,15,base_ctor_int,33);
	TEST("5 objects added (constructed) to end",strcmp(output,"BCTI33BCTI33BCTI33BCTI33BCTI33")==0);
	TEST("Size is 15",get_n_elem(b)==15);
	print_base_array(b);
	TEST("Values 5 zeros, 5 12's, and 5 33's",strcmp(output,"0 0 0 0 0 12 12 12 12 12 33 33 33 33 33 ")==0);

	delete(temp);
	delete(b);
}


test_function tests[]=
{
  test_type_sizes,
 	test_new_delete,
	test_new_delete_array,
	test_pod,
	test_operators,
	test_copy,
	test_derived_dtor,
	test_renew,
};

STD_MAIN(tests)
