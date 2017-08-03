#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/json.h>
#include "test_harness.h"

void test_null()
{
  TESTCASE("NULL");
  json_null_pointer jn=new(json_null);
  TEST("Type is JSON_NULL",M(jn,type)==JSON_NULL);
  int nb=M(jn,print_to_string,output,1024);
  TEST("NULL print to string is 'null'",strcmp(output,"null")==0);
  TEST("Print to string reports 4 chars printed",nb==4);
  delete(jn);
}

void test_bool()
{
  TESTCASE("Bool");
  json_bool_pointer jb=new(json_bool);
  TEST("Type is JSON_BOOL",M(jb,type)==JSON_BOOL);
  TEST("Default value is false",M(jb,get)==false);
  M(jb,set,true);
  TEST("Set value is true",M(jb,get)==true);
  int nb=M(jb,print_to_string,output,1024);
  TEST("Print to string is 'true'",strcmp(output,"true")==0);
  TEST("Print to string reports 4 chars printed",nb==4);
  M(jb,set,false);
  TEST("Set value to false",M(jb,get)==false);
  nb=M(jb,print_to_string,output,1024);
  TEST("Print to string is 'false'",strcmp(output,"false")==0);
  TEST("Print to string reports 5 chars printed",nb==5);
  M(jb,set,true);
  M(jb,clear);
  TEST("Clear sets value to false",M(jb,get)==false);
  delete(jb);
}

void test_integer()
{
  TESTCASE("Integer");
  json_integer_pointer ji=new(json_integer);
  TEST("Type is JSON_INTEGER",M(ji,type)==JSON_INTEGER);
  TEST("Default value is zero",M(ji,get)==0);
  int nb=M(ji,print_to_string,output,1024);
  TEST("Print to string is '0'",strcmp(output,"0")==0);
  TEST("Print to string reports 1 char printed",nb==1);
  M(ji,set,872345234);
  TEST("Set to 872345234",M(ji,get)==872345234);
  nb=M(ji,print_to_string,output,1024);
  TEST("Print to string is '872345234'",strcmp(output,"872345234")==0);
  TEST("Print to string reports 9 chars printed",nb==9);
  M(ji,clear);
  TEST("Clear resets value to zero",M(ji,get)==0);
  delete(ji);
}

void test_real()
{
  TESTCASE("Real");
  json_real_pointer jr=new(json_real);
  TEST("Type is JSON_REAL",M(jr,type)==JSON_REAL);
  TEST("Default value is 0.0",M(jr,get)==0.0);
  int nb=M(jr,print_to_string,output,1024);
  TEST("print to sring is '0'",strcmp(output,"0")==0);
  M(jr,set,3.1415);
  TEST("Value is pi",M(jr,get)==3.1415);
  nb=M(jr,print_to_string,output,1024);
  TEST("Print to string is '3.1415'",strcmp(output,"3.1415")==0);
  TEST("Print to string reports 6 chars printed",nb==6);
  M(jr,clear);
  TEST("Clear resets to zero",M(jr,get)==0);

  delete(jr);
}

void test_string()
{
  TESTCASE("String");
  json_string_pointer js=new(json_string);
  TEST("Type is JSON_STRING",M(js,type)==JSON_STRING);
  TEST("Default value is NULL",M(js,get)==NULL);
  int nb=M(js,print_to_string,output,1024);
  TEST("Print to string is '\"\"'",strcmp(output,"\"\"")==0);
  TEST("Print to string reports 2 chars printed",nb==2);
  M(js,set,"Testing");
  TEST("Value set to 'Testing'",strcmp(M(js,get),"Testing")==0);
  nb=M(js,print_to_string,output,1024);
  TEST("Print to string is '\"Testing\"'",strcmp(output,"\"Testing\"")==0);
  TEST("Print to string reports 9 chars printed",nb==9);
  M(js,clear);
  TEST("Clear resets value to NULL",M(js,get)==NULL);

  delete(js);
}


void test_array()
{
  TESTCASE("Array");
  json_array_pointer ja=new(json_array);
  TEST("Type is JSON_ARRAY",M(ja,type)==JSON_ARRAY);
  TEST("Size is zero",M(ja,size)==0);
  int nb=M(ja,print_to_string,output,1024);
  TEST("Print to string is '[]'",strcmp(output,"[]")==0);
  TEST("Print to string reports 2 chars printed",nb==2);
  json_integer_pointer ji=new(json_integer);
  json_string_pointer js=new(json_string);
  M(ji,set,1234);
  M(js,set,"1234");
  M(ja,add,ji);
  M(ja,add,js);
  puts("Adding integer and string");
  TEST("Size is 2",M(ja,size)==2);
  nb=M(ja,print_to_string,output,1024);
  TEST("Print to string is '[1234,\"1234\"]'",strcmp(output,"[1234,\"1234\"]")==0);
  TEST("Print to string reports 13 chars printed",nb==13);
  json_array_pointer ja2=new(json_array);
  M(ja2,add,ji);
  M(ja2,add,js);
  M(ja,add,ja2);
  puts("Add array of integer and string");
  TEST("Size is 3",M(ja,size)==3);
  nb=M(ja,print_to_string,output,1024);
//  puts(output);
  TEST("Print to string is '[1234,\"1234\",[1234,\"1234\"]]'",strcmp(output,"[1234,\"1234\",[1234,\"1234\"]]")==0);
  TEST("Print to string reports 27 chars printed",nb==27);

  delete(ji);
  delete(js);
  delete(ja2);
  delete(ja);
}

typedef struct {
  const char* color;
  const char* value;
} color_value_t;

color_value_t color_values[] =
{
	{ "red", "#f00"	},
	{	"green","#0f0"},
	{	"blue","#00f"	},
	{	"cyan","#0ff"	},
	{	"magenta","#f0f"},
	{	"yellow","#ff0"},
	{	"black","#000"},
  { NULL, NULL }
};

void test_object()
{
  TESTCASE("Object");
  json_object_pointer jo=new(json_object);
  TEST("Type is JSON_OBJECT",M(jo,type)==JSON_OBJECT);
  TEST("Size is zero",M(jo,size)==0);
  int nb=M(jo,print_to_string,output,1024);
  TEST("Print to string is '{}'",strcmp(output,"{}")==0);
  TEST("Print to string reports 2 chars printed",nb==2);
  json_string_pointer js=new_ctor(json_string,json_string_ctor_ccs,"pi");
  json_real_pointer jr=new_ctor(json_real,json_real_ctor_real,3.1415);
  M(jo,insert,js,jr);
  TEST("Size is 1",M(jo,size)==1);
  nb=M(jo,print_to_string,output,1024);
  TEST("Print to string is '{\"pi\":3.1415}'",strcmp(output,"{\"pi\":3.1415}")==0);
  TEST("Print to string reports 13 chars printed",nb==13);
  color_value_t* icolor;
  json_array_pointer ja=new(json_array);
  json_string_pointer color=new_ctor(json_string,json_string_ctor_ccs,"color");
  json_string_pointer value=new_ctor(json_string,json_string_ctor_ccs,"value");
  json_string_pointer color_value=new(json_string);
  json_string_pointer value_value=new(json_string);
  const char* result="[{\"color\":\"red\",\"value\":\"#f00\"},{\"color\":\"green\",\"value\":\"#0f0\"},"
      "{\"color\":\"blue\",\"value\":\"#00f\"},{\"color\":\"cyan\",\"value\":\"#0ff\"},"
      "{\"color\":\"magenta\",\"value\":\"#f0f\"},{\"color\":\"yellow\",\"value\":\"#ff0\"},"
      "{\"color\":\"black\",\"value\":\"#000\"}]";
  for(icolor=color_values;icolor->color!=NULL;icolor++) {
    M(color_value,set,icolor->color);
    M(value_value,set,icolor->value);
    json_object_pointer jo=new(json_object);
    M(jo,insert,color,color_value);
    M(jo,insert,value,value_value);
    M(jo,print_to_string,output,1024);
    M(ja,add,jo);
    delete(jo);
  }
  nb=M(ja,print_to_string,output,1024);
  TEST("print to string output same as result",strcmp(output,result)==0);
  TEST("print to string reports 231 charaters printed",nb==231);

  delete(color_value);
  delete(value_value);
  delete(color);
  delete(value);
  delete(ja);
  delete(jo);
  delete(js);
  delete(jr);
}

void test_swap()
{
  TESTCASE("SWAP");
  json_value_pointer jv1=new_ctor(json_string,json_string_ctor_ccs,"Testing");
  json_value_pointer jv2=new(json_array);
  json_integer_pointer ji=new_ctor(json_integer,json_integer_ctor_int,1234);
  M((json_array_pointer)jv2,add,ji);
  TEST("jv1 is string",M(jv1,type)==JSON_STRING);
  TEST("jv1 value is 'Testing'",strcmp(M((json_string_pointer)jv1,get),"Testing")==0);
  TEST("jv2 is array",M(jv2,type)==JSON_ARRAY);
  TEST("jv2 size is 1",M((json_array_pointer)jv2,size)==1);

  M(jv1,swap,jv2);
  puts("After swap");
  TEST("jv1 is array",M(jv1,type)==JSON_ARRAY);
  TEST("jv1 size is 1",M((json_array_pointer)jv1,size)==1);
  TEST("jv2 is string",M(jv2,type)==JSON_STRING);
  TEST("jv2 value is 'Testing'",strcmp(M((json_string_pointer)jv2,get),"Testing")==0);

  puts("Add another item to jv1");
  M((json_array_pointer)jv1,add,ji);
  delete(ji);
  delete(jv1);
  delete(jv2);
}
test_function tests[]=
{
	test_null,
  test_bool,
  test_integer,
  test_real,
  test_string,
  test_array,
  test_object,
  test_swap
};

STD_MAIN(tests)
