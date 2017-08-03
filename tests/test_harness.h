#ifndef __TEST_HARNESS_INCLUDED__
#define __TEST_HARNESS_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
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
#define TEST_ALL(a) for(unsigned i=0;i<sizeof(a)/sizeof(a[1]);i++) a[i]()

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
	int ntest=sizeof(test_array)/sizeof(test_array[0]); \
	if(argc == 1) \
		TEST_ALL(test_array); \
	else { \
		for(int i=1;i<argc;i++) { \
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
