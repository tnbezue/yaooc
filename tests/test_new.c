#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/new.h>
#include "test_harness.h"

int base_x=0;
typedef struct {
	int x;
} demo_t;

void demo_default_ctor(pointer p)
{
	demo_t* this=p;
	this->x=base_x++;
	if(optr) optr+=sprintf(optr,"DC%d",this->x);
}

void demo_dtor(pointer p)
{
	if(optr) optr+=sprintf(optr,"DT%d",((demo_t*)p)->x);
}

void demo_assign(pointer dst,const_pointer src)
{
	((demo_t*)dst)->x=((const demo_t*)src)->x;
	if(optr) optr+=sprintf(optr,"AS%d",((const demo_t*)src)->x);
}

void demo_copy_ctor(pointer dst,const_pointer src)
{
  /*
    Normallly, the default constructor is called for dst and then assignment.
    Buf of course it is up to user to determine the best implementation.
  */
  if(optr) optr+=sprintf(optr,"CC%d",((const demo_t*)src)->x);
  demo_default_ctor(dst);
  demo_assign(dst,src);
}

bool demo_less_than_compare(const_pointer v1,const_pointer v2)
{
	if(optr) optr+=sprintf(optr,"%d<%d",((const demo_t*)v1)->x,((const demo_t*)v2)->x);
	return ((const demo_t*)v1)->x < ((const demo_t*)v2)->x;
}

DEFINE_TYPE_INFO(demo,demo_default_ctor,demo_dtor,demo_copy_ctor,demo_assign,
    demo_less_than_compare,NULL,NULL)

/*
  Demo constructor that takes a integer as an argument
*/
void demo_ctor_int(pointer p,va_list args)
{
	demo_t* this=p;
	this->x=va_arg(args,int);
	if(optr) optr+=sprintf(optr,"CT%d",this->x);
}

void test_new_delete()
{
	optr=output;
	demo_t* d1 = new(demo);
	TESTCASE("New/delete");
	TEST("Default ctor called",strcmp(output,"DC0")==0);
	optr=output;
	delete(d1);
	TEST("Dtor called",strcmp(output,"DT0")==0);
	optr=output;
	d1=new_ctor(demo,demo_ctor_int,99);
	TEST("Non default ctor called",strcmp(output,"CT99")==0);
	optr=output;
	demo_t* d2=new_copy(d1);
	TEST("Copy ctor (calls default and assign)",strcmp(output,"CC99DC1AS99")==0);
	optr=output;
	delete(d1);
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

typedef const demo_t* demo_const_iterator;
void test_new_delete_array()
{
	base_x=0;
	optr=output;
	demo_t* d1 = new_array(demo,5);
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
	d1=new_array_ctor(demo,5,demo_ctor_int,127);
	demo_const_iterator iter;
	for(iter=d1;iter!=d1+5;iter++)
		TEST("Value is 127",iter->x == 127);
	TEST("Ctor called for each",strcmp(output,"CT127CT127CT127CT127CT127") ==0);
	delete(d1);

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

	demo_t* di = new_ctor(demo,demo_ctor_int,33);
	demo_t* dj = new_ctor(demo,demo_ctor_int,24);
	demo_t* dk = new_ctor(demo,demo_ctor_int,33);
	demo_t* dm = new_ctor(demo,demo_ctor_int,40);
	puts("Static compares");
	printf("%d %d\n",di->x,dj->x);
	TEST("EQ: false",op_eq_static(di,dj,demo_ti)== 0);
	TEST("NE: true",op_ne_static(di,dj,demo_ti)!=0);
	TEST("LT: false",op_lt_static(di,dj,demo_ti)==0);
	TEST("LE: false",op_le_static(di,dj,demo_ti)==0);
	TEST("GT: true",op_gt_static(di,dj,demo_ti)!=0);
	TEST("GE: true",op_ge_static(di,dj,demo_ti)!=0);

	puts("Dynamic compares");
	printf("%d %d\n",di->x,dk->x);
	TEST("EQ: true",op_eq_static(di,dk,demo_ti)!=0);
	TEST("NE: false",op_ne_static(di,dk,demo_ti)==0);
	TEST("LT: false",op_lt_static(di,dk,demo_ti)==0);
	TEST("LE: true",op_le_static(di,dk,demo_ti)!=0);
	TEST("GT: false",op_gt_static(di,dk,demo_ti)==0);
	TEST("GE: true",op_ge_static(di,dk,demo_ti)!=0);

	printf("%d %d\n",di->x,dm->x);
	TEST("EQ: false",op_eq_static(di,dm,demo_ti)==0);
	TEST("NE: true",op_ne_static(di,dm,demo_ti)!=0);
	TEST("LT: true",op_lt_static(di,dm,demo_ti)!=0);
	TEST("LE: true",op_le_static(di,dm,demo_ti)!=0);
	TEST("GT: false",op_gt_static(di,dm,demo_ti)==0);
	TEST("GE: false",op_ge_static(di,dm,demo_ti)==0);

	delete(di);
	delete(dj);
	delete(dk);
	delete(dm);
}

void test_copy()
{
	demo_t* dx=new_ctor(demo,demo_ctor_int,23);
	demo_t* dy=new_copy(dx);
  TEST("dx == dy",op_eq(dx,dy));
  TEST("dx->x == dy->x",dx->x==dy->x);
	delete(dx);
	delete(dy);
}

typedef struct {
	int x;
} base_t;

void base_default_ctor(pointer p)
{
  ((base_t*)p)->x = 0;
  if(optr) sprintf(optr,"BDC0");
}

void base_dtor(pointer p)
{
  if(optr) sprintf(optr,"BDT%d",((base_t*)p)->x);
}

void base_assign(pointer dst,const_pointer src) {
  if(optr) sprintf(optr,"BAS%d-%d",((const base_t*)dst)->x,((const base_t*)src)->x);
  ((base_t*)dst)->x = ((const base_t*)src)->x;
}
void base_copy_ctor(pointer dst,const_pointer src)
{
  if(optr) sprintf(optr,"BCC%d-%d",((const base_t*)dst)->x,((const base_t*)src)->x);
  base_default_ctor(dst);
  base_assign(dst,src);
}

bool base_less_than_compare(const_pointer v1,const_pointer v2)
{
  if(optr) sprintf(optr,"BLTC%d-%d",((const base_t*)v1)->x,((const base_t*)v2)->x);
  return ((const base_t*)v1)->x < ((const base_t*)v2)->x;
}
DEFINE_TYPE_INFO(base,base_default_ctor,base_dtor,base_copy_ctor,base_assign,base_less_than_compare,
    NULL,NULL);

void base_ctor_int(pointer p,va_list args)
{
  /*
    The base constructor can be called by here (well, anywhere).  But in most cases, it's not what's
    desired.

    base_default_ctor(p);
  */
  int x=va_arg(args,int);
  if(optr) sprintf(optr,"BCTI%d",x);
  ((base_t*)p)->x=x;
}

typedef struct {
	base_t;
	int y;
} derived_t;

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

DEFINE_TYPE_INFO(derived,derived_default_ctor,derived_dtor,derived_copy_ctor,derived_assign,
    NULL,NULL,base)

void derived_ctor_int_int(pointer p,va_list args)
{
  int x=va_arg(args,int);
  int y=va_arg(args,int);
  if(optr) optr+=sprintf(optr,"DCTII%d",y);
  call_constructor(p,base_ctor_int,x);
  ((derived_t*)p)->y=y;
}

typedef struct {
	derived_t;
	int z;
} derived2_t;

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

DEFINE_TYPE_INFO(derived2,derived2_default_ctor,derived2_dtor,derived2_copy_ctor,derived2_assign,
  NULL,NULL,derived)

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

  DELETE(b,d,d2);
}

/*
int xx=0;
char* dtor_ptr;
void base_default_ctor2(pointer p) { ((base_t*)p)->x = xx++; }
void base_copy_ctor2(pointer dst,const_pointer src) { ((base_t*)dst)->x = ((const base_t*)src)->x; }
void base_dtor2(pointer p) { dtor_ptr+=sprintf(dtor_ptr,"%d ",((base_t*)p)->x); }
void base_ctor2(pointer p,va_list args) { ((base_t*)p)->x = va_arg(args,int) + xx++; }
const type_info_t __base2_ti=
{
	sizeof(base_t),
	base_default_ctor2,
	base_dtor2,
	base_copy_ctor2,
	NULL,
	NULL,
	NULL,
	NULL
};

typedef const base_t* base_const_iterator;

void test_renew()
{
	char* ptr=output;
	const type_info_t* ti=&__base2_ti;
	base_t* b1 = new_array(ti,5);
	base_const_iterator bi;
	for(bi=b1;bi!=b1+5;bi++)
		ptr+=sprintf(ptr,"%d ",bi->x);
	TEST("Output is '0 1 2 3 4 '",strcmp(output,"0 1 2 3 4 ")==0);
	b1=renew_array(b1,10);
	ptr=output;
	for(bi=b1;bi!=b1+10;bi++)
		ptr+=sprintf(ptr,"%d ",bi->x);
	TEST("Output is '0 1 2 3 4 5 6 7 8 9 '",strcmp(output,"0 1 2 3 4 5 6 7 8 9 ")==0);
	b1=renew_array_copy(b1,15,b1+4);
	ptr=output;
	for(bi=b1;bi!=b1+15;bi++)
		ptr+=sprintf(ptr,"%d ",bi->x);
	TEST("Output is '0 1 2 3 4 5 6 7 8 9 4 4 4 4 4 '",strcmp(output,"0 1 2 3 4 5 6 7 8 9 4 4 4 4 4 ")==0);
	b1=renew_array_ctor(b1,20,base_ctor2,100);
	ptr=output;
	for(bi=b1;bi!=b1+20;bi++)
		ptr+=sprintf(ptr,"%d ",bi->x);
	TEST("Output is '0 1 2 3 4 5 6 7 8 9 4 4 4 4 4 110 111 112 113 114 '",strcmp(output,"0 1 2 3 4 5 6 7 8 9 4 4 4 4 4 110 111 112 113 114 ")==0);
	dtor_ptr=output;
	b1=renew_array_ctor(b1,15,base_ctor2,100);
	TEST("Output is '110 111 112 113 114 '",strcmp(output,"110 111 112 113 114 ")==0);
	dtor_ptr=output;
	b1=renew_array_copy(b1,10,b1+4);
	TEST("Output is '4 4 4 4 4 '",strcmp(output,"4 4 4 4 4 ")==0);
	dtor_ptr=output;
	b1=renew_array(b1,5);
	TEST("Output is '5 6 7 8 9 '",strcmp(output,"5 6 7 8 9 ")==0);
	dtor_ptr=output;
	delete(b1);
}
*/

test_function tests[]=
{
 	test_new_delete,
	test_new_delete_array,
	test_pod,
	test_operators,
	test_copy,
	test_derived_dtor,
/*	test_renew, */
};

STD_MAIN(tests)
