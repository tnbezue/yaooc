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
#include <yaooc/json.h>
#include <yaooc/sstream.h>
#include "test_harness.h"

void test_sizes()
{
  TESTCASE("Sizes");
  TEST("Size of yaooc_json_null_t is same as yaooc_json_value_t",sizeof(yaooc_json_null_t)==sizeof(yaooc_json_value_t));
  TEST("Size of yaooc_json_bool_t is same as yaooc_json_value_t",sizeof(yaooc_json_bool_t)==sizeof(yaooc_json_value_t));
  TEST("Size of yaooc_json_integer_t is same as yaooc_json_value_t",sizeof(yaooc_json_integer_t)==sizeof(yaooc_json_value_t));
  TEST("Size of yaooc_json_real_t is same as yaooc_json_value_t",sizeof(yaooc_json_real_t)==sizeof(yaooc_json_value_t));
  TEST("Size of yaooc_json_string_t is same as yaooc_json_value_t",sizeof(yaooc_json_string_t)==sizeof(yaooc_json_value_t));
  TEST("Size of yaooc_json_array_t is same as yaooc_json_value_t",sizeof(yaooc_json_array_t)==sizeof(yaooc_json_value_t));
  TEST("Size of yaooc_json_object_t is same as yaooc_json_value_t",sizeof(yaooc_json_object_t)==sizeof(yaooc_json_value_t));
}

void test_null()
{
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  TESTCASE("NULL");
  yaooc_json_null_pointer jn=new(yaooc_json_null);
  TEST("Type is JSON_NULL",M(jn,type)==JSON_NULL);
  M(jn,print,os);
  TEST("NULL print to string is 'null'",strcmp(M(os,c_str),"null")==0);
  delete(jn);
  delete(os);
}

void test_bool()
{
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  TESTCASE("Bool");
  yaooc_json_bool_pointer jb=new(yaooc_json_bool);
  TEST("Type is JSON_BOOL",M(jb,type)==JSON_BOOL);
  TEST("Default value is false",M(jb,get)==false);
  M(jb,set,true);
  TEST("Set value is true",M(jb,get)==true);
  M(os,clear);
  M(jb,print,os);
  TEST("Print to string is 'true'",strcmp(M(os,c_str),"true")==0);
  M(jb,set,false);
  TEST("Set value to false",M(jb,get)==false);
  M(os,clear);
  M(jb,print,os);
  TEST("Print to string is 'false'",strcmp(M(os,c_str),"false")==0);
  M(jb,set,true);
//  M(jb,clear);
//  TEST("Clear sets value to false",M(jb,get)==false);
  delete(jb);
  delete(os);
}

void test_integer()
{
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  TESTCASE("Integer");
  yaooc_json_integer_pointer ji=new(yaooc_json_integer);
  TEST("Type is JSON_INTEGER",M(ji,type)==JSON_INTEGER);
  TEST("Default value is zero",M(ji,get)==0);
  M(ji,print,os);
  TEST("Print to string is '0'",strcmp(M(os,c_str),"0")==0);
  M(ji,set,872345234);
  TEST("Set to 872345234",M(ji,get)==872345234);
  M(os,clear);
  M(ji,print,os);
  TEST("Print to string is '872345234'",strcmp(M(os,c_str),"872345234")==0);
//  M(ji,clear);
//  TEST("Clear resets value to zero",M(ji,get)==0);
  delete(ji);
  delete(os);
}

void test_real()
{
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  TESTCASE("Real");
  yaooc_json_real_pointer jr=new(yaooc_json_real);
  TEST("Type is JSON_REAL",M(jr,type)==JSON_REAL);
  TEST("Default value is 0.0",M(jr,get)==0.0);
  M(jr,print,os);
  TEST("print to sring is '0'",strcmp(M(os,c_str),"0")==0);
  M(jr,set,3.1415);
  TEST("Value is pi",M(jr,get)==3.1415);
  M(os,clear);
  M(jr,print,os);
  TEST("Print to string is '3.1415'",strcmp(M(os,c_str),"3.1415")==0);
//  M(jr,clear);
//  TEST("Clear resets to zero",M(jr,get)==0);

  delete(jr);
  delete(os);
}

void test_string()
{
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  TESTCASE("String");
  yaooc_json_string_pointer js=new(yaooc_json_string);
  TEST("Type is JSON_STRING",M(js,type)==JSON_STRING);
  TEST("Default value is \"\"",strcmp(M(js,get),"")==0);
  M(js,print,os);
  TEST("Print to string is '\"\"'",strcmp(M(os,c_str),"\"\"")==0);
  printf("X%sX\n",M(os,c_str));
  M(js,set,"Testing");
  TEST("Value set to 'Testing'",strcmp(M(js,get),"Testing")==0);
  M(os,clear);
  M(js,print,os);
  TEST("Print to string is '\"Testing\"'",strcmp(M(os,c_str),"\"Testing\"")==0);
  M(js,clear);
  TEST("Clear resets value to \"\"",strcmp(M(js,get),"")==0);

  delete(js);
  delete(os);
}


void test_array()
{
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  TESTCASE("Array");
  yaooc_json_array_pointer ja=new(yaooc_json_array);
  TEST("Type is JSON_ARRAY",M(ja,type)==JSON_ARRAY);
  TEST("Size is zero",M(ja,size)==0);
  M(ja,print,os);
  TEST("Print to string is '[]'",strcmp(M(os,c_str),"[]")==0);
  yaooc_json_integer_pointer ji=new(yaooc_json_integer);
  yaooc_json_string_pointer js=new(yaooc_json_string);
  M(ji,set,1234);
  M(js,set,"1234");
  M(ja,insert,ji);
  M(ja,insert,js);
  puts("Adding integer and string");
  TEST("Size is 2",M(ja,size)==2);
  M(os,clear);
  M(ja,print,os);
  TEST("Print to string is '[1234,\"1234\"]'",strcmp(M(os,c_str),"[1234,\"1234\"]")==0);
  yaooc_json_array_pointer ja2=new(yaooc_json_array);
  M(ja2,insert,ji);
  M(ja2,insert,js);
  M(ja,insert,ja2);
  puts("Add array of integer and string");
  TEST("Size is 3",M(ja,size)==3);
  M(os,clear);
  M(ja,print,os);
//  puts(M(os,c_str));
  TEST("Print to string is '[1234,\"1234\",[1234,\"1234\"]]'",strcmp(M(os,c_str),"[1234,\"1234\",[1234,\"1234\"]]")==0);

  delete(ji);
  delete(js);
  delete(ja2);
  delete(ja);
  delete(os);
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
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  TESTCASE("Object");
  yaooc_json_object_pointer jo=new(yaooc_json_object);
  TEST("Type is JSON_OBJECT",M(jo,type)==JSON_OBJECT);
  TEST("Size is zero",M(jo,size)==0);
  M(jo,print,os);
  TEST("Print to string is '{}'",strcmp(M(os,c_str),"{}")==0);
  yaooc_json_string_pointer js=new_ctor(yaooc_json_string,yaooc_json_string_ctor_ccs,"pi");
  yaooc_json_real_pointer jr=new_ctor(yaooc_json_real,yaooc_json_real_ctor_real,3.1415);
  M(jo,insert,js,jr);
  TEST("Size is 1",M(jo,size)==1);
  M(os,clear);
  M(jo,print,os);
  printf("X%sX\n",M(os,c_str));
  TEST("Print to string is '{\"pi\":3.1415}'",strcmp(M(os,c_str),"{\"pi\":3.1415}")==0);
  color_value_t* icolor;
  yaooc_json_array_pointer ja=new(yaooc_json_array);
  yaooc_json_string_pointer color=new_ctor(yaooc_json_string,yaooc_json_string_ctor_ccs,"color");
  yaooc_json_string_pointer value=new_ctor(yaooc_json_string,yaooc_json_string_ctor_ccs,"value");
  yaooc_json_string_pointer color_value=new(yaooc_json_string);
  yaooc_json_string_pointer value_value=new(yaooc_json_string);
  const char* result="[{\"color\":\"red\",\"value\":\"#f00\"},{\"color\":\"green\",\"value\":\"#0f0\"},"
      "{\"color\":\"blue\",\"value\":\"#00f\"},{\"color\":\"cyan\",\"value\":\"#0ff\"},"
      "{\"color\":\"magenta\",\"value\":\"#f0f\"},{\"color\":\"yellow\",\"value\":\"#ff0\"},"
      "{\"color\":\"black\",\"value\":\"#000\"}]";
  for(icolor=color_values;icolor->color!=NULL;icolor++) {
    M(color_value,set,icolor->color);
    M(value_value,set,icolor->value);
    yaooc_json_object_pointer jo=new(yaooc_json_object);
    M(jo,insert,color,color_value);
    M(jo,insert,value,value_value);
    M(jo,print,os);
    M(ja,insert,jo);
    delete(jo);
  }
  M(os,clear);
  M(ja,print,os);
  TEST("print to string output same as result",strcmp(M(os,c_str),result)==0);

  delete(color_value);
  delete(value_value);
  delete(color);
  delete(value);
  delete(ja);
  delete(jo);
  delete(js);
  delete(jr);
  delete(os);
}

void test_assign()
{
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  yaooc_json_string_pointer js = new_ctor(yaooc_json_string,yaooc_json_string_ctor_ccs,"Testing");
  yaooc_json_value_pointer jv = new(yaooc_json_value);
  assign(jv,js);
  TEST("jv is a string",M(jv,type)==JSON_STRING);
  TEST("jv value is 'Testing'",strcmp(M((yaooc_json_string_pointer)jv,get),"Testing")==0);

  yaooc_json_integer_pointer ji=new(yaooc_json_integer);
  TRY {
    assign(jv,ji);
  } CATCH(yaooc_json_exception,e) {
    printf("%s\n",M(e,what));
  }
  ETRY
  delete(ji);
  delete(js);
  delete(jv);
  delete(os);
  YAOOC_THREAD_CLEANUP
}

#if 0
void test_swap()
{
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  TESTCASE("SWAP");
  yaooc_json_value_pointer jv1=new_ctor(yaooc_json_string,yaooc_json_string_ctor_ccs,"Testing");
  yaooc_json_value_pointer jv2=new(yaooc_json_array);
  yaooc_json_integer_pointer ji=new_ctor(yaooc_json_integer,yaooc_json_integer_ctor_int,1234);
  M((yaooc_json_array_pointer)jv2,insert,ji);
  TEST("jv1 is string",M(jv1,type)==JSON_STRING);
  TEST("jv1 value is 'Testing'",strcmp(M((yaooc_json_string_pointer)jv1,get),"Testing")==0);
  TEST("jv2 is array",M(jv2,type)==JSON_ARRAY);
  TEST("jv2 size is 1",M((yaooc_json_array_pointer)jv2,size)==1);

  M(jv1,swap,jv2);
  puts("After swap");
  TEST("jv1 is array",M(jv1,type)==JSON_ARRAY);
  TEST("jv1 size is 1",M((yaooc_json_array_pointer)jv1,size)==1);
  TEST("jv2 is string",M(jv2,type)==JSON_STRING);
  TEST("jv2 value is 'Testing'",strcmp(M((yaooc_json_string_pointer)jv2,get),"Testing")==0);

  puts("Add another item to jv1");
  M((yaooc_json_array_pointer)jv1,insert,ji);
  delete(ji);
  delete(jv1);
  delete(jv2);
  delete(os);
}
#endif
test_function tests[]=
{
  test_sizes,
	test_null,
  test_bool,
  test_integer,
  test_real,
  test_string,
  test_array,
  test_object,
  test_assign,
  //test_swap
};

STD_MAIN(tests)
