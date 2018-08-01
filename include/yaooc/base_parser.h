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

#ifndef __BASE_PARSER_INCLUDED__
#define __BASE_PARSER_INCLUDED__

#include <yaooc/object.h>
#include <yaooc/stack.h>

typedef struct {
  const char* pos_;
  size_t line_no_;
} parser_position_t;

STACK_DEFINITION(parser_position,parser_position_stack)
yaooc_class_table(yaooc_terminal)
{
  char* (*get_text)(const_pointer);
  char* (*get_raw_text)(const_pointer);
};

yaooc_class_instance(yaooc_terminal)
{
  const char* beg_;
  const char* end_;
};

yaooc_class(yaooc_terminal);
void yaooc_terminal_default_ctor(pointer);
char* yaooc_terminal_get_text(const_pointer);
char* yaooc_terminal_get_raw_text(const_pointer);
#define default_terminal { .class_table_ = &yaooc_terminal_class_table , .beg_=this->current_pos_, .end_=NULL }

typedef enum { CRLF=1,C_COMMENT=2,CPP_COMMENT=4,SHELL_COMMENT=8,CUSTOM_WHITESPACE=16} yaooc_base_parser_whitespace_t;
typedef enum { PARSE_SUCCESS = 0, PARSE_FAILED } yaooc_base_parser_result_t;
/*  Begin YAOOC PreProcessor generated content */


/*
  Class definition for yaooc_base_parser
*/
yaooc_class_table(yaooc_base_parser)
{
  yaooc_object_class_table_t;
  void (*set_parse_string)(pointer,const char*);
  void (*rule_start)(pointer);
  void (*rule_success)(pointer);
  void (*rule_fail)(pointer);
  yaooc_terminal_t (*eos)(pointer);
  yaooc_terminal_t (*string_until_chrs)(pointer,const char*);
  yaooc_terminal_t (*string_while_chrs)(pointer,const char*);
//  yaooc_terminal_t (*string_until_chr)(pointer,char);
  yaooc_terminal_t (*string_until_eol)(pointer);
  yaooc_terminal_t (*shell_comment)(pointer);
  yaooc_terminal_t (*c_comment)(pointer);
  yaooc_terminal_t (*cpp_comment)(pointer);
  yaooc_terminal_t (*custom_whitespace)(pointer);
  void (*set_whitespace_types)(pointer,yaooc_base_parser_whitespace_t);
  yaooc_base_parser_whitespace_t (*get_whitespace_types)(pointer);
  int (*whitespace)(pointer);
  yaooc_terminal_t (*chr)(pointer,char);
  int (*chr_choices)(pointer,const char*);
  yaooc_terminal_t (*str)(pointer,const char*);
  int (*str_choices)(pointer,...);
  yaooc_terminal_t (*digits)(pointer);
  yaooc_terminal_t (*hexdigits)(pointer);
  yaooc_terminal_t (*integer)(pointer);
  yaooc_terminal_t (*hexinteger)(pointer);
  yaooc_terminal_t (*real)(pointer);
  yaooc_terminal_t (*ident)(pointer);
  yaooc_terminal_t (*regex)(pointer,const char*,uint32_t,uint32_t);
  yaooc_terminal_t (*quoted_string)(pointer,char);
  yaooc_terminal_t (*single_quoted_string)(pointer);
  yaooc_terminal_t (*double_quoted_string)(pointer);
  yaooc_terminal_t (*bare_string)(pointer);
  yaooc_terminal_t (*string_until_matching_chr)(pointer,char,char);
  yaooc_base_parser_result_t (*result)(const_pointer);
};

yaooc_class_instance(yaooc_base_parser)
{
  yaooc_object_class_instance_t;
  const char* string_to_parse_;
  const char* current_pos_;
  parser_position_stack_t* stack_;
  unsigned int line_no_;
  unsigned int whitespace_types_;
  yaooc_base_parser_result_t result_;
};

yaooc_class(yaooc_base_parser);
/* Prototypes for yaooc_base_parser type info */
void yaooc_base_parser_default_ctor(pointer);
void yaooc_base_parser_dtor(pointer);
void yaooc_base_parser_copy_ctor(pointer,const_pointer);
void yaooc_base_parser_assign(pointer,const_pointer);

/* Constructors for yaooc_base_parser */

/* Prototypes for yaooc_base_parser class table*/
const char* yaooc_base_parser_isa(const_pointer);
#define yaooc_base_parser_is_descendant yaooc_object_is_descendant
void yaooc_base_parser_swap(pointer,pointer);
void yaooc_base_parser_set_parse_string(pointer,const char*);
void yaooc_base_parser_rule_start(pointer);
void yaooc_base_parser_rule_success(pointer);
void yaooc_base_parser_rule_fail(pointer);
yaooc_terminal_t yaooc_base_parser_eos(pointer);
yaooc_terminal_t yaooc_base_parser_string_until_chrs(pointer,const char*);
yaooc_terminal_t yaooc_base_parser_string_while_chrs(pointer,const char*);
yaooc_terminal_t yaooc_base_parser_string_until_eol(pointer);
yaooc_terminal_t yaooc_base_parser_shell_comment(pointer);
yaooc_terminal_t yaooc_base_parser_c_comment(pointer);
yaooc_terminal_t yaooc_base_parser_cpp_comment(pointer);
yaooc_terminal_t yaooc_base_parser_custom_whitespace(pointer);
void yaooc_base_parser_set_whitespace_types(pointer,uint32_t);
uint32_t yaooc_base_parser_get_whitespace_types(pointer);
int yaooc_base_parser_whitespace(pointer);
yaooc_terminal_t yaooc_base_parser_chr(pointer,char);
int yaooc_base_parser_chr_choices(pointer,const char*);
yaooc_terminal_t yaooc_base_parser_str(pointer,const char*);
int yaooc_base_parser_str_choices(pointer,...);
yaooc_terminal_t yaooc_base_parser_digits(pointer);
yaooc_terminal_t yaooc_base_parser_hexdigits(pointer);
yaooc_terminal_t yaooc_base_parser_integer(pointer);
yaooc_terminal_t yaooc_base_parser_hexinteger(pointer);
yaooc_terminal_t yaooc_base_parser_real(pointer);
yaooc_terminal_t yaooc_base_parser_ident(pointer);
yaooc_terminal_t yaooc_base_parser_regex(pointer,const char*,uint32_t,uint32_t);
yaooc_terminal_t yaooc_base_parser_quoted_string(pointer,char);
yaooc_terminal_t yaooc_base_parser_single_quoted_string(pointer);
yaooc_terminal_t yaooc_base_parser_double_quoted_string(pointer);
yaooc_terminal_t yaooc_base_parser_bare_string(pointer);
yaooc_terminal_t yaooc_base_parser_string_until_matching_chr(pointer,char,char);
yaooc_base_parser_result_t yaooc_base_parser_result(const_pointer);

/* Prototypes for yaooc_base_parser class instance*/

/* Prototypes for yaooc_base_parser class protected items*/

/*  End YAOOC PreProcessor generated content */

#endif
