#include "test_new.h"

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
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


static  int demo_temp=0;
void demo_default_ctor(pointer __pthis__)
{
demo_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,demo);



      this->x =demo_temp++;
      if(optr) optr+=sprintf(optr,"DC%d",this->x);
    
}
void demo_dtor(pointer __pthis__)
{
demo_pointer this=__pthis__;(void)this;


      if(optr) optr+=sprintf(optr,"DT%d",this->x);
    
}
void demo_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
demo_pointer this=__pthis__;(void)this;
demo_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,demo);


      if(optr) optr+=sprintf(optr,"CC%d",src->x);
      demo_assign(this,src); 
    
}
void demo_assign(pointer __pthis__,const_pointer __psrc__)
{
demo_pointer this=__pthis__;(void)this;
demo_const_pointer src=__psrc__;(void)src;


      this->x=src->x;
      if(optr) optr+=sprintf(optr,"AS%d",this->x);
    
}
int demo_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
demo_const_pointer lhs=__plhs__;(void)lhs;
demo_const_pointer rhs=__prhs__;(void)rhs;

      int rc = (lhs->x > rhs->x) - (lhs->x < rhs->x);
      if(optr) optr+=sprintf(optr,"%d<=>%d = %d",lhs->x,rhs->x,rc);
      return rc;
    
}
void demo_ctor_int(pointer __pthis,va_list __con_args__){
demo_pointer this=__pthis;(void)this;
int x = va_arg(__con_args__,int);

call_default_ctor_static(this,demo);


      this->x = x;
      if(optr) optr+=sprintf(optr,"CT%d",this->x);
    
}
const type_info_t __demo_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(demo_t),
.rich_compare_=demo_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=demo_default_ctor,
.dtor_=demo_dtor,
.copy_ctor_=demo_copy_ctor,
.assign_=demo_assign,
.class_table_=NULL,
.parent_=NULL
};
const type_info_t* const demo_ti=(const type_info_t* const)&__demo_ti;
void test_new_delete()
{
	optr=output;
	demo_pointer d1 = new(demo);
	TESTCASE("New/delete");
	TEST("Initialize with default ctor",strcmp(output,"DC0")==0);
	optr=output;
	delete(d1);
	TEST("Dtor called",strcmp(output,"DT0")==0);
	optr=output;
	demo_pointer d1a=new_ctor(demo,demo_ctor_int,99);
	TEST("Initialize with non default ctor -- will use default ctor first",strcmp(output,"DC1CT99")==0);
	optr=output;
	demo_pointer d2=new_copy(d1a);
	TEST("Copy ctor (calls default and assign)",strcmp(output,"DC2CC99AS99")==0);
	optr=output;
	delete(d1a);
	delete(d2);
	TEST("Dtor called",strcmp(output,"DT99DT99")==0);

	TESTCASE("Placement new");
	demo_t d3;

	demo_temp=25;
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
	demo_temp=0;
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
	TEST("Ctor called for each",strcmp(output,"DC5CT127DC6CT127DC7CT127DC8CT127DC9CT127") ==0);
	delete(d1a);

	demo_t d2[5];
	optr=output;
	demo_temp=0;
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
	TEST("Ctor called for each",strcmp(output,"DC5CT256DC6CT256DC7CT256DC8CT256DC9CT256") ==0);
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


void base_default_ctor(pointer __pthis__)
{
base_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,base);



      this->x = 0;
      if(optr) optr+=sprintf(optr,"BDC0");
    
}
void base_dtor(pointer __pthis__)
{
base_pointer this=__pthis__;(void)this;


      if(optr) optr+=sprintf(optr,"BDT%d",this->x);
    
}
void base_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
base_pointer this=__pthis__;(void)this;
base_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,base);


      if(optr) optr+=sprintf(optr,"BCC%d-%d",this->x,src->x);
      base_assign(this,src);
    
}
void base_assign(pointer __pthis__,const_pointer __psrc__)
{
base_pointer this=__pthis__;(void)this;
base_const_pointer src=__psrc__;(void)src;


      this->x=src->x;
      if(optr) optr+=sprintf(optr,"BAS%d-%d",this->x,src->x);
    
}
int base_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
base_const_pointer lhs=__plhs__;(void)lhs;
base_const_pointer rhs=__prhs__;(void)rhs;

      if(optr) optr+=sprintf(optr,"BLTC%d-%d",lhs->x,rhs->x);
      return lhs->x - rhs->x;
    
}
void base_ctor_int(pointer __pthis,va_list __con_args__){
base_pointer this=__pthis;(void)this;
int x = va_arg(__con_args__,int);

call_default_ctor_static(this,base);


      if(optr) optr+=sprintf(optr,"BCTI%d",x);
      this->x=x;
    
}
const type_info_t __base_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(base_t),
.rich_compare_=base_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=base_default_ctor,
.dtor_=base_dtor,
.copy_ctor_=base_copy_ctor,
.assign_=base_assign,
.class_table_=NULL,
.parent_=NULL
};
const type_info_t* const base_ti=(const type_info_t* const)&__base_ti;
void derived_default_ctor(pointer __pthis__)
{
derived_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,derived);



      if(optr) optr+=sprintf(optr,"DDC0");
      this->y = 0;
    
}
void derived_dtor(pointer __pthis__)
{
derived_pointer this=__pthis__;(void)this;


      if(optr) optr+=sprintf(optr,"DDT%d",this->y);
    
}
void derived_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
derived_pointer this=__pthis__;(void)this;
derived_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,derived);


      if(optr) optr+=sprintf(optr,"DCC%d:%d-%d:%d",this->x,this->y,src->x,src->y);
      derived_assign(this,src); 
    
}
void derived_assign(pointer __pthis__,const_pointer __psrc__)
{
derived_pointer this=__pthis__;(void)this;
derived_const_pointer src=__psrc__;(void)src;


      if(optr) optr+=sprintf(optr,"DAS%d:%d-%d:%d",this->x,this->y,src->x,src->y);
      base_assign(this,src);
      this->y = src->y;
    
}
void derived_ctor_int_int(pointer __pthis,va_list __con_args__){
derived_pointer this=__pthis;(void)this;
int x = va_arg(__con_args__,int);
int y = va_arg(__con_args__,int);

call_constructor(this,base_ctor_int,x);
this->y=y;


      if(optr) optr+=sprintf(optr,"DCTII%d",y);
    
}
const type_info_t __derived_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(derived_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=derived_default_ctor,
.dtor_=derived_dtor,
.copy_ctor_=derived_copy_ctor,
.assign_=derived_assign,
.class_table_=NULL,
.parent_=&__base_ti};
const type_info_t* const derived_ti=(const type_info_t* const)&__derived_ti;
void derived2_default_ctor(pointer __pthis__)
{
derived2_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,derived2);



      if(optr) optr+=sprintf(optr,"D2DC0");
      this->z=0;
    
}
void derived2_dtor(pointer __pthis__)
{
derived2_pointer this=__pthis__;(void)this;


      if(optr) optr+=sprintf(optr,"D2DT%d",this->z);
    
}
void derived2_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
derived2_pointer this=__pthis__;(void)this;
derived2_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,derived2);


      if(optr) optr+=sprintf(optr,"D2CC%d:%d:%d-%d:%d:%d",this->x,this->y,this->z,src->x,src->y,src->z);
      derived2_assign(this,src);
    
}
void derived2_assign(pointer __pthis__,const_pointer __psrc__)
{
derived2_pointer this=__pthis__;(void)this;
derived2_const_pointer src=__psrc__;(void)src;


      if(optr) optr+=sprintf(optr,"D2AS%d:%d:%d-%d:%d:%d",this->x,this->y,this->z,src->x,src->y,src->z);
      derived_assign(this,src);
      this->z = src->z;
    
}
void derived2_ctor_int_int_int(pointer __pthis,va_list __con_args__){
derived2_pointer this=__pthis;(void)this;
int x = va_arg(__con_args__,int);
int y = va_arg(__con_args__,int);
int z = va_arg(__con_args__,int);

call_constructor(this,derived_ctor_int_int,x,y);


      if(optr) optr+=sprintf(optr,"D2CTIII%d",z);
      this->z=z;
    
}
const type_info_t __derived2_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(derived2_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=derived2_default_ctor,
.dtor_=derived2_dtor,
.copy_ctor_=derived2_copy_ctor,
.assign_=derived2_assign,
.class_table_=NULL,
.parent_=&__derived_ti};
const type_info_t* const derived2_ti=(const type_info_t* const)&__derived2_ti;
void test_derived_dtor()
{
  TESTCASE("Default ctor");
  optr=output;
  base_t *b=new(base);
  TEST("output is: BDC0",strcmp(output,"BDC0")==0);

  optr=output;
	derived_t* d=new(derived);
  TEST("output is: BDC0DDC0",strcmp(output,"BDC0DDC0")==0);
  optr=output;
	derived2_t* d2=new(derived2);
  TEST("output is: BDC0DDC0D2DC0",strcmp(output,"BDC0DDC0D2DC0")==0);

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
  TEST("output is: BDC0BCTI10",strcmp(output,"BDC0BCTI10")==0);

  optr=output;
  d=new_ctor(derived,derived_ctor_int_int,15,20);
  TEST("output is: BDC0BCTI15DCTII20",strcmp(output,"BDC0BCTI15DCTII20")==0);

  optr=output;
  d2=new_ctor(derived2,derived2_ctor_int_int_int,30,40,50);
  TEST("output is: BDC0BCTI30DCTII40D2CTIII50",strcmp(output,"BDC0BCTI30DCTII40D2CTIII50")==0);

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
	TEST("5 objects added (copied) to end",strcmp(output,"BDC0BCC0-12BAS12-12BDC0BCC0-12BAS12-12BDC0BCC0-12BAS12-12BDC0BCC0-12BAS12-12BDC0BCC0-12BAS12-12")==0);
	TEST("Size is 10",get_n_elem(b)==10);
	print_base_array(b);
	TEST("Values 5 zeros and 5 12's",strcmp(output,"0 0 0 0 0 12 12 12 12 12 ")==0);

	optr=output;
	b=renew_array_ctor(b,15,base_ctor_int,33);
  puts(output);
	TEST("5 objects added (constructed) to end",strcmp(output,"BDC0BCTI33BDC0BCTI33BDC0BCTI33BDC0BCTI33BDC0BCTI33")==0);
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

