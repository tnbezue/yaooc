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
#include <stddef.h>
#include <yaooc/object.h>
#include "test_harness.h"
#include "demo_def.inc"

char dummy[sizeof(demo_t)];

void test_basic()
{
  TEST("Size yaooc_object_t is 8",sizeof(yaooc_object_t) == 8);
  TEST("Size demo_t is 24",sizeof(demo_t) == 24);
	demo_t* d= new(demo);
  M(d,setx,32);

  TEST("isa demo_t",ISA(d,demo));
  TEST("is a decendant of object_t",ISA(d,yaooc_object));
  TEST("Not a decendant of string_t",!ISA(d,yaooc_string));
//  TEST("ISA method return 'demo_t'",ISA(d,"demo_t"));
//  TEST("ISA from static yaooc_object table",strcmp(yaooc_object_isa(d),"yaooc_object_t")==0);
  TEST("D is 32",d->x==32);
  demo_pointer d2=new(demo);
  M(d2,setx,19);
  TEST("D2 is 19",d2->x==19);
  M(d,swap,d2);
  TEST("after swap D is 19",d->x==19);
  TEST("and D2 is 32",d2->x==32);

  /*
    Ways of calling parent method
  */
  /*
    Using method similar to M macro
    Works for calling the parent if only one level will be traversed.
    Will not work if more than one level is traversed (parent calls its' parent method using same form).
    Bad -- Can get into infinite loop
  */
  TEST("Parent isa method returns 'yaooc_object_t'",strcmp(((yaooc_object_class_table_t*)(d->class_table_->parent_class_table_))->type_name_,"yaooc_object_t")==0);

  /*
    Using the complete method name
    If a different parent method is implemented with different name (or inheritance hierarchy changed), may not work as expected
    Code would have to be manually changed.
    Good -- Implementing parent method with different name is rare.
  */
//  TEST("Parent isa method returns 'yaooc_object_t'",strcmp(yaooc_object_isa(d),"yaooc_object_t")==0);

  /*
    Using parent class table directly.
    Slighty better than above.  May still require code changes if heirarchy changed.
    Better -- Parenting changes are very rare
  */
//  TEST("Parent isa method returns 'yaooc_object_t'",strcmp(yaooc_object_class_table.isa(d),"yaooc_object_t")==0);

  /*
    Using parent class table via this class table parent_class_table entry
    Eliminates the shortcomings of the above three methods.
    Best -- can't think of any case it would not work. A simple #define makes it easier
  */
#define demo_parent_class_table ((yaooc_object_class_table_t*)(demo_class_table.parent_class_table_))
//  TEST("Parent isa method returns 'yaooc_object_t'",strcmp(demo_parent_class_table->isa(d),"yaooc_object_t")==0);
  delete(d);
  delete(d2);
}

/*
	The following classes (base, derived1, and derived2) will show 4 methods of calling a parent method.
	Each class will define the do_something method.
*/
yaooc_class_table(base)
{
  yaooc_object_class_table_t;
  void (*do_something)(pointer);
};
#define base_parent_class_table ((yaooc_object_class_table_t*)(demo_class_table.parent_class_table_))

yaooc_class_instance(base)
{
  yaooc_object_class_instance_t;
};
yaooc_class(base);

int base_do_something_count=0;
void base_do_something(pointer p)
{
  printf("Base do something has been called %d times\n",++base_do_something_count);
}
base_class_table_t base_class_table =
{
  .parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
  .type_name_ = (const char*) "base_t",
  .swap = yaooc_object_swap,
  .do_something = base_do_something
};
DEFINE_TYPE_INFO(base,N,N,N,N,N,N,N,Y,yaooc_object)

yaooc_class_table(derived1)
{
  base_class_table_t;
};
#define derived1_parent_class_table ((base_class_table_t*)(derived1_class_table.parent_class_table_))

yaooc_class_instance(derived1)
{
  base_class_instance_t;
};
yaooc_class(derived1);

int derived1_do_something_count=0;
void derived1_do_something_bad(pointer p)
{
  derived1_pointer this=p;
  if(++derived1_do_something_count > 5)
    return;
  printf("Derived 1 (bad) do something has been called %d times\n",derived1_do_something_count);
  ((base_class_table_t*)(this->class_table_->parent_class_table_))->do_something(p);
}
void derived1_do_something_good(pointer p)
{
  if(++derived1_do_something_count > 5)
    return;
  printf("Derived 1 (good) do something has been called %d times\n",derived1_do_something_count);
  base_do_something(p);
}
void derived1_do_something_better(pointer p)
{
  if(++derived1_do_something_count > 5)
    return;
  printf("Derived 1 (better) do something has been called %d times\n",derived1_do_something_count);
  base_class_table.do_something(p);
}
void derived1_do_something_best(pointer p)
{
  if(++derived1_do_something_count > 5)
    return;
  printf("Derived 1 (best) do something has been called %d times\n",derived1_do_something_count);
  ((const base_class_table_t*)(derived1_class_table.parent_class_table_))->do_something(p);
}
derived1_class_table_t derived1_class_table =
{
  .parent_class_table_ = (const class_table_t*)&base_class_table,
  .type_name_ = (const char*) "derived1_t",
  .swap = yaooc_object_swap,
  .do_something = derived1_do_something_bad
};
DEFINE_TYPE_INFO(derived1,N,N,N,N,N,N,N,Y,base)



yaooc_class_table(derived2)
{
  derived1_class_table_t;
};
#define derived2_parent_class_table ((derived1_class_table_t*)(derived2_class_table.parent_class_table_))

yaooc_class_instance(derived2)
{
  derived1_class_instance_t;
};
yaooc_class(derived2);

int derived2_do_something_count=0;
void derived2_do_something(pointer p)
{
  derived2_pointer this=p;
  if(++derived2_do_something_count > 5)
    return;
  printf("Derived 2 do something has been called %d times\n",derived2_do_something_count);
  ((base_class_table_t*)(this->class_table_->parent_class_table_))->do_something(p);
}
derived2_class_table_t derived2_class_table =
{
  .parent_class_table_ = (const class_table_t*)&derived1_class_table,
  .type_name_ = (const char*) "derived2_t",
  .swap = yaooc_object_swap,
  .do_something = derived2_do_something
};
DEFINE_TYPE_INFO(derived2,N,N,N,N,N,N,N,Y,derived1)

void test_inheritance()
{
  TESTCASE("Inheritance");
  base_pointer b=new(base);
  TEST("base object isa returns base_t",ISA(b,base));
  TEST("base is descendant from base_t",ISA(b,base));
  TEST("base is descendant from yaooc_object_t",ISA(b,yaooc_object));
  TEST("base is not a descendant of yaooc_string_t",!ISA(b,yaooc_string));

  derived1_pointer d1=new(derived1);
  TEST("derived 1 object isa returns derived1_t",ISA(d1,derived1));
  TEST("derived 1 is descendant from derived1_t",ISA(d1,derived1));
  TEST("derived 1 is descendant from base_t",ISA(d1,base));
  TEST("derived 1 is descendant from yaooc_object_t",ISA(d1,yaooc_object));
  TEST("derived 1 is not a descendant of yaooc_string_t",!ISA(d1,yaooc_string));

  derived2_pointer d2=new(derived2);
  TEST("derived 2 object isa returns derived2_t",ISA(d2,derived2));
  TEST("derived 2 is descendant from derived2_t",ISA(d2,derived2));
  TEST("derived 2 is descendant from derived1_t",ISA(d2,derived1));
  TEST("derived 2 is descendant from base_t",ISA(d2,base));
  TEST("derived 2 is descendant from yaooc_object_t",ISA(d2,yaooc_object));
  TEST("derived 2 is not a descendant of yaooc_string_t",!ISA(d2,yaooc_string));

  delete_list(b,d1,d2,NULL);
}

void test_calling_parent_bad()
{
  base_do_something_count=0;
  derived1_do_something_count=0;
  derived2_do_something_count=0;
  derived1_class_table.do_something=derived1_do_something_bad;
  TESTCASE("Bad way to call parent methods");
  derived2_pointer d2=new(derived2);
  M(d2,do_something);
  TEST("Base method called 1 times (intentionally made to fail)",base_do_something_count==1);
  TEST("Derived 1 method called 1 times (intentionally made to fail)",derived1_do_something_count==1);
  TEST("Derived 2 method called 1 times",derived2_do_something_count==1);
  delete(d2);
}

void test_calling_parent_good()
{
  base_do_something_count=0;
  derived1_do_something_count=0;
  derived2_do_something_count=0;
  derived1_class_table.do_something=derived1_do_something_good;
  TESTCASE("Good way to call parent methods");
  derived2_pointer d2=new(derived2);
  M(d2,do_something);
  TEST("Base method called 1 times",base_do_something_count==1);
  TEST("Derived 1 method called 1 times",derived1_do_something_count==1);
  TEST("Derived 2 method called 1 times",derived2_do_something_count==1);
  delete(d2);
}

void test_calling_parent_better()
{
  base_do_something_count=0;
  derived1_do_something_count=0;
  derived2_do_something_count=0;
  derived1_class_table.do_something=derived1_do_something_better;
  TESTCASE("Good way to call parent methods");
  derived2_pointer d2=new(derived2);
  M(d2,do_something);
  TEST("Base method called 1 times",base_do_something_count==1);
  TEST("Derived 1 method called 1 times",derived1_do_something_count==1);
  TEST("Derived 2 method called 1 times",derived2_do_something_count==1);
  delete(d2);
}

void test_calling_parent_best()
{
  base_do_something_count=0;
  derived1_do_something_count=0;
  derived2_do_something_count=0;
  derived1_class_table.do_something=derived1_do_something_best;
  TESTCASE("Best way to call parent methods");
  derived2_pointer d2=new(derived2);
  M(d2,do_something);
  TEST("Base method called 1 times",base_do_something_count==1);
  TEST("Derived 1 method called 1 times",derived1_do_something_count==1);
  TEST("Derived 2 method called 1 times",derived2_do_something_count==1);
  delete(d2);
}


test_function tests[]=
{
 	test_basic,
  test_inheritance,
  test_calling_parent_bad,
  test_calling_parent_good,
  test_calling_parent_better,
  test_calling_parent_best,
};

STD_MAIN(tests)
