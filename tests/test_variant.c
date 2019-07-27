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
#include <yaooc/variant.h>
#include <yaooc/string.h>
#include "test_harness.h"


void test_constructor()
{
	TESTCASE("Variant Constructor");
	yaooc_variant_t* var=new(yaooc_variant);
	TEST("Type is VAR_NONE",M(var,type)==VAR_NONE);
	delete(var);
}

void test_char()
{
	TESTCASE("Variant char");
	yaooc_variant_t* var=new(yaooc_variant);
	char ch='a';
	M(var,set,VAR_CHAR,&ch);
	TEST("Type is VAR_CHAR",M(var,type)==VAR_CHAR);
	TEST("Value is 'a'",*(const char*)M(var,value)=='a');
	unsigned char uch='z';
	M(var,set,VAR_UCHAR,&uch);
	TEST("Type is VAR_UCHAR",M(var,type)==VAR_UCHAR);
	TEST("Value is 'z'",*(const unsigned char*)M(var,value)=='z');
	delete(var);
}

void test_short()
{
	TESTCASE("Variant short");
	yaooc_variant_t* var=new(yaooc_variant);
	short sh=3773;
	M(var,set,VAR_SHORT,&sh);
	TEST("Type is VAR_SHORT",M(var,type)==VAR_SHORT);
	TEST("Value is 3773",*(const short*)M(var,value)==3773);
	unsigned short ush=7337;
	M(var,set,VAR_USHORT,&ush);
	TEST("Type is VAR_USHORT",M(var,type)==VAR_USHORT);
	TEST("Value is 7337",*(const unsigned short*)M(var,value)==7337);
	delete(var);
}

void test_int()
{
	TESTCASE("Variant int");
	yaooc_variant_t* var=new(yaooc_variant);
	int i=16777216;
	M(var,set,VAR_INT,&i);
	TEST("Type is VAR_INT",M(var,type)==VAR_INT);
	TEST("Value is 16777216",*(const int*)M(var,value)==16777216);
	unsigned int ui=4294967295;
	M(var,set,VAR_UINT,&ui);
	TEST("Type is VAR_UINT",M(var,type)==VAR_UINT);
	TEST("Value is 4294967295",*(const unsigned int*)M(var,value)==4294967295);
	delete(var);
}

void test_long()
{
	TESTCASE("Variant long");
	yaooc_variant_t* var=new(yaooc_variant);
	long long l=274877906944;
	M(var,set,VAR_LONG,&l);
	TEST("Type is VAR_LONG",M(var,type)==VAR_LONG);
	TEST("Value is 274877906944",*(const long*)M(var,value)==274877906944);
	unsigned long long ul=4294967295;
	M(var,set,VAR_ULONG,&ul);
	TEST("Type is VAR_ULONG",M(var,type)==VAR_ULONG);
	TEST("Value is 4294967295",*(const unsigned long long*)M(var,value)==4294967295);
	delete(var);
}

void test_double()
{
	TESTCASE("Variant double");
	yaooc_variant_t* var=new(yaooc_variant);
	double d=3.1415927;
	M(var,set,VAR_DOUBLE,&d);
	TEST("Type is VAR_DOUBLE",M(var,type)==VAR_DOUBLE);
	TEST("Value is 3.1415927",*(const double*)M(var,value)==3.1415927);
	delete(var);
}

void test_ccs()
{
	TESTCASE("Variant ccs");
	yaooc_variant_t* var=new(yaooc_variant);
	const char* s="this is a test";
	M(var,set,VAR_CHAR_PTR,s);
	TEST("Type is VAR_CHAR_PTR",M(var,type)==VAR_CHAR_PTR);
	TEST("Value is \"this is a test\"",strcmp(s,M(var,value))==0);
	delete(var);
}

void test_object()
{
	TESTCASE("Variant ccs");
	yaooc_variant_t* var=new(yaooc_variant);
	yaooc_string_t* s=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"this is a test");
	M(var,set,VAR_OBJECT_PTR,s);
	TEST("Type is VAR_OBJECT_PTR",M(var,type)==VAR_OBJECT_PTR);
	TEST("Value is \"this is a test\"",strcmp(M(s,c_str),M((yaooc_string_t*)M(var,value),c_str))==0);
	delete(s);
	delete(var);
}

test_function tests[]=
{
	test_constructor,
	test_char,
	test_short,
	test_int,
	test_long,
	test_double,
	test_ccs,
	test_object,
};

STD_MAIN(tests)
