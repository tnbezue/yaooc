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
#include <yaooc/dir.h>
#include "test_harness.h"
void test_entries()
{
	yaooc_file_vector_t* files = yaooc_dir_entries("tests");
	yaooc_file_vector_const_iterator i;
	FOR_EACH(i,files) {
		printf("%s\n",i->name_);
	}
	delete(files);
}

void test_glob()
{
	yaooc_file_vector_t* files = yaooc_dir_glob("tests/*.c");
	yaooc_file_vector_const_iterator i;
	FOR_EACH(i,files) {
		printf("%s\n",i->name_);
	}
	delete(files);
}

test_function tests[]=
{
	test_entries,
  test_glob,
};

STD_MAIN(tests)
