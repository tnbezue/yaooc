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
#include <yaooc/memory.h>
#include <yaooc/garbage_bag.h>
#include <yaooc/vector.h>
#include <yaooc/algorithm.h>
#include "test_harness.h"

typedef struct
{
	int x;
} demo_t;

void demo_default_ctor(pointer p)
{
	((demo_t*)p)->x=0;
}

void demo_dtor(pointer p)
{
}

void demo_ctor_int(pointer p,va_list args)
{
  ((demo_t*)p)->x=va_arg(args,int);
}

DEFINE_TYPE_INFO(demo,demo_default_ctor,demo_dtor,NULL,NULL,NULL,NULL,NULL)

void test_sp()
{

	yaooc_shared_ptr_pointer spDemo1=new_ctor(yaooc_shared_ptr,yaooc_shared_ptr_ctor_ptr,
        new_ctor(demo,demo_ctor_int,12));

	yaooc_shared_ptr_pointer spDemo2=new(yaooc_shared_ptr);
	TEST("spDemo1 is unique",M(spDemo1,unique));
	TEST("spDemo2 is unique",M(spDemo2,unique));
  puts("assign(spDemo2,spDemo1)");
	assign(spDemo2,spDemo1);
	TEST("SpDemo1 has count is 2",M(spDemo1,count) == 2);
	TEST("SpDemo2 has Count is 2",M(spDemo2,count) == 2);
	TEST("spDemo1 is not unique",!M(spDemo1,unique));
	TEST("spDemo2 is not unique",!M(spDemo2,unique));
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
  M(spDemo3,reset,new_ctor(demo,demo_ctor_int,31));
  puts("Reset spDemo3");
	TEST("SpDemo1 has count is 2",M(spDemo1,count) == 2);
	TEST("SpDemo2 has Count is 2",M(spDemo2,count) == 2);
	TEST("SpDemo3 has Count is 1",M(spDemo3,count) == 1);
  puts("delete SpDemo1 and SpDemo3");
  delete(spDemo3);
	delete(spDemo1);
	TEST("spDemo2 count is 1",M(spDemo2,count) == 1);
	TEST("spDemo2 unique",M(spDemo2,unique));
	delete(spDemo2);
}

/*
  Same as above but using template
*/
SHARED_PTR_DEFINITION(demo)
SHARED_PTR_IMPLEMENTATION(demo)

void test_tmpl()
{
	demo_t* d1=new(demo); /* Don't delete because shared pointer will delete it */
	d1->x=12;
	demo_shared_ptr_pointer spDemo1=new_ctor(demo_shared_ptr,demo_shared_ptr_ctor_ptr,d1);

	demo_shared_ptr_pointer spDemo2=new(demo_shared_ptr);

	assign(spDemo2,spDemo1);
	TEST("Count is 2",M(spDemo1,count) == 2);
	TEST("spDemo1 not unique",!M(spDemo1,unique));
	TEST("spDemo2 not unique",!M(spDemo2,unique));
	demo_t* d2=M(spDemo1,get);
	TEST("demo_t value via spDemo1 is 12",d2->x == 12);
	demo_t* d3=M(spDemo2,get);
	TEST("demo_t value via spDemo2 is 12",d3->x == 12);
	TEST("spDemo1.get and spDemo2.get are the same",M(spDemo1,get) == M(spDemo2,get));
	delete(spDemo1);
	TEST("spDemo2 count is 1",M(spDemo2,count) == 1);
	TEST("spDemo2 unique",M(spDemo2,unique));
	delete(spDemo2);
}

VECTOR_DEFINITION(demo_shared_ptr,demo_shared_ptr_vector)
VECTOR_IMPLEMENTATION(demo_shared_ptr,demo_shared_ptr_vector)

void test_vector()
{
	demo_t* d1=new(demo);
	d1->x=12;
  demo_shared_ptr_pointer spDemo1=new_ctor(demo_shared_ptr,demo_shared_ptr_ctor_ptr,d1);
  demo_shared_ptr_vector_pointer spv=new(demo_shared_ptr_vector);
  M(spv,push_back,spDemo1);
  delete(spDemo1);
  d1=new(demo);
  d1->x=32;
  spDemo1=new_ctor(demo_shared_ptr,demo_shared_ptr_ctor_ptr,d1);
  M(spv,push_back,spDemo1);
  delete(spDemo1);
  demo_shared_ptr_vector_const_iterator idsp;
  for(idsp=M(spv,cbegin);idsp!=M(spv,cend);idsp++) {
    printf("%d\n",M(idsp,cget)->x);
  }
  delete(spv);
}

#include "shape.inc"

SHARED_PTR_DEFINITION(shape)
SHARED_PTR_IMPLEMENTATION(shape)

VECTOR_DEFINITION(shape_shared_ptr,shape_shared_ptr_vector)
VECTOR_IMPLEMENTATION(shape_shared_ptr,shape_shared_ptr_vector)

void test_polymorphism()
{
  shape_shared_ptr_vector_pointer sspv=new(shape_shared_ptr_vector);
  TESTCASE("Polymorphism");
  /*
    Don't have to save circle becase shared pointer has it.
  */
  optr=output;
  shape_shared_ptr_pointer s=new_ctor(shape_shared_ptr,shape_shared_ptr_ctor_ptr,
        new_ctor(circle,circle_ctor_radius,5.127));
  M(sspv,push_back,s);
  delete(s);
  TEST("Called Circle ctor radius, Circle set radius",strcmp(output,"CCR:CSR:")==0);
  optr=output;
  s=new_ctor(shape_shared_ptr,shape_shared_ptr_ctor_ptr,
        new_ctor(square,square_ctor_length,3.62));
  M(sspv,push_back,s);
  delete(s);
  TEST("Called Square ctor length, square set length",strcmp(output,"SQCL:SQSL:")==0);
  optr=output;
  s=new_ctor(shape_shared_ptr,shape_shared_ptr_ctor_ptr,
        new_ctor(rectangle,rectangle_ctor_length_width,2.17,18.33));
  M(sspv,push_back,s);
  delete(s);
  TEST("Called Rectange ctor length width, square set length, rectange set width",strcmp(output,"RCLW:SQSL:RSW:")==0);
  optr=output;
  shape_shared_ptr_vector_const_iterator i;
  for(i=M(sspv,cbegin);i!=M(sspv,cend);i++) {
    shape_const_pointer ssp=M(i,cget);
    printf("%lg\n",M(ssp,area));
  }
  TEST("Reported areas are: Circle Area=82.5803 : Square area=13.1044 : Rectangle Area=39.7761",strcmp(output,"Circle Area=82.5803 : Square area=13.1044 : Rectangle Area=39.7761 : ")==0);
  shape_shared_ptr_pointer sq=new_ctor(shape_shared_ptr,shape_shared_ptr_ctor_ptr,
        new_ctor(square,square_ctor_length,3.62));
  optr=output; *optr=0;
  shape_shared_ptr_pointer item=yaooc_find(shape_shared_ptr_ti,M(sspv,cbegin),M(sspv,cend),sq);
  bool found=item!=M(sspv,cend);
  TEST("Item found",found);
  if(found)
    TEST("Values ==",M(M(sq,cget),area)==M(M(item,cget),area));
  M((square_pointer)M(sq,get),set_length,20.0);
  item=yaooc_find(shape_shared_ptr_ti,M(sspv,cbegin),M(sspv,cend),sq);
  TEST("Item not found",item==M(sspv,cend));
  delete(sq);
  optr=output;
  delete(sspv);
  TEST("Delete vector report Shape virtual dtor, circle virtual dtor, shape virtual dtor, square virtual dtor, shape virtual dtor, rectangle virtual dtor, ",strcmp(output,"SVD:CVD:SVD:SQVD:SVD:RVD:")==0); printf("X%sX\n",output);
}

test_function tests[]=
{
 	test_sp,
  test_tmpl,
  test_vector,
  test_polymorphism
};

STD_MAIN(tests)
