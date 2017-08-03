#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/regex.h>
#include <yaooc/garbage_bag.h>
#include "test_harness.h"


void test_regex()
{
  GB_INIT;
	printf("%zu\n",sizeof(yaooc_regex_t));
	yaooc_regex_pointer re=GB_SAVE(new(yaooc_regex));

	TEST("RE not ok",M(re,bad));
	M(re,set_pattern,"this( \\w+",PCRE2_EXTENDED);
	TEST("RE not ok",M(re,bad));
	M(re,set_pattern,"this\\s+(\\w+)\\s+(\\d+)",PCRE2_EXTENDED);
	TEST("RE is ok",M(re,good));

	yaooc_matchdata_t* md=GB_SAVE(M(re,match,"should not match",0));
	TEST("Not matches",M(md,bad))

	const char* subject="this is 27 and it should match";
	md=GB_SAVE(M(re,match,subject,0));
	TEST("matches",M(md,good))
	TEST("number of matches is 3",M(md,size)==3)
	yaooc_string_const_pointer scp=M(md,subject);
	TEST("subject is same as str",strcmp(M(scp,c_str),subject)==0);
	char* s=GB_SAVE(M(md,at,0));
	TEST("String is \"this is 27\"",strcmp(s,"this is 27")==0);
	s=GB_SAVE(M(md,at,1));
	TEST("String is \"is\"",strcmp(s,"is")==0);

	GB_EXIT;
}

void test_next()
{
	GB_INIT;
	const char* numbers="  123  45 6 28 ignore this 9084 853 4444235 99924";
	const char* numbs[]={"123","45","6","28","9084","853","4444235","99924"};
	const char* re_str="(\\d+)";
	yaooc_regex_pointer re=GB_SAVE(new_ctor(yaooc_regex,yaooc_regex_ctor_pat_flags,re_str,PCRE2_EXTENDED));
	TEST("RE OK",M(re,good));

	yaooc_matchdata_pointer md = GB_SAVE(M(re,match,numbers,0));
	char* s=NULL;
	int nmatch=0;
	char msg[64];
	while(M(md,good)) {
		s=GB_SAVE(M(md,at,0));
		sprintf(msg,"Matched %s",numbs[nmatch]);
		TEST(msg,strcmp(s,numbs[nmatch++])==0);
		M(re,match_next,md);
	}
	TEST("All numbers matched",nmatch==8);
	GB_EXIT;
}

test_function tests[]=
{
	test_regex,
	test_next
};

STD_MAIN(tests)
