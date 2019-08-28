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
#include <unistd.h>
#include <yaooc/complex.h>
#include <yaooc/sstream.h>
#include <math.h>
#include "test_harness.h"


void test_constructor()
{
  TESTCASE("Constructors")
  yaooc_complex_t c; //= { NULL, 9999, 9999 };
  newp_ctor(&c,yaooc_complex,yaooc_complex_ctor_r_i,0.0,0.0);
  TEST("ctor_r_i",c.real_==0.0 && c.imag_==0.0);
}

void test_mul_double()
{
  TESTCASE("complex * double")
  yaooc_complex_t c;
  newp_ctor(&c,yaooc_complex,yaooc_complex_ctor_r_i,8.0,-3.0);
  yaooc_complex_t* d= M(&c,times_real,2.0);
  TEST("c*d",d->real_==16.0 && d->imag_ == -6.0);
  delete(d);
}

void test_div_double()
{
  TESTCASE("complex * double")
  yaooc_complex_t c;
  newp_ctor(&c,yaooc_complex,yaooc_complex_ctor_r_i,8.0,-3.0);
  yaooc_complex_t* d= M(&c,divided_by_real,2.0);
  TEST("c/d",d->real_==4.0 && d->imag_ == -1.5);
  delete(d);
}

void test_add_complex()
{
  TESTCASE("complex + comples")
  yaooc_complex_t c1;
  newp_ctor(&c1,yaooc_complex,yaooc_complex_ctor_r_i,2.0,3.0);
  yaooc_complex_t c2;
  newp_ctor(&c2,yaooc_complex,yaooc_complex_ctor_r_i,4.0,5.0);
  yaooc_complex_t* c3 = M(&c1,plus_complex,&c2);
  TEST("c1+c2",c3->real_==6.0 && c3->imag_ == 8.0);
  delete(c3);
}

void test_minus_complex()
{
  TESTCASE("complex + comples")
  yaooc_complex_t c1;
  newp_ctor(&c1,yaooc_complex,yaooc_complex_ctor_r_i,2.0,3.0);
  yaooc_complex_t c2;
  newp_ctor(&c2,yaooc_complex,yaooc_complex_ctor_r_i,4.0,5.0);
  yaooc_complex_t* c3 = M(&c1,minus_complex,&c2);
  TEST("c1-c2",c3->real_==-2.0 && c3->imag_ == -2.0);
  delete(c3);
}

void test_times_complex()
{
  TESTCASE("complex * comples")
  yaooc_complex_t c1;
  newp_ctor(&c1,yaooc_complex,yaooc_complex_ctor_r_i,2.0,3.0);
  yaooc_complex_t c2;
  newp_ctor(&c2,yaooc_complex,yaooc_complex_ctor_r_i,4.0,5.0);
  yaooc_complex_t* c3 = M(&c1,times_complex,&c2);
  TEST("c1*c2",c3->real_==-7.0 && c3->imag_ == 22.0);
  delete(c3);
}

void test_divided_by_complex()
{
  TESTCASE("complex / comples")
  yaooc_complex_t c1;
  newp_ctor(&c1,yaooc_complex,yaooc_complex_ctor_r_i,2.0,3.0);
  yaooc_complex_t c2;
  newp_ctor(&c2,yaooc_complex,yaooc_complex_ctor_r_i,4.0,5.0);
  yaooc_complex_t* c3 = M(&c1,divided_by_complex,&c2);
  TEST("c1+c2",fabs(c3->real_-0.56097560976)<0.000001 && fabs(c3->imag_-0.0487804878)<0.000001);
  delete(c3);
}

void test_to_stream()
{
  yaooc_complex_t c;
  yaooc_ostringstream_t* os=new(yaooc_ostringstream);
  TESTCASE("To stream")

  newp_ctor(&c,yaooc_complex,yaooc_complex_ctor_r_i,0.0,0.0);
  STREAM(os,O_OBJ(yaooc_complex,c));
  TEST("(0 + 0i) to stream",strcmp(M(os,c_str),"(0 + 0i)")==0);
  M(os,seek,0,SEEK_SET);

  c.real_=-12.5;
  c.imag_=-0.8;
  STREAM(os,O_OBJ(yaooc_complex,c));
  TEST("(-12.5 - 0.8i) to stream",strcmp(M(os,c_str),"(-12.5 - 0.8i)")==0);
  M(os,seek,0,SEEK_SET);

  delete(os);
}

void test_from_stream()
{
  yaooc_istringstream_t* is=new_ctor(yaooc_istringstream,yaooc_istringstream_ctor_ccs,"    (0 + 0i   )  (     -12.5 - 0.8i  ) (   19 + )");
  yaooc_complex_t c;
  TESTCASE("From Stream")

  STREAM(is,I_OBJ(yaooc_complex,c));
  TEST("read (0 + 0i) from stream",c.real_==0.0 && c.imag_==0.0);

  STREAM(is,I_OBJ(yaooc_complex,c));
  TEST("read (-12.5 - 0.8i) from stream",c.real_==-12.5 && c.imag_==-0.8);
  printf("%lg %lg\n",c.real_,c.imag_);
  TRY {
    STREAM(is,I_OBJ(yaooc_complex,c));
    TEST("read (19 + ) from stream did not throw exception",false);
  } CATCH(yaooc_complex_exception,e) {
    (void)e;  // avoid not used warning
    TEST("read (19 + ) from stream fails",true);
  }
  ETRY
  delete(is);
}

test_function tests[]=
{
	test_constructor,
  test_mul_double,
  test_div_double,
  test_add_complex,
  test_minus_complex,
  test_times_complex,
  test_divided_by_complex,
  test_to_stream,
  test_from_stream
};

STD_MAIN(tests)
