#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <yaooc/vector.h>
#include <yaooc/algorithm.h>
#include <yaooc/string.h>
#include <time.h>

extern int count;
#include "demo_def.inc"
#include "test_harness.h"

VECTOR_DEFINITION(int64)  /* Normally in header file */
VECTOR_IMPLEMENTATION(int64) /* Normally in c source file (.c) */

void test_int64()
{
	int64_vector_pointer vi64=new(int64_vector);
	int64_t numbers[]={ 9,10, -2, 44, 55};
	size_t n=sizeof(numbers)/sizeof(numbers[0]);
	size_t i;
	for(i=0;i<n;i++)
		M(vi64,push_back,numbers+i);
	int64_vector_const_iterator ivi;
	for(ivi=M(vi64,begin);ivi!=M(vi64,end);ivi++)
		printf("%ld ",*ivi);
	puts("\n");
  delete(vi64);
}

/*
  A 8 character string type
*/
/*
typedef char str_8_t[8];

void str_8_default_ctor(pointer p)
{
	*(char*)p=0;
}

bool str_8_less_than_compare(const_pointer v1,const_pointer v2)
{
	return strcmp((const char*)v1,(const char*)v2) < 0;
}

DEFINE_TYPE_INFO(str_8_t,str_8_ti,str_8_default_ctor,NULL,NULL,NULL,str_8_less_than_compare,NULL,NULL)*/
/*const type_info_t __str_8_ti =
{
	sizeof(str_8_t),
	str_8_default_ctor, // ctor
	NULL,
	NULL,
	NULL,
	str_8_less_than_compare,
	NULL,
	NULL
};
const type_info_t* const str_8_ti=&__str_8_ti;
*/
/*
	Same as test_long but using VECTOR macros
*/

typedef char str_8_t[8];
void str_8_default_ctor(pointer p)
{
	*(char*)p=0;
}
bool str_8_less_than_compare(const_pointer v1,const_pointer v2)
{
	return strcmp((const char*)v1,(const char*)v2) < 0;
}
DEFINE_TYPE_INFO(str_8,str_8_default_ctor,NULL,NULL,NULL,str_8_less_than_compare,NULL,NULL)

VECTOR_DEFINITION(str_8)
VECTOR_IMPLEMENTATION(str_8)
void test_str_8()
{
  printf("Size is %zu\n",sizeof(str_8_t));
	str_8_vector_pointer vec = new(str_8_vector);
	clock_t start=clock();
	str_8_t s;
	s[4]=0;
	int i,j,k,l;
	M(vec,reserve,456976);
	printf("Size: %zu Cap: %zu\n",M(vec,size),M(vec,capacity));
	clock_t duration=clock()-start;
	for(i='a';i<='z';i++) {
		s[0]=i;
		for(j='a';j<='z';j++) {
			s[1]=j;
			for(k='a';k<='z';k++) {
				s[2]=k;
				for(l='a';l<='z';l++) {
					s[3]=l;
					M(vec,push_back,s);
				}
			}
		}
	}
	clock_t insert_time=clock()-start;
	printf("Size is %zu Insert time: %zu\n",M(vec,size),insert_time);
	start=clock();
	str_8_vector_iterator fpos=yaooc_find(str_8_ti,M(vec,cbegin),M(vec,cend),"zmzz");
	duration=clock()-start;
	printf("Found: %d pos: %zu Time to find: %zu\n",fpos != M(vec,end),fpos-M(vec,begin),duration);
	if(fpos != M(vec,end))
		printf("%s\n",*fpos);

  str_8_vector_const_iterator z;
  for(z=M(vec,cbegin);z!=M(vec,cend);z++)
    printf("%s\n",*z);
  delete(vec);
}

/*
	Same as above but using yaooc_string_t objects
*/
VECTOR_DEFINITION(yaooc_string)
VECTOR_IMPLEMENTATION(yaooc_string)
void test_string_vector()
{
	yaooc_string_vector_pointer vec = new(yaooc_string_vector);
	clock_t start=clock();
	yaooc_string_t s;
	newp_ctor(&s,yaooc_string,yaooc_string_ctor_chr_n,'a',4);
	int i,j,k,l;
	M(vec,reserve,456976);
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
//  yaooc_string_vector_const_iterator svi;
//  for(svi=M(vec,cbegin);svi!=M(vec,cend);svi++)
//    printf("%s\n",M(svi,c_str));
  si[1]='m';
	yaooc_string_vector_iterator fpos=yaooc_find(yaooc_string_ti,M(vec,cbegin),M(vec,cend),&s);
	duration=clock()-start;
  printf("%s\n",M(&s,c_str));
	printf("Found: %d pos: %zu Time to find: %zu\n",fpos != M(vec,end),fpos-M(vec,begin),duration);
	if(fpos != M(vec,end))
		printf("%s\n",M(fpos,c_str));
  deletep(&s,yaooc_string);
  delete(vec);
}

test_function tests[]=
{
	test_int64,
	test_str_8,
  test_string_vector
};

STD_MAIN(tests)
