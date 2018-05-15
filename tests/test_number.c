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
#include <yaooc/integer.h>
#include <yaooc/real.h>
#include <time.h>
#include "test_harness.h"

void test_integer()
{
  TESTCASE("Ctor and set");
  yaooc_integer_pointer i1=new(yaooc_integer);
  TEST("Default value is 0",M(i1,get)==0);
  yaooc_integer_pointer i2=new_ctor(yaooc_integer,yaooc_integer_ctor_int,34);
  TEST("Ctor sets value to 34",M(i2,get)==34);
  M(i1,set,22);
  TEST("set method sets value to 22",M(i1,get)==22);
  
  TESTCASE("comparison i1=22, i2=34");
  TEST("i1 == i2 (false)",!op_eq(i1,i2));
  TEST("i1 != i2 (true)",op_ne(i1,i2));
  TEST("i1 <  i2 (true)",op_lt(i1,i2));
  TEST("i1 <= i2 (true)",op_le(i1,i2));
  TEST("i1 >  i2 (false)",!op_gt(i1,i2));
  TEST("i1 <= i2 (false)",!op_ge(i1,i2));
  
  TESTCASE("comparison i1=34, i2=34");
  M(i1,set,34);
  TEST("i1 == i2 (true)",op_eq(i1,i2));
  TEST("i1 != i2 (false)",!op_ne(i1,i2));
  TEST("i1 <  i2 (false)",!op_lt(i1,i2));
  TEST("i1 <= i2 (true)",op_le(i1,i2));
  TEST("i1 >  i2 (false)",!op_gt(i1,i2));
  TEST("i1 <= i2 (true)",op_ge(i1,i2));

  TESTCASE("comparison i1=34, i2=22");
  M(i2,set,22);
  TEST("i1 == i2 (false)",!op_eq(i1,i2));
  TEST("i1 != i2 (true)",op_ne(i1,i2));
  TEST("i1 <  i2 (false)",!op_lt(i1,i2));
  TEST("i1 <= i2 (false)",!op_le(i1,i2));
  TEST("i1 >  i2 (true)",op_gt(i1,i2));
  TEST("i1 <= i2 (true)",op_ge(i1,i2));
}

void test_real()
{
  TESTCASE("Ctor and set");
  yaooc_real_pointer r1=new(yaooc_real);
  TEST("Default value is zero",M(r1,get)==0.0);
  yaooc_real_pointer r2=new_ctor(yaooc_real,yaooc_real_ctor_real,34.0);
  TEST("Ctor sets value to 34",M(r2,get)==34.0);
  
  TESTCASE("comparison r1=22, r2=34");
  TEST("r1 == r2 (false)",!op_eq(r1,r2));
  TEST("r1 != r2 (true)",op_ne(r1,r2));
  TEST("r1 <  r2 (true)",op_lt(r1,r2));
  TEST("r1 <= r2 (true)",op_le(r1,r2));
  TEST("r1 >  r2 (false)",!op_gt(r1,r2));
  TEST("r1 <= r2 (false)",!op_ge(r1,r2));
  
  TESTCASE("comparison r1=34, r2=34");
  M(r1,set,34);
  TEST("r1 == r2 (true)",op_eq(r1,r2));
  TEST("r1 != r2 (false)",!op_ne(r1,r2));
  TEST("r1 <  r2 (false)",!op_lt(r1,r2));
  TEST("r1 <= r2 (true)",op_le(r1,r2));
  TEST("r1 >  r2 (false)",!op_gt(r1,r2));
  TEST("r1 <= r2 (true)",op_ge(r1,r2));

  TESTCASE("comparison r1=34, r2=22");
  M(r2,set,22);
  TEST("r1 == r2 (false)",!op_eq(r1,r2));
  TEST("r1 != r2 (true)",op_ne(r1,r2));
  TEST("r1 <  r2 (false)",!op_lt(r1,r2));
  TEST("r1 <= r2 (false)",!op_le(r1,r2));
  TEST("r1 >  r2 (true)",op_gt(r1,r2));
  TEST("r1 <= r2 (true)",op_ge(r1,r2));
}

test_function tests[]=
{
	test_integer,
  test_real
};

STD_MAIN(tests)
