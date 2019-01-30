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
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/new.h>
#include <yaooc/utils.h>
#include "test_harness.h"

void test_mkstemp_in_tmpdir()
{
	char tmpfile[256]="abc";
	TEST("mkstemp successful",mkstemp_in_tmpdir(tmpfile,256));
	unlink(tmpfile);
	TEST("mkstemp fails",!mkstemp_in_tmpdir(tmpfile,6));
}

test_function tests[]=
{
 	test_mkstemp_in_tmpdir,
};

STD_MAIN(tests)
