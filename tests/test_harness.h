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

#ifndef __TEST_HARNESS_INCLUDED__
#define __TEST_HARNESS_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef void(*test_function)(void);

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
int nFail = 0;
int nPass = 0;
int nTotalFail=0;
int nTotalPass=0;

#define SUMMARY  printf("  Passed: %d Failed: %d\n\n",nPass,nFail)
#define TEST(S,T) { printf("  %s . .",S); if((T)) { nPass++; puts("pass"); } else { nFail++; puts("fail"); } fflush(stdout); }
#define TESTCASE(S) if(nFail || nPass) SUMMARY; puts(S); \
	nTotalFail+=nFail;nTotalPass+=nPass; \
	nFail=0;nPass=0;
#define FINAL_SUMMARY  if(nFail || nPass) SUMMARY; \
	nTotalFail+=nFail;nTotalPass+=nPass; \
	printf("%d Passed\n%d Failed\n",nTotalPass,nTotalFail)
#define TEST_ALL(test_funcs) for(unsigned i=0;i<sizeof(test_funcs)/sizeof(test_funcs[1]);i++) \
      { optr=NULL; test_funcs[i](); }

char* output;
char* optr;
#define STD_MAIN(test_array) \
int main(int argc,char*argv[]) \
{ \
	setbuf(stdout,NULL); \
	setbuf(stderr,NULL); \
	output=(char*)malloc(10240);\
	optr=NULL; \
	GC_INIT(); \
  srand(time(NULL)); \
	int ntest=sizeof(test_array)/sizeof(test_array[0]); \
	if(argc == 1) \
		{ TEST_ALL(test_array); }\
	else { \
		for(int i=1;i<argc;i++) { \
      optr=NULL; \
			int itest=atoi(argv[i]); \
			if(itest >=0 && itest < ntest) \
				test_array[itest](); \
			else \
				printf("No test for %d\n",itest); \
		} \
	} \
	FINAL_SUMMARY; \
	free(output); \
	return 0; \
}

#endif
