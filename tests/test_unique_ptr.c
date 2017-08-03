#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <yaooc/memory.h>
#include <yaooc/vector.h>
#include "test_harness.h"

typedef struct
{
	int x;
	int y;
} demo_t;

void demo_default_ctor(pointer p)
{
  if(optr)
    optr+=sprintf(optr,"DDC:");
	((demo_t*)p)->x=0;
	((demo_t*)p)->y=0;
	fflush(stdout);
	fflush(stderr);
}

void demo_dtor(pointer p)
{
  if(optr)
    optr+=sprintf(optr,"DD:");
	fflush(stdout);
	fflush(stderr);
}
DEFINE_TYPE_INFO(demo,demo_default_ctor,demo_dtor,NULL,NULL,NULL,NULL,NULL)
typedef demo_t* demo_pointer;
typedef const demo_t* demo_const_pointer;

void test_up()
{
  TESTCASE("Unique pointer")
	demo_t* d1=new(demo);  /* Don't delete because unique pointer will delete it */
	d1->x=12;

	yaooc_unique_ptr_pointer upDemo1=new_ctor(yaooc_unique_ptr,yaooc_unique_ptr_ctor_ptr,d1);
  TEST("upDemo1 has d1 pointer",M(upDemo1,get)==d1);
	yaooc_unique_ptr_pointer upDemo2=new(yaooc_unique_ptr);
  TEST("upDemo2 has null pointer",M(upDemo2,get)==NULL);
  assign(upDemo2,upDemo1);
  puts("assign upDemo1 to upDemo2");
  TEST("upDemo1 has NULL pointer",M(upDemo1,get)==NULL);
  TEST("upDemo2 has d1 pointer",M(upDemo2,get)==d1);

	demo_t* d2=new(demo);  /* Don't delete because unique pointer will delete it */
	d2->x=36;
  M(upDemo1,set,d2);
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


/*
  Same as above but using template
*/
UNIQUE_PTR_DEFINITION(demo)
UNIQUE_PTR_IMPLEMENTATION(demo)

void test_tmpl()
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

	demo_t* d2=new(demo);  /* Don't delete because unique pointer will delete it */
	d2->x=36;
  M(upDemo1,set,d2);
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

VECTOR_DEFINITION(demo_unique_ptr)
VECTOR_IMPLEMENTATION(demo_unique_ptr)

void test_vector()
{
  demo_unique_ptr_vector_pointer dupv=new(demo_unique_ptr_vector);
  int numbers[] = { 12, 10, 22, 48 , 53 };
  int i;
  int n=ARRAY_SIZE(numbers);
  /* Just to demonstrate another way for an object to be on stack */
  char dupp_space[sizeof(demo_unique_ptr_t)];
  demo_unique_ptr_pointer dupp=newp(dupp_space,demo_unique_ptr);
  for(i=0;i<n;i++) {
    demo_t* d1=new(demo);
    d1->x=numbers[i];
    M(dupp,set,d1);
    M(dupv,push_back,dupp);
  }
  demo_unique_ptr_vector_const_iterator idup;
  optr=output;
  for(idup=M(dupv,cbegin);idup!=M(dupv,cend);idup++) {
    optr+=sprintf(optr,"%d:",M(idup,cget)->x);
  }
  TEST("Array is '12:10:22:48:53:'",strcmp(output,"12:10:22:48:53:")==0);
  delete(dupv);
}

#include "shape.inc"

UNIQUE_PTR_DEFINITION(shape)
UNIQUE_PTR_IMPLEMENTATION(shape)

VECTOR_DEFINITION(shape_unique_ptr)
VECTOR_IMPLEMENTATION(shape_unique_ptr)

void test_polymorphism()
{
  shape_unique_ptr_vector_pointer supv=new(shape_unique_ptr_vector);
  /* Below is same as:
    STACK_PTR(shape_unique_ptr,s);
    Because default ctor set's value to NULL.  Just showing off different method.
  */
  STACK_PTR_CTOR(shape_unique_ptr,s,shape_unique_ptr_ctor_ptr,NULL);
  TESTCASE("Polymorphism");
  /*
    Don't have to save circle becase unique pointer has it.
  */
  optr=output;
  M(s,set,new_ctor(circle,circle_ctor_radius,5.127));
  M(supv,push_back,s);
  TEST("Called Circle ctor radius, Circle set radius",strcmp(output,"CCR:CSR:")==0);
  optr=output;
  M(s,set,new_ctor(square,square_ctor_length,3.62));
  M(supv,push_back,s);
  TEST("Called Square ctor length, square set length",strcmp(output,"SQCL:SQSL:")==0);
  optr=output;
  M(s,set,new_ctor(rectangle,rectangle_ctor_length_width,2.17,18.33));
  M(supv,push_back,s);
  TEST("Called Rectange ctor length width, square set length, rectange set width",strcmp(output,"RCLW:SQSL:RSW:")==0);
  optr=output;
  shape_unique_ptr_vector_const_iterator i;
  for(i=M(supv,cbegin);i!=M(supv,cend);i++) {
    printf("%lg\n",M(M(i,cget),area));
  }
  TEST("Reported areas are: Circle Area=82.5803 : Square area=13.1044 : Rectangle Area=39.7761",strcmp(output,"Circle Area=82.5803 : Square area=13.1044 : Rectangle Area=39.7761 : ")==0);
  optr=output;
  delete(supv);
  TEST("Delete vector report Shape virtual dtor, circle virtual dtor, shape virtual dtor, square virtual dtor, shape virtual dtor, rectangle virtual dtor, ",strcmp(output,"SVD:CVD:SVD:SQVD:SVD:RVD:")==0); printf("X%sX\n",output);
}

test_function tests[]=
{
 	test_up,
  test_tmpl,
  test_vector,
  test_polymorphism
};

STD_MAIN(tests)
