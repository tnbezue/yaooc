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
#include <yaooc/vector.h>
#include <yaooc/algorithm.h>

#include <time.h>

extern int count;
#include "demo_def.inc"
#include "test_harness.h"

VECTOR_DEFINITION(long,long_vector)  /* Normally in header file */
VECTOR_IMPLEMENTATION(long,long_vector) /* Normally in c source file (.c) */

void test_long()
{
	long_vector_pointer vlong=new(long_vector);
	long_t numbers[]={ 9,10, -2, 44, 55};
	size_t n=sizeof(numbers)/sizeof(numbers[0]);
	size_t i;
	for(i=0;i<n;i++)
		M(vlong,push_back,numbers+i);
	long_vector_const_iterator ivi;
	for(ivi=M(vlong,begin);ivi!=M(vlong,end);ivi++)
		printf("%lld ",*ivi);
	puts("\n");
  delete(vlong);
}

/*
  A 8 character string type
*/

class_(str_8){
  char str[8];
};
void str_8_default_ctor(pointer p)
{
	((str_8_pointer)p)->str[0]=0;
}
bool str_8_less_than_compare(const_pointer v1,const_pointer v2)
{
	return strcmp((const char*)(((str_8_const_pointer)v1)->str),(const char*)(((str_8_const_pointer)v2)->str)) < 0;
}
DEFINE_TYPE_INFO(str_8,str_8_default_ctor,NULL,NULL,NULL,str_8_less_than_compare,NULL,NULL,NULL,NULL)

VECTOR_DEFINITION(str_8,str_8_vector)
VECTOR_IMPLEMENTATION(str_8,str_8_vector)
void test_str_8()
{
  printf("Size is %zu\n",sizeof(str_8_t));
	str_8_vector_pointer vec = new(str_8_vector);
	clock_t start=clock();
	str_8_t s;
	s.str[4]=0;
	int i,j,k,l;
//	M(vec,reserve,456976);
	printf("Size: %zu Cap: %zu\n",M(vec,size),M(vec,capacity));
	clock_t duration=clock()-start;
	for(i='a';i<='z';i++) {
		s.str[0]=i;
		for(j='a';j<='z';j++) {
			s.str[1]=j;
			for(k='a';k<='z';k++) {
				s.str[2]=k;
				for(l='a';l<='z';l++) {
					s.str[3]=l;
					M(vec,push_back,&s);
				}
			}
		}
	}
	clock_t insert_time=clock()-start;
	printf("Size is %zu Insert time: %zu\n",M(vec,size),insert_time);
	start=clock();
	str_8_vector_iterator fpos=yaooc_find(str_8,M(vec,begin),M(vec,end),"zmzz");
	duration=clock()-start;
	printf("Found: %d pos: %zu Time to find: %zu\n",fpos != M(vec,end),fpos-(str_8_vector_iterator)M(vec,begin),duration);
	if(fpos != M(vec,end))
		printf("%s\n",fpos->str);

  str_8_vector_const_iterator z;
  for(z=M(vec,begin);z!=M(vec,end);z++)
    printf("%s\n",z->str);
  delete(vec);
}

#include <yaooc/string.h>
/*
	Same as above but using yaooc_string_t objects
*/
VECTOR_DEFINITION(yaooc_string,string_vector)
VECTOR_IMPLEMENTATION(yaooc_string,string_vector)
void test_string_vector()
{
	string_vector_pointer vec = new(string_vector);
	clock_t start=clock();
	yaooc_string_t s;
	newp_ctor(&s,yaooc_string,yaooc_string_ctor_n_chr,4,'a');
	int i,j,k,l;
//	M(vec,reserve,456976);
	printf("Size: %zu Cap: %zu\n",M(vec,size),M(vec,capacity));
	clock_t duration=clock()-start;
  yaooc_string_iterator si=M(&s,begin);
	for(i='a';i<='z';i++) {
		si[0]=i;
		for(j='a';j<='z';j++) {
			si[1]=j;
			for(k='a';k<='z';k++) {
				si[2]=k;
				for(l='a';l<='z';l++) {
					si[3]=l;
					M(vec,push_back,&s);
				}
			}
		}
	}
	clock_t insert_time=clock()-start;
	printf("Size is %zu Insert time: %zu\n",M(vec,size),insert_time);
	start=clock();
/*  string_vector_const_iterator svi;
  for(svi=M(vec,begin);svi!=M(vec,end);svi++)
    printf("%s\n",M(svi,c_str));*/
  si[1]='m';
	string_vector_iterator fpos=yaooc_find(yaooc_string,M(vec,begin),M(vec,end),&s);
	duration=clock()-start;
  printf("%s\n",M(&s,c_str));
	printf("Found: %d pos: %zu Time to find: %zu\n",fpos != (string_vector_iterator)M(vec,end),fpos-(string_vector_iterator)M(vec,begin),duration);
	if(fpos != M(vec,end))
		printf("%s\n",M(fpos,c_str));
  deletep(&s,yaooc_string);
  delete(vec);
}

test_function tests[]=
{
	test_long,
	test_str_8,
  test_string_vector
};

STD_MAIN(tests)
