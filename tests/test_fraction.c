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
#include <yaooc/fraction.h>
#include <yaooc/sstream.h>
#include <math.h>
#include "test_harness.h"


void test_basic()
{
  TESTCASE("Constructor")
  TEST("Fraction struct size",sizeof(yaooc_fraction_t)==(sizeof(long)+sizeof(long)));
  yaooc_fraction_t* f= new(yaooc_fraction);
  TEST("Fraction object created",f!=NULL);
  delete(f);
}

void test_to_double()
{
  yaooc_fraction_t f;
  TESTCASE("To double")

  f.numerator_=0;
  f.denominator_=1;
  TEST("Fraction 0/1 as double == 0",fabs(yaooc_fraction_to_double(&f) - 0.0) < yaooc_fraction_epsilon);

  f.numerator_=1;
  TEST("Fraction 1/1 as double == 1",fabs(yaooc_fraction_to_double(&f) - 1.0) < yaooc_fraction_epsilon);

  f.denominator_=2;
  TEST("Fraction 1/2 as double == 0.5",fabs(yaooc_fraction_to_double(&f) - 0.5) < yaooc_fraction_epsilon);

  f.denominator_=3;
  TEST("Fraction 1/3 as double == 0.33333333",fabs(yaooc_fraction_to_double(&f) - 1.0/3.0) < yaooc_fraction_epsilon);

  f.numerator_=3;
  f.denominator_=5;
  TEST("Fraction 3/5 as double == 0.6",fabs(yaooc_fraction_to_double(&f) - 3.0/5.0) < yaooc_fraction_epsilon);

  f.numerator_=20;
  f.denominator_=3;
  TEST("Fraction 20/3 as double == 6.66666667",fabs(yaooc_fraction_to_double(&f) - 20.0/3.0) < yaooc_fraction_epsilon);

  f.numerator_=-20;
  f.denominator_=3;
  TEST("Fraction -20/3 as double == -6.66666667",fabs(yaooc_fraction_to_double(&f) - (-20.0/3.0)) < yaooc_fraction_epsilon);
}

void test_from_double()
{
  yaooc_fraction_t f;
  TESTCASE("From double")

  yaooc_fraction_from_double(&f,0.0);
  TEST("Fraction from 0.0 is 0/1",f.numerator_==0 && f.denominator_==1);

  yaooc_fraction_from_double(&f,1.0);
  TEST("Fraction from 0.0 is 1/1",f.numerator_==1 && f.denominator_==1);

  yaooc_fraction_from_double(&f,10.0);
  TEST("Fraction from 0.0 is 10/1",f.numerator_==10 && f.denominator_==1);

  yaooc_fraction_from_double(&f,0.3333333333);
  TEST("Fraction from 0.33333333 is 1/3",f.numerator_==1 && f.denominator_==3);

  yaooc_fraction_from_double(&f,-1.0625);
  TEST("Fraction from -1.0625 is -17/16",f.numerator_==-17 && f.denominator_==16);
}

void test_to_stream()
{
  yaooc_fraction_t f;
  yaooc_ostringstream_t* os=new(yaooc_ostringstream);
  TESTCASE("To stream")

  f.numerator_=0;
  f.denominator_=1;
  STREAM(os,O_OBJ(yaooc_fraction,f));
  TEST("Fraction 0/1 to stream is \"0\"",strcmp(M(os,c_str),"0")==0);
  M(os,seek,0,SEEK_SET);

  f.numerator_=1;
  f.denominator_=1;
  STREAM(os,O_OBJ(yaooc_fraction,f));
  TEST("Fraction 1/1 to stream is \"1\"",strcmp(M(os,c_str),"1")==0);
  M(os,seek,0,SEEK_SET);

  f.numerator_=1;
  f.denominator_=3;
  STREAM(os,O_OBJ(yaooc_fraction,f));
  TEST("Fraction 1/3 to stream is \"1/3\"",strcmp(M(os,c_str),"1/3")==0);
  M(os,seek,0,SEEK_SET);

  delete(os);
}

void test_from_stream()
{
  yaooc_istringstream_t* is=new_ctor(yaooc_istringstream,yaooc_istringstream_ctor_ccs,"0 1 10/3 -3/4 -8 5/10 8/ 3");
  yaooc_fraction_t f;
  TESTCASE("From Stream")

  STREAM(is,I_OBJ(yaooc_fraction,f));
  TEST("Fraction 0 from stream",f.numerator_==0 && f.denominator_==1);

  STREAM(is,I_OBJ(yaooc_fraction,f));
  TEST("Fraction 1 from stream",f.numerator_==1 && f.denominator_==1);

  STREAM(is,I_OBJ(yaooc_fraction,f));
  TEST("Fraction 10/3 from stream",f.numerator_==10 && f.denominator_==3);

  STREAM(is,I_OBJ(yaooc_fraction,f));
  TEST("Fraction -3/4 from stream",f.numerator_==-3 && f.denominator_==4);

  STREAM(is,I_OBJ(yaooc_fraction,f));
  TEST("Fraction -8 from stream",f.numerator_==-8 && f.denominator_==1);

  STREAM(is,I_OBJ(yaooc_fraction,f));
  TEST("Fraction 5/10 from stream reduced to 1/2",f.numerator_==1 && f.denominator_==2);

  TRY {
    STREAM(is,I_OBJ(yaooc_fraction,f));
  } CATCH(yaooc_fraction_exception,e) {
    (void)e; // to avoid warning of unused variable
    TEST("Fraction 8/ 3 from stream throws exception",true);
  }
  ETRY
  delete(is);
}

test_function tests[]=
{
	test_basic,
  test_to_double,
  test_from_double,
  test_to_stream,
  test_from_stream,
};

STD_MAIN(tests)
