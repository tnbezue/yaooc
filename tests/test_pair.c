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
#include <yaooc/pair.h>
#include <yaooc/string.h>

#include "test_harness.h"

PAIR_DEFINITION(int,yaooc_string,int_string_pair);
PAIR_IMPLEMENTATION(int,yaooc_string,int_string_pair);

void test_ctor_dtor()
{
  int_string_pair_t p1;
  int value=12;
  yaooc_string_pointer str=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"Testing");
  make_int_string_pair(&p1,&value,str);

  int_string_pair_t* p2 = new(int_string_pair);
  assign_static(p2,&p1,int_string_pair);

  delete(str);
  delete(p2);
}

void test_copy_ctor()
{
  int_string_pair_t p1;
  int value=12;
  yaooc_string_pointer str=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"Testing");
  make_int_string_pair(&p1,&value,str);

  int_string_pair_t p2;
  newp_copy_static(&p2,int_string_pair,&p1);
  TEST("p1=p2",op_eq_static(&p1,&p2,int_string_pair));

  deletep(&p2,int_string_pair);
  delete(str);
}

void test_assign()
{
  int_string_pair_t p1;

  int value=12;
  yaooc_string_pointer str=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"Testing");
  make_int_string_pair(&p1,&value,str);

  int_string_pair_t p2;
  newp(&p2,int_string_pair);
  assign_static(&p2,&p1,int_string_pair);
  TEST("p1=p2",op_eq_static(&p1,&p2,int_string_pair));
  deletep(&p2,int_string_pair);
  delete(str);
}

void test_less_than()
{
  int_string_pair_t p1;
  int value=12;
  yaooc_string_pointer str=new(yaooc_string);
  make_int_string_pair(&p1,&value,str);
  M(&p1.second,set,"AAAAAA");

  int_string_pair_t p2;
  value=10;
  yaooc_string_pointer str2=new(yaooc_string);
  make_int_string_pair(&p2,&value,str2);
  M(&p2.second,set,"BBBBB");

  TEST("p1 == p2 (false)",!op_eq_static(&p1,&p2,int_string_pair));
  TEST("p1 != p2 (true)",op_ne_static(&p1,&p2,int_string_pair));
  TEST("p1 < p2 (false)",!op_lt_static(&p1,&p2,int_string_pair));
  TEST("p1 <= p2 (false)",!op_le_static(&p1,&p2,int_string_pair));
  TEST("p1 > p2 (true)",op_gt_static(&p1,&p2,int_string_pair));
  TEST("p1 >= p2 (true)",op_ge_static(&p1,&p2,int_string_pair));

  value=3;
  make_int_string_pair(&p1,&value,NULL);
  TEST("p1 == p2 (false)",!op_eq_static(&p1,&p2,int_string_pair));
  TEST("p1 != p2 (true)",op_ne_static(&p1,&p2,int_string_pair));
  TEST("p1 < p2 (true)",op_lt_static(&p1,&p2,int_string_pair));
  TEST("p1 <= p2 (true)",op_le_static(&p1,&p2,int_string_pair));
  TEST("p1 > p2 (false)",!op_gt_static(&p1,&p2,int_string_pair));
  TEST("p1 >= p2 (false)",!op_ge_static(&p1,&p2,int_string_pair));

  deletep(&p1,int_string_pair);
  value=10;
  make_int_string_pair(&p1,&value,NULL);
  TEST("p1 == p2 (true)",op_eq_static(&p1,&p2,int_string_pair));
  TEST("p1 != p2 (false)",!op_ne_static(&p1,&p2,int_string_pair));
  TEST("p1 < p2 (false)",!op_lt_static(&p1,&p2,int_string_pair));
  TEST("p1 <= p2 (true)",op_le_static(&p1,&p2,int_string_pair));
  TEST("p1 > p2 (false)",!op_gt_static(&p1,&p2,int_string_pair));
  TEST("p1 >= p2 (true)",op_ge_static(&p1,&p2,int_string_pair));

  delete(str);
  delete(str2);

}

test_function tests[] =
{
  test_ctor_dtor,
  test_copy_ctor,
  test_assign,
  test_less_than
};

STD_MAIN(tests)
