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
#include <yaooc/regex.h>
#include <yaooc/pointer_bag.h>
#include "test_harness.h"

int yaooc_regex_regexec(const regex_t* re,const char* subject,int ofs,size_t n,regmatch_t* ov,int eflags);
void test_regex_regexec()
{
//  puts(tre_version());
  regex_t* re = malloc(sizeof(regex_t));
  char re_str[256];
  strcpy(re_str,"(\\w+)");
  if(regcomp(re,re_str,REG_EXTENDED)==0) {
    regmatch_t ov;
    const char* str="this   is   a  test";
    TEST("Return from regexec is 0",yaooc_regex_regexec(re,str,0,1,&ov,0)==0);
    TEST("Start is 0",ov.rm_so==0);
    TEST("End is 4",ov.rm_eo==4);
    TEST("Segment is 'this'",strncmp(str+ov.rm_so,"this",ov.rm_eo-ov.rm_so)==0);

    TEST("Return from regexec is 0",yaooc_regex_regexec(re,str,ov.rm_eo,1,&ov,0)==0);
    TEST("Start is 7",ov.rm_so==7);
    TEST("End is 9",ov.rm_eo==9);
    TEST("Segment is 'is'",strncmp(str+ov.rm_so,"is",ov.rm_eo-ov.rm_so)==0);
    TEST("Return from regexec is 0",yaooc_regex_regexec(re,str,ov.rm_eo,1,&ov,0)==0);

    TEST("Start is 12",ov.rm_so==12);
    TEST("End is 13",ov.rm_eo==13);
    TEST("Segment is 'a'",strncmp(str+ov.rm_so,"a",ov.rm_eo-ov.rm_so)==0);
    TEST("Return from regexec is 0",yaooc_regex_regexec(re,str,ov.rm_eo,1,&ov,0)==0);

    TEST("Start is 15",ov.rm_so==15);
    TEST("End is 19",ov.rm_eo==19);
    TEST("Segment is 'test'",strncmp(str+ov.rm_so,"test",ov.rm_eo-ov.rm_so)==0);
    TEST("Return from regexec is not 0",yaooc_regex_regexec(re,str,ov.rm_eo,1,&ov,0)!=0);
    regfree(re);
  }
  free(re);

}

typedef struct
{
	const char* re_str;
	const char* pat;
	int flags;
} regexp_match_test_info_t;

regexp_match_test_info_t regexp_match_test_cases[] =
{
	{ "apple",NULL,REG_EXTENDED },
	{ "/apple/","apple",REG_EXTENDED },
	{ "/apple/i","apple",REG_EXTENDED|REG_ICASE },
	{ "/apple/m","apple",REG_EXTENDED|REG_NEWLINE },
	{ "/apple/mi","apple",REG_EXTENDED|REG_NEWLINE|REG_ICASE },
	{ "/apple/im","apple",REG_EXTENDED|REG_NEWLINE|REG_ICASE },
	{ "/appleim",NULL,REG_EXTENDED },
	{ "//im",NULL,REG_EXTENDED },
  { NULL, NULL, 0 }
};

void test_match_info()
{
	char msg[128];
	regexp_match_test_info_t* rmti=regexp_match_test_cases;
	for(;rmti->re_str!=NULL;rmti++) {
		yaooc_regex_regexp_match_info_t rmi=yaooc_regex_is_re_string(rmti->re_str);
		sprintf(msg,"'%s' has re of '%s'",rmti->re_str,(rmti->pat == NULL ? "NULL" : rmti->pat));
		if(rmti->pat) {
			TEST(msg,strcmp(rmi.pattern_,rmti->pat)==0)
    } else
			TEST(msg,rmi.pattern_==rmti->pat);
		sprintf(msg,"'%s' has flags of '%x'",rmti->re_str,rmti->flags);
		TEST(msg,rmi.flags_)
	}
}

void test_regex()
{
  PB_INIT;
	printf("%" PRIULONG " %" PRIULONG "\n",sizeof(yaooc_matchdata_t),sizeof(yaooc_regex_t));
	yaooc_regex_pointer re=PB_SAVE(new(yaooc_regex));

	TEST("RE not ok",!M(re,bool));
	M(re,set_pattern_flags,"this( \\w+",REG_EXTENDED);
	TEST("RE not ok",!M(re,bool));
#ifdef __YAOOC_USE_TRE__
	M(re,set_pattern_flags,"this\\s+(\\w+)\\s+(\\d+)",REG_EXTENDED);
#else
	M(re,set_pattern_flags,"this\\s+(\\w+)\\s+([0-9]+)",REG_EXTENDED);
#endif
	TEST("RE is ok",M(re,bool));
	yaooc_matchdata_t* md=PB_SAVE(M(re,match,"should not match",0));
	TEST("Not matches",!M(md,bool))

	const char* subject="this is 27 and it should match";
	md=PB_SAVE(M(re,match,subject,0));
	TEST("matches",M(md,bool))
	TEST("number of matches is 3",M(md,size)==3)
	const char* scp=M(md,subject);
	TEST("subject is same as str",strcmp(scp,subject)==0);
	yaooc_string_t* s=PB_SAVE(M(md,at,0));
	TEST("String is \"this is 27\"",strcmp(M(s,c_str),"this is 27")==0);
	s=PB_SAVE(M(md,at,1));
	TEST("String is \"is\"",strcmp(M(s,c_str),"is")==0);

	PB_EXIT;
}

void test_next()
{
	PB_INIT;
	const char* numbers="  123  45 6 28 ignore this 9084 853 4444235 99924";
	const char* numbs[]={"123","45","6","28","9084","853","4444235","99924"};
#ifdef __YAOOC_USE_TRE__
	const char* re_str="(\\d+)";
#else
	const char* re_str="([0-9]+)";
#endif
	yaooc_regex_pointer re=PB_SAVE(new_ctor(yaooc_regex,yaooc_regex_ctor_ccs_int,re_str,REG_EXTENDED));
	TEST("RE OK",M(re,bool));

	yaooc_matchdata_pointer md = PB_SAVE(M(re,match,numbers,0));
	int nmatch=0;
	char msg[64];
	while(M(md,bool)) {
		yaooc_string_pointer s=PB_SAVE(M(md,at,0));
		sprintf(msg,"Matched %s",numbs[nmatch]);
		TEST(msg,strcmp(M(s,c_str),numbs[nmatch++])==0);
		M(re,match_next,md);
	}
	TEST("All numbers matched",nmatch==8);
	PB_EXIT;
}

test_function tests[]=
{
  test_regex_regexec,
	test_match_info,
	test_regex,
	test_next
};

STD_MAIN(tests)
