#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/json_parser.h>
#include "test_harness.h"

void test_simple()
{
  TESTCASE("Simple");
  json_parser_pointer jparser=new(json_parser);
  json_value_pointer jv=M(jparser,parse_file,"simple.jsn");
  TEST("Parsing successful",jv!=NULL);
  TEST("Json object returned",M(jv,type)==JSON_OBJECT);
  M(jv,print_to_string,output,1024);
  TEST("Object is '{\"id\":12}'",strcmp(output,"{\"id\":12}")==0);

  delete(jv);
  delete(jparser);
}

void test_color()
{
  TESTCASE("Color");
  json_parser_pointer jparser=new(json_parser);
  json_value_pointer jv=M(jparser,parse_file,"color.jsn");
  TEST("Parsing successful",jv!=NULL);
  TEST("Json array returned",M(jv,type)==JSON_ARRAY);
  M(jv,print_to_string,output,1024);
  TEST("Object is '{\"id\":12}'",strcmp(output,"{\"id\":12}")==0);
  puts(output);
  delete(jv);
  delete(jparser);
}

void test_donuts()
{
  TESTCASE("Donuts");
  json_parser_pointer jparser=new(json_parser);
  json_value_pointer jv=M(jparser,parse_file,"donuts.jsn");
  TEST("Parsing successful",jv!=NULL);
  TEST("Json array returned",M(jv,type)==JSON_ARRAY);
  M(jv,print_to_string,output,1024);
  TEST("Object is '{\"id\":12}'",strcmp(output,"{\"id\":12}")==0);
  puts(output);
  delete(jv);
  delete(jparser);
}

void test_properties()
{
  TESTCASE("Properties");
  json_parser_pointer jparser=new(json_parser);
  json_value_pointer jv=M(jparser,parse_file,"properties.jsn");
  TEST("Parsing successful",jv!=NULL);
  TEST("Json array returned",M(jv,type)==JSON_ARRAY);
  M(jv,print_to_string,output,1024);
  TEST("Object is '{\"id\":12}'",strcmp(output,"{\"id\":12}")==0);
  puts(output);
  delete(jv);
  delete(jparser);
}

test_function tests[]=
{
  test_simple,
  test_color,
  test_donuts,
  test_properties
};

STD_MAIN(tests)
