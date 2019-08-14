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
#include <yaooc/uint24.h>
#include "test_harness.h"


#define func(v) ((v)*(v) + 12*(v) +5)
void test_basic()
{
  yaooc_uint24_t uint24[10];
  uint32_t i;
  for(i=0;i<10;i++) {
    yaooc_uint24_from_uint32(uint24+i,func(i));
  }
  char msg[64];
  for(i=0;i<10;i++) {
    sprintf(msg,"Value is %u",func(i));
    TEST(msg,yaooc_uint24_to_uint32(uint24+i));
  }
}

void test_max_value()
{
  uint32_t ui=16777215;
  uint32_t i;
  yaooc_uint24_t uint24[10];
  for(i=0;i<10;i++,ui--) {
    yaooc_uint24_from_uint32(uint24,ui);
  }
}

test_function tests[]=
{
 	test_basic,
  test_max_value,
};

STD_MAIN(tests)
