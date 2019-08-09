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
#include <yaooc/string.h>
#include "test_harness.h"

void test_construtor()
{
	yaooc_string_t* s1=new(yaooc_string);
	TEST("Size is 0",M(s1,size) == 0);
	TEST("Emtpy is true",M(s1,empty));
	TEST("Capacity is 16",M(s1,capacity) == 16);
	TEST("c_str is ''",strcmp(M(s1,c_str),"") == 0);

	const char* temp="This is a test of a string longer than 16";
	yaooc_string_t* s2=new_ctor(yaooc_string,yaooc_string_ctor_ccs,temp);
	TEST("Size is 41",M(s2,size) == 41);
	TEST("Empty is not true",!M(s2,empty));
	TEST("Capacity is 64",M(s2,capacity) == 64);
	TEST("matched original",strcmp(M(s2,c_str),temp) == 0);
//	printf("%d %d %s\n",s2 M size(s2),s2 M capacity(s2),s2 M c_str(s2));

	yaooc_string_t* s3=new_ctor(yaooc_string,yaooc_string_ctor_ccs_n,temp,30);
	TEST("Size is 30",M(s3,size) == 30);
	TEST("Capacity is 32",M(s3,capacity) == 32);
	TEST("matched original",strncmp(M(s3,c_str),temp,30) == 0);

	yaooc_string_t* s4=new_ctor(yaooc_string,yaooc_string_ctor_n_chr,10,'c');
	printf("%zu %zu %s\n",M(s4,size),M(s4,capacity),M(s4,c_str));
	TEST("Size is 10",M(s4,size) == 10);
	TEST("Capacity is 16",M(s4,capacity) == 16);
	TEST("matched 10 c's'",strcmp(M(s4,c_str),"cccccccccc") == 0);
  delete(s1);
  delete(s2);
  delete(s3);
  delete(s4);
}

void test_substr()
{
	const char* str="this is the test string";

	yaooc_string_t* s1=new(yaooc_string);

	yaooc_string_t* s2 = M(s1,substr,0,20);
	TEST("Substr of empty string is empty string",M(s2,size) == 0);
  delete(s2);

	M(s1,append,str);
	TEST("String matches str",strcmp(M(s1,c_str),str)==0);
	s2 = M(s1,substr,0,5);
	TEST("substr 0 5",strcmp(M(s2,c_str),"this ")==0);
  delete(s2);

	s2 = M(s1,substr,0,-1);
	TEST("substr 0 -1 is entire string",strcmp(M(s2,c_str),str)==0);
  delete(s2);

  /*	s2 = M(s1,substr,100,-1);
	TEST("substr beyond end is empty string",M(s2,size) == 0);
	*/
	s2 = M(s1,substr,5,0);
	TEST("substr retrieving 0 chars is empty string",M(s2,size) == 0);
  delete(s2);
  delete(s1);
}

void test_append()
{
	const char* str1="This is";
	const char* str2=" a test";

	yaooc_string_t* s1=new(yaooc_string);
	TEST("s1 is empty",M(s1,size) == 0);

	M(s1,append,str1);
	TEST("s1 equal str1",strcmp(M(s1,c_str),str1)==0);

	M(s1,appendn,str2,2);
	TEST("s1 equal str1",strcmp(M(s1,c_str),"This is a")==0);

	M(s1,append,str2+2);
	TEST("s1 equal str1",strcmp(M(s1,c_str),"This is a test")==0);
  delete(s1);
}

void test_set()
{
  TESTCASE("SET");
  yaooc_string_t* s1=new(yaooc_string);
	TEST("s1 is empty",M(s1,size) == 0);

  M(s1,set,"Testing");

  TEST("s1 is \"Testing\"",strcmp(M(s1,c_str),"Testing")==0);

  M(s1,setn,"This is a test",10);
  TEST("s1 is \"This is a \"",strcmp(M(s1,c_str),"This is a ")==0);
  TEST("Size is 10",M(s1,size)==10);
  delete(s1);
}

void test_erase()
{
	yaooc_string_pointer s1=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"This is a test string");
//  yaooc_string_const_iterator epos=M(s1,begin)+8;

  TESTCASE("Erase");
	M(s1,erase,8);
	TEST("Erase 'a'",strcmp(M(s1,c_str),"This is  test string")==0);
	TEST("Size is 16",M(s1,size)==20);
/*	M(s1,erase,20,10);
	TEST("Erase",strcmp(M(s1,c_str),"This test string")==0);
	TEST("Size is 16",M(s1,size)==16);
	M(s1,erase,20,yaooc_string_npos);
	TEST("Erase",strcmp(M(s1,c_str),"This test string")==0);
	TEST("Size is 16",M(s1,size)==16);*/
	M(s1,erasen,8,yaooc_string_npos);
	printf("*** X%sX %zu ****\n",M(s1,c_str),M(s1,size));
  puts(M(s1,c_str));
	TEST("Erase",strcmp(M(s1,c_str),"This is ")==0);
	puts(M(s1,c_str));
	TEST("Size is 8",M(s1,size)==8);
	M(s1,erasen,0,1);
	TEST("Erase",strcmp(M(s1,c_str),"his is ")==0);
	TEST("Size is 7",M(s1,size)==7);

//	printf("*** %s %zu ****\n",M(s1,c_str),M(s1,size));
  delete(s1);
}

void test_replace()
{
  yaooc_string_pointer s=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"This is a test");
  M(s,replacen,5,2,"was",3);
  TEST("Replace 'is' with 'was'",strcmp(M(s,c_str),"This was a test")==0);
  M(s,replacen,0,200,"Replace entire string",500);
  TEST("Replace entire string",strcmp(M(s,c_str),"Replace entire string")==0);
  delete(s);
}

void test_up_down()
{
	const char* temp="aBcDeFGh";
	const char* temp_upper="ABCDEFGH";
	const char* temp_lower="abcdefgh";

	yaooc_string_t* s=new(yaooc_string);
	TEST("String is emtpy",M(s,size) == 0);
	yaooc_string_t* s_new=M(s,upcase);
	TEST("Upper case of empty string is empty string",M(s_new,size) == 0);
  delete(s_new);
	s_new=M(s,downcase);
	TEST("Lower case of empty string is empty string",M(s_new,size) == 0);
  delete(s_new);
  delete(s);
	s=new_ctor(yaooc_string,yaooc_string_ctor_ccs,temp);
	sprintf(output,"string is \"%s\"",temp);
	TEST(output,strcmp(M(s,c_str),temp)==0);
	s_new=M(s,upcase);
	sprintf(output,"string is \"%s\"",temp_upper);
	TEST(output,strcmp(M(s_new,c_str),temp_upper)==0);
  delete(s_new);
	s_new=M(s,downcase);
	sprintf(output,"string is \"%s\"",temp_lower);
	TEST(output,strcmp(M(s_new,c_str),temp_lower)==0);
  delete(s_new);
  delete(s);
}

void test_trim()
{
	const char* temp="   this is a test    ";
	yaooc_string_t* s=new_ctor(yaooc_string,yaooc_string_ctor_ccs,temp);
  yaooc_string_t* s_new=M(s,ltrim);
	TEST("ltrim: s_new='this is a test    '",strcmp(M(s_new,c_str),"this is a test    ")==0);
  delete(s_new);

	s_new=M(s,rtrim);
	TEST("rtrim: s_new='   this is a test'",strcmp(M(s_new,c_str),"   this is a test")==0);
  printf("*** X%sX\n",M(s_new,c_str));
  delete(s_new);

	s_new=M(s,trim);
	TEST("trim: s2='this is a test'",strcmp(M(s_new,c_str),"this is a test")==0);
  printf("X%sX\n",M(s_new,c_str));
  delete(s_new);
  delete(s);

	const char* temp2="Does not need trimming";
	s=new_ctor(yaooc_string,yaooc_string_ctor_ccs,temp2);
  s_new=M(s,ltrim);
	TEST("ltrim of string that does not need ltrimming is same string",op_eq_static(s,s_new,yaooc_string));
  delete(s_new);

  s_new=M(s,rtrim);
	TEST("rtrim of string that does not need rtrimming is same string",op_eq_static(s,s_new,yaooc_string));
  delete(s_new);

  s_new=M(s,trim);
	TEST("trim of string that does not need trimming is same string",op_eq_static(s,s_new,yaooc_string));
  delete(s_new);
  delete(s);

  s=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"                    ");
  s_new=M(s,ltrim);
  TEST("ltrim of all blank string has size 0",M(s_new,size)==0);
  TEST("ltrim of all blank string is ''",strcmp(M(s_new,c_str),"")==0);
  delete(s_new);

  s_new=M(s,rtrim);
  TEST("rtrim of all blank string has size 0",M(s_new,size)==0);
  TEST("ltrim of all blank string is ''",strcmp(M(s_new,c_str),"")==0);
  delete(s_new);

  delete(s);
}
#if 0
void test_squeeze()
{
	char* temp="thiiiiiiis is aaaaaaa         teeeeeeeeesssssssssst";
	yaooc_string_t* s1=new_ctor(yaooc_string,yaooc_string_ctor_ccs,temp);
	yaooc_string_t* s2=new_copy(s1);
  M(s2,squeeze,"ae");
	TEST("Squeeze: 'ae'",strcmp(M(s2,c_str),"thiiiiiiis is a         tesssssssssst")==0);
  delete(s2);

  s2=new_copy(s1);
	M(s2,squeeze," ");
	TEST("Squeeze: ' '",strcmp(M(s2,c_str),"thiiiiiiis is aaaaaaa teeeeeeeeesssssssssst")==0);
  delete(s2);

  s2=new_copy(s1);
	M(s2,squeeze,"m");
	TEST("Squeeze: 'm' (not in string) -- return same string",strcmp(M(s2,c_str),temp)==0);
  delete(s2);

  s2=new_copy(s1);
	M(s2,squeeze,"");
	TEST("Squeeze: '' (squeeze everything)",strcmp(M(s2,c_str),"this is a test")==0);
  delete(s2);

  s2=new_copy(s1);
	M(s2,squeeze,NULL);
	TEST("Squeeze: NULL (squeeze everything)",strcmp(M(s2,c_str),"this is a test")==0);
  delete(s2);

  delete(s1);
}
#endif
void test_find()
{
	const char* str=
/*          1         2         3         4         5         6         7         8         9
  0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789 */
 "needle.  What needle?  The needle in the haystack.  Can someone find the needle?  Who found the needle";

	yaooc_string_t* s1=new_ctor(yaooc_string,yaooc_string_ctor_ccs,str);
	size_t pos=M(s1,findstr,"Needle",0);
	TEST("findstr(\"Needle\",0) == npos",pos==yaooc_string_npos);
	pos=M(s1,findstr,"needle",0);
	TEST("findstr(\"needle\",0) found at 0",pos==0);
	pos=M(s1,findstr,"needle",27);
	TEST("findstr(\"needle\",27) found at 27",pos==27);
	pos=M(s1,findstr,"needle",28);
	TEST("findstr(\"needle\",28) found at 73",pos==73);

	pos=M(s1,rfindstr,"needle",yaooc_string_npos);
  printf("Z%zuZ\n",pos);
	TEST("rfindstr(\"needle\",string_npos) found at 96",pos==96);
	pos=M(s1,rfindstr,"needle",97);
	TEST("rfindstr(\"needle\",97) found at 73",pos==73);
	pos=M(s1,rfindstr,"needle",60);
	TEST("rfindstr(\"needle\",27) found at 27",pos==27);
	pos=M(s1,rfindstr,"needle",5);
	TEST("rfindstr(\"needle\",5) not found ",pos==yaooc_string_npos);
	pos=M(s1,rfindstr,"needle",4);
	TEST("rfindstr(\"needle\",27) not found",pos==yaooc_string_npos);

	pos=M(s1,findchr,'H',yaooc_string_npos);
	TEST("findchr('H',string_npos) not found",pos==yaooc_string_npos);
	pos=M(s1,findchr,'h',0);
//	printf("**** %zd\n",pos);
	TEST("findchr('h',0) found at 10",pos==10);
	pos=M(s1,findchr,'h',33);
	TEST("findchr('h',33) found at 38",pos==38);
	pos=M(s1,findchr,'h',83);
	TEST("findchr('h',83) found at 83",pos==83);
	pos=M(s1,findchr,'h',94);
	TEST("findchr('h',94) not found",pos==yaooc_string_npos);
	pos=M(s1,rfindchr,'H',yaooc_string_npos);
	TEST("rfindchr('H',string_npos) not found",pos==yaooc_string_npos);
	pos=M(s1,rfindchr,'h',yaooc_string_npos);
	TEST("rfindchr('h',string_npos) found at 93",pos==93);
	printf("BB %zu %zu\n",pos,(size_t)-1);
	pos=M(s1,rfindchr,'h',33);
	TEST("rfindchr('h',33) found at 24",pos==24);
	printf("**** %zu\n",pos);
	pos=M(s1,rfindchr,'h',92);
	TEST("rfindchr('h',92) found at 83",pos==83);
	pos=M(s1,rfindchr,'h',9);
	TEST("rfindchr('h',9) not found",pos==yaooc_string_npos);
//	printf("%zd %zd\n",pos,yaooc_string_npos);

  delete(s1);
}

void test_iterator()
{
	yaooc_string_t* s1=new(yaooc_string);

	TEST("Begin of empty sting is same as end",M(s1,begin)==M(s1,end));
	TEST("Const Begin of empty sting is same as const end",M(s1,cbegin)==M(s1,cend));

	M(s1,append,"The rain in spain falls mainly in Spain");
	yaooc_string_const_iterator i = M(s1,begin);
	optr=output;
	for(i= M(s1,begin);i!= M(s1,end);optr++,i++)
		*optr=*i;
	*optr=0;
	TEST("String iteration",strcmp(output,"The rain in spain falls mainly in Spain")==0);
	yaooc_string_iterator j = M(s1,begin)+12;
	*j = 'S';
	TEST("Character at postion 12 changed",strcmp(M(s1,c_str),"The rain in Spain falls mainly in Spain")==0);
	puts(M(s1,c_str));

  delete(s1);
}

void test_resize_shrink()
{
	char* temp=
/*          1         2         3         4         5         6         7         8         9
   0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789 */
	"This should be a long string.  I would make it longer but I'm tired of typing";
	yaooc_string_t* s1=new_ctor(yaooc_string,yaooc_string_ctor_ccs,temp);

	TEST("Length size is same size as temp string",M(s1,size)==strlen(temp));
	TEST("Capacity is 128",M(s1,capacity)==128);

	M(s1,resize_value,strlen(temp),'a');
	TEST("Resize to same length does not change length",M(s1,size)==strlen(temp));
	TEST("Resize to same length does not change capacity",M(s1,capacity)==128);
	TEST("Resize to same length does not change string",strcmp(M(s1,c_str),temp)==0);

	M(s1,resize_value,100,'a');
	TEST("Resize to greater than length but less than capacity: Size=100",M(s1,size)==100);
	TEST("Resize to greater than length but less than capacity: Capacity=128",M(s1,capacity)==128);
	yaooc_string_t* s2=M(s1,substr,0,strlen(temp));
	TEST("Resize to greater than length but less than capacity, string begins with original",strcmp(M(s2,c_str),temp)==0);
  delete(s2);

	s2=M(s1,substr,strlen(temp),yaooc_string_npos);
	TEST("Resize to greater than length but less than capacity, ends with pad character",
				strcmp(M(s2,c_str),"aaaaaaaaaaaaaaaaaaaaaaa")==0);
  delete(s2);

	M(s1,resize_value,150,'b');
	TEST("Resize to greater than capacity",M(s1,size)==150);
	TEST("Resize to greater than capacity",M(s1,capacity)==256);
	s2=M(s1,substr,0,strlen(temp));
	TEST("Resize to greater than , string begins with original",strcmp(M(s2,c_str),temp)==0);
  delete(s2);

	s2=M(s1,substr,strlen(temp),yaooc_string_npos);
	TEST("Resize to greater than length but less than capacity, ends with pad character",
				strcmp(M(s2,c_str),"aaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")==0);

	M(s1,shrink_to_fit);
	TEST("After shrink size is 150",M(s1,size)==150);
	TEST("Capacity is 256",M(s1,capacity)==256);
	TEST("String not changed",strcmp(M(s1,c_str),"This should be a long string.  I would make it longer but I'm tired of typingaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")==0);

  printf("&&&&&  %zu %zu %s\n",M(s1,size),M(s1,capacity),M(s1,c_str));
	M(s1,resize_value,100,'a');
	TEST("Resize to 100 changes size to 100",M(s1,size)==100);
	TEST("Resize to 100 does not change capacity",M(s1,capacity)==256);
  printf("&&&&&  %zu %zu %s\n",M(s1,size),M(s1,capacity),M(s1,c_str));
	TEST("String changed",strcmp(M(s1,c_str),"This should be a long string.  I would make it longer but I'm tired of typingaaaaaaaaaaaaaaaaaaaaaaa")==0);

	M(s1,shrink_to_fit);
	TEST("After shrink size is 100",M(s1,size)==100);
	TEST("capacity to 128",M(s1,capacity)==128);
	TEST("String not changed",strcmp(M(s1,c_str),"This should be a long string.  I would make it longer but I'm tired of typingaaaaaaaaaaaaaaaaaaaaaaa")==0);

	M(s1,resize_value,0,'b');
	TEST("Resize string to 0 length.  Size is 0",M(s1,size)==0);
	TEST("Resize string to 0 length.  Capacity is 128",M(s1,capacity)==128);
	TEST("Resize string to 0 length.  sting is ''",strcmp(M(s1,c_str),"")==0);

	M(s1,shrink_to_fit);
	TEST("Shrink to fit doesn't change size",M(s1,size)==0);
	TEST("Shrink change capacity to 16",M(s1,capacity)==16);
	TEST("String not changed",strcmp(M(s1,c_str),"")==0);

  delete(s1);
  delete(s2);
}

void test_split()
{
  TESTCASE("Split");
  yaooc_string_pointer str=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"This  is   a    test    ");
  yaooc_string_vector_pointer sv=M(str,split," ",3);
  TEST("Array size is 4",M(sv,size)==4);
  printf("%zu\n",M(sv,size));
  yaooc_string_vector_const_iterator isv;
  for(isv=M(sv,begin);isv!=M(sv,end);isv++) {
    printf("%s\n",M(isv,c_str));
  }
  delete(str);
  delete(sv);
}

void test_match()
{
	TESTCASE("Match");
	yaooc_string_pointer str=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"This is a test");
	TEST("Does not match /IS/",M(str,match,"/IS/")==false);
	TEST("Does match /IS/i",M(str,match,"/IS/i")==true);
	delete(str);
}

void test_sub()
{
	TESTCASE("Sub");
	yaooc_string_pointer str=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"This is a test");
	M(str,sub_," is"," was");
	TEST("'is' repaced with 'was'",strcmp(M(str,c_str),"This was a test")==0);

	M(str,set,"This   is a test");
	puts(M(str,c_str));
	M(str,sub_," "," "); // Replace multiple spaces with single space */
	TEST("Multiple consecutive spaces replaced with single space",strcmp(M(str,c_str),"This is a test")==0);
	puts(M(str,c_str));
	delete(str);
}

void test_gsub()
{
	TESTCASE("Gsub");
	yaooc_string_pointer str=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"This is a test");
	M(str,gsub_,"/is/i","was");
	TEST("'is' repaced with 'was'",strcmp(M(str,c_str),"Thwas was a test")==0);

	M(str,set,"This<this will>is<be>a<replaced>test");
	M(str,gsub_,"/<.*?>/"," ");
	puts(M(str,c_str));
	TEST("Replace things in < > with a single space",strcmp(M(str,c_str),"This is a test")==0);
	M(str,set,"aaaaa");
	M(str,gsub_,"a","ab");
	TEST("replace 'a' with 'ab'",strcmp(M(str,c_str),"ababababab")==0);
	puts(M(str,c_str));
	delete(str);
}

void test_start_end()
{
	TESTCASE("Starts with");
	yaooc_string_pointer str=new_ctor(yaooc_string,yaooc_string_ctor_ccs,"This is a test");
  TEST("Starts with \"This\"",M(str,starts_with,"This"));
  TEST("Starts with entire string",M(str,starts_with,"This is a test"));
  TEST("Does not start with \"this\"",!M(str,starts_with,"this"));
  TEST("Does not start with a longer string",!M(str,starts_with,"This is a test "));
  TEST("Does not start with a zero length string",!M(str,starts_with,""));
	TESTCASE("Ends with");
  TEST("Ends with \"test\"",M(str,ends_with,"test"));
  TEST("Ends with entire string",M(str,ends_with,"This is a test"));
  TEST("Does not start with a longer string",!M(str,ends_with,"This is a test "));
  TEST("Does not end with \"Test\"",!M(str,ends_with,"Test"));
  TEST("Does not end with a zero length string",!M(str,ends_with,""));
	delete(str);
}

void test_vector()
{
  yaooc_string_t temp;
  newp(&temp,yaooc_string);
  yaooc_string_vector_t* sv=new(yaooc_string_vector);
  M(&temp,set,"testing");
  M(&temp,append,"and more testing to make length long");
  int i;
  for(i=0;i<255;i++)
    M(sv,push_back,&temp);
  TEST("String vector size is 256",M(sv,size)==255);
  STREAM(cout,O_OBJ(yaooc_string,*M(sv,at,254)));
  delete(sv);
  deletep(&temp,yaooc_string);
}

test_function tests[]=
{
	test_construtor,
	test_substr,
	test_append,
  test_set,
	test_erase,
  test_replace,
	test_up_down,
	test_trim,
//	test_squeeze,
	test_find,
	test_iterator,
	test_resize_shrink,
  test_split,
	test_match,
	test_sub,
	test_gsub,
  test_start_end,
  test_vector,
};

STD_MAIN(tests)
