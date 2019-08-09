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
#include <yaooc/fstream.h>
#include <yaooc/sstream.h>
#include <yaooc/string.h>
#include "test_harness.h"

void test_stream()
{
	M(cout,printf,"%s\n","Testing");
	yaooc_string_pointer sp=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"This is a test");
	yaooc_string_t ss;
	newp_ctor(&ss,yaooc_string,yaooc_string_ctor_ccs,"Still testing.");
	STREAM(cout,sp,endl,O_CCS("This is another test "), O_INT(32)); //,O_OBJ(yaooc_string,ss),endl);

	char temp[128];
	int z;
	STREAM(cout,O_CCS("Enter an integer and string"),endl);
	STREAM(cin,I_INT(z),I_CCS(temp));
	STREAM(cout,O_CCS("Integer is "),O_INT(z),O_CCS(" and first word of string is "),O_CCS(temp),endl);
	delete(sp);
	deletep(&ss,yaooc_string);
}

void test_fstream()
{
	yaooc_ofstream_pointer out=new_ctor(yaooc_ofstream,yaooc_ofstream_ctor_fname_mode,"samp.out","w");
	M(out,printf,"%s %d\n","Testing",27);
	delete(out);
}

void test_sstream()
{
	yaooc_ostringstream_pointer out=new(yaooc_ostringstream);
	M(out,printf,"%s %d\n","Testing",27);
	STREAM(out,O_CCS("Testing "),O_INT(27),endl);
	M(cout,putstr,M(out,c_str));
	delete(out);
}


test_function tests[]=
{
	test_stream,
	test_fstream,
	test_sstream
};

STD_MAIN(tests)
