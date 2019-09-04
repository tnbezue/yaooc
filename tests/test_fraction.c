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
#include <yaooc/pointer_bag.h>
#include <math.h>
#include "test_harness.h"

void test_init()
{
}

void test_gcd()
{
  TESTCASE("Greatest Common Divisor");

  TEST("GCD(0,2) = 1",yaooc_fraction_gcd(0,2)==2);
  TEST("GCD(10,1) = 1",yaooc_fraction_gcd(10,1)==1);
  TEST("GCD(105,15) = 1",yaooc_fraction_gcd(105,15)==15);
  TEST("GCD(10,230) = 1",yaooc_fraction_gcd(10,230)==10);
  TEST("GCD(28,234) = 1",yaooc_fraction_gcd(28,234)==2);
  TEST("GCD(872452914,78241452) = 1",yaooc_fraction_gcd(872452914,78241452)==6);
}

#define S(f,n,d) yaooc_fraction_set(&f,n,d)
#define SM(f,w,n,d) yaooc_fraction_set_mixed(&f,w,n,d)
#define R(f,n,d) (f.numerator_==n && f.denominator_==d)

void test_default_constructor()
{
  pb_init();
  TESTCASE("Constructor")
  TEST("Fraction struct size",sizeof(yaooc_fraction_t)==(sizeof(void*)+sizeof(int32_t)+sizeof(int32_t)));
  yaooc_fraction_t* f= pb_new(yaooc_fraction);
  TEST("Fraction object created",f!=NULL);
  TEST("Default value 0/1",R((*f),0,1));
  pb_exit();
}

void test_fraction_set()
{
  TESTCASE("Fraction set");
  yaooc_fraction_t f;

  S(f,0,1);
  TEST("Set 0/1 = 0/1",R(f,0,1));

  S(f,1,1);
  TEST("Set 1/1 = 1/1",R(f,1,1));

  S(f,-2,3);
  TEST("Set -2/3 = -2/3",R(f,-2,3));

  S(f,2,-3);
  TEST("Set 2/-3 = -2/3",R(f,-2,3));

  S(f,-2,-3);
  TEST("Set -2/-3 = 2/3",R(f,2,3));

  SM(f,10,0,1);
  TEST("Set 10 0/1 = 10/1",R(f,10,1));

  SM(f,-10,2,3);
  TEST("Set -10 2/3 = -32/3",R(f,-32,3));

  SM(f,0,0,1);
  TEST("Set 0 0/1 = 0/1",R(f,0,1));

}

void test_fraction_plus_fraction()
{
  pb_init();
  TESTCASE("Add Fractions");
  yaooc_fraction_t f1;
  newp(&f1,yaooc_fraction);
  yaooc_fraction_t f2;
  newp(&f2,yaooc_fraction);
  yaooc_fraction_t* f3;

  S(f1,0,1);
  S(f2,0,1);
  f3=pb_save(yaooc_fraction_plus_fraction(&f1,&f2));
  TEST("0/1 + 0/1 = 0/1",R((*f3),0,1));

  S(f1,0,1);
  S(f2,1,1);
  f3=pb_save(yaooc_fraction_plus_fraction(&f1,&f2));
  TEST("0/1 + 1/1 = 1/1",R((*f3),1,1));

  S(f1,3,5);
  S(f2,-2,9);
  f3=pb_save(yaooc_fraction_plus_fraction(&f1,&f2));
  TEST("3/5 + -2/9 = 17/45",R((*f3),17,45));

  S(f1,-2,8);
  S(f2,-6,8);
  f3=pb_save(yaooc_fraction_plus_fraction(&f1,&f2));
  TEST("-2/8 + -6/8 = -1/1",R((*f3),-1,1));

  S(f1,7,3);
  S(f2,10,7);
  f3=pb_save(yaooc_fraction_plus_fraction(&f1,&f2));
  TEST("7/3 + 10/7 = 79/21",R((*f3),79,21));

  S(f1,-5,7);
  S(f2,25,35);
  f3=pb_save(yaooc_fraction_plus_fraction(&f1,&f2));
  TEST("-5/7 + 25/35 = 0/1",R((*f3),0,1));

  pb_exit();
}

void test_fraction_minus_fraction()
{
  pb_init();
  TESTCASE("Subtract Fractions");
  yaooc_fraction_t f1;
  newp(&f1,yaooc_fraction);
  yaooc_fraction_t f2;
  newp(&f2,yaooc_fraction);
  yaooc_fraction_t* f3;

  S(f1,0,1);
  S(f2,0,1);
  f3=pb_save(yaooc_fraction_minus_fraction(&f1,&f2));
  TEST("0/1 - 0/1 = 0/1",R((*f3),0,1));

  S(f1,0,1);
  S(f2,1,1);
  f3=pb_save(yaooc_fraction_minus_fraction(&f1,&f2));
  TEST("0/1 - 1/1 = -1/1",R((*f3),-1,1));

  S(f1,3,5);
  S(f2,-2,9);
  f3=pb_save(yaooc_fraction_minus_fraction(&f1,&f2));
  TEST("3/5 - -2/9 = 37/45",R((*f3),37,45));

  S(f1,-2,8);
  S(f2,-6,8);
  f3=pb_save(yaooc_fraction_minus_fraction(&f1,&f2));
  TEST("-2/8 - -6/8 = 1/2",R((*f3),1,2));

  S(f1,7,3);
  S(f2,10,7);
  f3=pb_save(yaooc_fraction_minus_fraction(&f1,&f2));
  TEST("7/3 - 10/7 = 19/21",R((*f3),19,21));

  S(f1,-5,7);
  S(f2,25,35);
  f3=pb_save(yaooc_fraction_minus_fraction(&f1,&f2));
  TEST("-5/7 - 25/35 = -10/7",R((*f3),-10,7));

  pb_exit();
}

void test_fraction_times_fraction()
{
  pb_init();
  TESTCASE("Multiply Fractions");
  yaooc_fraction_t f1;
  newp(&f1,yaooc_fraction);
  yaooc_fraction_t f2;
  newp(&f2,yaooc_fraction);
  yaooc_fraction_t* f3;

  S(f1,0,1);
  S(f2,0,1);
  f3=pb_save(yaooc_fraction_times_fraction(&f1,&f2));
  TEST("0/1 * 0/1 = 0/1",R((*f3),0,1));

  S(f1,0,1);
  S(f2,1,1);
  f3=pb_save(yaooc_fraction_times_fraction(&f1,&f2));
  TEST("0/1 * 1/1 = 0/1",R((*f3),0,1));

  S(f1,3,5);
  S(f2,-2,9);
  f3=pb_save(yaooc_fraction_times_fraction(&f1,&f2));
  TEST("3/5 * -2/9 = -2/15",R((*f3),-2,15));

  S(f1,-2,8);
  S(f2,-6,8);
  f3=pb_save(yaooc_fraction_times_fraction(&f1,&f2));
  TEST("-2/8 * -6/8 = 3/16",R((*f3),3,16));

  S(f1,7,3);
  S(f2,10,7);
  f3=pb_save(yaooc_fraction_times_fraction(&f1,&f2));
  TEST("7/3 * 10/7 = 10/3",R((*f3),10,3));

  S(f1,-5,7);
  S(f2,25,35);
  f3=pb_save(yaooc_fraction_times_fraction(&f1,&f2));
  TEST("-5/7 * 25/35 = -25/49",R((*f3),-25,49));

  pb_exit();
}

void test_fraction_divided_by_fraction()
{
  pb_init();
  TESTCASE("Divide Fractions");
  yaooc_fraction_t f1;
  newp(&f1,yaooc_fraction);
  yaooc_fraction_t f2;
  newp(&f2,yaooc_fraction);
  yaooc_fraction_t* f3;

  S(f1,0,1);
  S(f2,1,1);
  f3=pb_save(yaooc_fraction_divided_by_fraction(&f1,&f2));
  TEST("0/1 / 1/1 = 1/1",R((*f3),0,1));

  S(f1,3,5);
  S(f2,-2,9);
  f3=pb_save(yaooc_fraction_divided_by_fraction(&f1,&f2));
  TEST("3/5 / -2/9 = -27/10",R((*f3),-27,10));

  S(f1,-2,8);
  S(f2,-6,8);
  f3=pb_save(yaooc_fraction_divided_by_fraction(&f1,&f2));
  TEST("-2/8 / -6/8 = 1/3",R((*f3),1,3));

  S(f1,7,3);
  S(f2,10,7);
  f3=pb_save(yaooc_fraction_divided_by_fraction(&f1,&f2));
  TEST("7/3 / 10/7 = 49/30",R((*f3),49,30));

  S(f1,-5,7);
  S(f2,25,35);
  f3=pb_save(yaooc_fraction_divided_by_fraction(&f1,&f2));
  TEST("-5/7 / 25/35 = -1",R((*f3),-1,1));

  pb_exit();
}

void test_fraction_eq_fraction()
{
  TESTCASE("Fraction Equality");
  yaooc_fraction_t f1;
  newp(&f1,yaooc_fraction);
  yaooc_fraction_t f2;

  S(f1,0,1);
  S(f2,0,1);
  TEST("0/1 == 0/1 - true ",op_eq_static(&f1,&f2,yaooc_fraction));

  S(f1,0,1);
  S(f2,1,1);
  TEST("0/1 == 1/2 - false ",!op_eq_static(&f1,&f2,yaooc_fraction));

  S(f1,2,3);
  S(f2,-2,3);
  TEST("2/1 == -2/3 - false ",!op_eq_static(&f1,&f2,yaooc_fraction));

  S(f1,2,3);
  S(f2,16,24);
  TEST("2/3 == 16/24 - true ",op_eq_static(&f1,&f2,yaooc_fraction));

  S(f1,1,3);
  S(f2,1,3);
  TEST("1/3 == 1/3 - true ",op_eq_static(&f1,&f2,yaooc_fraction));

  S(f1,-5,7);
  S(f2,25,35);
  TEST("-5/7 == 25/35 - false ",!op_eq_static(&f1,&f2,yaooc_fraction));
}

void test_fraction_ne_fraction()
{
  TESTCASE("Fraction inequality");
  yaooc_fraction_t f1;
  newp(&f1,yaooc_fraction);
  yaooc_fraction_t f2;

  S(f1,0,1);
  S(f2,0,1);
  TEST("0/1 != 0/1 - true ",!op_ne_static(&f1,&f2,yaooc_fraction));

  S(f1,0,1);
  S(f2,1,1);
  TEST("0/1 != 1/2 - true ",op_ne_static(&f1,&f2,yaooc_fraction));

  S(f1,2,3);
  S(f2,-2,3);
  TEST("2/1 != -2/3 - true ",op_ne_static(&f1,&f2,yaooc_fraction));

  S(f1,2,3);
  S(f2,16,24);
  TEST("2/3 != 16/24 - false ",!op_ne_static(&f1,&f2,yaooc_fraction));

  S(f1,1,3);
  S(f2,1,3);
  TEST("1/3 != 1/3 - false ",!op_ne_static(&f1,&f2,yaooc_fraction));

  S(f1,-5,7);
  S(f2,25,35);
  TEST("-5/7 != 25/35 - true ",op_ne_static(&f1,&f2,yaooc_fraction));
}

void test_fraction_lt_fraction()
{
  TESTCASE("Fraction less than");
  yaooc_fraction_t f1;
  newp(&f1,yaooc_fraction);
  yaooc_fraction_t f2;

  S(f1,0,1);
  S(f2,0,1);
  TEST("0/1 < 0/1 - false ",!op_lt_static(&f1,&f2,yaooc_fraction));

  S(f1,0,1);
  S(f2,1,1);
  TEST("0/1 < 1/2 - true ",op_lt_static(&f1,&f2,yaooc_fraction));

  S(f1,2,3);
  S(f2,-2,3);
  TEST("2/1 < -2/3 - false ",!op_lt_static(&f1,&f2,yaooc_fraction));

  S(f1,2,3);
  S(f2,16,24);
  TEST("2/3 < 16/24 - talse ",!op_lt_static(&f1,&f2,yaooc_fraction));

  S(f1,1,3);
  S(f2,1,3);
  TEST("1/3 < 1/3 - false ",!op_lt_static(&f1,&f2,yaooc_fraction));

  S(f1,-5,7);
  S(f2,25,35);
  TEST("-5/7 < 25/35 - true ",op_lt_static(&f1,&f2,yaooc_fraction));
}

void test_fraction_le_fraction()
{
  TESTCASE("Fraction less than or equal");
  yaooc_fraction_t f1;
  newp(&f1,yaooc_fraction);
  yaooc_fraction_t f2;

  S(f1,0,1);
  S(f2,0,1);
  TEST("0/1 <= 0/1 - true ",op_le_static(&f1,&f2,yaooc_fraction));

  S(f1,0,1);
  S(f2,1,1);
  TEST("0/1 <= 1/2 - true ",op_le_static(&f1,&f2,yaooc_fraction));

  S(f1,2,3);
  S(f2,-2,3);
  TEST("2/3 <= -2/3 - false ",!op_le_static(&f1,&f2,yaooc_fraction));

  S(f1,2,3);
  S(f2,16,24);
  TEST("2/3 <= 16/24 - true ",op_le_static(&f1,&f2,yaooc_fraction));

  S(f1,1,3);
  S(f2,1,3);
  TEST("1/3 <= 1/3 - true ",op_le_static(&f1,&f2,yaooc_fraction));

  S(f1,-5,7);
  S(f2,25,35);
  TEST("-5/7 <= 25/35 - true ",op_le_static(&f1,&f2,yaooc_fraction));
}

void test_fraction_gt_fraction()
{
  TESTCASE("Fraction greater than");
  yaooc_fraction_t f1;
  newp(&f1,yaooc_fraction);
  yaooc_fraction_t f2;
  newp(&f1,yaooc_fraction);

  S(f1,0,1);
  S(f2,0,1);
  TEST("0/1 > 0/1 - false ",!op_gt_static(&f1,&f2,yaooc_fraction));

  S(f1,0,1);
  S(f2,1,1);
  TEST("0/1 > 1/2 - false ",!op_gt_static(&f1,&f2,yaooc_fraction));

  S(f1,2,3);
  S(f2,-2,3);
  TEST("2/1 > -2/3 - true ",op_gt_static(&f1,&f2,yaooc_fraction));

  S(f1,2,3);
  S(f2,16,24);
  TEST("2/3 > 16/24 - talse ",!op_gt_static(&f1,&f2,yaooc_fraction));

  S(f1,1,3);
  S(f2,1,3);
  TEST("1/3 > 1/3 - false ",!op_gt_static(&f1,&f2,yaooc_fraction));

  S(f1,-5,7);
  S(f2,25,35);
  TEST("-5/7 > 25/35 - false ",!op_gt_static(&f1,&f2,yaooc_fraction));
}


void test_fraction_ge_fraction()
{
  TESTCASE("Fraction greater than or equal");
  yaooc_fraction_t f1;
  newp(&f1,yaooc_fraction);
  yaooc_fraction_t f2;
  newp(&f1,yaooc_fraction);

  S(f1,0,1);
  S(f2,0,1);
  TEST("0/1 >= 0/1 - true ",op_ge_static(&f1,&f2,yaooc_fraction));

  S(f1,0,1);
  S(f2,1,1);
  TEST("0/1 >= 1/2 - false ",!op_ge_static(&f1,&f2,yaooc_fraction));

  S(f1,2,3);
  S(f2,-2,3);
  TEST("2/1 >= -2/3 - true ",op_ge_static(&f1,&f2,yaooc_fraction));

  S(f1,2,3);
  S(f2,16,24);
  TEST("2/3 >= 16/24 - true ",op_ge_static(&f1,&f2,yaooc_fraction));

  S(f1,1,3);
  S(f2,1,3);
  TEST("1/3 >= 1/3 - true ",op_ge_static(&f1,&f2,yaooc_fraction));

  S(f1,-5,7);
  S(f2,25,35);
  TEST("-5/7 >= 25/35 - false ",!op_ge_static(&f1,&f2,yaooc_fraction));
}

void test_to_double()
{
  yaooc_fraction_t f;
  TESTCASE("To double")
  newp(&f,yaooc_fraction);

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
  newp(&f,yaooc_fraction);

  TESTCASE("From double")

  M(&f,from_double,0.0);
  TEST("Fraction from 0.0 is 0/1",R(f,0,1));

  M(&f,from_double,1.0);
  TEST("Fraction from 1.0 is 1/1",R(f,1,1));

  M(&f,from_double,12.25);
  TEST("Fraction from 12.25 is 49/4",R(f,49,4));

  M(&f,from_double,-100.0625);
  TEST("Fraction from -100.0625 is -1601/16",R(f,-1601,16));

  M(&f,from_double,0.3);
  TEST("Fraction from 0.3 is 3/10",R(f,3,10));

  M(&f,from_double,0.33);
  TEST("Fraction from 0.33 is 33/100",R(f,33,100));

  M(&f,from_double,0.33333333333);
  TEST("Fraction from 0.33333333 is 1/3",R(f,1,3));
}

void test_to_stream()
{
  yaooc_fraction_t f;
  newp(&f,yaooc_fraction);
  yaooc_ostringstream_t* os=new(yaooc_ostringstream);
  TESTCASE("To stream")

  S(f,0,1);
  STREAM(os,O_OBJ(yaooc_fraction,f));
  TEST("Fraction 0/1 to stream is \"0\"",strcmp(M(os,c_str),"0")==0);
  M(os,seek,0,SEEK_SET);

  S(f,1,1);
  STREAM(os,O_OBJ(yaooc_fraction,f));
  TEST("Fraction 1/1 to stream is \"1\"",strcmp(M(os,c_str),"1")==0);
  M(os,seek,0,SEEK_SET);

  S(f,1,3);
  STREAM(os,O_OBJ(yaooc_fraction,f));
  TEST("Fraction 1/3 to stream is \"1/3\"",strcmp(M(os,c_str),"1/3")==0);
  M(os,seek,0,SEEK_SET);

  delete(os);
}

void test_from_stream()
{
  yaooc_istringstream_t* is=new_ctor(yaooc_istringstream,yaooc_istringstream_ctor_ccs,"0 1 10/3 -3/4 -8 5/10 8/ 3");
  yaooc_fraction_t f;
  newp(&f,yaooc_fraction);
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
  test_gcd,
	test_default_constructor,
  test_fraction_set,
  test_fraction_plus_fraction,
  test_fraction_minus_fraction,
  test_fraction_times_fraction,
  test_fraction_divided_by_fraction,
  test_fraction_eq_fraction,
  test_fraction_ne_fraction,
  test_fraction_lt_fraction,
  test_fraction_le_fraction,
  test_fraction_gt_fraction,
  test_fraction_ge_fraction,
  test_to_double,
  test_from_double,
  test_to_stream,
  test_from_stream,
};

STD_MAIN(tests)
