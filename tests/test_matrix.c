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
#include <yaooc/matrix.h>
#include <yaooc/sstream.h>
#include <math.h>
#include "test_harness.h"


void test_ctor_dtor()
{
  TESTCASE("Constructors")
  yaooc_matrix_t* mat=new(yaooc_matrix);
  TEST("Default ctor",mat->rows_==0 &&  mat->cols_==0 && mat->data_==NULL);
  delete(mat);
  mat=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,3,3);
  TEST("Ctor rows cols",mat->rows_==3 &&  mat->cols_==3 && mat->data_!=NULL);
  delete(mat);

}

void test_copy_assign()
{
  TESTCASE("Copy constructor and assignment")
  yaooc_matrix_t* mat=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,3,3);
  unsigned int r,c,v=0;
  for(r=0;r<3;r++)
    for(c=0;c<3;c++)
      mat->data_[r][c]=v++;
  yaooc_matrix_t* dup=new_copy(mat);
  bool rc=true;
  for(r=0;r<3;r++)
    for(c=0;c<3;c++)
      if(mat->data_[r][c] != dup->data_[r][c]) {
        rc=false;
        break;
      }
  TEST("Copy constructor",rc);
  delete(dup);

  dup=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,3,3);
  memset(dup->data_[0],0,3*3*sizeof(double)); // be sure values are zero
  assign(dup,mat);
  for(r=0;r<3;r++)
    for(c=0;c<3;c++)
      if(mat->data_[r][c] != dup->data_[r][c]) {
        rc=false;
        break;
      }
  TEST("Assignment",rc);
  delete(dup);
  delete(mat);
}

void test_addition()
{
  yaooc_matrix_t* mat=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,3,3);
  TESTCASE("Addition")
  unsigned int r,c;
  for(r=0;r<3;r++)
    for(c=0;c<3;c++)
      mat->data_[r][c]=8888;
  yaooc_matrix_t* mat2=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,3,3);
  for(r=0;r<3;r++)
    for(c=0;c<3;c++)
      mat2->data_[r][c]=9999;
  yaooc_matrix_t* mat3 = M(mat,plus,mat2);
  TEST("Rows cols match",mat3->cols_==mat->cols_ && mat3->rows_==mat->rows_);
  bool rc=true;
  for(r=0;r<3;r++)
    for(c=0;c<3;c++) {
      if(fabs(mat3->data_[r][c] - (mat->data_[r][c]+mat2->data_[r][c])) > 0.0001) {
        rc=false;
        break;
      }
    }
  TEST("mat3 = mat1+mat2",rc);
  delete(mat);
  delete(mat2);
  delete(mat3);
}

void test_subtraction()
{
  yaooc_matrix_t* mat=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,3,3);
  TESTCASE("Subtraction")
  unsigned int r,c;
  for(r=0;r<3;r++)
    for(c=0;c<3;c++)
      mat->data_[r][c]=8888;
  yaooc_matrix_t* mat2=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,3,3);
  for(r=0;r<3;r++)
    for(c=0;c<3;c++)
      mat2->data_[r][c]=9999;
  yaooc_matrix_t* mat3 = M(mat,minus,mat2);
  TEST("Rows cols match",mat3->cols_==mat->cols_ && mat3->rows_==mat->rows_);
  bool rc=true;
  for(r=0;r<3;r++)
    for(c=0;c<3;c++) {
      if(fabs(mat3->data_[r][c] - (mat->data_[r][c]-mat2->data_[r][c])) > 0.0001) {
        rc=false;
        break;
      }
    }
  TEST("mat3 = mat1-mat2",rc);
  delete(mat);
  delete(mat2);
  delete(mat3);
}

double times_result[3][3] = {
  { 27, 30, 33 },
  { 61, 68, 75 },
  { 95, 106, 117 }
};

double times_result2[2][2] = {
  { 76, 100 },
  { 103, 136 },
};

void test_multiplication()
{
  yaooc_matrix_t* mat=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,3,2);
  TESTCASE("Multiplication")
  unsigned int r,c,v=1;
  for(r=0;r<3;r++)
    for(c=0;c<2;c++)
      mat->data_[r][c]=v++;
  yaooc_matrix_t* mat2=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,2,3);
  for(r=0;r<2;r++)
    for(c=0;c<3;c++)
      mat2->data_[r][c]=v++;
  yaooc_matrix_t* mat3 = M(mat,times,mat2);
  TEST("Rows cols match",mat3->rows_==mat->rows_ && mat3->cols_==mat2->cols_);
  bool rc=true;
  for(r=0;r<mat3->rows_;r++) {
    for(c=0;c<mat3->cols_;c++) {
      if(fabs(mat3->data_[r][c] - times_result[r][c]) > 0.0001) {
        rc=false;
        break;
      }
    }
  }
  delete(mat3);
  TEST("mat3 = mat1*mat2",rc);
  mat3 = M(mat2,times,mat);
  TEST("Rows cols match",mat3->rows_==mat2->rows_ && mat3->cols_==mat->cols_);
  rc=true;
  for(r=0;r<mat3->rows_;r++) {
    for(c=0;c<mat3->cols_;c++) {
      if(fabs(mat3->data_[r][c] - times_result2[r][c]) > 0.0001) {
        rc=false;
        break;
      }
    }
  }
  TEST("mat3 = mat2*mat1",rc);

  delete(mat);
  delete(mat2);
  delete(mat3);
}

double inv[3][3] = {
  { -43.0/24.0 , 11.0/12.0, -1.0/8.0 },
  { 19.0/12.0, -5.0/6.0, 1.0/4.0, },
  { -1.0/8.0, 1.0/4.0, -1.0/8.0 }
};

void test_inverse()
{
  yaooc_matrix_t* mat=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,3,3);
  TESTCASE("Inverse")
  unsigned int r,c,v=1;
  for(r=0;r<mat->rows_;r++)
    for(c=0;c<mat->cols_;c++)
      mat->data_[r][c]=v++;
  mat->data_[2][2]=1;
  yaooc_matrix_t* im=M(mat,inverse);

  bool rc=true;
  for(r=0;r<im->rows_;r++) {
    for(c=0;c<im->cols_;c++) {
      if(fabs(im->data_[r][c] - inv[r][c]) > 0.0001) {
        rc=false;
        break;
      }
    }
    printf("\n");
  }
  TEST("im = inverse(mat)",rc);

  delete(mat);
  delete(im);
}

void test_determinant()
{
  TESTCASE("Determinant")
  yaooc_matrix_t* mat=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,3,3);
  unsigned int r,c,v=1;
  for(r=0;r<mat->rows_;r++)
    for(c=0;c<mat->cols_;c++)
      mat->data_[r][c]=v++;
  TEST("Determinant is 0",(int)M(mat,determinant) == 0);
  mat->data_[2][2]=1;
  TEST("Determinant is 24",(int)M(mat,determinant) == 24);
}

void test_transpose()
{
  TESTCASE("Transpose")
  yaooc_matrix_t* mat=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,3,2);
  unsigned int r,c,v=1;
  for(r=0;r<mat->rows_;r++)
    for(c=0;c<mat->cols_;c++)
      mat->data_[r][c]=v++;
  yaooc_matrix_t* tm=M(mat,transpose);
  bool rc=true;
  for(r=0;r<mat->rows_;r++)
    for(c=0;c<mat->cols_;c++) {
      if(tm->data_[c][r] != mat->data_[r][c]) {
        rc=false;
        break;
      }
    }
  TEST("tm = transpose(mat)",rc)
}

test_function tests[]=
{
	test_ctor_dtor,
  test_copy_assign,
  test_addition,
  test_subtraction,
  test_multiplication,
  test_inverse,
  test_determinant,
  test_transpose,
};

STD_MAIN(tests)
