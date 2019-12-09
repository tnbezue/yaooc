#include "test_memory.h"


#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <yaooc/memory.h>
#include <yaooc/algorithm.h>
#include <yaooc/string.h>
#include "test_harness.h"


void demo_say(const_pointer __pthis__)
{
demo_const_pointer this=__pthis__;(void)this;

      printf("X = %d  Y = %d\n",this->x,this->y);
    
}
void demo_ctor_int_int(pointer __pthis__,va_list __con_args__)
{
demo_pointer this=__pthis__;
int x = va_arg(__con_args__,int);
int y = va_arg(__con_args__,int);



      this->x=x;
      this->y=y;
    
}
void demo_default_ctor(pointer __pthis__)
{
demo_pointer this=__pthis__;(void)this;



      if(optr)
        optr+=sprintf(optr,"DDC:");
      this->x=0;
      this->y=0;
    
}
void demo_dtor(pointer __pthis__)
{
demo_pointer this=__pthis__;(void)this;


      if(optr)
        optr+=sprintf(optr,"DD:");
    
}
void demo_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
demo_pointer this=__pthis__;(void)this;
demo_const_pointer src=__psrc__;(void)src;



      assign_static(this,src,demo);
    
}
void demo_assign(pointer __pthis__,const_pointer __psrc__)
{
demo_pointer this=__pthis__;(void)this;
demo_const_pointer src=__psrc__;(void)src;


      this->x=src->x;
      this->y=src->y;

    
}
int demo_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
demo_const_pointer lhs=__plhs__;(void)lhs;
demo_const_pointer rhs=__prhs__;(void)rhs;

      return (lhs->x > rhs->x) - (lhs->x < rhs->x);
    
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

DYNAMIC_POINTER_IMPLEMENTATION(demo,dynamic_demo);

void test_dynamic_pointer()
{
  dynamic_demo_pointer dd=new(dynamic_demo);
  demo_pointer d=new_ctor(demo,demo_ctor_int_int,12,-8);
  assign_static(dd,&d,dynamic_demo);
  demo_say(*dd);
  DELETE_LIST(dd,d);
}



VECTOR_IMPLEMENTATION(dynamic_demo,dynamic_demo_pointer_vector);

void test_dynamic_pointer_vector()
{
  dynamic_demo_pointer_vector_t* dpv=new(dynamic_demo_pointer_vector);
  demo_t* d=new_ctor(demo,demo_ctor_int_int,12,-8);
  M(dpv,push_back,&d);
  delete(d);
  d=new_ctor(demo,demo_ctor_int_int,8,20);
  M(dpv,push_back,&d);
  delete(d);
  d=new_ctor(demo,demo_ctor_int_int,21,0);
  M(dpv,push_back,&d);
  delete(d);
  d=new_ctor(demo,demo_ctor_int_int,88,0);
  demo_t** dp=yaooc_find(dynamic_demo,M(dpv,cbegin),M(dpv,cend),&d);
  TEST("Should not be found",dp==M(dpv,cend));
  d->x=8;
  dp=yaooc_find(dynamic_demo,M(dpv,cbegin),M(dpv,cend),&d);
  TEST("Should be found",dp!=M(dpv,cend));
  TEST("X = X of found item",(*dp)->x == d->x);
  delete(d);
  delete(dpv);
}

void test_unique_pointer()
{
  TESTCASE("Unique pointer")
 demo_t* d1=new(demo);
 d1->x=12;

 yaooc_unique_ptr_pointer upDemo1=new_ctor(yaooc_unique_ptr,yaooc_unique_ptr_ctor_ptr,d1);
  TEST("upDemo1 has d1 pointer",M(upDemo1,get)==d1);
 yaooc_unique_ptr_pointer upDemo2=new(yaooc_unique_ptr);
  TEST("upDemo2 has null pointer",M(upDemo2,get)==NULL);
  assign(upDemo2,upDemo1);
  puts("assign upDemo1 to upDemo2");
  TEST("upDemo1 has NULL pointer",M(upDemo1,get)==NULL);
  TEST("upDemo2 has d1 pointer",M(upDemo2,get)==d1);

 demo_t* d2=new(demo);
 d2->x=36;
  M(upDemo1,reset,d2);
  TEST("set upDemo1 to d2",M(upDemo1,get)==d2);
  puts("swap upDemo1 and upDemo2");
  M(upDemo1,swap,upDemo2);
  TEST("upDemo1 has d1",M(upDemo1,get)==d1);
  TEST("upDemo2 has d2",M(upDemo2,get)==d2);

  TEST("upDemo1 value is 12",((demo_pointer)M(upDemo1,get))->x==12);
  TEST("upDemo2 value is 36",((demo_pointer)M(upDemo2,get))->x==36);
  delete(upDemo1);
  delete(upDemo2);
}





UNIQUE_PTR_DEFINITION(demo,demo_unique_ptr);
UNIQUE_PTR_IMPLEMENTATION(demo,demo_unique_ptr);

void test_unique_pointer_tmpl()
{
  TESTCASE("Unique pointer template")
 demo_t* d1=new(demo);
 d1->x=12;

 demo_unique_ptr_pointer upDemo1=new_ctor(demo_unique_ptr,demo_unique_ptr_ctor_ptr,d1);
  TEST("upDemo1 has d1 pointer",M(upDemo1,get)==d1);
 demo_unique_ptr_pointer upDemo2=new(demo_unique_ptr);
  TEST("upDemo2 has null pointer",M(upDemo2,get)==NULL);
  assign(upDemo2,upDemo1);
  puts("assign upDemo1 to upDemo2");
  TEST("upDemo1 has NULL pointer",M(upDemo1,get)==NULL);
  TEST("upDemo2 has d1 pointer",M(upDemo2,get)==d1);

 demo_t* d2=new(demo);
 d2->x=36;
  M(upDemo1,reset,d2);
  TEST("set upDemo1 to d2",M(upDemo1,get)==d2);
  puts("swap upDemo1 and upDemo2");
  M(upDemo1,swap,upDemo2);
  TEST("upDemo1 has d1",M(upDemo1,get)==d1);
  TEST("upDemo2 has d2",M(upDemo2,get)==d2);
  TEST("upDemo1 value is 12",M(upDemo1,get)->x==12);
  TEST("upDemo2 value is 36",M(upDemo2,get)->x==36);
  delete(upDemo1);
  delete(upDemo2);
}

void test_shared_pointer()
{

 yaooc_shared_ptr_pointer spDemo1=new_ctor(yaooc_shared_ptr,yaooc_shared_ptr_ctor_ptr,
        new_ctor(demo,demo_ctor_int_int,12,17));

 yaooc_shared_ptr_pointer spDemo2=new(yaooc_shared_ptr);
 TEST("spDemo1 is count is 1",M(spDemo1,count)==1);
 TEST("spDemo2 is unique",M(spDemo2,count)==0);
  puts("assign(spDemo2,spDemo1)");
 assign(spDemo2,spDemo1);
 TEST("SpDemo1 has count is 2",M(spDemo1,count) == 2);
 TEST("SpDemo2 has Count is 2",M(spDemo2,count) == 2);


 demo_t* d2=M(spDemo1,get);
 TEST("demo_t value via spDemo1 is 12",d2->x == 12);
 demo_t* d3=M(spDemo2,get);
 TEST("demo_t value via spDemo2 is 12",d3->x == 12);
 TEST("spDemo1.get and spDemo2.get are the same",M(spDemo1,get) == M(spDemo2,get));
  yaooc_shared_ptr_pointer spDemo3=new(yaooc_shared_ptr);
  assign(spDemo3,spDemo1);
  puts("spDemo3 assigned to spDemo1");
 TEST("SpDemo1 has count is 3",M(spDemo1,count) == 3);
 TEST("SpDemo2 has Count is 3",M(spDemo2,count) == 3);
 TEST("SpDemo3 has Count is 3",M(spDemo3,count) == 3);
  M(spDemo3,reset,new_ctor(demo,demo_ctor_int_int,31, 44));
  puts("Reset spDemo3");
 TEST("SpDemo1 has count is 2",M(spDemo1,count) == 2);
 TEST("SpDemo2 has Count is 2",M(spDemo2,count) == 2);
 TEST("SpDemo3 has Count is 1",M(spDemo3,count) == 1);
  puts("delete SpDemo1 and SpDemo3");
  delete(spDemo3);
 delete(spDemo1);
 TEST("spDemo2 count is 1",M(spDemo2,count) == 1);

 delete(spDemo2);
}




SHARED_PTR_DEFINITION(demo,demo_shared_ptr);
SHARED_PTR_IMPLEMENTATION(demo,demo_shared_ptr);

void test_shared_pointer_tmpl()
{
 demo_t* d1=new(demo);
 d1->x=12;
 demo_shared_ptr_pointer spDemo1=new_ctor(demo_shared_ptr,demo_shared_ptr_ctor_ptr,d1);

 demo_shared_ptr_pointer spDemo2=new(demo_shared_ptr);

 assign(spDemo2,spDemo1);
 TEST("Count is 2",M(spDemo1,count) == 2);


 demo_t* d2=M(spDemo1,get);
 TEST("demo_t value via spDemo1 is 12",d2->x == 12);
 demo_t* d3=M(spDemo2,get);
 TEST("demo_t value via spDemo2 is 12",d3->x == 12);
 TEST("spDemo1.get and spDemo2.get are the same",M(spDemo1,get) == M(spDemo2,get));
 delete(spDemo1);
 TEST("spDemo2 count is 1",M(spDemo2,count) == 1);

 delete(spDemo2);
}

#include <yaooc/vector.h>
VECTOR_DEFINITION(demo_unique_ptr,demo_unique_ptr_vector);
VECTOR_IMPLEMENTATION(demo_unique_ptr,demo_unique_ptr_vector);

void test_vector()
{
  demo_unique_ptr_vector_pointer dupv=new(demo_unique_ptr_vector);
  int numbers[] = { 12, 10, 22, 48 , 53 };
  int i;
  int n=ARRAY_SIZE(numbers);

  char dupp_space[sizeof(demo_unique_ptr_t)];
  demo_unique_ptr_pointer dupp=newp(dupp_space,demo_unique_ptr);
  for(i=0;i<n;i++) {
    demo_t* d1=new(demo);
    d1->x=numbers[i];
    M(dupp,reset,d1);
    M(dupv,push_back,dupp);
  }
  demo_unique_ptr_vector_const_iterator idup;
  optr=output;
  for(idup=M(dupv,begin);idup!=M(dupv,end);idup++) {
    optr+=sprintf(optr,"%d:",M(idup,get)->x);
  }
  TEST("Array is '12:10:22:48:53:'",strcmp(output,"12:10:22:48:53:")==0);
  delete(dupv);
}

#include "shape.inc"

UNIQUE_PTR_DEFINITION(shape,shape_unique_ptr);
UNIQUE_PTR_IMPLEMENTATION(shape,shape_unique_ptr);

VECTOR_DEFINITION(shape_unique_ptr,shape_unique_ptr_vector);
VECTOR_IMPLEMENTATION(shape_unique_ptr,shape_unique_ptr_vector);

void test_polymorphism()
{
  shape_unique_ptr_vector_pointer supv=new(shape_unique_ptr_vector);




  STACK_VAR_CTOR(shape_unique_ptr,s,shape_unique_ptr_ctor_ptr,NULL);
  TESTCASE("Polymorphism");



  optr=output;
  M(&s,reset,new_ctor(circle,circle_ctor_radius,5.127));
  M(supv,push_back,&s);
  TEST("Called Circle ctor radius, Circle set radius",strcmp(output,"CCR:CSR:")==0);
  optr=output;
  M(&s,reset,new_ctor(square,square_ctor_length,3.62));
  M(supv,push_back,&s);
  TEST("Called Square ctor length, square set length",strcmp(output,"SQCL:SQSL:")==0);
  optr=output;
  M(&s,reset,new_ctor(rectangle,rectangle_ctor_length_width,2.17,18.33));
  M(supv,push_back,&s);
  TEST("Called Rectange ctor length width, square set length, rectange set width",strcmp(output,"RCLW:SQSL:RSW:")==0);
  optr=output;
  shape_unique_ptr_vector_const_iterator i;
  for(i=M(supv,begin);i!=M(supv,end);i++) {
    printf("%lg\n",M(M(i,get),area));
  }
  TEST("Reported areas are: Circle Area=82.5803 : Square area=13.1044 : Rectangle Area=39.7761",strcmp(output,"Circle Area=82.5803 : Square area=13.1044 : Rectangle Area=39.7761 : ")==0);
  optr=output;
  delete(supv);
  TEST("Delete vector report Shape virtual dtor, circle virtual dtor, shape virtual dtor, square virtual dtor, shape virtual dtor, rectangle virtual dtor, ",strcmp(output,"SVD:CVD:SVD:SQVD:SVD:RVD:")==0); printf("X%sX\n",output);
}

test_function tests[]=
{
  test_dynamic_pointer,
  test_dynamic_pointer_vector,
  test_unique_pointer,
  test_unique_pointer_tmpl,
  test_shared_pointer,
  test_shared_pointer_tmpl,
  test_vector,
  test_polymorphism,
};

STD_MAIN(tests)

