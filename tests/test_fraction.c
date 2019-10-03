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
  typedef struct {
    int n;
    int d;
    int gcd;
  } gcd_test_data_t;
  gcd_test_data_t test_data[] = { {0,2,2},{ 10,1,1},{105,15,15},{10,230,10},{28,234,2 },{872452914,78241452,6}};
  char msg[256];
  int n = ARRAY_SIZE(test_data);
  TESTCASE("Greatest Common Divisor");
  int i;
  for(i=0;i<n;i++) {
    sprintf(msg,"GCD(%d,%d) = %d",test_data[i].n,test_data[i].d,test_data[i].gcd);
    TEST(msg,yaooc_fraction_gcd(test_data[i].n,test_data[i].d)==test_data[i].gcd);
  }
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

  int set_test_data[][4]={ { 0,1,0,1 }, {1,1,1,1}, {-2,3,-2,3}, {2,-3,-2,3}, {-2,-3,2,3}};
  int i,n = ARRAY_SIZE(set_test_data);
  char msg[64];
  for(i=0;i<n;i++) {
    sprintf(msg,"set(%d,%d) = (%d,%d)",set_test_data[i][0],set_test_data[i][1],
            set_test_data[i][2],set_test_data[i][3]);
    S(f,set_test_data[i][0],set_test_data[i][1]);
    TEST(msg,R(f,set_test_data[i][2],set_test_data[i][3]));
  }
}

void test_fraction_set_wnd()
{
  TESTCASE("Fraction set");
  yaooc_fraction_t f;

  int set_test_data[][5]={ { -10,2,3,-32,3 }, {0,-2,3,-2,3}, {0,0,1,0,1}, {0,2,3,2,3}, {10,2,3,32,3}};
  int i,n = ARRAY_SIZE(set_test_data);
  char msg[64];
  for(i=0;i<n;i++) {
    sprintf(msg,"set(%d,%d,%d) = (%d,%d)",set_test_data[i][0],set_test_data[i][1],
            set_test_data[i][2],set_test_data[i][3],set_test_data[i][4]);
    SM(f,set_test_data[i][0],set_test_data[i][1],set_test_data[i][2]);
    TEST(msg,R(f,set_test_data[i][3],set_test_data[i][4]));
  }

}

void test_fraction_plus_fraction()
{
  TESTCASE("Add Fractions");
  int plus_data[][6] = { {0,1,0,1,0,1}, {0,1,1,1,1,1},{3,5,-2,9,17,45},
        {-2,8,-6,8,-1,1}, {7,3,10,7,79,21}, {-5,7,25,35,0,1}};
  int n = ARRAY_SIZE(plus_data);
  int i;
  yaooc_fraction_t f1 = YAOOC_FRACTION_DEF_INIT;
  yaooc_fraction_t f2 = YAOOC_FRACTION_DEF_INIT;
  yaooc_fraction_t f3;
  char msg[64];
  for(i=0;i<n;i++) {
    sprintf(msg,"(%d/%d) + (%d/%d) = (%d/%d)",plus_data[i][0],plus_data[i][1],plus_data[i][2],plus_data[i][3],
          plus_data[i][4],plus_data[i][5]);
    S(f1,plus_data[i][0],plus_data[i][1]);
    S(f2,plus_data[i][2],plus_data[i][3]);
    f3 = yaooc_fraction_plus_fraction(f1,f2);
    TEST(msg,R(f3,plus_data[i][4],plus_data[i][5]));
  }
}

void test_fraction_minus_fraction()
{
  TESTCASE("Subtract Fractions");
  int minus_data[][6] = { {0,1,0,1,0,1} , {0,1,1,1,-1,1},{3,5,-2,9,37,45},
          {-2,8,-6,8,1,2}, {7,3,10,7,19,21}, {-5,7,25,35,-10,7}};
  int n = ARRAY_SIZE(minus_data);
  int i;
  yaooc_fraction_t f1 = YAOOC_FRACTION_DEF_INIT;
  yaooc_fraction_t f2 = YAOOC_FRACTION_DEF_INIT;
  yaooc_fraction_t f3;
  char msg[64];
  for(i=0;i<n;i++) {
    sprintf(msg,"(%d/%d) - (%d/%d) = (%d/%d)",minus_data[i][0],minus_data[i][1],minus_data[i][2],minus_data[i][3],
          minus_data[i][4],minus_data[i][5]);
    S(f1,minus_data[i][0],minus_data[i][1]);
    S(f2,minus_data[i][2],minus_data[i][3]);
    f3 = yaooc_fraction_minus_fraction(f1,f2);
    TEST(msg,R(f3,minus_data[i][4],minus_data[i][5]));
  }
}

void test_fraction_times_fraction()
{
  TESTCASE("Multiply Fractions");
  int times_data[][6] = { {0,1,0,1,0,1} , {0,1,1,1,0,1},{3,5,-2,9,-2,15},
          {-2,8,-6,8,3,16}, {7,3,10,7,10,3}, {-5,7,25,35,-25,49}};
  int n = ARRAY_SIZE(times_data);
  int i;
  yaooc_fraction_t f1 = YAOOC_FRACTION_DEF_INIT;
  yaooc_fraction_t f2 = YAOOC_FRACTION_DEF_INIT;
  yaooc_fraction_t f3;
  char msg[64];
  for(i=0;i<n;i++) {
    sprintf(msg,"(%d/%d) * (%d/%d) = (%d/%d)",times_data[i][0],times_data[i][1],times_data[i][2],times_data[i][3],
          times_data[i][4],times_data[i][5]);
    S(f1,times_data[i][0],times_data[i][1]);
    S(f2,times_data[i][2],times_data[i][3]);
    f3 = yaooc_fraction_times_fraction(f1,f2);
    TEST(msg,R(f3,times_data[i][4],times_data[i][5]));
  }
}

void test_fraction_divided_by_fraction()
{
  TESTCASE("Divide Fractions");
  int divide_data[][6] = { {0,1,1,1,0,1},{3,5,-2,9,-27,10},
          {-2,8,-6,8,1,3}, {7,3,10,7,49,30}, {-5,7,25,35,-1,1}};
  int n = ARRAY_SIZE(divide_data);
  int i;
  yaooc_fraction_t f1 = YAOOC_FRACTION_DEF_INIT;
  yaooc_fraction_t f2 = YAOOC_FRACTION_DEF_INIT;
  yaooc_fraction_t f3;
  char msg[64];
  for(i=0;i<n;i++) {
    sprintf(msg,"(%d/%d) / (%d/%d) = (%d/%d)",divide_data[i][0],divide_data[i][1],divide_data[i][2],divide_data[i][3],
          divide_data[i][4],divide_data[i][5]);
    S(f1,divide_data[i][0],divide_data[i][1]);
    S(f2,divide_data[i][2],divide_data[i][3]);
    f3 = yaooc_fraction_divided_by_fraction(f1,f2);
    TEST(msg,R(f3,divide_data[i][4],divide_data[i][5]));
  }
}

void test_fraction_eq_fraction()
{
  int eq_data[][5] = { { 0,1,0,1,1}, {0,1,1,2,0}, {2,3,-2,4,0}, {2,3,16,24,1}, {1,3,1,3,1},{-5,7,25,35,0}};
  TESTCASE("Fraction Equality");
  yaooc_fraction_t f1;
  yaooc_fraction_t f2;

  char msg[64];
  int i,n=ARRAY_SIZE(eq_data);
  for(i=0;i<n;i++) {
    sprintf(msg,"(%d/%d) == (%d/%d) -- %s",eq_data[i][0],eq_data[i][1],eq_data[i][2],
          eq_data[i][3],(eq_data[i][4] == 1 ? "true" : "false"));
    S(f1,eq_data[i][0],eq_data[i][1]);
    S(f2,eq_data[i][2],eq_data[i][3]);
    TEST(msg,op_eq_static(&f1,&f2,yaooc_fraction) == (eq_data[i][4] == 1));
  }
}

void test_fraction_ne_fraction()
{
  int ne_data[][5] = { { 0,1,0,1,0}, {0,1,1,2,1}, {2,3,-2,4,1}, {2,3,16,24,0}, {1,3,1,3,0}, {-5,7,25,35,1}};
  TESTCASE("Fraction inquality");
  yaooc_fraction_t f1;
  yaooc_fraction_t f2;

  char msg[64];
  int i,n=ARRAY_SIZE(ne_data);
  for(i=0;i<n;i++) {
    sprintf(msg,"(%d/%d) == (%d/%d) -- %s",ne_data[i][0],ne_data[i][1],ne_data[i][2],
          ne_data[i][3],(ne_data[i][4] == 1 ? "true" : "false"));
    S(f1,ne_data[i][0],ne_data[i][1]);
    S(f2,ne_data[i][2],ne_data[i][3]);
    TEST(msg,op_ne_static(&f1,&f2,yaooc_fraction) == (ne_data[i][4] == 1));
  }
}

void test_fraction_lt_fraction()
{
  int lt_data[][5] = { { 0,1,0,1,0}, {0,1,1,2,1}, {2,3,-2,4,0}, {2,3,16,24,0}, {1,3,1,3,0}, {-5,7,25,35,1}};
  TESTCASE("Fraction less than");
  yaooc_fraction_t f1;
  yaooc_fraction_t f2;

  char msg[64];
  int i,n=ARRAY_SIZE(lt_data);
  for(i=0;i<n;i++) {
    sprintf(msg,"(%d/%d) == (%d/%d) -- %s",lt_data[i][0],lt_data[i][1],lt_data[i][2],
          lt_data[i][3],(lt_data[i][4] == 1 ? "true" : "false"));
    S(f1,lt_data[i][0],lt_data[i][1]);
    S(f2,lt_data[i][2],lt_data[i][3]);
    TEST(msg,op_lt_static(&f1,&f2,yaooc_fraction) == (lt_data[i][4] == 1));
  }
}

void test_fraction_le_fraction()
{
  int le_data[][5] = { { 0,1,0,1,1}, {0,1,1,2,1}, {2,3,-2,4,0}, {2,3,16,24,1}, {1,3,1,3,1}, {-5,7,25,35,1}};
  TESTCASE("Fraction Equality");
  yaooc_fraction_t f1;
  yaooc_fraction_t f2;

  char msg[64];
  int i,n=ARRAY_SIZE(le_data);
  for(i=0;i<n;i++) {
    sprintf(msg,"(%d/%d) == (%d/%d) -- %s",le_data[i][0],le_data[i][1],le_data[i][2],
          le_data[i][3],(le_data[i][4] == 1 ? "true" : "false"));
    S(f1,le_data[i][0],le_data[i][1]);
    S(f2,le_data[i][2],le_data[i][3]);
    TEST(msg,op_le_static(&f1,&f2,yaooc_fraction) == (le_data[i][4] == 1));
  }
}

void test_fraction_gt_fraction()
{
  int gt_data[][5] = { { 0,1,0,1,0}, {0,1,1,2,0}, {2,3,-2,4,1}, {2,3,16,24,0}, {1,3,1,3,0}, {-5,7,25,35,0}};
  TESTCASE("Fraction greater than");
  yaooc_fraction_t f1;
  yaooc_fraction_t f2;

  char msg[64];
  int i,n=ARRAY_SIZE(gt_data);
  for(i=0;i<n;i++) {
    sprintf(msg,"(%d/%d) == (%d/%d) -- %s",gt_data[i][0],gt_data[i][1],gt_data[i][2],
          gt_data[i][3],(gt_data[i][4] == 1 ? "true" : "false"));
    S(f1,gt_data[i][0],gt_data[i][1]);
    S(f2,gt_data[i][2],gt_data[i][3]);
    TEST(msg,op_gt_static(&f1,&f2,yaooc_fraction) == (gt_data[i][4] == 1));
  }
}

void test_fraction_ge_fraction()
{
  int ge_data[][5] = { { 0,1,0,1,1}, {0,1,1,2,0}, {2,3,-2,4,1}, {2,3,16,24,1}, {1,3,1,3,1}, {-5,7,25,35,0}};
  TESTCASE("Fraction greater than or equal");
  yaooc_fraction_t f1;
  yaooc_fraction_t f2;

  char msg[64];
  int i,n=ARRAY_SIZE(ge_data);
  for(i=0;i<n;i++) {
    sprintf(msg,"(%d/%d) == (%d/%d) -- %s",ge_data[i][0],ge_data[i][1],ge_data[i][2],
          ge_data[i][3],(ge_data[i][4] == 1 ? "true" : "false"));
    S(f1,ge_data[i][0],ge_data[i][1]);
    S(f2,ge_data[i][2],ge_data[i][3]);
    TEST(msg,op_ge_static(&f1,&f2,yaooc_fraction) == (ge_data[i][4] == 1));
  }
}


void test_to_double()
{
  TESTCASE("Fraction to double")
  yaooc_fraction_t f;
  int to_double_input [][2] = { {0,1}, {1,1}, {1,2}, {1,3}, {3,5}, {20,3}, {-20,3}, {-2,3}};
  double to_double_output[] = { 0.0, 1.0, 0.5, 1.0/3.0, 3.0/5.0, 20.0/3.0, -20.0/3.0, -2.0/3.0 };
  newp(&f,yaooc_fraction);

  int n =ARRAY_SIZE(to_double_input);
  int i;
  char msg[64];
  for(i=0;i<n;i++) {
    sprintf(msg,"to_double(%d/%d) = %lg",to_double_input[i][0],to_double_input[i][1],to_double_output[i]);
    S(f,to_double_input[i][0],to_double_input[i][1]);
    TEST(msg,fabs(yaooc_fraction_to_double(&f) - to_double_output[i]) < yaooc_fraction_epsilon);
  }
}


void test_from_double()
{
  TESTCASE("Fraction from double")
  double from_double_input [] = { -2.25, -.25, 0.0, .25, 2.25, .3, .33, .333333333 };
  int from_double_output [][2] = { { -9,4} , { -1, 4}, { 0,1 }, {1,4}, {9,4} , {3,10}, {33,100}, {1,3}};
  yaooc_fraction_t f = YAOOC_FRACTION_DEF_INIT;
  int n=ARRAY_SIZE(from_double_input);
  int i;
  char msg[64];
  for(i=0;i<n;i++) {
    sprintf(msg,"from_double(%lg)=(%d/%d)",from_double_input[i],from_double_output[i][0],from_double_output[i][1]);
    M(&f,from_double,from_double_input[i]);
    TEST(msg,R(f,from_double_output[i][0],from_double_output[i][1]));
  }
}

void test_to_string()
{
  TESTCASE("To String");
  int to_string_input[][2] = { { -9,4} , { -1, 4}, { 0,1 }, {1,4}, {9,4} };
  const char* to_string_output[] = {"-9/4", "-1/4", "0" , "1/4","9/4"};
  int n=ARRAY_SIZE(to_string_input);
  int i;
  char msg[64];
  pb_init();
  for(i=0;i<n;i++) {
    sprintf(msg,"to_s(%d/%d) = \"%s\"",to_string_input[i][0],to_string_input[i][1],to_string_output[i]);
    yaooc_fraction_t f = YAOOC_FRACTION_DEF_INIT;
    S(f,to_string_input[i][0],to_string_input[i][1]);
    yaooc_string_t* f_str = pb_save(M(&f,to_s));
    TEST(msg,strcmp(M(f_str,c_str),to_string_output[i])==0);
  }
  pb_exit();
}

void test_to_mixed_string()
{
  pb_init();
  TESTCASE("To Mixed String");
  int to_mixed_string_input[][2] = { { -9,4} , { -1, 4}, { 0,1 }, {1,4}, {9,4} };
  const char* to_mixed_string_output[] = {"-2 1/4", "-1/4", "0" , "1/4","2 1/4"};
  int n=ARRAY_SIZE(to_mixed_string_input);
  int i;
  char msg[64];
  for(i=0;i<n;i++) {
    sprintf(msg,"to_mixed_s(%d/%d) = \"%s\"",to_mixed_string_input[i][0],to_mixed_string_input[i][1],to_mixed_string_output[i]);
    yaooc_fraction_t f = YAOOC_FRACTION_DEF_INIT;
    S(f,to_mixed_string_input[i][0],to_mixed_string_input[i][1]);
    yaooc_string_t* f_str = pb_save(M(&f,to_mixed_s));
    TEST(msg,strcmp(M(f_str,c_str),to_mixed_string_output[i])==0);
  }
  pb_exit();
}

void test_to_stream()
{
  pb_init();
  yaooc_ostringstream_t* os=new(yaooc_ostringstream);
  TESTCASE("To stream")
  int to_stream_input[][2] = { { -9,4} , { -1, 4}, { 0,1 }, {1,4}, {9,4} };
  const char* to_stream_output[] = {"-9/4", "-1/4", "0" , "1/4","9/4"};
  int n=ARRAY_SIZE(to_stream_input);
  int i;
  char msg[64];
  yaooc_fraction_t f = YAOOC_FRACTION_DEF_INIT;
  for(i=0;i<n;i++) {
    sprintf(msg,"to_stream(%d/%d) = \"%s\"",to_stream_input[i][0],to_stream_input[i][1],to_stream_output[i]);
    S(f,to_stream_input[i][0],to_stream_input[i][1]);
    STREAM(os,O_OBJ(yaooc_fraction,f));
    TEST(msg,strcmp(M(os,c_str),to_stream_output[i])==0);
    M(os,seek,0,SEEK_SET);
  }
  pb_exit();
}

void test_from_stream()
{
  pb_init();
  yaooc_istringstream_t* is=pb_new_ctor(yaooc_istringstream,yaooc_istringstream_ctor_ccs,"0 1 10/3 -3/4 -8 5/10 8/ 3");
  const char* from_stream_input[] = {"0", "1","10/3","-3/4","-8","5/10"};
  int from_stream_output[][2] = { {0,1}, {1,1}, {10,3}, {-3,4}, {-8,1}, {1,2}};
  yaooc_fraction_t f = YAOOC_FRACTION_DEF_INIT;
  TESTCASE("From Stream")

  int n = ARRAY_SIZE(from_stream_input);
  int i;
  char msg[64];
  for(i=0;i<n;i++) {
    sprintf(msg,"Read \"%s\" from stream is (%d/%d)",from_stream_input[i],from_stream_output[i][0],from_stream_output[i][1]);
    STREAM(is,I_OBJ(yaooc_fraction,f));
    TEST(msg,R(f,from_stream_output[i][0],from_stream_output[i][1]));
  }

  TRY {
    STREAM(is,I_OBJ(yaooc_fraction,f));
    TEST("Fraction 8/ 3 from stream throws exception",false);
  } CATCH(yaooc_fraction_exception,e) {
    TEST("Fraction 8/ 3 from stream throws exception",true);
  }
  ETRY
  pb_exit();
}

test_function tests[]=
{
  test_gcd,
	test_default_constructor,
  test_fraction_set,
  test_fraction_set_wnd,
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
  test_to_string,
  test_to_mixed_string,
  test_to_stream,
  test_from_stream,
};

STD_MAIN(tests)
