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
#include <yaooc/base_parser.h>

#include "test_harness.h"

bool do_crlf=false;
bool do_c_comment=false;
bool do_cpp_comment=false;
bool do_shell_comment=false;
bool test_yaooc_base_parser_whitespace(pointer p,yaooc_terminal_t* r)
{
  *r=default_terminal(p);
  yaooc_terminal_t temp;
  while(true) {
    if(!yaooc_base_parser_space(p,&temp))
      if(!(do_crlf && yaooc_base_parser_crlf(p,&temp)))
        if(!(do_c_comment && yaooc_base_parser_c_comment(p,&temp)))
          if(!(do_cpp_comment && yaooc_base_parser_cpp_comment(p,&temp)))
            if(!(do_shell_comment && yaooc_base_parser_shell_comment(p,&temp)))
              break;
  }
  r->end_=yaooc_base_parser_current_pos(p);
  return r->beg_ != r->end_;
}

void test_parser_position()
{
  parser_position_t pp;
  const char* str="this is a test";
  pp.pos_=str;
  pp.line_no_=27;
  parser_position_stack_pointer sp=new(parser_position_stack);
  TEST("SP size is 0",M(sp,size)==0);
  M(sp,push,&pp);
  pp.pos_+=1;
  pp.line_no_++;
  M(sp,push,&pp);
  TEST("SP size is 2",M(sp,size)==2);
  TEST("TOP is str+1",M(sp,top)->pos_==str+1);
  M(sp,pop);
  TEST("TOP is str",M(sp,top)->pos_==str);
  M(sp,pop);
  TEST("SP is empty",M(sp,empty));
  delete(sp);
}

void test_whitespace()
{
  // Never do this in production application
  bool (*old_ws)(pointer, yaooc_terminal_t*)=yaooc_base_parser_class_table.whitespace;
  yaooc_base_parser_class_table.whitespace=test_yaooc_base_parser_whitespace;

  yaooc_terminal_t ws;
  yaooc_base_parser_pointer bp=new(yaooc_base_parser);
  const char* str="   \r\n   /* C comment */ \r\n  // cpp comment \r\n  # shell comment\r\n";
  M(bp,set_parse_string,str);
  M(bp,whitespace,&ws);
  TEST("Offset is 3",bp->current_pos_-str == 3);
  M(bp,whitespace,&ws);
  TEST("Offset is still 3",bp->current_pos_-str == 3);
  do_crlf=true;
  M(bp,whitespace,&ws);
  TEST("Offset is 8",bp->current_pos_-str == 8);
  do_c_comment=true;
  M(bp,whitespace,&ws);
  TEST("Offset is 28",bp->current_pos_-str == 28);
  do_cpp_comment=true;
  M(bp,whitespace,&ws);
  TEST("Offset is 47",bp->current_pos_-str == 47);
  printf("%zu X%s\n",bp->current_pos_-str,bp->current_pos_);
  do_shell_comment=true;
  M(bp,whitespace,&ws);
  TEST("Offset is 64",bp->current_pos_-str == 64);
  TEST("At end of string",M(bp,eos));
  M(bp,set_parse_string,str);
  M(bp,whitespace,&ws);
  TEST("After reset, Offset is 64",bp->current_pos_-str == 64);
  TEST("After reset, At end of string",M(bp,eos));
  delete(bp);

  yaooc_base_parser_class_table.whitespace=old_ws;
}

void test_chr()
{
  yaooc_base_parser_pointer bp=new(yaooc_base_parser);
  const char* str="a test";
  yaooc_terminal_t r;
  M(bp,set_parse_string,str);
  TEST("Matches 'a'",M(bp,chr,'a',&r));
  TEST("Offset is 2",bp->current_pos_-str == 2);
  TEST("Does not matches 'b'",!M(bp,chr,'b',&r));
  TEST("Offset is 2",bp->current_pos_-str == 2);

  TEST("Matches one of \"stu\"",M(bp,chr_choices,"stu"));
  TEST("Offset is 3",bp->current_pos_-str == 3);
  TEST("Does not match one of \"stu\"",M(bp,chr_choices,"stu"));
  TEST("Offset is 3",bp->current_pos_-str == 3);
  delete(bp);
}

void test_str()
{
  yaooc_base_parser_pointer bp=new(yaooc_base_parser);
  const char* str="this is some test";
  M(bp,set_parse_string,str);
  yaooc_terminal_t r;
  TEST("Matches \"this\"",M(bp,str,"this",&r));
  printf("%zu X%s\n",bp->current_pos_-str,bp->current_pos_);
  TEST("Offset is 5",bp->current_pos_-str == 5);
  TEST("Does not match \"this\"",!M(bp,str,"this",&r));
  TEST("Offset is 5",bp->current_pos_-str == 5);

  TEST("Matches item 1 of \"this\",\"is\",\"a\",\"test\"",M(bp,str_choices,"this","is","a","test",NULL)==1);
  TEST("Offset is 8",bp->current_pos_-str == 8);
  TEST("Does not match any of \"this\",\"is\",\"a\",\"test\"",M(bp,str_choices,"this","is","a","test",NULL)==-1);
  TEST("Offset is 8",bp->current_pos_-str == 8);
  delete(bp);
}

void test_integer()
{
  yaooc_base_parser_pointer bp=new(yaooc_base_parser);
  const char* str="12 12. 12e3 +324 -0002";
  char* ts;
  M(bp,set_parse_string,str);

  yaooc_terminal_t r;
  M(bp,integer,&r);
  TEST("12 is integer",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is 12",strcmp(ts,"12")==0);
  if(ts) delete(ts);
  TEST("Offset is 3",bp->current_pos_-str==3);
  M(bp,integer,&r);
  TEST("12. is not an integer",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  bp->current_pos_+=4;
  TEST("Offset is 7",bp->current_pos_-str==7);
  M(bp,integer,&r);
  TEST("12e3 is not integer",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  bp->current_pos_+=5;
  TEST("Offset is 12",bp->current_pos_-str==12);
  M(bp,integer,&r);
  TEST("+324 is an integer",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is +324",strcmp(ts,"+324")==0);
  if(ts) delete(ts);
  TEST("Offset is 17",bp->current_pos_-str==17);
  M(bp,integer,&r);
  TEST("-0002 is an integer",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is -0002",strcmp(ts,"-0002")==0);
  if(ts) delete(ts);

  delete(bp);
}

void test_hexinteger()
{
  yaooc_base_parser_pointer bp=new(yaooc_base_parser);
  const char* str="12 0X12 0xG12 0x12e3 +0x324 -0x0002 0x 0x1 0x-3";
  char* ts;
  M(bp,set_parse_string,str);

  yaooc_terminal_t r;
  M(bp,hexinteger,&r);
  TEST("12 is not a hexinteger",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  bp->current_pos_+=3;
  M(bp,hexinteger,&r);
  TEST("0X12 is a hexinteger",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is 0X12",ts == NULL ? false : strcmp(ts,"0X12")==0);
  if(ts) delete(ts);
  TEST("Offset is 8",bp->current_pos_-str==8);
  M(bp,hexinteger,&r);
  TEST("0X12. is not hexinteger",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  bp->current_pos_+=6;
  TEST("Offset is 14",bp->current_pos_-str==14);
  M(bp,hexinteger,&r);
  TEST("0x12e3 is hexinteger",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts == NULL ? false : strcmp(ts,"0x12e3")==0);
  if(ts) delete(ts);
  TEST("Offset is 21",bp->current_pos_-str==21);
  M(bp,hexinteger,&r);
  TEST("+0x324 is not ahexinteger",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  bp->current_pos_+=7;
  TEST("Offset is 28",bp->current_pos_-str==28);
  M(bp,hexinteger,&r);
  TEST("-0x0002 is not a hexinteger",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  bp->current_pos_+=8;
  TEST("Offset is 36",bp->current_pos_-str==36);
  M(bp,hexinteger,&r);
  TEST("0x is not a hexinteger",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  bp->current_pos_+=3;
  TEST("Offset is 39",bp->current_pos_-str==39);
  M(bp,hexinteger,&r);
  TEST("0x1 is hexinteger",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts == NULL ? false : strcmp(ts,"0x1")==0);
  if(ts) delete(ts);
  TEST("Offset is 43",bp->current_pos_-str==43);
  M(bp,hexinteger,&r);
  TEST("0x-3 is not a hexinteger",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  delete(bp);
}

void test_real()
{
  yaooc_base_parser_pointer bp=new(yaooc_base_parser);
  const char* str="12 12. 12e3 +324 .002 -.02 -1.3 +3e-3 +3.e-3 -3.2e4 -3e3x";
  char* ts;
  M(bp,set_parse_string,str);

  yaooc_terminal_t r;
  M(bp,real,&r);
  TEST("12 is not a real",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  bp->current_pos_+=3;
  TEST("Offset is 3",bp->current_pos_-str==3);
  M(bp,real,&r);
  TEST("12. is a real",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is 12.",strcmp(ts,"12.")==0);
  if(ts) delete(ts);
  M(bp,real,&r);
  TEST("12e3 is a real",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is 12e3",strcmp(ts,"12e3")==0);
  if(ts) delete(ts);
  M(bp,real,&r);
  TEST("+324 is not a real",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is 12.",ts==NULL);
  if(ts) delete(ts);
  bp->current_pos_+=5;
  M(bp,real,&r);
  TEST(".002 is a real",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is .002",strcmp(ts,".002")==0);
  if(ts) delete(ts);
  M(bp,real,&r);
  TEST("-.02 is a real",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is -.02",strcmp(ts,"-.02")==0);
  if(ts) delete(ts);
  TEST("Offset is 27",bp->current_pos_-str==27);
  M(bp,real,&r);
  TEST("-1.3 is a real",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is -1.3",strcmp(ts,"-1.3")==0);
  if(ts) delete(ts);
  TEST("Offset is 32",bp->current_pos_-str==32);
  M(bp,real,&r);
  TEST("+3e-3 is a real",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is +3e-3",strcmp(ts,"+3e-3")==0);
  if(ts) delete(ts);
  TEST("Offset is 38",bp->current_pos_-str==38);
  M(bp,real,&r);
  TEST("+3.e-3 is a real",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is +3.e-3",strcmp(ts,"+3.e-3")==0);
  if(ts) delete(ts);
  TEST("Offset is 45",bp->current_pos_-str==45);
  M(bp,real,&r);
  TEST("-3.2e4 is a real",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is -3.2e4",strcmp(ts,"-3.2e4")==0);
  if(ts) delete(ts);
  TEST("Offset is 52",bp->current_pos_-str==52);
  M(bp,real,&r);
  TEST("-3e3x is not a real",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  delete(bp);
}

void test_ident()
{
  yaooc_base_parser_pointer bp=new(yaooc_base_parser);
  const char* str="a 3a a3a _ident7 a-7 m_m";
  char* ts;
  M(bp,set_parse_string,str);

  yaooc_terminal_t r;
  M(bp,ident,&r);
  TEST("a is an ident",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is a",strcmp(ts,"a")==0);
  if(ts) delete(ts);
  TEST("Offset is 2",bp->current_pos_-str==2);
  M(bp,ident,&r);
  TEST("3a is not an ident",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  bp->current_pos_+=3;
  TEST("Offset is 5",bp->current_pos_-str==5);
  M(bp,ident,&r);
  TEST("a3a is an ident",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is a3a",strcmp(ts,"a3a")==0);
  if(ts) delete(ts);
  TEST("Offset is 9",bp->current_pos_-str==9);
  M(bp,ident,&r);
  TEST("_ident7 is an ident",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is _ident7",strcmp(ts,"_ident7")==0);
  if(ts) delete(ts);
  TEST("Offset is 17",bp->current_pos_-str==17);
  M(bp,ident,&r);
  TEST("a is an ident",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is a",strcmp(ts,"a")==0);
  if(ts) delete(ts);
  TEST("Offset is 18",bp->current_pos_-str==18);
  M(bp,ident,&r);
  TEST("-7 is not an ident",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  bp->current_pos_+=3;
  TEST("Offset is 21",bp->current_pos_-str==21);
  M(bp,ident,&r);
  TEST("m_m is an ident",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is m_m",strcmp(ts,"m_m")==0);
  if(ts) delete(ts);
  delete(bp);
}

void test_regex()
{
  yaooc_base_parser_pointer bp=new(yaooc_base_parser);
  const char* str="yaooc_test  test_yaooc";
  char* ts;
  M(bp,set_parse_string,str);

  yaooc_terminal_t r;
  M(bp,regex,"yaooc.*\\s",0,0,&r);
  TEST("Match found",r.end_!=NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Matched text is",strcmp(ts,"yaooc_test"));
  if(ts) delete(ts);
  TEST("Offset is 12",bp->current_pos_-str==12);
  M(bp,regex,"yaooc.*\\s",0,0,&r);
  TEST("Match failed",r.end_==NULL);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Matched text is NULL",ts==NULL);
  TEST("Offset is 12",bp->current_pos_-str==12);
  delete(bp);
}

void test_qouted_string()
{
  yaooc_base_parser_pointer bp=new(yaooc_base_parser);
  const char* str="\"quoted string\"   \"This is \\a \\b \\f \\r \\n \\t \\v \\\"inside\\\" \\\\ \\t test\"   \"Start but no end";
//  const char* str="\"quoted string\"   \"This is \\\"inside\\\"\"  \"Start but no end";
  char* ts;
  M(bp,set_parse_string,str);
//  puts(str);
  yaooc_terminal_t r;
  M(bp,double_quoted_string,&r);
  TEST("Found valid quoted string",r.end_!=NULL);
  ts=yaooc_terminal_text(&r);
//  printf("%zu X%sX\n",strlen(ts),ts);
  TEST("Match string is \"quoted string\"",strcmp(ts,"quoted string")==0);
  TEST("Offset is 18",bp->current_pos_-str==18);
  if(ts) delete(ts);
  M(bp,double_quoted_string,&r);
  TEST("Found valid quoted string",r.end_!=NULL);
//  printf("%zu X%sX\n",strlen(ts),ts);
  ts=yaooc_terminal_text(&r);
//  printf("%zu Y%sY\n",strlen(ts),ts);
  char *ns="This is \a \b \f \r \n \t \v \"inside\" \\ \t test";
//  printf("%zu Z%sZ\n",strlen(ns),ns);
  TEST("Match string is \"quoted string\"",strcmp(ts,ns)==0);
/*  puts(ts);
  puts(ns);*/
  TEST("Offset is 73",bp->current_pos_-str==73);
  if(ts) delete(ts);
  M(bp,double_quoted_string,&r);
  TEST("No quoted string found",r.end_==NULL);
  TEST("Offset is 73",bp->current_pos_-str==73);
  delete(bp);
}

void test_string_until_chrs()
{
  const char* str="abcdefghijklmnopqrstuvwxyz5173904268";
  yaooc_base_parser_pointer bp=new(yaooc_base_parser);
  M(bp,set_parse_string,str);
  yaooc_terminal_t r;
  M(bp,string_until_chrs,"0123456789",&r);
  char* ts=yaooc_terminal_raw_text(&r);
  TEST("Matched alpha string",strcmp(ts,"abcdefghijklmnopqrstuvwxyz")==0);
  if(ts)
    delete(ts);
  M(bp,string_until_chrs,"0123456789",&r);
  TEST("Matched no characters",r.end_==NULL);
	delete(bp);
}

void test_string_while_chrs()
{
  const char* str="abcdefghijklmnopqrstuvwxyz5173904268";
  yaooc_base_parser_pointer bp=new(yaooc_base_parser);
  M(bp,set_parse_string,str);
  yaooc_terminal_t r;
  M(bp,string_while_chrs,"prwanzbkjtxmohygdcqufvslie",&r);
  char* ts=yaooc_terminal_raw_text(&r);
  TEST("Matched alpha string",strcmp(ts,"abcdefghijklmnopqrstuvwxyz")==0);
  if(ts)
    delete(ts);
  M(bp,string_while_chrs,"prwanzbkjtxmohygdcqufvslie",&r);
  TEST("Matched no characters",r.end_==NULL);
  delete(bp);
}

void test_string_until_matching_chr()
{
  yaooc_base_parser_pointer bp=new(yaooc_base_parser);
  const char* str="( parens ) {  { (within braces) } }   [ { [ inside square brackets ] }  ] [  [ unmatched ] ";
  yaooc_terminal_t r;
  char* ts;
  M(bp,set_parse_string,str);
  TEST("Found open paren",M(bp,chr,'(',&r));
  TEST("Offset is 2",bp->current_pos_-str==2);
  M(bp,string_until_matching_chr,'(',')',&r);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is \"parens \"",strcmp(ts,"parens ")==0);
  puts(ts);
  if(ts) delete(ts);
  TEST("Offset is 11",bp->current_pos_-str==11);
  TEST("Found open bracket",M(bp,chr,'{',&r));
  M(bp,string_until_matching_chr,'{','}',&r);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is \"{ (within braces) } \"",strcmp(ts,"{ (within braces) } ")==0);
  if(ts) delete(ts);
  TEST("Offset is 38",bp->current_pos_-str==38);
  TEST("Found open bracket",M(bp,chr,'[',&r));
  M(bp,string_until_matching_chr,'[',']',&r);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is \"{ [ inside square brackets ] }  \"",strcmp(ts,"{ [ inside square brackets ] }  ")==0);
  if(ts) delete(ts);
  TEST("Offset is 74",bp->current_pos_-str==74);
  TEST("Found open bracket",M(bp,chr,'[',&r));
  M(bp,string_until_matching_chr,'[',']',&r);
  ts=yaooc_terminal_raw_text(&r);
  TEST("Captured string is NULL",ts==NULL);
  if(ts) delete(ts);
  delete(bp);
}

test_function tests[] =
{
  test_parser_position,
  test_whitespace,
  test_chr,
  test_str,
  test_integer,
  test_hexinteger,
  test_real,
  test_ident,
  test_regex,
  test_qouted_string,
  test_string_until_chrs,
  test_string_while_chrs,
  test_string_until_matching_chr
};

STD_MAIN(tests)
