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
#include <yaooc/json_parser.h>
#include <yaooc/sstream.h>
#include "test_harness.h"

void test_simple()
{
  TESTCASE("Simple");
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  yaooc_json_parser_pointer jparser=new(yaooc_json_parser);
  yaooc_json_value_pointer jv=M(jparser,parse_file,"simple.jsn");
  TEST("Parsing successful",jv!=NULL);
  TEST("Json object returned",M(jv,type)==JSON_OBJECT);
  M(jv,print,os);
  TEST("Object is '{\"id\":12}'",strcmp(M(os,c_str),"{\"id\":12}")==0);

  delete(jv);
  delete(jparser);
  delete(os);
}

void test_color()
{
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  TESTCASE("Color");
  const char* result_str="[{\"color\":\"red\",\"value\":\"#f00\"},{\"color\":\"green\",\"value\":\"#0f0\"},{\"color\":\"blue\",\"value\":\"#00f\"},{\"color\":\"cyan\",\"value\":\"#0ff\"},{\"color\":\"magenta\",\"value\":\"#f0f\"},{\"color\":\"yellow\",\"value\":\"#ff0\"},{\"color\":\"black\",\"value\":\"#000\"}]";
  yaooc_json_parser_pointer jparser=new(yaooc_json_parser);
  yaooc_json_value_pointer jv=M(jparser,parse_file,"color.jsn");
  TEST("Parsing successful",jv!=NULL);
  TEST("Json array returned",M(jv,type)==JSON_ARRAY);
  M(jv,print,os);
  TEST("Object matches result string",strcmp(M(os,c_str),result_str)==0);
  delete(jv);
  delete(jparser);
  delete(os);
}

void test_donuts()
{
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  const char* result_str="{\"id\":\"0001\",\"type\":\"donut\",\"name\":\"Cake\",\"ppu\":0.55,\"batters\":"
    "{\"batter\":[{\"id\":\"1001\",\"type\":\"Regular\"},{\"id\":\"1002\",\"type\":\"Chocolate\"},{\"id\":"
    "\"1003\",\"type\":\"Blueberry\"},{\"id\":\"1004\",\"type\":\"Devil's Food\"}]},\"topping\":"
    "[{\"id\":\"5001\",\"type\":\"None\"},{\"id\":\"5002\",\"type\":\"Glazed\"},{\"id\":\"5005\","
    "\"type\":\"Sugar\"},{\"id\":\"5007\",\"type\":\"Powdered Sugar\"},{\"id\":\"5006\",\"type\":"
    "\"Chocolate with Sprinkles\"},{\"id\":\"5003\",\"type\":\"Chocolate\"},{\"id\":\"5004\",\"type\":"
    "\"Maple\"}]}";
  TESTCASE("Donuts");
  yaooc_json_parser_pointer jparser=new(yaooc_json_parser);
  yaooc_json_value_t* jv=NULL;
  jv=M(jparser,parse_file,"donuts.jsn");

  TEST("Parsing successful",jv!=NULL);
  if(jv) {
    TEST("Json object returned",M(jv,type)==JSON_OBJECT);
    M(jv,print,os);
    TEST("Object matches result string",strcmp(M(os,c_str),result_str)==0);
  }
  delete(jv);
  delete(jparser);
  delete(os);
}

void test_properties()
{
  yaooc_ostringstream_pointer os=new(yaooc_ostringstream);
  const char* result_str="{\"$schema\":\"http://json-schema.org/draft-04/schema#\",\"type\":"
        "\"object\",\"properties\":{\"/\":{}},\"patternProperties\":{\"^(/[^/]+)+$\":{}},"
        "\"additionalProperties\":false,\"required\":[\"/\"]}";
  TESTCASE("Properties");
  yaooc_json_parser_pointer jparser=new(yaooc_json_parser);
  yaooc_json_value_pointer jv=M(jparser,parse_file,"properties.jsn");
  TEST("Parsing successful",jv!=NULL);
  TEST("Json object returned",M(jv,type)==JSON_OBJECT);
  M(jv,print,os);
  TEST("Object matches result string",strcmp(M(os,c_str),result_str)==0);
  delete(jv);
  delete(jparser);
  delete(os);
}

test_function tests[]=
{
  test_simple,
  test_color,
  test_donuts,
  test_properties
};

STD_MAIN(tests)
