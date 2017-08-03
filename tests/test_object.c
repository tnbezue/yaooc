#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/object.h>
#include "test_harness.h"
#include "demo_def.inc"

char dummy[sizeof(demo_t)];

void test_all()
{
  TEST("Size yaooc_object_t is 8",sizeof(yaooc_object_t) == 8);
  TEST("Size demo_t is 24",sizeof(demo_t) == 24);
	demo_t* d= new(demo);
  M(d,setx,32);

  TEST("isa demo_t",strcmp(M(d,isa),"demo_t")==0);
  TEST("is a decendant of object_t",M(d,is_descendent,"yaooc_object_t"));
  TEST("Not a decendant of string_t",!M(d,is_descendent,"yaooc_string_t"));
//  TEST("ISA from static demo table",strcmp(CVM(demo,d,isa),"demo_t")==0);
  TEST("ISA from static yaooc_object table",strcmp(yaooc_object_isa(d),"yaooc_object_t")==0);
  TEST("D is 32",d->x==32);
  demo_pointer d2=new(demo);
  M(d2,setx,19);
  TEST("D2 is 19",d2->x==19);
  M(d,swap,d2);
  TEST("after swap D is 19",d->x==19);
  TEST("and D2 is 32",d2->x==32);

  delete(d);
  delete(d2);
}

test_function tests[]=
{
 	test_all
};

STD_MAIN(tests)
