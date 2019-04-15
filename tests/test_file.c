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
#include <yaooc/file.h>

#include "test_harness.h"


void test_basic()
{
	yaooc_file_t * f=new(yaooc_file);
	TEST("f1: Name is NULL",f->name_==NULL);
	TEST("f1: Stat struct is NULL",f->stat_==NULL);
	TEST("f1: Stat result is -2",f->stat_result_==-2);

	yaooc_file_t * f2 =new_ctor(yaooc_file,yaooc_file_ctor_name,"tests/test_file.c");
	TEST("f2: Name is not NULL",f2->name_!=NULL);
	TEST("f2: Stat struct is NULL",f2->stat_==NULL);
	TEST("f2: Stat result is -2",f2->stat_result_==-2);

	TEST("f2: test_file.c exists",M(f2,exists));
	TEST("f2: Name is not NULL",f2->name_!=NULL);
	TEST("f2: Stat struct is not NULL",f2->stat_!=NULL);
	TEST("f2: Stat result is 0",f2->stat_result_==0);

	M(f,swap,f2);
	puts("After Swap");
	TEST("f2: Name is NULL",f2->name_==NULL);
	TEST("f2: Stat struct is NULL",f2->stat_==NULL);
	TEST("f2: Stat result is -2",f2->stat_result_==-2);

	TEST("f1: Name is not NULL",f->name_!=NULL);
	TEST("f1: Stat struct is not NULL",f->stat_!=NULL);
	TEST("f1: Stat result is 0",f->stat_result_==0);
	delete(f);
	delete(f2);
}

void test_other()
{
	yaooc_file_t * f=new_ctor(yaooc_file,yaooc_file_ctor_name,"tests");
	TEST("'tests' is a directory",M(f,isdir));
#ifndef _WIN32
	TEST("UID is same as process id",M(f,uid)==getuid());
	TEST("GID is same as process id",M(f,gid)==getgid());
#endif
	delete(f);

}

void test_modes()
{
	yaooc_file_t * f=new_ctor(yaooc_file,yaooc_file_ctor_name,"tests/test_file.c");
	TEST("'test_file.c' is not a directory",!M(f,isdir));
	TEST("'test_file.c' is not a character device",!M(f,ischr));
	TEST("'test_file.c' is not a block device",!M(f,isblk));
	TEST("'test_file.c' is a regular file",M(f,isreg));
	TEST("'test_file.c' is not a directory",!M(f,isfifo));
	delete(f);

	f=new_ctor(yaooc_file,yaooc_file_ctor_name,"tests/test_file.c");
}

test_function tests[]=
{
	test_basic,
	test_other,
	test_modes,
};

STD_MAIN(tests)
